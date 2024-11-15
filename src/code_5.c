#include <dolphin.h>

#include "global.h"

#include "relocation.h"

// code_5.c
struct Struct802F1C10 lbl_802F1C10;
u8 g_unlockFlags;
u8 lbl_802F1C0C;
struct Struct802F1C04 lbl_802F1C04;
struct Struct802F1BFC lbl_802F1BFC;
struct Struct802F1BF4 lbl_802F1BF4;
u32 lbl_802F1BF0;
struct Struct802F1BE8 lbl_802F1BE8;

// I think these variables should belong in sel.c. However, they appear before
// this file's variables, while sel.c is linked after this file.
struct StageSelection stageSelection;
struct RelModule lbl_802F1BD8;
void (*lbl_802F1BD4)(void);
void (*menuCallback)(void);

u8 lbl_802F02F8[6] = { 5, 5, 4, 3, 4, 2 };

struct
{
    u8 unk0;
    u8 filler1[3];
    s16 unk4;
    s16 unk6;
    u32 unk8;
    s16 unkC;
    s16 unkE;
    u32 unk10;
    s16 unk14;
    s16 unk16;
    u32 unk18;
    s16 unk1C;
    s16 unk1E;
    u32 unk20;
    s16 unk24;
    s16 unk26;
    u32 unk28;
    u32 unk2C;
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u8 unk34;
    u8 filler35[3];
} lbl_801EED50;

struct Struct801EED88 lbl_801EED88;

struct
{
    u32 unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    u8 unk50;
    u8 filler9[0x10-0x9];
} lbl_801EED98;

struct Struct801EEDA8 lbl_801EEDA8;

void u_reset_gamedata(void)
{
    u8 filler[8];
    int i;

    lbl_802F1C10.unk0 = 0;
    lbl_802F1C10.unk1 = 0;
    lbl_802F1C10.unk2 = -1;
    lbl_802F1C10.unk4[0] = 0;
    lbl_802F1C10.unk4[1] = 1;
    lbl_802F1C10.unk4[2] = 2;
    lbl_802F1C10.unk4[3] = 3;

    g_unlockFlags = 0;
    lbl_802F1C0C = 0;

    lbl_801EED50.unk0 = 3;
    lbl_801EED50.unk6 = 3;
    lbl_801EED50.unk4 = 1;
    lbl_801EED50.unk8 = 0;
    lbl_801EED50.unkE = 3;
    lbl_801EED50.unkC = 1;
    lbl_801EED50.unk10 = 0;
    lbl_801EED50.unk16 = 3;
    lbl_801EED50.unk14 = 1;
    lbl_801EED50.unk18 = 0;
    lbl_801EED50.unk1E = 3;
    lbl_801EED50.unk1C = 1;
    lbl_801EED50.unk20 = 0;
    lbl_801EED50.unk26 = 3;
    lbl_801EED50.unk24 = 1;
    lbl_801EED50.unk28 = 0;
    lbl_801EED50.unk2C = 0;
    lbl_801EED50.unk30 = 0x33;
    lbl_801EED50.unk31 = 5;
    lbl_801EED50.unk32 = 3;
    lbl_801EED50.unk33 = 1;
    lbl_801EED50.unk34 = 0;

    lbl_802F1C04.unk2 = 3;
    lbl_802F1C04.unk0 = 1;
    lbl_802F1C04.unk4 = 0;

    lbl_801EED88.unk0 = 0;
    for (i = 0; i < 6; i++)
        lbl_801EED88.unk1[i] = lbl_802F02F8[i];
    lbl_801EED88.unk8 = 6;
    lbl_801EED88.unkC = 0;

    lbl_801EED98.unk48 = 0;
    lbl_801EED98.unk4C = 3;
    lbl_801EED98.unk4D = 0;
    lbl_801EED98.unk4E = 0;
    lbl_801EED98.unk4F = 0;
    lbl_801EED98.unk50 = 0;

    lbl_802F1BFC.unk0 = 10;
    lbl_802F1BFC.unk4 = 0x18;

    lbl_802F1BF4.unk0 = 3;
    lbl_802F1BF4.unk1 = 2;
    lbl_802F1BF4.unk4 = 0;

    lbl_802F1BF0 = 0;

    lbl_802F1BE8.unk0 = 0;
    lbl_802F1BE8.unk4 = 0;
}

void u_store_gamedata(struct MemcardContents *data)
{
    int i;

    data->gameData.unk44 = lbl_802F1C10.unk0;
    data->gameData.unk45 = lbl_802F1C10.unk1;
    data->gameData.unk46 = lbl_802F1C10.unk2;
    data->gameData.unk47 = 0;
    data->gameData.unk48 = lbl_802F1C10.unk4[0];
    data->gameData.unk49 = lbl_802F1C10.unk4[1];
    data->gameData.unk4A = lbl_802F1C10.unk4[2];
    data->gameData.unk4B = lbl_802F1C10.unk4[3];

    data->gameData.unk2BF = g_unlockFlags;
    data->gameData.unk4F = lbl_802F1C0C;

    data->gameData.unk50 = lbl_801EED50.unk0;
    data->gameData.unk51 = lbl_801EED50.unk30;
    data->gameData.unk52 = lbl_801EED50.unk31;
    data->gameData.unk53 = lbl_801EED50.unk32;
    data->gameData.unk54 = lbl_801EED50.unk33;
    data->gameData.unk55 = lbl_801EED50.unk34;
    data->gameData.unk84 = lbl_801EED50.unk2C;
    data->gameData.unk58 = lbl_801EED50.unk6;
    data->gameData.unk5A = lbl_801EED50.unk4;
    data->gameData.unk70 = lbl_801EED50.unk8;
    data->gameData.unk5C = lbl_801EED50.unkE;
    data->gameData.unk5E = lbl_801EED50.unkC;
    data->gameData.unk74 = lbl_801EED50.unk10;
    data->gameData.unk60 = lbl_801EED50.unk16;
    data->gameData.unk62 = lbl_801EED50.unk14;
    data->gameData.unk78 = lbl_801EED50.unk18;
    data->gameData.unk64 = lbl_801EED50.unk1E;
    data->gameData.unk66 = lbl_801EED50.unk1C;
    data->gameData.unk7C = lbl_801EED50.unk20;
    data->gameData.unk68 = lbl_801EED50.unk26;
    data->gameData.unk6A = lbl_801EED50.unk24;
    data->gameData.unk80 = lbl_801EED50.unk28;

    data->gameData.unk88 = lbl_802F1C04.unk2;
    data->gameData.unk8A = lbl_802F1C04.unk0;
    data->gameData.unk8C = lbl_802F1C04.unk4;

    for (i = 0; i < 6; i++)
        data->gameData.unkA4[i] = lbl_801EED88.unk1[i];
    data->gameData.unkAA = lbl_801EED88.unk0;
    data->gameData.unkAB = lbl_801EED88.unkC;
    data->gameData.unkA0 = lbl_801EED88.unk8;

    data->gameData.unk2AC = lbl_801EED98.unk48;
    data->gameData.unk2B0 = lbl_801EED98.unk4E;
    data->gameData.unk2B1 = lbl_801EED98.unk4F;
    data->gameData.unk2B2 = lbl_801EED98.unk50;
    data->gameData.unk2B3 = lbl_801EED98.unk4C;
    data->gameData.unk2B4 = lbl_801EED98.unk4D;

    data->gameData.unkAE = lbl_802F1BFC.unk0;
    data->gameData.unk2B8 = lbl_802F1BFC.unk4;

    data->gameData.unk2B5 = lbl_802F1BF4.unk0;
    data->gameData.unk2B6 = lbl_802F1BF4.unk1;
    data->gameData.unk2B7 = lbl_802F1BF4.unk4;
    data->gameData.unkAF = lbl_802F1BF0;
    data->gameData.unk2BC = lbl_802F1BE8.unk0;
    data->gameData.unk2BD = lbl_802F1BE8.unk4;
}

void u_load_gamedata(struct MemcardContents *data)
{
    int i;

    lbl_802F1C10.unk0 = data->gameData.unk44;
    lbl_802F1C10.unk1 = data->gameData.unk45;
    lbl_802F1C10.unk2 = data->gameData.unk46;
    lbl_802F1C10.unk3 = data->gameData.unk47;

    lbl_802F1C10.unk4[0] = data->gameData.unk48;
    lbl_802F1C10.unk4[1] = data->gameData.unk49;
    lbl_802F1C10.unk4[2] = data->gameData.unk4A;
    lbl_802F1C10.unk4[3] = data->gameData.unk4B;

    g_unlockFlags = data->gameData.unk2BF;
    lbl_802F1C0C = data->gameData.unk4F;

    lbl_801EED50.unk0 = data->gameData.unk50;
    lbl_801EED50.unk30 = data->gameData.unk51;
    lbl_801EED50.unk31 = data->gameData.unk52;
    lbl_801EED50.unk32 = data->gameData.unk53;
    lbl_801EED50.unk33 = data->gameData.unk54;
    lbl_801EED50.unk34 = data->gameData.unk55;
    lbl_801EED50.unk2C = data->gameData.unk84;
    lbl_801EED50.unk6 = data->gameData.unk58;
    lbl_801EED50.unk4 = data->gameData.unk5A;
    lbl_801EED50.unk8 = data->gameData.unk70;
    lbl_801EED50.unkE = data->gameData.unk5C;
    lbl_801EED50.unkC = data->gameData.unk5E;
    lbl_801EED50.unk10 = data->gameData.unk74;
    lbl_801EED50.unk16 = data->gameData.unk60;
    lbl_801EED50.unk14 = data->gameData.unk62;
    lbl_801EED50.unk18 = data->gameData.unk78;
    lbl_801EED50.unk1E = data->gameData.unk64;
    lbl_801EED50.unk1C = data->gameData.unk66;
    lbl_801EED50.unk20 = data->gameData.unk7C;
    lbl_801EED50.unk26 = data->gameData.unk68;
    lbl_801EED50.unk24 = data->gameData.unk6A;
    lbl_801EED50.unk28 = data->gameData.unk80;

    lbl_802F1C04.unk2 = data->gameData.unk88;
    lbl_802F1C04.unk0 = data->gameData.unk8A;
    lbl_802F1C04.unk4 = data->gameData.unk8C;

    for (i = 0; i < 6; i++)
        lbl_801EED88.unk1[i] = data->gameData.unkA4[i];
    lbl_801EED88.unk0 = data->gameData.unkAA;
    lbl_801EED88.unkC = data->gameData.unkAB;
    lbl_801EED88.unk8 = data->gameData.unkA0;

    lbl_801EED98.unk48 = data->gameData.unk2AC;
    lbl_801EED98.unk4E = data->gameData.unk2B0;
    lbl_801EED98.unk4F = data->gameData.unk2B1;
    lbl_801EED98.unk50 = data->gameData.unk2B2;
    lbl_801EED98.unk4C = data->gameData.unk2B3;
    lbl_801EED98.unk4D = data->gameData.unk2B4;

    lbl_802F1BFC.unk0 = data->gameData.unkAE;
    lbl_802F1BFC.unk4 = data->gameData.unk2B8;

    lbl_802F1BF4.unk0 = data->gameData.unk2B5;
    lbl_802F1BF4.unk1 = data->gameData.unk2B6;
    lbl_802F1BF4.unk4 = data->gameData.unk2B7;
    lbl_802F1BF0 = data->gameData.unkAF;
    lbl_802F1BE8.unk0 = data->gameData.unk2BC;
    lbl_802F1BE8.unk4 = data->gameData.unk2BD;
}
