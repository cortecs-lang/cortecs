#include <cortecs/gc.h>
#include <cortecs/string.h>
#include <cortecs/world.h>
#include <gtest/gtest.h>

class StringBaseFixture : public ::testing::Test {
   protected:
    void SetUp() override {
        cortecs_world_init();
        cortecs_finalizer_init();
        cortecs_gc_init(NULL);
        ecs_defer_begin(world);
    }

    void TearDown() override {
        ecs_defer_end(world);
        cortecs_world_cleanup();
    }
};

TEST_F(StringBaseFixture, TestNewString) {
    auto run_test_new_string = [](const char *target) {
        uint32_t target_length = strlen(target) + 1;
        CN(Cortecs, String) out = CN(Cortecs, String, new)("%s", target);

        ASSERT_NE(nullptr, out.content);
        ASSERT_EQ(target_length, CN(Cortecs, String, capacity)(out));
        ASSERT_EQ(0, memcmp(target, out.content->elements, target_length));
    };

    run_test_new_string("");
    run_test_new_string("hello world");
}

TEST_F(StringBaseFixture, TestStringEquals) {
    auto run_test_equality = [](const char *left, const char *right, bool areEqual) {
        CN(Cortecs, String) left_str = CN(Cortecs, String, new)("%s", left);
        CN(Cortecs, String) right_str = CN(Cortecs, String, new)("%s", right);

        ASSERT_EQ(areEqual, CN(Cortecs, String, equals)(left_str, right_str));
    };

    run_test_equality("", "", true);
    run_test_equality("foo", "foo", true);
    run_test_equality("", "foo", false);
    run_test_equality("foobar", "baz", false);
    run_test_equality("foo", "bar", false);
    run_test_equality("foo", "foobar", false);
}
