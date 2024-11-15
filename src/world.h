#ifndef _SRC_WORLD_H_
#define _SRC_WORLD_H_

#include <dolphin/types.h>
#include <dolphin/mtx.h>

enum
{
    WORLD_STATE_INPUT_INIT = 1,
    WORLD_STATE_INPUT_MAIN = 2,
};

struct World
{
    s16 xrot;
    s16 zrot;
    s16 xrotPrev;
    s16 zrotPrev;
    s8 state;
    s8 playerId;
    u8 fillerA[0xC-0xA];
    float maxTilt;  // maximum tilt angle (in degrees)
    Vec gravityDir;
    float unk1C;
    s16 unk20;
    u8 filler22[0x40-0x22];
};  // size = 0x40

extern struct World *currentWorld;
extern struct World worldInfo[];
extern Vec g_gravityDir;

#define WORLD_FOREACH(code) \
    { \
        struct World *world = worldInfo; \
        s8 *status = g_poolInfo.playerPool.statusList; \
        int i_; \
        for (i_ = 0; i_ < g_poolInfo.playerPool.count; i_++, world++, status++) \
        { \
            if (*status == STAT_NORMAL) \
                { code } \
        } \
    }

void ev_world_init(void);
void ev_world_main(void);
void ev_world_dest(void);
void world_clear(struct World *);
void world_sub_input_init(struct World *);
void world_sub_input_main(struct World *);
void world_sub_6(struct World *);
void world_sub_7(struct World *);
void world_sub_8(struct World *);
void world_sub_9(struct World *);
void world_sub_10(struct World *);
void world_sub_11(struct World *);

#endif
