.include "macros.inc"

.section .text, "ax"  # 0x800065A0 - 0x8010F860

.global __CARDGetFatBlock
__CARDGetFatBlock:
/* 800D799C 000D38BC  80 63 00 88 */	lwz r3, 0x88(r3)
/* 800D79A0 000D38C0  4E 80 00 20 */	blr

.global WriteCallback
WriteCallback:
/* 800D79A4 000D38C4  7C 08 02 A6 */	mflr r0
/* 800D79A8 000D38C8  90 01 00 04 */	stw r0, 4(r1)
/* 800D79AC 000D38CC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800D79B0 000D38D0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800D79B4 000D38D4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800D79B8 000D38D8  7C 9E 23 79 */	or. r30, r4, r4
/* 800D79BC 000D38DC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800D79C0 000D38E0  3B A3 00 00 */	addi r29, r3, 0
/* 800D79C4 000D38E4  1C BD 01 08 */	mulli r5, r29, 0x108
/* 800D79C8 000D38E8  3C 60 80 2C */	lis r3, __CARDBlock@ha
/* 800D79CC 000D38EC  38 03 7C 60 */	addi r0, r3, __CARDBlock@l
/* 800D79D0 000D38F0  7F E0 2A 14 */	add r31, r0, r5
/* 800D79D4 000D38F4  41 80 00 48 */	blt lbl_800D7A1C
/* 800D79D8 000D38F8  80 7F 00 80 */	lwz r3, 0x80(r31)
/* 800D79DC 000D38FC  80 1F 00 88 */	lwz r0, 0x88(r31)
/* 800D79E0 000D3900  38 83 60 00 */	addi r4, r3, 0x6000
/* 800D79E4 000D3904  7C 00 20 40 */	cmplw r0, r4
/* 800D79E8 000D3908  3C A3 00 01 */	addis r5, r3, 1
/* 800D79EC 000D390C  38 A5 80 00 */	addi r5, r5, -32768
/* 800D79F0 000D3910  40 82 00 18 */	bne lbl_800D7A08
/* 800D79F4 000D3914  90 BF 00 88 */	stw r5, 0x88(r31)
/* 800D79F8 000D3918  38 65 00 00 */	addi r3, r5, 0
/* 800D79FC 000D391C  38 A0 20 00 */	li r5, 0x2000
/* 800D7A00 000D3920  4B F2 BA 15 */	bl memcpy
/* 800D7A04 000D3924  48 00 00 18 */	b lbl_800D7A1C
lbl_800D7A08:
/* 800D7A08 000D3928  90 9F 00 88 */	stw r4, 0x88(r31)
/* 800D7A0C 000D392C  38 64 00 00 */	addi r3, r4, 0
/* 800D7A10 000D3930  38 85 00 00 */	addi r4, r5, 0
/* 800D7A14 000D3934  38 A0 20 00 */	li r5, 0x2000
/* 800D7A18 000D3938  4B F2 B9 FD */	bl memcpy
lbl_800D7A1C:
/* 800D7A1C 000D393C  80 1F 00 D0 */	lwz r0, 0xd0(r31)
/* 800D7A20 000D3940  28 00 00 00 */	cmplwi r0, 0
/* 800D7A24 000D3944  40 82 00 10 */	bne lbl_800D7A34
/* 800D7A28 000D3948  38 7F 00 00 */	addi r3, r31, 0
/* 800D7A2C 000D394C  38 9E 00 00 */	addi r4, r30, 0
/* 800D7A30 000D3950  4B FF E8 51 */	bl __CARDPutControlBlock
lbl_800D7A34:
/* 800D7A34 000D3954  80 1F 00 D8 */	lwz r0, 0xd8(r31)
/* 800D7A38 000D3958  28 00 00 00 */	cmplwi r0, 0
/* 800D7A3C 000D395C  7C 0C 03 78 */	mr r12, r0
/* 800D7A40 000D3960  41 82 00 1C */	beq lbl_800D7A5C
/* 800D7A44 000D3964  38 00 00 00 */	li r0, 0
/* 800D7A48 000D3968  7D 88 03 A6 */	mtlr r12
/* 800D7A4C 000D396C  90 1F 00 D8 */	stw r0, 0xd8(r31)
/* 800D7A50 000D3970  38 7D 00 00 */	addi r3, r29, 0
/* 800D7A54 000D3974  38 9E 00 00 */	addi r4, r30, 0
/* 800D7A58 000D3978  4E 80 00 21 */	blrl
lbl_800D7A5C:
/* 800D7A5C 000D397C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800D7A60 000D3980  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800D7A64 000D3984  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800D7A68 000D3988  7C 08 03 A6 */	mtlr r0
/* 800D7A6C 000D398C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800D7A70 000D3990  38 21 00 20 */	addi r1, r1, 0x20
/* 800D7A74 000D3994  4E 80 00 20 */	blr

.global EraseCallback
EraseCallback:
/* 800D7A78 000D3998  7C 08 02 A6 */	mflr r0
/* 800D7A7C 000D399C  90 01 00 04 */	stw r0, 4(r1)
/* 800D7A80 000D39A0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800D7A84 000D39A4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800D7A88 000D39A8  3B E3 00 00 */	addi r31, r3, 0
/* 800D7A8C 000D39AC  3C 60 80 2C */	lis r3, __CARDBlock@ha
/* 800D7A90 000D39B0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800D7A94 000D39B4  1C BF 01 08 */	mulli r5, r31, 0x108
/* 800D7A98 000D39B8  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800D7A9C 000D39BC  38 03 7C 60 */	addi r0, r3, __CARDBlock@l
/* 800D7AA0 000D39C0  7C 9D 23 79 */	or. r29, r4, r4
/* 800D7AA4 000D39C4  7F C0 2A 14 */	add r30, r0, r5
/* 800D7AA8 000D39C8  41 80 00 3C */	blt lbl_800D7AE4
/* 800D7AAC 000D39CC  80 BE 00 88 */	lwz r5, 0x88(r30)
/* 800D7AB0 000D39D0  3C 60 80 0D */	lis r3, WriteCallback@ha
/* 800D7AB4 000D39D4  80 1E 00 80 */	lwz r0, 0x80(r30)
/* 800D7AB8 000D39D8  38 E3 79 A4 */	addi r7, r3, WriteCallback@l
/* 800D7ABC 000D39DC  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 800D7AC0 000D39E0  7C 00 28 50 */	subf r0, r0, r5
/* 800D7AC4 000D39E4  54 00 9B 7E */	srwi r0, r0, 0xd
/* 800D7AC8 000D39E8  7C 83 01 D6 */	mullw r4, r3, r0
/* 800D7ACC 000D39EC  38 C5 00 00 */	addi r6, r5, 0
/* 800D7AD0 000D39F0  38 7F 00 00 */	addi r3, r31, 0
/* 800D7AD4 000D39F4  38 A0 20 00 */	li r5, 0x2000
/* 800D7AD8 000D39F8  4B FF FE 61 */	bl __CARDWrite
/* 800D7ADC 000D39FC  7C 7D 1B 79 */	or. r29, r3, r3
/* 800D7AE0 000D3A00  40 80 00 44 */	bge lbl_800D7B24
lbl_800D7AE4:
/* 800D7AE4 000D3A04  80 1E 00 D0 */	lwz r0, 0xd0(r30)
/* 800D7AE8 000D3A08  28 00 00 00 */	cmplwi r0, 0
/* 800D7AEC 000D3A0C  40 82 00 10 */	bne lbl_800D7AFC
/* 800D7AF0 000D3A10  38 7E 00 00 */	addi r3, r30, 0
/* 800D7AF4 000D3A14  38 9D 00 00 */	addi r4, r29, 0
/* 800D7AF8 000D3A18  4B FF E7 89 */	bl __CARDPutControlBlock
lbl_800D7AFC:
/* 800D7AFC 000D3A1C  80 1E 00 D8 */	lwz r0, 0xd8(r30)
/* 800D7B00 000D3A20  28 00 00 00 */	cmplwi r0, 0
/* 800D7B04 000D3A24  7C 0C 03 78 */	mr r12, r0
/* 800D7B08 000D3A28  41 82 00 1C */	beq lbl_800D7B24
/* 800D7B0C 000D3A2C  38 00 00 00 */	li r0, 0
/* 800D7B10 000D3A30  7D 88 03 A6 */	mtlr r12
/* 800D7B14 000D3A34  90 1E 00 D8 */	stw r0, 0xd8(r30)
/* 800D7B18 000D3A38  38 7F 00 00 */	addi r3, r31, 0
/* 800D7B1C 000D3A3C  38 9D 00 00 */	addi r4, r29, 0
/* 800D7B20 000D3A40  4E 80 00 21 */	blrl
lbl_800D7B24:
/* 800D7B24 000D3A44  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800D7B28 000D3A48  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800D7B2C 000D3A4C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800D7B30 000D3A50  7C 08 03 A6 */	mtlr r0
/* 800D7B34 000D3A54  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800D7B38 000D3A58  38 21 00 28 */	addi r1, r1, 0x28
/* 800D7B3C 000D3A5C  4E 80 00 20 */	blr

.global __CARDAllocBlock
__CARDAllocBlock:
/* 800D7B40 000D3A60  7C 08 02 A6 */	mflr r0
/* 800D7B44 000D3A64  1C E3 01 08 */	mulli r7, r3, 0x108
/* 800D7B48 000D3A68  90 01 00 04 */	stw r0, 4(r1)
/* 800D7B4C 000D3A6C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800D7B50 000D3A70  3C C0 80 2C */	lis r6, __CARDBlock@ha
/* 800D7B54 000D3A74  38 06 7C 60 */	addi r0, r6, __CARDBlock@l
/* 800D7B58 000D3A78  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800D7B5C 000D3A7C  7D 20 3A 14 */	add r9, r0, r7
/* 800D7B60 000D3A80  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800D7B64 000D3A84  80 09 00 00 */	lwz r0, 0(r9)
/* 800D7B68 000D3A88  2C 00 00 00 */	cmpwi r0, 0
/* 800D7B6C 000D3A8C  40 82 00 0C */	bne lbl_800D7B78
/* 800D7B70 000D3A90  38 60 FF FD */	li r3, -3
/* 800D7B74 000D3A94  48 00 00 CC */	b lbl_800D7C40
lbl_800D7B78:
/* 800D7B78 000D3A98  81 09 00 88 */	lwz r8, 0x88(r9)
/* 800D7B7C 000D3A9C  A0 08 00 06 */	lhz r0, 6(r8)
/* 800D7B80 000D3AA0  7C 00 20 40 */	cmplw r0, r4
/* 800D7B84 000D3AA4  40 80 00 0C */	bge lbl_800D7B90
/* 800D7B88 000D3AA8  38 60 FF F7 */	li r3, -9
/* 800D7B8C 000D3AAC  48 00 00 B4 */	b lbl_800D7C40
lbl_800D7B90:
/* 800D7B90 000D3AB0  7C 04 00 50 */	subf r0, r4, r0
/* 800D7B94 000D3AB4  B0 08 00 06 */	sth r0, 6(r8)
/* 800D7B98 000D3AB8  3C C0 00 01 */	lis r6, 0x0000FFFF@ha
/* 800D7B9C 000D3ABC  39 86 FF FF */	addi r12, r6, 0x0000FFFF@l
/* 800D7BA0 000D3AC0  A1 68 00 08 */	lhz r11, 8(r8)
/* 800D7BA4 000D3AC4  38 0C 00 00 */	addi r0, r12, 0
/* 800D7BA8 000D3AC8  3B C0 00 00 */	li r30, 0
/* 800D7BAC 000D3ACC  48 00 00 7C */	b lbl_800D7C28
lbl_800D7BB0:
/* 800D7BB0 000D3AD0  A1 49 00 10 */	lhz r10, 0x10(r9)
/* 800D7BB4 000D3AD4  3B DE 00 01 */	addi r30, r30, 1
/* 800D7BB8 000D3AD8  57 C6 04 3E */	clrlwi r6, r30, 0x10
/* 800D7BBC 000D3ADC  38 EA FF FB */	addi r7, r10, -5
/* 800D7BC0 000D3AE0  7C 07 30 00 */	cmpw r7, r6
/* 800D7BC4 000D3AE4  40 80 00 0C */	bge lbl_800D7BD0
/* 800D7BC8 000D3AE8  38 60 FF FA */	li r3, -6
/* 800D7BCC 000D3AEC  48 00 00 74 */	b lbl_800D7C40
lbl_800D7BD0:
/* 800D7BD0 000D3AF0  39 6B 00 01 */	addi r11, r11, 1
/* 800D7BD4 000D3AF4  55 66 04 3E */	clrlwi r6, r11, 0x10
/* 800D7BD8 000D3AF8  28 06 00 05 */	cmplwi r6, 5
/* 800D7BDC 000D3AFC  41 80 00 0C */	blt lbl_800D7BE8
/* 800D7BE0 000D3B00  7C 06 50 40 */	cmplw r6, r10
/* 800D7BE4 000D3B04  41 80 00 08 */	blt lbl_800D7BEC
lbl_800D7BE8:
/* 800D7BE8 000D3B08  39 60 00 05 */	li r11, 5
lbl_800D7BEC:
/* 800D7BEC 000D3B0C  55 66 0B FC */	rlwinm r6, r11, 1, 0xf, 0x1e
/* 800D7BF0 000D3B10  7C E8 32 14 */	add r7, r8, r6
/* 800D7BF4 000D3B14  A0 C7 00 00 */	lhz r6, 0(r7)
/* 800D7BF8 000D3B18  28 06 00 00 */	cmplwi r6, 0
/* 800D7BFC 000D3B1C  40 82 00 2C */	bne lbl_800D7C28
/* 800D7C00 000D3B20  55 86 04 3E */	clrlwi r6, r12, 0x10
/* 800D7C04 000D3B24  28 06 FF FF */	cmplwi r6, 0xffff
/* 800D7C08 000D3B28  40 82 00 0C */	bne lbl_800D7C14
/* 800D7C0C 000D3B2C  7D 6C 5B 78 */	mr r12, r11
/* 800D7C10 000D3B30  48 00 00 0C */	b lbl_800D7C1C
lbl_800D7C14:
/* 800D7C14 000D3B34  57 E6 0B FC */	rlwinm r6, r31, 1, 0xf, 0x1e
/* 800D7C18 000D3B38  7D 68 33 2E */	sthx r11, r8, r6
lbl_800D7C1C:
/* 800D7C1C 000D3B3C  B0 07 00 00 */	sth r0, 0(r7)
/* 800D7C20 000D3B40  3B EB 00 00 */	addi r31, r11, 0
/* 800D7C24 000D3B44  38 84 FF FF */	addi r4, r4, -1
lbl_800D7C28:
/* 800D7C28 000D3B48  28 04 00 00 */	cmplwi r4, 0
/* 800D7C2C 000D3B4C  40 82 FF 84 */	bne lbl_800D7BB0
/* 800D7C30 000D3B50  B1 68 00 08 */	sth r11, 8(r8)
/* 800D7C34 000D3B54  7D 04 43 78 */	mr r4, r8
/* 800D7C38 000D3B58  B1 89 00 BE */	sth r12, 0xbe(r9)
/* 800D7C3C 000D3B5C  48 00 00 B9 */	bl __CARDUpdateFatBlock
lbl_800D7C40:
/* 800D7C40 000D3B60  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800D7C44 000D3B64  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800D7C48 000D3B68  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800D7C4C 000D3B6C  7C 08 03 A6 */	mtlr r0
/* 800D7C50 000D3B70  38 21 00 20 */	addi r1, r1, 0x20
/* 800D7C54 000D3B74  4E 80 00 20 */	blr

.global __CARDFreeBlock
__CARDFreeBlock:
/* 800D7C58 000D3B78  7C 08 02 A6 */	mflr r0
/* 800D7C5C 000D3B7C  1C E3 01 08 */	mulli r7, r3, 0x108
/* 800D7C60 000D3B80  90 01 00 04 */	stw r0, 4(r1)
/* 800D7C64 000D3B84  3C C0 80 2C */	lis r6, __CARDBlock@ha
/* 800D7C68 000D3B88  94 21 FF F8 */	stwu r1, -8(r1)
/* 800D7C6C 000D3B8C  38 06 7C 60 */	addi r0, r6, __CARDBlock@l
/* 800D7C70 000D3B90  7D 20 3A 14 */	add r9, r0, r7
/* 800D7C74 000D3B94  80 09 00 00 */	lwz r0, 0(r9)
/* 800D7C78 000D3B98  2C 00 00 00 */	cmpwi r0, 0
/* 800D7C7C 000D3B9C  40 82 00 0C */	bne lbl_800D7C88
/* 800D7C80 000D3BA0  38 60 FF FD */	li r3, -3
/* 800D7C84 000D3BA4  48 00 00 60 */	b lbl_800D7CE4
lbl_800D7C88:
/* 800D7C88 000D3BA8  81 09 00 88 */	lwz r8, 0x88(r9)
/* 800D7C8C 000D3BAC  38 E0 00 00 */	li r7, 0
/* 800D7C90 000D3BB0  48 00 00 40 */	b lbl_800D7CD0
lbl_800D7C94:
/* 800D7C94 000D3BB4  54 84 04 3E */	clrlwi r4, r4, 0x10
/* 800D7C98 000D3BB8  28 04 00 05 */	cmplwi r4, 5
/* 800D7C9C 000D3BBC  41 80 00 10 */	blt lbl_800D7CAC
/* 800D7CA0 000D3BC0  A0 09 00 10 */	lhz r0, 0x10(r9)
/* 800D7CA4 000D3BC4  7C 04 00 40 */	cmplw r4, r0
/* 800D7CA8 000D3BC8  41 80 00 0C */	blt lbl_800D7CB4
lbl_800D7CAC:
/* 800D7CAC 000D3BCC  38 60 FF FA */	li r3, -6
/* 800D7CB0 000D3BD0  48 00 00 34 */	b lbl_800D7CE4
lbl_800D7CB4:
/* 800D7CB4 000D3BD4  54 80 08 3C */	slwi r0, r4, 1
/* 800D7CB8 000D3BD8  7C C8 02 14 */	add r6, r8, r0
/* 800D7CBC 000D3BDC  A0 86 00 00 */	lhz r4, 0(r6)
/* 800D7CC0 000D3BE0  B0 E6 00 00 */	sth r7, 0(r6)
/* 800D7CC4 000D3BE4  A0 C8 00 06 */	lhz r6, 6(r8)
/* 800D7CC8 000D3BE8  38 06 00 01 */	addi r0, r6, 1
/* 800D7CCC 000D3BEC  B0 08 00 06 */	sth r0, 6(r8)
lbl_800D7CD0:
/* 800D7CD0 000D3BF0  54 80 04 3E */	clrlwi r0, r4, 0x10
/* 800D7CD4 000D3BF4  28 00 FF FF */	cmplwi r0, 0xffff
/* 800D7CD8 000D3BF8  40 82 FF BC */	bne lbl_800D7C94
/* 800D7CDC 000D3BFC  7D 04 43 78 */	mr r4, r8
/* 800D7CE0 000D3C00  48 00 00 15 */	bl __CARDUpdateFatBlock
lbl_800D7CE4:
/* 800D7CE4 000D3C04  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800D7CE8 000D3C08  38 21 00 08 */	addi r1, r1, 8
/* 800D7CEC 000D3C0C  7C 08 03 A6 */	mtlr r0
/* 800D7CF0 000D3C10  4E 80 00 20 */	blr

.global __CARDUpdateFatBlock
__CARDUpdateFatBlock:
/* 800D7CF4 000D3C14  7C 08 02 A6 */	mflr r0
/* 800D7CF8 000D3C18  90 01 00 04 */	stw r0, 4(r1)
/* 800D7CFC 000D3C1C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800D7D00 000D3C20  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800D7D04 000D3C24  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800D7D08 000D3C28  3B C5 00 00 */	addi r30, r5, 0
/* 800D7D0C 000D3C2C  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800D7D10 000D3C30  3B A4 00 00 */	addi r29, r4, 0
/* 800D7D14 000D3C34  38 BD 00 00 */	addi r5, r29, 0
/* 800D7D18 000D3C38  93 81 00 18 */	stw r28, 0x18(r1)
/* 800D7D1C 000D3C3C  3B 83 00 00 */	addi r28, r3, 0
/* 800D7D20 000D3C40  38 DD 00 02 */	addi r6, r29, 2
/* 800D7D24 000D3C44  A0 64 00 04 */	lhz r3, 4(r4)
/* 800D7D28 000D3C48  1C 9C 01 08 */	mulli r4, r28, 0x108
/* 800D7D2C 000D3C4C  38 03 00 01 */	addi r0, r3, 1
/* 800D7D30 000D3C50  3C 60 80 2C */	lis r3, __CARDBlock@ha
/* 800D7D34 000D3C54  B0 1D 00 04 */	sth r0, 4(r29)
/* 800D7D38 000D3C58  38 03 7C 60 */	addi r0, r3, __CARDBlock@l
/* 800D7D3C 000D3C5C  7F E0 22 14 */	add r31, r0, r4
/* 800D7D40 000D3C60  38 7D 00 04 */	addi r3, r29, 4
/* 800D7D44 000D3C64  38 80 1F FC */	li r4, 0x1ffc
/* 800D7D48 000D3C68  48 00 02 BD */	bl __CARDUpdateSum
/* 800D7D4C 000D3C6C  38 7D 00 00 */	addi r3, r29, 0
/* 800D7D50 000D3C70  38 80 20 00 */	li r4, 0x2000
/* 800D7D54 000D3C74  4B FE B2 41 */	bl DCStoreRange
/* 800D7D58 000D3C78  93 DF 00 D8 */	stw r30, 0xd8(r31)
/* 800D7D5C 000D3C7C  3C 60 80 0D */	lis r3, EraseCallback@ha
/* 800D7D60 000D3C80  38 A3 7A 78 */	addi r5, r3, EraseCallback@l
/* 800D7D64 000D3C84  80 1F 00 80 */	lwz r0, 0x80(r31)
/* 800D7D68 000D3C88  7F 83 E3 78 */	mr r3, r28
/* 800D7D6C 000D3C8C  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 800D7D70 000D3C90  7C 00 E8 50 */	subf r0, r0, r29
/* 800D7D74 000D3C94  54 00 9B 7E */	srwi r0, r0, 0xd
/* 800D7D78 000D3C98  7C 84 01 D6 */	mullw r4, r4, r0
/* 800D7D7C 000D3C9C  4B FF E2 CD */	bl __CARDEraseSector
/* 800D7D80 000D3CA0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800D7D84 000D3CA4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800D7D88 000D3CA8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800D7D8C 000D3CAC  7C 08 03 A6 */	mtlr r0
/* 800D7D90 000D3CB0  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800D7D94 000D3CB4  83 81 00 18 */	lwz r28, 0x18(r1)
/* 800D7D98 000D3CB8  38 21 00 28 */	addi r1, r1, 0x28
/* 800D7D9C 000D3CBC  4E 80 00 20 */	blr