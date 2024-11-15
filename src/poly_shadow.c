#include <dolphin.h>

#include "global.h"
#include "avdisp.h"
#include "camera.h"
#include "mathutil.h"

void func_800948F4(void)
{
    poly_shadow_init();
}

static s32 entryRemain;
static struct PolyShadowUnit *entryPtr;
static struct PolyShadowUnit entryBuf[64];

void poly_shadow_init(void)
{
    entryRemain = ARRAY_COUNT(entryBuf);
    entryPtr = entryBuf;
}

int set_poly_shadow(struct PolyShadowUnit *arg0)
{
    if (entryRemain == 0)
        return 0;
    *entryPtr = *arg0;
    entryPtr->unk30 = MAX(MAX(entryPtr->unk14.x, entryPtr->unk14.y), entryPtr->unk14.z);
    entryPtr->unk34 = entryPtr->unk30 * entryPtr->unk28->boundSphereRadius;
    entryPtr++;
    entryRemain--;
    return 1;
}

void poly_shadow_draw(void)
{
    Vec sp14;
    Vec sp8;
    int var_r29;
    struct PolyShadowUnit *var_r28;
    float var_f28;
    float temp_f1;
    float temp_f27;
    float temp_f3;

    var_r29 = ARRAY_COUNT(entryBuf) - entryRemain;
    if (var_r29 != 0)
    {
        temp_f1 = -currentCamera->sub28.unk38;
        temp_f27 = temp_f1 / currentCamera->sub28.vp.height;
        avdisp_set_z_mode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);

        var_r28 = entryBuf;
        for (; var_r29 > 0; var_r29--, var_r28++)
        {
            mathutil_mtxA_from_mtxB_translate(&var_r28->unk0);
            mathutil_mtxA_rotate_y(var_r28->unkC.y);
            mathutil_mtxA_rotate_x(var_r28->unkC.x);
            mathutil_mtxA_rotate_z(var_r28->unkC.z);
            mathutil_mtxA_get_translate_alt(&sp14);
            if (sp14.z < 0.0f)
            {
                float temp_f2 = var_r28->unk20;
                var_f28 = var_r28->unk34 / (sp14.z * temp_f27);
                if (var_f28 < temp_f2)
                    continue;
                var_f28 = (var_f28 - temp_f2) / (var_r28->unk24 - temp_f2);
                if (var_f28 > 1.0f)
                    var_f28 = 1.0f;
            }
            else
                var_f28 = 1.0f;
            temp_f3 = 1.0f - (0.2f / mathutil_vec_len(&sp14));
            sp14.x *= temp_f3;
            sp14.y *= temp_f3;
            sp14.z *= temp_f3;
            mathutil_mtxA_set_translate(&sp14);
            sp8.x = var_r28->unk14.x * temp_f3;
            sp8.y = var_r28->unk14.y * temp_f3;
            sp8.z = var_r28->unk14.z * temp_f3;
            mathutil_mtxA_scale(&sp8);
            avdisp_set_bound_sphere_scale(var_r28->unk30);
            GXLoadPosMtxImm(mathutilData->mtxA, GX_PNMTX0);
            GXLoadNrmMtxImm(mathutilData->mtxA, GX_PNMTX0);
            var_f28 *= 0.003921569f;
            avdisp_set_post_mult_color(var_r28->unk2C.r * var_f28, var_r28->unk2C.g * var_f28, var_r28->unk2C.b * var_f28, 1.0f);
            avdisp_draw_model_culled_sort_none(var_r28->unk28);
            avdisp_set_post_mult_color(1.0f, 1.0f, 1.0f, 1.0f);
        }
        avdisp_set_z_mode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    }
}
