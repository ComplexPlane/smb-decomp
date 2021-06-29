.include "macros.inc"

.section .text, "ax"  # 0x800065A0 - 0x8010F860

.global __CARDGetDirBlock
__CARDGetDirBlock:
/* 800D7DA0 000D3CC0  80 63 00 84 */	lwz r3, 0x84(r3)
/* 800D7DA4 000D3CC4  4E 80 00 20 */	blr 

.global WriteCallback_2
WriteCallback_2:
/* 800D7DA8 000D3CC8  7C 08 02 A6 */	mflr r0
/* 800D7DAC 000D3CCC  90 01 00 04 */	stw r0, 4(r1)
/* 800D7DB0 000D3CD0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800D7DB4 000D3CD4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800D7DB8 000D3CD8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800D7DBC 000D3CDC  7C 9E 23 79 */	or. r30, r4, r4
/* 800D7DC0 000D3CE0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800D7DC4 000D3CE4  3B A3 00 00 */	addi r29, r3, 0
/* 800D7DC8 000D3CE8  1C BD 01 08 */	mulli r5, r29, 0x108
/* 800D7DCC 000D3CEC  3C 60 80 2C */	lis r3, __CARDBlock@ha
/* 800D7DD0 000D3CF0  38 03 7C 60 */	addi r0, r3, __CARDBlock@l
/* 800D7DD4 000D3CF4  7F E0 2A 14 */	add r31, r0, r5
/* 800D7DD8 000D3CF8  41 80 00 44 */	blt lbl_800D7E1C
/* 800D7DDC 000D3CFC  80 7F 00 80 */	lwz r3, 0x80(r31)
/* 800D7DE0 000D3D00  80 1F 00 84 */	lwz r0, 0x84(r31)
/* 800D7DE4 000D3D04  38 83 20 00 */	addi r4, r3, 0x2000
/* 800D7DE8 000D3D08  7C 00 20 40 */	cmplw r0, r4
/* 800D7DEC 000D3D0C  38 03 40 00 */	addi r0, r3, 0x4000
/* 800D7DF0 000D3D10  40 82 00 18 */	bne lbl_800D7E08
/* 800D7DF4 000D3D14  90 1F 00 84 */	stw r0, 0x84(r31)
/* 800D7DF8 000D3D18  7C 03 03 78 */	mr r3, r0
/* 800D7DFC 000D3D1C  38 A0 20 00 */	li r5, 0x2000
/* 800D7E00 000D3D20  4B F2 B6 15 */	bl memcpy
/* 800D7E04 000D3D24  48 00 00 18 */	b lbl_800D7E1C
lbl_800D7E08:
/* 800D7E08 000D3D28  90 9F 00 84 */	stw r4, 0x84(r31)
/* 800D7E0C 000D3D2C  38 64 00 00 */	addi r3, r4, 0
/* 800D7E10 000D3D30  7C 04 03 78 */	mr r4, r0
/* 800D7E14 000D3D34  38 A0 20 00 */	li r5, 0x2000
/* 800D7E18 000D3D38  4B F2 B5 FD */	bl memcpy
lbl_800D7E1C:
/* 800D7E1C 000D3D3C  80 1F 00 D0 */	lwz r0, 0xd0(r31)
/* 800D7E20 000D3D40  28 00 00 00 */	cmplwi r0, 0
/* 800D7E24 000D3D44  40 82 00 10 */	bne lbl_800D7E34
/* 800D7E28 000D3D48  38 7F 00 00 */	addi r3, r31, 0
/* 800D7E2C 000D3D4C  38 9E 00 00 */	addi r4, r30, 0
/* 800D7E30 000D3D50  4B FF E4 51 */	bl __CARDPutControlBlock
lbl_800D7E34:
/* 800D7E34 000D3D54  80 1F 00 D8 */	lwz r0, 0xd8(r31)
/* 800D7E38 000D3D58  28 00 00 00 */	cmplwi r0, 0
/* 800D7E3C 000D3D5C  7C 0C 03 78 */	mr r12, r0
/* 800D7E40 000D3D60  41 82 00 1C */	beq lbl_800D7E5C
/* 800D7E44 000D3D64  38 00 00 00 */	li r0, 0
/* 800D7E48 000D3D68  7D 88 03 A6 */	mtlr r12
/* 800D7E4C 000D3D6C  90 1F 00 D8 */	stw r0, 0xd8(r31)
/* 800D7E50 000D3D70  38 7D 00 00 */	addi r3, r29, 0
/* 800D7E54 000D3D74  38 9E 00 00 */	addi r4, r30, 0
/* 800D7E58 000D3D78  4E 80 00 21 */	blrl 
lbl_800D7E5C:
/* 800D7E5C 000D3D7C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800D7E60 000D3D80  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800D7E64 000D3D84  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800D7E68 000D3D88  7C 08 03 A6 */	mtlr r0
/* 800D7E6C 000D3D8C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800D7E70 000D3D90  38 21 00 20 */	addi r1, r1, 0x20
/* 800D7E74 000D3D94  4E 80 00 20 */	blr 

.global EraseCallback_2
EraseCallback_2:
/* 800D7E78 000D3D98  7C 08 02 A6 */	mflr r0
/* 800D7E7C 000D3D9C  90 01 00 04 */	stw r0, 4(r1)
/* 800D7E80 000D3DA0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800D7E84 000D3DA4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800D7E88 000D3DA8  3B E3 00 00 */	addi r31, r3, 0
/* 800D7E8C 000D3DAC  3C 60 80 2C */	lis r3, __CARDBlock@ha
/* 800D7E90 000D3DB0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800D7E94 000D3DB4  1C BF 01 08 */	mulli r5, r31, 0x108
/* 800D7E98 000D3DB8  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800D7E9C 000D3DBC  38 03 7C 60 */	addi r0, r3, __CARDBlock@l
/* 800D7EA0 000D3DC0  7C 9D 23 79 */	or. r29, r4, r4
/* 800D7EA4 000D3DC4  7F C0 2A 14 */	add r30, r0, r5
/* 800D7EA8 000D3DC8  41 80 00 3C */	blt lbl_800D7EE4
/* 800D7EAC 000D3DCC  80 BE 00 84 */	lwz r5, 0x84(r30)
/* 800D7EB0 000D3DD0  3C 60 80 0D */	lis r3, WriteCallback_2@ha
/* 800D7EB4 000D3DD4  80 1E 00 80 */	lwz r0, 0x80(r30)
/* 800D7EB8 000D3DD8  38 E3 7D A8 */	addi r7, r3, WriteCallback_2@l
/* 800D7EBC 000D3DDC  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 800D7EC0 000D3DE0  7C 00 28 50 */	subf r0, r0, r5
/* 800D7EC4 000D3DE4  54 00 9B 7E */	srwi r0, r0, 0xd
/* 800D7EC8 000D3DE8  7C 83 01 D6 */	mullw r4, r3, r0
/* 800D7ECC 000D3DEC  38 C5 00 00 */	addi r6, r5, 0
/* 800D7ED0 000D3DF0  38 7F 00 00 */	addi r3, r31, 0
/* 800D7ED4 000D3DF4  38 A0 20 00 */	li r5, 0x2000
/* 800D7ED8 000D3DF8  4B FF FA 61 */	bl __CARDWrite
/* 800D7EDC 000D3DFC  7C 7D 1B 79 */	or. r29, r3, r3
/* 800D7EE0 000D3E00  40 80 00 44 */	bge lbl_800D7F24
lbl_800D7EE4:
/* 800D7EE4 000D3E04  80 1E 00 D0 */	lwz r0, 0xd0(r30)
/* 800D7EE8 000D3E08  28 00 00 00 */	cmplwi r0, 0
/* 800D7EEC 000D3E0C  40 82 00 10 */	bne lbl_800D7EFC
/* 800D7EF0 000D3E10  38 7E 00 00 */	addi r3, r30, 0
/* 800D7EF4 000D3E14  38 9D 00 00 */	addi r4, r29, 0
/* 800D7EF8 000D3E18  4B FF E3 89 */	bl __CARDPutControlBlock
lbl_800D7EFC:
/* 800D7EFC 000D3E1C  80 1E 00 D8 */	lwz r0, 0xd8(r30)
/* 800D7F00 000D3E20  28 00 00 00 */	cmplwi r0, 0
/* 800D7F04 000D3E24  7C 0C 03 78 */	mr r12, r0
/* 800D7F08 000D3E28  41 82 00 1C */	beq lbl_800D7F24
/* 800D7F0C 000D3E2C  38 00 00 00 */	li r0, 0
/* 800D7F10 000D3E30  7D 88 03 A6 */	mtlr r12
/* 800D7F14 000D3E34  90 1E 00 D8 */	stw r0, 0xd8(r30)
/* 800D7F18 000D3E38  38 7F 00 00 */	addi r3, r31, 0
/* 800D7F1C 000D3E3C  38 9D 00 00 */	addi r4, r29, 0
/* 800D7F20 000D3E40  4E 80 00 21 */	blrl 
lbl_800D7F24:
/* 800D7F24 000D3E44  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800D7F28 000D3E48  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800D7F2C 000D3E4C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800D7F30 000D3E50  7C 08 03 A6 */	mtlr r0
/* 800D7F34 000D3E54  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800D7F38 000D3E58  38 21 00 28 */	addi r1, r1, 0x28
/* 800D7F3C 000D3E5C  4E 80 00 20 */	blr 

.global __CARDUpdateDir
__CARDUpdateDir:
/* 800D7F40 000D3E60  7C 08 02 A6 */	mflr r0
/* 800D7F44 000D3E64  90 01 00 04 */	stw r0, 4(r1)
/* 800D7F48 000D3E68  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800D7F4C 000D3E6C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800D7F50 000D3E70  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800D7F54 000D3E74  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800D7F58 000D3E78  3B A4 00 00 */	addi r29, r4, 0
/* 800D7F5C 000D3E7C  93 81 00 18 */	stw r28, 0x18(r1)
/* 800D7F60 000D3E80  3B 83 00 00 */	addi r28, r3, 0
/* 800D7F64 000D3E84  1C BC 01 08 */	mulli r5, r28, 0x108
/* 800D7F68 000D3E88  3C 60 80 2C */	lis r3, __CARDBlock@ha
/* 800D7F6C 000D3E8C  38 03 7C 60 */	addi r0, r3, __CARDBlock@l
/* 800D7F70 000D3E90  7F C0 2A 14 */	add r30, r0, r5
/* 800D7F74 000D3E94  80 1E 00 00 */	lwz r0, 0(r30)
/* 800D7F78 000D3E98  2C 00 00 00 */	cmpwi r0, 0
/* 800D7F7C 000D3E9C  40 82 00 0C */	bne lbl_800D7F88
/* 800D7F80 000D3EA0  38 60 FF FD */	li r3, -3
/* 800D7F84 000D3EA4  48 00 00 60 */	b lbl_800D7FE4
lbl_800D7F88:
/* 800D7F88 000D3EA8  83 FE 00 84 */	lwz r31, 0x84(r30)
/* 800D7F8C 000D3EAC  38 80 1F FC */	li r4, 0x1ffc
/* 800D7F90 000D3EB0  A8 BF 1F FA */	lha r5, 0x1ffa(r31)
/* 800D7F94 000D3EB4  38 DF 1F C0 */	addi r6, r31, 0x1fc0
/* 800D7F98 000D3EB8  38 7F 00 00 */	addi r3, r31, 0
/* 800D7F9C 000D3EBC  38 05 00 01 */	addi r0, r5, 1
/* 800D7FA0 000D3EC0  B0 1F 1F FA */	sth r0, 0x1ffa(r31)
/* 800D7FA4 000D3EC4  38 A6 00 3C */	addi r5, r6, 0x3c
/* 800D7FA8 000D3EC8  38 C6 00 3E */	addi r6, r6, 0x3e
/* 800D7FAC 000D3ECC  48 00 00 59 */	bl __CARDUpdateSum
/* 800D7FB0 000D3ED0  38 7F 00 00 */	addi r3, r31, 0
/* 800D7FB4 000D3ED4  38 80 20 00 */	li r4, 0x2000
/* 800D7FB8 000D3ED8  4B FE AF DD */	bl DCStoreRange
/* 800D7FBC 000D3EDC  93 BE 00 D8 */	stw r29, 0xd8(r30)
/* 800D7FC0 000D3EE0  3C 60 80 0D */	lis r3, EraseCallback_2@ha
/* 800D7FC4 000D3EE4  38 A3 7E 78 */	addi r5, r3, EraseCallback_2@l
/* 800D7FC8 000D3EE8  80 1E 00 80 */	lwz r0, 0x80(r30)
/* 800D7FCC 000D3EEC  7F 83 E3 78 */	mr r3, r28
/* 800D7FD0 000D3EF0  80 9E 00 0C */	lwz r4, 0xc(r30)
/* 800D7FD4 000D3EF4  7C 00 F8 50 */	subf r0, r0, r31
/* 800D7FD8 000D3EF8  54 00 9B 7E */	srwi r0, r0, 0xd
/* 800D7FDC 000D3EFC  7C 84 01 D6 */	mullw r4, r4, r0
/* 800D7FE0 000D3F00  4B FF E0 69 */	bl __CARDEraseSector
lbl_800D7FE4:
/* 800D7FE4 000D3F04  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800D7FE8 000D3F08  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800D7FEC 000D3F0C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800D7FF0 000D3F10  7C 08 03 A6 */	mtlr r0
/* 800D7FF4 000D3F14  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800D7FF8 000D3F18  83 81 00 18 */	lwz r28, 0x18(r1)
/* 800D7FFC 000D3F1C  38 21 00 28 */	addi r1, r1, 0x28
/* 800D8000 000D3F20  4E 80 00 20 */	blr 