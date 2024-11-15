/**
 * bg_water.c - Code for the underwater background
 */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <dolphin.h>

#include "global.h"
#include "avdisp.h"
#include "background.h"
#include "effect.h"
#include "event.h"
#include "gxcache.h"
#include "gxutil.h"
#include "mathutil.h"
#include "mode.h"
#include "stage.h"
#include "window.h"

static struct BGModelSearch waterBgModelFind[] =
{
    { BG_MDL_CMP_FULL,   "WAT_SUIMEN_MAT_ONLY" },
    { BG_MDL_CMP_FULL,   "WAT_SANSYO_TEX_WATER" },
    { BG_MDL_CMP_FULL,   "WAT_SUIMEN_TEST_LOW_CONT" },
    { BG_MDL_CMP_PREFIX, "WAT_BUBBLE_" },
    { BG_MDL_CMP_FULL,   "WAT_LIGHTMAP" },
    { BG_MDL_CMP_FULL,   "WAT_LIGHTMAP_STAGE" },
    { BG_MDL_CMP_FULL,   "WAT_LIGHTMAP_GRAD" },
    { BG_MDL_CMP_END,    NULL },
};

static struct BGModelSearch waterBgObjFind[] =
{
    { BG_MDL_CMP_PREFIX, "WAT_SUB_SUKRYU" },
    { BG_MDL_CMP_FULL,   "WAT_SUIMEN" },
    { BG_MDL_CMP_PREFIX, "WAT_LIGHTCHAIN" },
    { BG_MDL_CMP_PREFIX, "WAT_LONG_CHAIN" },
    { BG_MDL_CMP_PREFIX, "WAT_PLANT" },
    { BG_MDL_CMP_PREFIX, "WAT_UKIWA" },
    { BG_MDL_CMP_PREFIX, "WAT_SUB" },
    { BG_MDL_CMP_END,    NULL },
};

static void lbl_8005E914(void);
static void bg_water_envmap_stage(struct GCMMatState_Unit *);
static void bg_water_envmap_background();
static void func_8005ED80(struct GCMMatState_Unit *);
static void bg_water_envmap_ball(struct GCMMatState_Unit *);
static void lbl_8005F520(struct GCMMatState_Unit *);
static int model_find_proc(int, struct GMAModelEntry *);
static int obj_find_proc(int, struct StageBgObject *);

void bg_water_init(void)
{
    struct BGWaterWork *work = backgroundInfo.work;

    bg_default_init();
    if (modeCtrl.unk30 < 2)
    {
        backgroundInfo.stageEnvMapFunc = bg_water_envmap_stage;
        backgroundInfo.bgEnvMapFunc = bg_water_envmap_background;
    }
    backgroundInfo.ballEnvMapFunc = bg_water_envmap_ball;
    if (work->unk0 == 0)
    {
        window_set_cursor_pos(4, 4);
        find_background_gma_models(waterBgModelFind, model_find_proc);
        work->unk0 = 1;
    }
    clear_background_parts_flag();
    work->waterSurface = NULL;
    find_background_objects(
        decodedStageLzPtr->bgObjects,
        decodedStageLzPtr->bgObjectCount,
        waterBgObjFind,
        obj_find_proc);
    find_background_objects(
        decodedStageLzPtr->fgObjects,
        decodedStageLzPtr->fgObjectCount,
        waterBgObjFind,
        obj_find_proc);
    backgroundInfo.unk14.x = RAND_FLOAT() - 0.5f;
    backgroundInfo.unk14.y = RAND_FLOAT() - 0.5f;
    backgroundInfo.unk14.z = RAND_FLOAT() - 0.5f;
    backgroundInfo.unk20.x = RAND_FLOAT() - 0.5f;
    backgroundInfo.unk20.y = 0.0f;
    backgroundInfo.unk20.z = RAND_FLOAT() - 0.5f;
    mathutil_vec_set_len(&backgroundInfo.unk20, &backgroundInfo.unk20, (0.9f + (0.2f * RAND_FLOAT())) / 30.0f);
    backgroundInfo.unk2C.x = RAND_FLOAT() - 0.5f;
    backgroundInfo.unk2C.y = RAND_FLOAT() - 0.5f;
    backgroundInfo.unk2C.z = RAND_FLOAT() - 0.5f;
    backgroundInfo.unk38.x = RAND_FLOAT() - 0.5f;
    backgroundInfo.unk38.y = 0.0f;
    backgroundInfo.unk38.z = RAND_FLOAT() - 0.5f;
    mathutil_vec_set_len(&backgroundInfo.unk38, &backgroundInfo.unk38, (0.9f + (0.2f * RAND_FLOAT())) / 30.0f);
    work->unk10 = rand() & 0x7FFF;
    work->unk12 = rand() & 0x7FFF;
    work->unk14 = rand() & 0x7FFF;
    work->unk16 = rand() & 0x7FFF;
    work->unk18 = rand() & 0x7FFF;
    work->unk1A = rand() & 0x7FFF;
    work->unk1E = 1;
    work->unk1C = 60;
    work->unk20 = 0.5f;
    backgroundInfo.u_lightAssignFunc = lbl_8005E914;
}

void bg_water_main(void)
{
    Vec scale;
    struct BGWaterWork *work;

    if ((debugFlags & 0xA) && eventInfo[12].state != 2)
        return;
    bg_default_main();
    work = backgroundInfo.work;
    backgroundInfo.unk14.x = backgroundInfo.unk14.x + backgroundInfo.unk20.x;
    backgroundInfo.unk14.y = backgroundInfo.unk14.y + backgroundInfo.unk20.y;
    backgroundInfo.unk14.z = backgroundInfo.unk14.z + backgroundInfo.unk20.z;
    backgroundInfo.unk2C.x += backgroundInfo.unk38.x;
    backgroundInfo.unk2C.y += backgroundInfo.unk38.y;
    backgroundInfo.unk2C.z += backgroundInfo.unk38.z;
    work->unk10 += 0x20;
    work->unk12 += 0x3F;
    work->unk14 += 0x5F;
    work->unk16 += 0x17;
    work->unk18 += 0x20;
    work->unk1A += 0x61;
    work->unk1C--;
    if (work->unk1E != 0)
        work->unk20 += 0.3f * (0.5f - work->unk20);
    else
        work->unk20 += 0.1f * (1.0f - work->unk20);
    mathutil_mtxA_from_identity();
    scale.x = 0.125 * (0.9f + 0.2f * mathutil_sin(work->unk10));
    scale.y = 0.125 * (0.9f + 0.2f * mathutil_sin(work->unk12));
    scale.z = 0.125 * (0.9f + 0.2f * mathutil_sin(work->unk14));
    mathutil_mtxA_scale(&scale);
    mathutil_mtxA_rotate_y(0x1000);
    mathutil_mtxA_rotate_x(0x3800);
    mathutil_mtxA_translate(&backgroundInfo.unk14);
    mathutil_mtxA_to_mtx(work->unk3C);
    mathutil_mtxA_from_identity();
    scale.x = 0.078125f * (0.9f + 0.2f * mathutil_sin(work->unk16));
    scale.y = 0.078125f * (0.9f + 0.2f * mathutil_sin(work->unk18));
    scale.z = 0.078125f * (0.9f + 0.2f * mathutil_sin(work->unk1A));
    mathutil_mtxA_scale(&scale);
    mathutil_mtxA_rotate_y(0x1000);
    mathutil_mtxA_rotate_x(0x3800);
    mathutil_mtxA_rotate_z(0x1000);
    mathutil_mtxA_translate(&backgroundInfo.unk2C);
    mathutil_mtxA_to_mtx(work->unk6C);
    mathutil_mtxA_from_identity();
    mathutil_mtxA_rotate_y(0x1000);
    mathutil_mtxA_rotate_x(0x3800);
    mathutil_mtxA_to_mtx(work->unk9C);
    mathutil_mtxA_from_identity();
    mathutilData->mtxA[0][0] = 0.0f;
    mathutilData->mtxA[0][2] = -0.5f;
    mathutilData->mtxA[0][3] = work->unk20;
    mathutilData->mtxA[1][1] = 0.0f;
    mathutilData->mtxA[2][2] = 0.0f;
    mathutilData->mtxA[2][3] = 1.0f;
    mathutil_mtxA_to_mtx(work->unkCC);
}

void bg_water_finish(void) {}

void bg_water_draw(void)
{
    struct BGWaterWork *work = backgroundInfo.work;
    struct StageBgObject *temp_r31;

    mathutil_mtxA_from_mtx(userWork->matrices[0]);
    temp_r31 = work->waterSurface;
    if (temp_r31 != NULL)
    {
        temp_r31->flags &= 0xFFFEFFFF;
        mathutil_mtxA_translate(&temp_r31->pos);
        mathutil_mtxA_rotate_z(temp_r31->rotZ);
        mathutil_mtxA_rotate_y(temp_r31->rotY);
        mathutil_mtxA_rotate_x(temp_r31->rotX);
        mathutil_mtxA_scale(&temp_r31->scale);
    }
    GXLoadPosMtxImm(mathutilData->mtxA, GX_PNMTX0);
    GXLoadNrmMtxImm(mathutilData->mtxA, GX_PNMTX0);
    u_avdisp_set_some_func_1(lbl_8005F520);
    avdisp_draw_model_culled_sort_none(work->waterSurfaceMat);
    u_avdisp_set_some_func_1(NULL);
    bg_default_draw();
}

void bg_water_interact(int a) {}

static void lbl_8005E914(void)
{
    struct BGWaterWork *work = backgroundInfo.work;
    Mtx sp8;

    mathutil_mtxA_from_mtx(userWork->matrices[0]);
    mathutil_mtxA_rigid_invert();
    mathutil_mtxA_to_mtx(sp8);
    mathutil_mtxA_mult_left(work->unk3C);
    mathutil_mtxA_to_mtx(work->unkFC);
    mathutil_mtxA_from_mtx(sp8);
    mathutil_mtxA_mult_left(work->unk6C);
    mathutil_mtxA_to_mtx(work->unk12C);
    mathutil_mtxA_from_mtx(sp8);
    mathutil_mtxA_mult_left(work->unk9C);
    mathutil_mtxA_to_mtx(work->unk15C);
}

struct TevStageInfo lbl_8027CBF8;

static void bg_water_envmap_stage(struct GCMMatState_Unit *arg0)
{
    struct TevStageInfo sp24 = arg0->unkC;
    float spC[2][3];

    if (arg0->unk0 == 0
     && sp24.tevStage == lbl_8027CBF8.tevStage
     && sp24.tevIndStage == lbl_8027CBF8.tevIndStage
     && sp24.texMtxId == lbl_8027CBF8.texMtxId
     && sp24.ptTexMtxId == lbl_8027CBF8.ptTexMtxId
     && sp24.indTexMtxId == lbl_8027CBF8.indTexMtxId
     && sp24.texMapId == lbl_8027CBF8.texMapId)
    {
        arg0->unkC.tevStage += 2;
        arg0->unkC.tevIndStage += 1;
        arg0->unkC.texCoordId += 3;
        arg0->unkC.texMtxId += 9;
        arg0->unkC.ptTexMtxId += 3;
        arg0->unkC.indTexMtxId += 1;
        arg0->unkC.texMapId += 2;
        return;
    }
    lbl_8027CBF8 = sp24;
    GXLoadTexObj_cached(((struct BGWaterWork *)backgroundInfo.work)->lightmapStageTex, arg0->unkC.texMapId);
    spC[0][0] = 0.8f;
    spC[0][1] = 0.0f;
    spC[0][2] = 0.0f;
    spC[1][0] = 0.0f;
    spC[1][1] = 0.8f;
    spC[1][2] = 0.0f;
    GXSetIndTexMtx(arg0->unkC.indTexMtxId, spC, 0);
    func_8005ED80(arg0);
}

static void bg_water_envmap_background(struct GCMMatState_Unit *arg0)
{
    struct TevStageInfo sp24 = arg0->unkC;
    float spC[2][3];

    if (arg0->unk0 == 0
     && sp24.tevStage == lbl_8027CBF8.tevStage
     && sp24.tevIndStage == lbl_8027CBF8.tevIndStage
     && sp24.texMtxId == lbl_8027CBF8.texMtxId
     && sp24.ptTexMtxId == lbl_8027CBF8.ptTexMtxId
     && sp24.indTexMtxId == lbl_8027CBF8.indTexMtxId
     && sp24.texMapId == lbl_8027CBF8.texMapId)
    {
        arg0->unkC.tevStage += 2;
        arg0->unkC.tevIndStage += 1;
        arg0->unkC.texCoordId += 3;
        arg0->unkC.texMtxId += 9;
        arg0->unkC.ptTexMtxId += 3;
        arg0->unkC.indTexMtxId += 1;
        arg0->unkC.texMapId += 2;
        return;
    }
    lbl_8027CBF8 = sp24;
    GXLoadTexObj_cached(((struct BGWaterWork *)backgroundInfo.work)->lightmapTex, arg0->unkC.texMapId);
    spC[0][0] = 0.6f;
    spC[0][1] = 0.0f;
    spC[0][2] = 0.0f;
    spC[1][0] = 0.0f;
    spC[1][1] = 0.6f;
    spC[1][2] = 0.0f;
    GXSetIndTexMtx(arg0->unkC.indTexMtxId, spC, 0);
    func_8005ED80(arg0);
}

static void func_8005ED80(struct GCMMatState_Unit *arg0)
{
    struct BGWaterWork *work = backgroundInfo.work;
    struct TevStageInfo sp2C = arg0->unkC;

    mathutil_mtxA_push();
    mathutil_mtxA_mult_left(work->unkFC);
    GXLoadTexMtxImm(mathutilData->mtxA, sp2C.texMtxId, GX_MTX3x4);
    mathutil_mtxA_pop();
    mathutil_mtxA_push();
    mathutil_mtxA_mult_left(work->unk12C);
    GXLoadTexMtxImm(mathutilData->mtxA, sp2C.texMtxId + 3, GX_MTX3x4);
    mathutil_mtxA_pop();
    GXSetTexCoordGen(sp2C.texCoordId, GX_TG_MTX2x4, GX_TG_POS, sp2C.texMtxId);
    GXSetTexCoordGen(sp2C.texCoordId + 1, GX_TG_MTX2x4, GX_TG_POS, sp2C.texMtxId + 3);
    GXSetIndTexOrder(sp2C.tevIndStage, sp2C.texCoordId + 1, sp2C.texMapId);
    GXSetTevIndirect(sp2C.tevStage, sp2C.tevIndStage, GX_ITF_8, GX_ITB_NONE, sp2C.indTexMtxId, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder_cached(sp2C.tevStage, sp2C.texCoordId, sp2C.texMapId, GX_COLOR_NULL);
    GXSetTevColorIn_cached(sp2C.tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp_cached(sp2C.tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
    GXSetTevAlphaIn_cached(sp2C.tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp_cached(sp2C.tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    mathutil_mtxA_push();
    mathutil_mtxA_mult_left(work->unk15C);
    mathutil_mtxA_set_translate_xyz(0.0f, 0.0f, 0.0f);
    GXLoadTexMtxImm(mathutilData->mtxA, sp2C.texMtxId + 6, GX_MTX3x4);
    mathutil_mtxA_pop();
    GXLoadTexMtxImm(work->unkCC, sp2C.ptTexMtxId, GX_MTX3x4);
    GXLoadTexObj_cached(work->lightmapGradTex, sp2C.texMapId + 2);
    GXSetTexCoordGen2(sp2C.texCoordId + 2, GX_TG_MTX3x4, GX_TG_NRM, sp2C.texMtxId + 6, GX_TRUE, sp2C.ptTexMtxId);
    GXSetTevDirect(sp2C.tevStage + 1);
    GXSetTevOrder_cached(sp2C.tevStage + 1, sp2C.texCoordId + 2, sp2C.texMapId + 2, GX_COLOR_NULL);
    GXSetTevColorIn_cached(sp2C.tevStage + 1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_CPREV);
    GXSetTevColorOp_cached(sp2C.tevStage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn_cached(sp2C.tevStage + 1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp_cached(sp2C.tevStage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    sp2C.tevStage += 2;
    sp2C.tevIndStage += 1;
    sp2C.texCoordId += 3;
    sp2C.texMtxId += 9;
    sp2C.ptTexMtxId += 3;
    sp2C.indTexMtxId += 1;
    sp2C.texMapId += 2;
    arg0->unkC = sp2C;
}

static void bg_water_envmap_ball(struct GCMMatState_Unit *arg0)
{
    struct BGWaterWork *work = backgroundInfo.work;
    struct TevStageInfo sp2C = arg0->unkC;
    float sp14[2][3];

    GXSetBlendMode_cached(1, 1, 1, 0);
    fog_gx_set();
    GXLoadTexObj_cached(work->lightmapStageTex, sp2C.texMapId);
    sp14[0][0] = 0.6f;
    sp14[0][1] = 0.0f;
    sp14[0][2] = 0.0f;
    sp14[1][0] = 0.0f;
    sp14[1][1] = 0.6f;
    sp14[1][2] = 0.0f;
    GXSetIndTexMtx(sp2C.indTexMtxId, sp14, 0);
    mathutil_mtxA_push();
    mathutil_mtxA_mult_left(work->unkFC);
    mathutil_mtxA_scale_s(3.0f);
    GXLoadTexMtxImm(mathutilData->mtxA, sp2C.texMtxId, GX_MTX3x4);
    mathutil_mtxA_pop();
    mathutil_mtxA_push();
    mathutil_mtxA_mult_left(work->unk12C);
    mathutil_mtxA_scale_s(3.0f);
    GXLoadTexMtxImm(mathutilData->mtxA, sp2C.texMtxId + 3, GX_MTX3x4);
    mathutil_mtxA_pop();
    GXSetTexCoordGen(sp2C.texCoordId, GX_TG_MTX2x4, GX_TG_POS, sp2C.texMtxId);
    GXSetTexCoordGen(sp2C.texCoordId + 1, GX_TG_MTX2x4, GX_TG_POS, sp2C.texMtxId + 3);
    GXSetIndTexOrder(sp2C.tevIndStage, sp2C.texCoordId + 1, sp2C.texMapId);
    GXSetTevIndirect(sp2C.tevStage, sp2C.tevIndStage, GX_ITF_8, GX_ITB_NONE, sp2C.indTexMtxId, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder_cached(sp2C.tevStage, sp2C.texCoordId, sp2C.texMapId, GX_COLOR_NULL);
    GXSetTevColorIn_cached(sp2C.tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp_cached(sp2C.tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
    GXSetTevAlphaIn_cached(sp2C.tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp_cached(sp2C.tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    mathutil_mtxA_push();
    mathutil_mtxA_mult_left(work->unk15C);
    mathutil_mtxA_set_translate_xyz(0.0f, 0.0f, 0.0f);
    GXLoadTexMtxImm(mathutilData->mtxA, sp2C.texMtxId + 6, GX_MTX3x4);
    mathutil_mtxA_pop();
    GXLoadTexMtxImm(work->unkCC, sp2C.ptTexMtxId, GX_MTX3x4);
    GXLoadTexObj_cached(work->lightmapGradTex, sp2C.texMapId + 2);
    GXSetTexCoordGen2(sp2C.texCoordId + 2, GX_TG_MTX3x4, GX_TG_NRM, sp2C.texMtxId + 6, GX_TRUE, sp2C.ptTexMtxId);
    GXSetTevDirect(sp2C.tevStage + 1);
    GXSetTevOrder_cached(sp2C.tevStage + 1, sp2C.texCoordId + 2, sp2C.texMapId + 2, GX_COLOR_NULL);
    GXSetTevColorIn_cached(sp2C.tevStage + 1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
    GXSetTevColorOp_cached(sp2C.tevStage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn_cached(sp2C.tevStage + 1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp_cached(sp2C.tevStage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    sp2C.tevStage += 2;
    sp2C.tevIndStage += 1;
    sp2C.texCoordId += 3;
    sp2C.texMtxId += 9;
    sp2C.ptTexMtxId += 3;
    sp2C.indTexMtxId += 1;
    arg0->unkC = sp2C;
}

#ifdef NONMATCHING
static void lbl_8005F520(struct GCMMatState_Unit *arg0)
{
    struct BGWaterWork *work = backgroundInfo.work;
    struct TevStageInfo sp2C = arg0->unkC;
    float sp14[2][3];

    GXLoadTexObj_cached(work->causticTex, sp2C.texMapId);
    GXLoadTexObj_cached(work->waterSurfaceTestTex, sp2C.texMapId + 1);
    mathutil_mtxA_push();
    mathutil_mtxA_from_identity();
    mathutil_mtxA_rotate_x(0x4000);
    mathutil_mtxA_rotate_y(backgroundInfo.u_otherSeed);
    mathutil_mtxA_translate_xyz(
        backgroundInfo.animTimer / 2160.0f,
        backgroundInfo.animTimer / 2160.0f,
        backgroundInfo.animTimer / -5280.0f);
    mathutil_mtxA_scale_s(1.0f / (214.0f + (20.0f * mathutil_sin(backgroundInfo.u_otherSeed << 6))));
    GXLoadTexMtxImm(mathutilData->mtxA, sp2C.texMtxId, GX_MTX3x4);
    mathutil_mtxA_from_identity();
    mathutil_mtxA_rotate_x(0x4000);
    mathutil_mtxA_rotate_y(0x400);
    mathutil_mtxA_translate_xyz(
        backgroundInfo.animTimer / 360.0f,
        backgroundInfo.animTimer / 360.0f,
        backgroundInfo.animTimer / 360.0f);
    mathutil_mtxA_scale_s(0.005f * (1.0f + (0.25f * mathutil_sin(backgroundInfo.u_otherSeed << 5))));
    GXLoadTexMtxImm(mathutilData->mtxA, sp2C.texMtxId + 3, GX_MTX3x4);
    mathutil_mtxA_pop();
    sp14[0][0] = 0.6f;
    sp14[0][1] = -0.01f;
    sp14[0][2] = 0.0f;
    sp14[1][0] = 0.0f;
    sp14[1][1] = 0.6f;
    sp14[1][2] = 0.2f;
    GXSetIndTexMtx(arg0->unkC.indTexMtxId, sp14, 1);
    GXSetTexCoordGen(sp2C.texCoordId, GX_TG_MTX2x4, GX_TG_POS, sp2C.texMtxId);
    // NONMATCHING: need it to reload sp2C.texCoordId here instead of using r29
    GXSetTexCoordGen(sp2C.texCoordId + 1, GX_TG_MTX2x4, GX_TG_POS, sp2C.texMtxId + 3);
    GXSetIndTexOrder(sp2C.tevIndStage, sp2C.texCoordId + 1, sp2C.texMapId + 1);
    GXSetTevIndirect(sp2C.tevStage, sp2C.tevIndStage, GX_ITF_8, GX_ITB_NONE, sp2C.indTexMtxId, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder_cached(sp2C.tevStage, sp2C.texCoordId, sp2C.texMapId, GX_COLOR_NULL);
    GXSetTevColorIn_cached(sp2C.tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevColorOp_cached(sp2C.tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn_cached(sp2C.tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp_cached(sp2C.tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    sp2C.tevStage += 1;
    sp2C.tevIndStage += 1;
    sp2C.texCoordId += 2;
    sp2C.texMtxId += 6;
    sp2C.texMapId += 2;
    sp2C.indTexMtxId += 1;
    arg0->unkC = sp2C;
}
#else
const float lbl_802F4314 = 2160.0f;
const float lbl_802F4318 = -5280.0f;
const float lbl_802F431C = 214.0f;
const float lbl_802F4320 = 20.0f;
const float lbl_802F4324 = 360.0f;
const float lbl_802F4328 = 0.004999999888241291f;
const float lbl_802F432C = 0.25f;
const float lbl_802F4330 = -0.0099999997764825821f;
static asm void lbl_8005F520(struct GCMMatState_Unit *arg0)
{
    nofralloc
#include "../asm/nonmatchings/lbl_8005F520.s"
}
#pragma peephole on
#endif

static int model_find_proc(int index, struct GMAModelEntry *entry)
{
    struct BGWaterWork *work = backgroundInfo.work;

    switch (index)
    {
    case 0:  // WAT_SUIMEN_MAT_ONLY
        work->waterSurfaceMat = entry->model;
        break;
    case 1:  // WAT_SANSYO_TEX_WATER
        work->causticTex = &entry->model->texObjs[0];
        break;
    case 2:  // WAT_SUIMEN_TEST_LOW_CONT
        work->waterSurfaceTestTex = &entry->model->texObjs[0];
        break;
    case 3:  // WAT_BUBBLE_
        work->bubbleModel = entry->model;
        break;
    case 4:  // WAT_LIGHTMAP
        work->lightmapTex = &entry->model->texObjs[0];
        break;
    case 5:  // WAT_LIGHTMAP_STAGE
        work->lightmapStageTex = &entry->model->texObjs[0];
        break;
    case 6:  // WAT_LIGHTMAP_GRAD
        work->lightmapGradTex = &entry->model->texObjs[0];
        break;
    }
    return 1;
}

static int obj_find_proc(int index, struct StageBgObject *bgObj)
{
    struct BGWaterWork *work = backgroundInfo.work;
    struct Effect effect;

    switch (index)
    {
    case 0:  // WAT_SUB_SUKRYU
        // submarine propeller
        memset(&effect, 0, sizeof(effect));
        effect.type = ET_BGWAT_BUBBLE_BASE;
        effect.model = (void *)bgObj;
        spawn_effect(&effect);
        break;
    case 1:  // WAT_SUIMEN
        work->waterSurface = bgObj;
        break;
    default:
        bgObj->flags |= 0x1000000;
        break;
    }
    return 1;
}
