#include <cortecs/gc.h>
#include <cortecs/log.h>
#include <cortecs/string.h>
#include <cortecs/world.h>
#include <gtest/gtest.h>

class LogBaseFixture : public ::testing::Test {
   protected:
    void SetUp() override {
        cortecs_world_init();
        cortecs_finalizer_init();
        CN(Cortecs, Log, init)();
        cortecs_gc_init(NULL);
    }

    void TearDown() override {
        cortecs_world_cleanup();
    }
};

TEST_F(LogBaseFixture, TestOpenLog) {
    ecs_defer_begin(world);

    CN(Cortecs, String) path = CN(Cortecs, String, new)("./test_open_log.log");
    CN(Cortecs, Log, open)(path);

    ecs_defer_end(world);

    struct stat buffer;
    ASSERT_EQ(stat(path.content->elements, &buffer), 0);

    remove(path.content->elements);
}

TEST_F(LogBaseFixture, TestWriteOneMessage) {
    ecs_defer_begin(world);

    CN(Cortecs, String) path = CN(Cortecs, String, new)("./test_write_one_message.log");
    CN(Cortecs, Ptr, CT(CN(Cortecs, Log))) log_stream = CN(Cortecs, Log, open)(path);

    cJSON *hello_world = cJSON_CreateObject();
    cJSON_AddStringToObject(hello_world, "message", "hello world");
    CN(Cortecs, Log, write)(log_stream, hello_world);
    cJSON_Delete(hello_world);

    ecs_defer_end(world);

    FILE *file = fopen(path.content->elements, "r");
    ASSERT_NE(file, nullptr);

    char line[1024];
    fgets(line, sizeof(line), file);
    fclose(file);

    cJSON *json = cJSON_Parse(line);
    ASSERT_NE(json, nullptr);

    cJSON *message = cJSON_GetObjectItem(json, "message");
    ASSERT_NE(message, nullptr);
    ASSERT_STREQ("hello world", message->valuestring);

    cJSON_Delete(json);
    remove(path.content->elements);
}

TEST_F(LogBaseFixture, TestWriteTwoMessages) {
    ecs_defer_begin(world);

    CN(Cortecs, String) path = CN(Cortecs, String, new)("./test_write_two_messages.log");
    CN(Cortecs, Ptr, CT(CN(Cortecs, Log))) log_stream = CN(Cortecs, Log, open)(path);

    cJSON *hello_world = cJSON_CreateObject();
    cJSON_AddStringToObject(hello_world, "message", "hello world");
    CN(Cortecs, Log, write)(log_stream, hello_world);
    cJSON_Delete(hello_world);

    cJSON *hi_there = cJSON_CreateObject();
    cJSON_AddStringToObject(hi_there, "message", "hi there");
    CN(Cortecs, Log, write)(log_stream, hi_there);
    cJSON_Delete(hi_there);

    ecs_defer_end(world);

    FILE *file = fopen(path.content->elements, "r");
    ASSERT_NE(file, nullptr);

    char line[1024];

    fgets(line, sizeof(line), file);
    cJSON *hello_world_out = cJSON_Parse(line);
    ASSERT_NE(hello_world_out, nullptr);
    cJSON *hello_world_message = cJSON_GetObjectItem(hello_world_out, "message");
    ASSERT_NE(hello_world_message, nullptr);
    ASSERT_STREQ("hello world", hello_world_message->valuestring);
    cJSON_Delete(hello_world_out);

    fgets(line, sizeof(line), file);
    cJSON *hi_there_out = cJSON_Parse(line);
    ASSERT_NE(hi_there_out, nullptr);
    cJSON *hi_there_message = cJSON_GetObjectItem(hi_there_out, "message");
    ASSERT_NE(hi_there_message, nullptr);
    ASSERT_STREQ("hi there", hi_there_message->valuestring);
    cJSON_Delete(hi_there_out);

    fclose(file);
    remove(path.content->elements);
}
