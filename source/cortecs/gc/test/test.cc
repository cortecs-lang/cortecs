#include <cortecs/finalizer.h>
#include <cortecs/gc.h>
#include <cortecs/log.h>
#include <cortecs/world.h>
#include <gtest/gtest.h>

class GcBaseFixture : public ::testing::Test {
   protected:
    void SetUp() override {
        cortecs_world_init();
        cortecs_finalizer_init();
        cortecs_gc_init(NULL);
    }

    void TearDown() override {
        cortecs_world_cleanup();
    }
};

TEST_F(GcBaseFixture, TestIncDecNull) {
    cortecs_gc_inc(nullptr);
    cortecs_gc_dec(nullptr);
}

typedef struct {
    uint32_t the_data[5];
} some_data;
cortecs_finalizer_declare(some_data);
#define TYPE_PARAM_T some_data
#include <cortecs/array.template.h>
#undef TYPE_PARAM_T

TEST_F(GcBaseFixture, TestCollectUnusedAllocation) {
    ecs_defer_begin(world);
    void *allocation = cortecs_gc_alloc(some_data);
    ASSERT_NE(allocation, nullptr);
    ecs_defer_end(world);

    ASSERT_FALSE(cortecs_gc_is_alive(allocation));
}

TEST_F(GcBaseFixture, TestCollectUnusedAllocationArray) {
    const uint32_t size_of_array = 4;
    ecs_defer_begin(world);
    CN(Cortecs, Array, CT(some_data)) allocation = cortecs_gc_alloc_array(some_data, size_of_array);
    ASSERT_NE(allocation, nullptr);

    ASSERT_EQ(size_of_array, allocation->size);
    ecs_defer_end(world);

    ASSERT_FALSE(cortecs_gc_is_alive(allocation));
}

TEST_F(GcBaseFixture, TestKeepUsedAllocation) {
    ecs_defer_begin(world);
    some_data *allocation = cortecs_gc_alloc(some_data);
    cortecs_gc_inc(allocation);
    ecs_defer_end(world);

    ASSERT_TRUE(cortecs_gc_is_alive(allocation));
}

TEST_F(GcBaseFixture, TestKeepUsedAllocationArray) {
    const uint32_t size_of_array = 4;
    ecs_defer_begin(world);
    CN(Cortecs, Array, CT(some_data)) allocation = cortecs_gc_alloc_array(some_data, size_of_array);
    cortecs_gc_inc(allocation);
    ecs_defer_end(world);

    ASSERT_TRUE(cortecs_gc_is_alive(allocation));
}

TEST_F(GcBaseFixture, TestKeepThenCollect) {
    ecs_defer_begin(world);
    some_data *allocation = cortecs_gc_alloc(some_data);
    cortecs_gc_inc(allocation);
    ecs_defer_end(world);

    ASSERT_TRUE(cortecs_gc_is_alive(allocation));

    ecs_defer_begin(world);
    cortecs_gc_dec(allocation);
    ecs_defer_end(world);

    ASSERT_FALSE(cortecs_gc_is_alive(allocation));
}

TEST_F(GcBaseFixture, TestKeepThenCollectArray) {
    const uint32_t size_of_array = 4;
    ecs_defer_begin(world);
    CN(Cortecs, Array, CT(some_data)) allocation = cortecs_gc_alloc_array(some_data, size_of_array);
    cortecs_gc_inc(allocation);
    ecs_defer_end(world);

    ASSERT_TRUE(cortecs_gc_is_alive(allocation));

    ecs_defer_begin(world);
    cortecs_gc_dec(allocation);
    ecs_defer_end(world);

    ASSERT_FALSE(cortecs_gc_is_alive(allocation));
}

TEST_F(GcBaseFixture, TestAllocateSizes) {
    for (uint32_t size = 32; size < 1024; size += 32) {
        ecs_defer_begin(world);
        void *allocation = cortecs_gc_alloc_impl(
            size,
            CORTECS_FINALIZER_NONE,
            __FILE__,
            __func__,
            __LINE__
        );
        ASSERT_NE(allocation, nullptr);
        ecs_defer_end(world);
    }
}

TEST_F(GcBaseFixture, TestAllocateSizesArray) {
    for (uint32_t size_of_elements = 32; size_of_elements < 512; size_of_elements += 32) {
        for (uint32_t size_of_array = 1; size_of_array < 128; size_of_array++) {
            ecs_defer_begin(world);
            uint32_t *array = (uint32_t *)cortecs_gc_alloc_array_impl(
                size_of_elements,
                size_of_array,
                8,
                CORTECS_FINALIZER_NONE,
                __FILE__,
                __func__,
                __LINE__
            );
            ASSERT_NE(array, nullptr);
            ASSERT_EQ(size_of_array, *array);
            ecs_defer_end(world);
        }
    }
}

typedef struct {
    uint32_t some_data[5];
} noop_data;
cortecs_finalizer_declare(noop_data);
#define TYPE_PARAM_T noop_data
#include <cortecs/array.template.h>
#undef TYPE_PARAM_T

static uint32_t noop_finalizer_called = 0;
void cortecs_finalizer(noop_data)(void *allocation) {
    UNUSED(allocation);
    noop_finalizer_called += 1;
}

class GcNoopFinalizerFixture : public GcBaseFixture {
   protected:
    void SetUp() override {
        GcBaseFixture::SetUp();
        cortecs_finalizer_register(noop_data);
    }

    void TearDown() override {
        GcBaseFixture::TearDown();
    }
};

TEST_F(GcNoopFinalizerFixture, TestNoopFinalizer) {
    noop_finalizer_called = 0;
    ecs_defer_begin(world);
    cortecs_gc_alloc(noop_data);
    ecs_defer_end(world);

    ASSERT_EQ(noop_finalizer_called, 1);
}

TEST_F(GcNoopFinalizerFixture, TestNoopFinalizerArray) {
    for (uint32_t size_of_array = 1; size_of_array < 128; size_of_array++) {
        noop_finalizer_called = 0;
        ecs_defer_begin(world);
        cortecs_gc_alloc_array(noop_data, size_of_array);
        ecs_defer_end(world);

        ASSERT_EQ(size_of_array, noop_finalizer_called);
    }
}

typedef struct {
    void *target;
} single_target;
cortecs_finalizer_define(single_target);

#define TYPE_PARAM_T single_target
#include <cortecs/array.template.h>
#undef TYPE_PARAM_T

void cortecs_finalizer(single_target)(void *allocation) {
    single_target *data = (single_target *)allocation;
    if (data->target != nullptr) {
        cortecs_gc_dec(data->target);
    }
}

class GcSingleTargetFinalizerFixture : public GcBaseFixture {
   protected:
    void SetUp() override {
        GcBaseFixture::SetUp();
        cortecs_finalizer_register(single_target);
    }

    void TearDown() override {
        GcBaseFixture::TearDown();
    }
};

TEST_F(GcSingleTargetFinalizerFixture, TestRecursiveCollect) {
    ecs_defer_begin(world);

    single_target *data = cortecs_gc_alloc(single_target);
    some_data *target = cortecs_gc_alloc(some_data);
    cortecs_gc_inc(target);
    data->target = target;

    ecs_defer_end(world);

    ASSERT_FALSE(cortecs_gc_is_alive(data));
    ASSERT_FALSE(cortecs_gc_is_alive(target));
}

TEST_F(GcSingleTargetFinalizerFixture, TestRecursiveCollectArray) {
    some_data *targets[512];

    ecs_defer_begin(world);

    CN(Cortecs, Array, CT(single_target)) data = cortecs_gc_alloc_array(single_target, 512);
    for (int i = 0; i < 512; i++) {
        targets[i] = cortecs_gc_alloc(some_data);
        cortecs_gc_inc(targets[i]);
        data->elements[i].target = targets[i];
    }

    ecs_defer_end(world);

    ASSERT_FALSE(cortecs_gc_is_alive(data));
    for (int i = 0; i < 512; i++) {
        ASSERT_FALSE(cortecs_gc_is_alive(targets[i]));
    }
}

class GcRecursiveCollectFixture : public GcBaseFixture {
   protected:
    void SetUp() override {
        GcBaseFixture::SetUp();
        cortecs_finalizer_register(single_target);
    }

    void TearDown() override {
        GcBaseFixture::TearDown();
    }
};

TEST_F(GcRecursiveCollectFixture, TestNRecursiveCollect) {
    ecs_defer_begin(world);
    single_target *targets[512];

    targets[0] = cortecs_gc_alloc(single_target);
    targets[0]->target = NULL;
    for (int i = 1; i < 512; i++) {
        targets[i] = cortecs_gc_alloc(single_target);
        cortecs_gc_inc(targets[i - 1]);
        targets[i]->target = targets[i - 1];
    }

    ecs_defer_end(world);

    for (int i = 1; i < 512; i++) {
        ASSERT_FALSE(cortecs_gc_is_alive(targets[i]));
    }
}

class GcLogFixture : public ::testing::Test {
   protected:
    const char *log_path = "./test_gc_log_open_close.log";
    void SetUp() override {
        cortecs_world_init();
        cortecs_finalizer_init();
        CN(Cortecs, Log, init)();
        cortecs_gc_init(log_path);
    }

    void TearDown() override {
        cortecs_world_cleanup();
        remove(log_path);
    }
};

TEST_F(GcLogFixture, TestGcLogOpenClose) {
    cortecs_gc_cleanup();

    FILE *log = fopen(log_path, "r");
    char line[2048];
    while (fgets(line, sizeof(line), log) != nullptr) {
        printf("%s", line);
    }
    fclose(log);
}
