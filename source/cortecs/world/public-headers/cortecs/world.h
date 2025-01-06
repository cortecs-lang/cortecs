#ifndef CORTECS_WORLD_WORLD_H
#define CORTECS_WORLD_WORLD_H

#include <flecs.h>

#ifdef __cplusplus
extern "C" {
#endif

extern ecs_world_t *world;

void cortecs_world_init(void);
void cortecs_world_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif
