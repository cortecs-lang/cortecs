#include <cortecs/finalizer.h>
#include <cortecs/gc.h>
#include <cortecs/world.h>
#include <gtest/gtest.h>

class GcNoLogFixture : public ::testing::Test {
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

typedef struct {
    uint32_t the_data[5];
} some_data;
cortecs_finalizer_declare(some_data);
#define TYPE_PARAM_T some_data
#include <cortecs/array.template.h>
#undef TYPE_PARAM_T

TEST_F(GcNoLogFixture, TestCollectUnusedAllocation) {
    ecs_defer_begin(world);
    void *allocation = cortecs_gc_alloc(some_data);
    ASSERT_NE(allocation, nullptr);
    ecs_defer_end(world);
}
