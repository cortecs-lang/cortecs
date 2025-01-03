#include <cortecs/world.h>

ecs_world_t *world;

void cortecs_world_init(void) {
    world = ecs_init();
}

void cortecs_world_cleanup(void) {
    ecs_fini(world);
}
