/**
 * item_coin.c - Item behavior of collectable bananas in the main game
 */
#include <string.h>
#include <dolphin.h>

#include "global.h"
#include "adv.h"
#include "avdisp.h"
#include "background.h"
#include "ball.h"
#include "camera.h"
#include "effect.h"
#include "info.h"
#include "item.h"
#include "mathutil.h"
#include "mode.h"
#include "sound.h"
#include "stage.h"
#include "stcoli.h"
#include "window.h"

#include "../data/common.gma.h"

struct ModelLOD s_singleBananaLODs[] =
{
    { OBJ_BANANA_01_LOD150, 150 },
    { OBJ_BANANA_01_LOD100, 100 },
    { OBJ_BANANA_01_LOD50,   50 },
    { OBJ_BANANA_01_LOD0,     0 },
    { -1, 0 },
};

struct ModelLOD s_bananaBunchLODs[] =
{
    { OBJ_BANANA_02_LOD100, 100 },
    { OBJ_BANANA_02_LOD0,     0 },
    { -1, 0 },
};

// Per banana type immutable info
struct BananaInfo
{
    struct ModelLOD **modelLODs;
    float radius;  // collision radius
    s16 bananaValue;  // number of bananas given when collected
    s16 unkA;
    s16 pointValue;  // number of points given when collected
    s16 rotVelX;
    s16 rotVelY;
    s16 rotVelZ;
};

struct ModelLOD *s_singleBananaLODsPtr = s_singleBananaLODs;
struct ModelLOD *s_bananaBunchLODsPtr  = s_bananaBunchLODs;

struct BananaInfo s_bananaInfos[] =
{
    { &s_singleBananaLODsPtr,  0.5,  1, 0,  100, 0, 1024,    0 },
    { &s_bananaBunchLODsPtr,  0.75, 10, 1, 1000, 0,  768,    0 },
    { &s_singleBananaLODsPtr,  0.5,  1, 0,  100, 0, 1024, -128 },
    { &s_bananaBunchLODsPtr,  0.75, 10, 1, 1000, 0, 1024, -128 },
};

void item_coin_init(struct Item *item)
{
    item->unk12 = -1;
    item->state = 1;
    item->modelLODs = s_bananaInfos[item->subType].modelLODs;
    item->flags = ITEM_FLAG_TANGIBLE|ITEM_FLAG_5;
    item->radius = s_bananaInfos[item->subType].radius;
    item->unk18 = 0.25f;
    item->rotVelX = s_bananaInfos[item->subType].rotVelX;
    item->rotVelY = s_bananaInfos[item->subType].rotVelY;
    item->rotVelZ = s_bananaInfos[item->subType].rotVelZ;
    item->shadowModel = commonGma->modelEntries[polyshadow01].model;
    item->shadowColor.r = 0x46;
    item->shadowColor.g = 0x47;
    item->shadowColor.b = 0x5F;
    item->unk7C.x = item->radius;
    item->unk7C.y = item->radius * 0.8f;
    item->unk7C.z = item->radius;
}

void item_coin_main(struct Item *item)
{
    if (item->state == 0)
        return;
    switch (item->state)
    {
    case 1:
        item->state = 2;
        break;
    case 2:
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
    item->unk6C.z = -item->rotY;
    item->unk7C.x = item->radius;
    item->unk7C.y = item->radius * 0.7f;
}

void item_coin_draw(struct Item *item)
{
    float scale;
    float f30 = item->radius;
    struct GMAModel *model;
    Vec spC;

    mathutil_mtxA_from_mtxB();
    mathutil_mtxA_translate(&item->pos);
    mathutil_mtxA_sq_from_mtx(userWork->matrices[2]);
    mathutil_mtxA_rotate_y(item->rotY);
    mathutil_mtxA_rotate_x(item->rotX);
    mathutil_mtxA_rotate_z(item->rotZ);
    model = get_lod(item->modelLODs);
    scale = (f30 / model->boundSphereRadius) * 1.5;
    if (test_scaled_sphere_in_frustum(&model->boundSphereCenter, model->boundSphereRadius, scale) == 0)
        return;
    if (scale != 1.0)
        mathutil_mtxA_scale_xyz(scale, scale, scale);
    mathutil_mtxA_get_translate_alt(&spC);
    f30 = -(((spC.z + f30) + 0.1f) / f30);
    if (modeCtrl.gameType == GAMETYPE_MAIN_COMPETITION && (currentBall->flags & (1 << 12)))
        f30 = 0.25f;
    if (f30 > 0.0f)
    {
        avdisp_set_bound_sphere_scale(scale);
        GXLoadPosMtxImm(mathutilData->mtxA, GX_PNMTX0);
        GXLoadNrmMtxImm(mathutilData->mtxA, GX_PNMTX0);
        if (f30 < 1.0f)
        {
            avdisp_set_alpha(f30);
            avdisp_draw_model_unculled_sort_all(model);
        }
        else
            avdisp_draw_model_unculled_sort_none(model);
    }
}

void item_coin_collect(struct Item *item, struct PhysicsBall *ball)
{
    if (modeCtrl.gameType == GAMETYPE_MAIN_COMPETITION && (currentBall->flags & (1 << 12)))
        return;
    item->flags &= ~ITEM_FLAG_TANGIBLE;
    item->state = 3;
    item->vel.y += item->radius * 0.1875;
    item->rotVelY <<= 2;
    item->vel.x += ball->vel.x * 0.25;
    item->vel.y += ball->vel.y * 0.25;
    item->vel.z += ball->vel.z * 0.25;
    if (item->unk5E < 0 && !(currentBall->flags & (1 << 24)))
    {
        struct Effect effect;

        item->unk5E = infoWork.timerCurr;
        give_bananas(s_bananaInfos[item->subType].bananaValue);
        u_give_points(s_bananaInfos[item->subType].unkA, s_bananaInfos[item->subType].pointValue);
        item->state = 0;
        item->flags |= ITEM_FLAG_INVISIBLE;
        item->flags &= ~ITEM_FLAG_TANGIBLE;

        // spawn banana effect that travels towards counter in HUD
        memset(&effect, 0, sizeof(effect));
        effect.type = ET_HOLDING_BANANA;
        effect.playerId = currentBall->playerId;
        mathutil_mtxA_from_mtx(animGroups[ball->animGroupId].transform);
        mathutil_mtxA_tf_point(&item->pos, &effect.pos);
        mathutil_mtxA_tf_vec(&item->vel, &effect.vel);
        effect.rotX = item->rotX;
        effect.rotY = item->rotY;
        effect.rotZ = item->rotZ;
        effect.model = get_lod((void *)item->modelLODs);
        effect.scale.x = (item->radius / effect.model->boundSphereRadius) * 1.5;
        effect.scale.y = effect.scale.x;
        effect.scale.z = effect.scale.y;
        spawn_effect(&effect);
    }
    if (advDemoInfo.flags & (1 << 8))
        return;
    if (item->subType == 1)
    {
        u_play_sound_0(0x39);
        if ((infoWork.flags & (1 << 11)) || !(infoWork.flags & (1 << 4)))
            u_play_sound_0(0x2820);
        background_interact(1);
    }
    else
    {
        u_play_sound_0(3);
        if ((infoWork.flags & (1 << 11)) || !(infoWork.flags & (1 << 4)))
            u_play_sound_0(0x281F);
        background_interact(0);
    }
}

void item_coin_destroy(struct Item *item) {}

void item_coin_release(struct Item *item)
{
    if (item->state != 2)
    {
        item->pos = item->stageBanana->pos;
        item->vel.x = 0.0f;
        item->vel.y = 0.0f;
        item->vel.z = 0.0f;
        item_coin_init(item);
    }
}

char wtfisthis[] =
{
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x16,
    0x16, 0x16, 0x16, 0x0A,
    0x00
};

void item_coin_debug(struct Item *item)
{
    window_printf(2, wtfisthis);
    window_printf(2, "Coin Value: %d\n", s_bananaInfos[item->subType].bananaValue);
}

// needed to force float constant ordering
float item_coin_dummy(void) { return -480.0f; }

struct GMAModel *get_lod(struct ModelLOD **a)
{
    struct ModelLOD *r31 = *a;
    struct GMAModel *model;
    int modelId;
    float f31;
    Vec spC;
    float f1;

    modelId = r31->modelId;
    model = commonGma->modelEntries[modelId].model;
    f31 = model->boundSphereRadius;
    mathutil_mtxA_tf_point(&model->boundSphereCenter, &spC);
    if (spC.z > f31)
    {
        while (r31->modelId > 0)
        {
            modelId = r31->modelId;
            r31++;
        }
        return commonGma->modelEntries[modelId].model;
    }
    if (spC.z > -0.1f)
        return model;
    f1 = (currentCamera->sub28.vp.height * -480.0f) * f31 / (spC.z * currentCamera->sub28.unk38);
    while (r31->modelId > 0)
    {
        modelId = r31->modelId;
        if (r31->distance < f1)
            break;
        r31++;
    }
    return commonGma->modelEntries[modelId].model;
}
