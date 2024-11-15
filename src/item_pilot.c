/**
 * item_pilot.c - Item behavior of collectable bananas in Monkey Target
 */
#include <stdlib.h>
#include <string.h>
#include <dolphin.h>

#include "global.h"
#include "avdisp.h"
#include "ball.h"
#include "effect.h"
#include "gxutil.h"
#include "info.h"
#include "item.h"
#include "mathutil.h"
#include "mode.h"
#include "polydisp.h"
#include "sound.h"
#include "stage.h"
#include "stcoli.h"
#include "vibration.h"
#include "window.h"

#include "../data/common.gma.h"

struct ModelLOD lbl_801BDF60[] =
{
    { OBJ_BANANA_01_LOD150, 150 },
    { OBJ_BANANA_01_LOD100, 100 },
    { OBJ_BANANA_01_LOD50,   50 },
    { OBJ_BANANA_01_LOD0,     0 },
    { -1, 0 },
};

struct ModelLOD lbl_801BDF88[] =
{
    { OBJ_BANANA_02_LOD100, 100 },
    { OBJ_BANANA_02_LOD0,     0 },
    { -1, 0 },
};

struct Struct801BDFA0
{
    struct ModelLOD **lodModelsPtr;
    s16 unk4;
    float radius;  // collision radius
    s16 unkC;
    s16 unkE;
    s16 xrotSpeed;
    s16 yrotSpeed;
    s16 zrotSpeed;
};

struct ModelLOD *lbl_802F0B38 = lbl_801BDF60;
struct ModelLOD *lbl_802F0B3C = lbl_801BDF88;

struct Struct801BDFA0 pilotBananaInfo[] =
{
    { &lbl_802F0B38, -1,  0.5, 1, 10, 0, 768, 0 },
    { &lbl_802F0B38, -1,  0.5, 1, 10, 0, 768, 0 },
    { &lbl_802F0B3C, -1, 0.75, 1, 20, 0, 768, 0 },
    { NULL,          37,    1, 1, 20, 0,   0, 0 },
    { NULL,          77,    5, 1, 20, 0, 128, 0 },
};

s16 lbl_802F1FF6;
s16 lbl_802F1FF4;
s32 lbl_802F1FF0;
s16 lbl_802F1FEC;
s16 lbl_802F1FE4[4];
s16 lbl_802F1FE0;
float lbl_802F1FDC;
float lbl_802F1FD8;
void (*lbl_802F1FD4)(void);
u32 lbl_802F1FD0;

static u32 lbl_80285A58[4];

u8 lbl_80285A80[0x30];
u8 lbl_80285A68[0x18];

void item_pilot_init(struct Item *item)
{
    struct Struct801BDFA0 *r6;

    item->unk12 = -1;
    item->state = 1;
    if (item->subType < 3)
        item->modelLODs = pilotBananaInfo[item->subType].lodModelsPtr;
    else
        item->modelLODs = minigameGma->modelEntries[pilotBananaInfo[item->subType].unk4].model;
    item->flags = ITEM_FLAG_TANGIBLE|ITEM_FLAG_5;
    item->radius = pilotBananaInfo[item->subType].radius;
    item->unk18 = 0.25f;
    item->rotVelX = pilotBananaInfo[item->subType].xrotSpeed;
    item->rotVelY = pilotBananaInfo[item->subType].yrotSpeed;
    item->rotVelZ = pilotBananaInfo[item->subType].zrotSpeed;
    item->shadowModel = commonGma->modelEntries[polyshadow01].model;
    item->shadowColor.r = 0x46;
    item->shadowColor.g = 0x47;
    item->shadowColor.b = 0x5F;
    item->unk7C.x = item->radius;
    item->unk7C.y = item->radius * 0.8f;
    item->unk7C.z = item->radius;
}

void item_pilot_main(struct Item *item)
{
    struct Ball *r29;
    float f31;

    r29 = currentBall;
    if (item->unk64 != 0)
        f31 = item->pos.y + item->unk74;
    else
        f31 = -100.0f;
    if (item->state == 0)
        return;
    switch (item->state)
    {
    case 1:
        item->state = 2;
        // fall through
    case 2:
        if (item->subType == 3 || item->subType == 1)
        {
            item->vel.y -= 0.008;
            if (item->pos.y < -1.0)
                item->state = 6;
        }
        else if (item->subType == 4)
        {
            Vec sp24;

            sp24.x = r29->pos.x - item->pos.x;
            sp24.y = r29->pos.y - item->pos.y;
            sp24.z = r29->pos.z - item->pos.z;
            if (mathutil_vec_len(&sp24) < 60.0 && mathutil_vec_dot_prod(&r29->vel, &sp24) < 0.0)
            {
                Vec sp18;

                sp18.x = r29->vel.x * 60.0;
                sp18.y = r29->vel.y * 60.0;
                sp18.z = r29->vel.z * 60.0;
                sp24.x += sp18.x;
                sp24.y += sp18.y;
                sp24.z += sp18.z;
                mathutil_vec_normalize_len(&sp24);
                sp24.x = 0.005 * sp24.x;
                sp24.y = 0.005 * sp24.y;
                sp24.z = 0.005 * sp24.z;
                if (item->pos.y < 30.0 && item->vel.y < 0.0)
                {
                    sp24.y = 0.0f;
                    item->vel.y *= 0.9;
                }
                item->vel.x += sp24.x;
                item->vel.y += sp24.y;
                item->vel.z += sp24.z;
                if (mathutil_vec_len(&item->vel) > 0.064814814814814811)
                {
                    mathutil_vec_normalize_len(&item->vel);
                    item->vel.x = 0.064814814814814811 * item->vel.x;
                    item->vel.y = 0.064814814814814811 * item->vel.y;
                    item->vel.z = 0.064814814814814811 * item->vel.z;
                }
            }
            else
            {
                item->vel.x = 0.9 * item->vel.x;
                item->vel.y = 0.9 * item->vel.y;
                item->vel.z = 0.9 * item->vel.z;
            }
        }
        break;
    case 3:
        item->state = 4;
        // fall through
    case 4:
        item->state = 5;
        item->unk10 = 15;
        // fall through
    case 5:
        item->unk10--;
        if (item->unk10 < 0)
            item->state = 6;
        break;
    case 6:
        item->radius -= 0.033333333333333333;
        if (item->radius < 1.1920928955078125e-07f)
        {
            item->state = 0;
            item->flags |= ITEM_FLAG_INVISIBLE;
            item->radius = 1.1920928955078125e-07f;
        }
        break;
    }

    item->prevPos = item->pos;

    item->prevRotX = item->rotX;
    item->prevRotY = item->rotY;
    item->prevRotZ = item->rotZ;

    item->pos.x += item->vel.x;
    item->pos.y += item->vel.y;
    item->pos.z += item->vel.z;

    item->rotX += item->rotVelX;
    item->rotY += item->rotVelY;
    item->rotZ += item->rotVelZ;

    if (item->animGroupId == 0)
        set_ball_look_point(2, &item->pos, 1.0f);
    else
    {
        Vec spC;

        mathutil_mtxA_from_mtx(animGroups[item->animGroupId].transform);
        mathutil_mtxA_tf_point(&item->pos, &spC);
        set_ball_look_point(2, &spC, 1.0f);
    }
    if (item->pos.y - f31 < item->radius)
    {
        item->pos.y = f31 + item->radius;
        if (item->vel.y < 0.0f)
            item->vel.y *= -0.4f;
    }
    item->unk6C.z = -item->rotY;
    item->unk7C.x = item->radius;
    item->unk7C.y = item->radius * 0.7f;
}

void item_pilot_draw(struct Item *item)
{
    float scale;
    float f30;
    struct GMAModel *model;
    Vec spC;

    if (polyDisp.flags & (1 << 2))
        return;
    f30 = item->radius;
    mathutil_mtxA_from_mtxB();
    mathutil_mtxA_translate(&item->pos);
    mathutil_mtxA_sq_from_mtx(userWork->matrices[2]);
    mathutil_mtxA_rotate_y(item->rotY);
    mathutil_mtxA_rotate_x(item->rotX);
    mathutil_mtxA_rotate_z(item->rotZ);
    if (item->subType < 3)
        model = get_lod(item->modelLODs);
    else
        model = item->modelLODs;
    if (item->subType == 3)
        scale = 1.0f;
    else
        scale = (f30 / model->boundSphereRadius) * 1.5;
    if (test_scaled_sphere_in_frustum(&model->boundSphereCenter, model->boundSphereRadius, scale) == 0)
        return;
    if (lbl_802F1FF6 == 6
     && (item->subType == 4 || item->subType == 3))
    {
        float f1 = (lbl_802F1FF0 - 20.0) / 40.0;

        if (f1 > 1.0)
            f1 = 1.0f;
        if (f1 < 0.0)
            f1 = 0.0f;
        scale *= f1;
    }
    if (scale != 1.0)
        mathutil_mtxA_scale_xyz(scale, scale, scale);
    mathutil_mtxA_get_translate_alt(&spC);
    f30 = -((spC.z + f30 + 0.1f) / f30);
    if (f30 > 0.0f)
    {
        if ((item->subType == 4 && -spC.z > 270.0) || (item->subType == 3 && -spC.z > 200.0))
        {
            int r30_;

            if (item->subType == 4)
            {
                if (-spC.z < 450.0)
                    r30_ = 0x86;
                else
                {
                    mathutil_mtxA_sq_from_identity();
                    mathutil_mtxA_scale_xyz(scale, scale, scale);
                    r30_ = 0x87;
                }
            }
            else
            {
                mathutil_mtxA_sq_from_identity();
                mathutil_mtxA_scale_xyz(scale, scale, scale);
                r30_ = 0x85;
            }
            avdisp_set_bound_sphere_scale(scale);
            gxutil_load_pos_nrm_matrix(mathutilData->mtxA, 0);
            avdisp_draw_model_unculled_sort_translucent(minigameGma->modelEntries[r30_].model);
        }
        else
        {
            avdisp_set_bound_sphere_scale(scale);
            gxutil_load_pos_nrm_matrix(mathutilData->mtxA, 0);
            if (f30 < 1.0f)
            {
                if (f30 < 0.5)
                    f30 = 0.5f;
                avdisp_set_alpha(f30);
                avdisp_draw_model_unculled_sort_all(model);
            }
            else
                avdisp_draw_model_unculled_sort_none(model);
        }
        if (item->subType == 2)
        {
            float f1, f2, f3;

            switch ((globalAnimTimer / 10) & 3)
            {
            case 0:
                f1 = 1.0f;
                f2 = 1.0f;
                f3 = 1.0f;
                break;
            case 1:
                f1 = 0.0f;
                f2 = 0.0f;
                f3 = 1.0f;
                break;
            case 2:
                f1 = 1.0f;
                f2 = 1.0f;
                f3 = 0.0f;
                break;
            default:
                f1 = 1.0f;
                f2 = 0.0f;
                f3 = 0.0f;
                break;
            }
            f30 = 1.0 + (((globalAnimTimer + item->uid * 10) % 60) * 0.033333333333333333);
            avdisp_set_post_mult_color(f1, f2, f3, 1.0f);
            mathutil_mtxA_sq_from_identity();
            mathutil_mtxA_scale_s(f30);
            gxutil_load_pos_nrm_matrix(mathutilData->mtxA, 0);
            avdisp_draw_model_unculled_sort_translucent(minigameGma->modelEntries[0x77].model);
            avdisp_set_post_mult_color(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
}

void item_pilot_collect(struct Item *item, struct PhysicsBall *ball)
{
    item->flags &= ~ITEM_FLAG_TANGIBLE;
    item->state = 3;
    item->vel.y += item->radius * 0.1875;
    item->rotVelY <<= 2;
    item->vel.x += ball->vel.x * 0.25;
    item->vel.y += ball->vel.y * 0.25;
    item->vel.z += ball->vel.z * 0.25;
    if (item->subType == 0 || item->subType == 1 || item->subType == 2)
    {
        if (item->unk5E < 0
         && (!(infoWork.flags & INFO_FLAG_REPLAY) || (infoWork.flags & INFO_FLAG_11)))
        {
            struct Effect effect;

            item->unk5E = infoWork.timerCurr;
            lbl_80285A58[modeCtrl.currPlayer] += pilotBananaInfo[item->subType].unkE;
            if (lbl_802F1FD0 & (1 << 3))
            {
                if (++lbl_802F1FE4[modeCtrl.currPlayer] >= 6)
                    lbl_802F1FE4[modeCtrl.currPlayer] = 1;
            }
            item->state = 0;
            item->flags |= ITEM_FLAG_INVISIBLE;
            item->flags &= ~ITEM_FLAG_TANGIBLE;
            memset(&effect, 0, sizeof(effect));
            effect.type = ET_HOLDING_BANANA;
            effect.playerId = currentBall->playerId;
            mathutil_mtxA_from_mtx(animGroups[ball->animGroupId].transform);
            mathutil_mtxA_tf_point(&item->pos, &effect.pos);
            mathutil_mtxA_tf_vec(&item->vel, &effect.vel);
            effect.rotX = item->rotX;
            effect.rotY = item->rotY;
            effect.rotZ = item->rotZ;
            effect.model = get_lod(item->modelLODs);
            effect.scale.x = (item->radius / effect.model->boundSphereRadius) * 1.5;
            effect.scale.y = effect.scale.x;
            effect.scale.z = effect.scale.y;
            spawn_effect(&effect);
        }
    }
    else if (item->subType == 3)
    {
        struct Ball *r31 = currentBall;
        struct Effect effect;

        lbl_802F1FD0 |= 0x42;
        if (lbl_802F1FF6 == 14)
            lbl_802F1FF4 = 15;
        u_play_sound_0(0x10B);
        u_play_sound_0(0x1C);
        vibration_control(playerControllerIDs[r31->playerId], VIBRATION_STATE_1, 28);
        ball->vel.y += 0.92592592592592582;
        lbl_802F1FE0 = 0x78;
        lbl_802F1FD8 = 0.6f;
        memset(&effect, 0, sizeof(effect));
        effect.type = ET_PILOT_BOMB;
        effect.playerId = r31->playerId;
        effect.pos.x = r31->pos.x;
        effect.pos.y = r31->pos.y - 1.0;
        effect.pos.z = r31->pos.z;
        effect.scale = (Vec){3.5, 4.5, 3.5};
        spawn_effect(&effect);
    }
    else if (item->subType == 4)
    {
        struct Ball *r31 = currentBall;
        struct Effect effect;
        int i;

        lbl_802F1FD0 |= 0x82;
        u_play_sound_0(0x2F);
        u_play_sound_0(0x1C);
        if (lbl_802F1FF6 == 14)
            u_play_sound_0(0x16C);
        vibration_control(playerControllerIDs[r31->playerId], VIBRATION_STATE_1, 28);
        ball->vel.y += 0.1388888888888889;
        ball->vel.x += RAND_FLOAT() * 0.64814814814814814;
        ball->vel.z += RAND_FLOAT() * 0.64814814814814814;
        lbl_802F1FD8 = 0.6f;
        lbl_802F1FDC = 1.0f;
        memset(&effect, 0, sizeof(effect));
        effect.type = ET_COLISTAR_PARTICLE;
        effect.playerId = r31->playerId;
        effect.pos = r31->pos;
        for (i = 0; i < 30; i++)
        {
            effect.vel.x = ball->vel.x + (RAND_FLOAT() * 0.2 - 0.1);
            effect.vel.y = ball->vel.y + 0.1 + (RAND_FLOAT() * 0.2 - 0.1);
            effect.vel.z = ball->vel.z + (RAND_FLOAT() * 0.2 - 0.1);
            spawn_effect(&effect);
        }
    }
    if (gameSubmode == 2)
        return;
    if (item->subType == 2)
    {
        u_play_sound_0(0x39);
        if ((infoWork.flags & INFO_FLAG_11) || !(infoWork.flags & INFO_FLAG_REPLAY))
            u_play_sound_0(0x2820);
    }
    else if (item->subType == 0 || item->subType == 1)
    {
        u_play_sound_0(3);
        if ((infoWork.flags & INFO_FLAG_11) || !(infoWork.flags & INFO_FLAG_REPLAY))
            u_play_sound_0(0x281F);
    }
}

void item_pilot_destroy(struct Item *item) {}

void item_pilot_release(struct Item *item)
{
    if (item->state != 2)
    {
        item->pos = item->stageBanana->pos;
        item->vel.x = 0.0f;
        item->vel.y = 0.0f;
        item->vel.z = 0.0f;
        item_pilot_init(item);
    }
}

char lbl_801BE018[] =
{
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x0A,
    0x00
};

void item_pilot_debug(struct Item *item)
{
    window_printf(2, lbl_801BE018);
    window_printf(2, "Coin Value: %d\n", pilotBananaInfo[item->subType].unkC);
}
