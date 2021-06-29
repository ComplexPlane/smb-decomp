.include "macros.inc"

.section .text, "ax"  # 0x800065A0 - 0x8010F860

.global SetExiInterruptMask
SetExiInterruptMask:
/* 800C3F5C 000BFE7C  7C 08 02 A6 */	mflr r0
/* 800C3F60 000BFE80  3C A0 80 2C */	lis r5, Ecb@ha
/* 800C3F64 000BFE84  90 01 00 04 */	stw r0, 4(r1)
/* 800C3F68 000BFE88  2C 03 00 01 */	cmpwi r3, 1
/* 800C3F6C 000BFE8C  38 A5 6C 28 */	addi r5, r5, Ecb@l
/* 800C3F70 000BFE90  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C3F74 000BFE94  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800C3F78 000BFE98  3B E4 00 00 */	addi r31, r4, 0
/* 800C3F7C 000BFE9C  38 85 00 70 */	addi r4, r5, 0x70
/* 800C3F80 000BFEA0  41 82 00 5C */	beq lbl_800C3FDC
/* 800C3F84 000BFEA4  40 80 00 10 */	bge lbl_800C3F94
/* 800C3F88 000BFEA8  2C 03 00 00 */	cmpwi r3, 0
/* 800C3F8C 000BFEAC  40 80 00 14 */	bge lbl_800C3FA0
/* 800C3F90 000BFEB0  48 00 00 AC */	b lbl_800C403C
lbl_800C3F94:
/* 800C3F94 000BFEB4  2C 03 00 03 */	cmpwi r3, 3
/* 800C3F98 000BFEB8  40 80 00 A4 */	bge lbl_800C403C
/* 800C3F9C 000BFEBC  48 00 00 70 */	b lbl_800C400C
lbl_800C3FA0:
/* 800C3FA0 000BFEC0  80 1F 00 00 */	lwz r0, 0(r31)
/* 800C3FA4 000BFEC4  28 00 00 00 */	cmplwi r0, 0
/* 800C3FA8 000BFEC8  40 82 00 10 */	bne lbl_800C3FB8
/* 800C3FAC 000BFECC  80 04 00 00 */	lwz r0, 0(r4)
/* 800C3FB0 000BFED0  28 00 00 00 */	cmplwi r0, 0
/* 800C3FB4 000BFED4  41 82 00 10 */	beq lbl_800C3FC4
lbl_800C3FB8:
/* 800C3FB8 000BFED8  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 800C3FBC 000BFEDC  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 800C3FC0 000BFEE0  41 82 00 10 */	beq lbl_800C3FD0
lbl_800C3FC4:
/* 800C3FC4 000BFEE4  3C 60 00 41 */	lis r3, 0x41
/* 800C3FC8 000BFEE8  48 00 24 95 */	bl __OSMaskInterrupts
/* 800C3FCC 000BFEEC  48 00 00 70 */	b lbl_800C403C
lbl_800C3FD0:
/* 800C3FD0 000BFEF0  3C 60 00 41 */	lis r3, 0x41
/* 800C3FD4 000BFEF4  48 00 25 11 */	bl __OSUnmaskInterrupts
/* 800C3FD8 000BFEF8  48 00 00 64 */	b lbl_800C403C
lbl_800C3FDC:
/* 800C3FDC 000BFEFC  80 1F 00 00 */	lwz r0, 0(r31)
/* 800C3FE0 000BFF00  28 00 00 00 */	cmplwi r0, 0
/* 800C3FE4 000BFF04  41 82 00 10 */	beq lbl_800C3FF4
/* 800C3FE8 000BFF08  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 800C3FEC 000BFF0C  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 800C3FF0 000BFF10  41 82 00 10 */	beq lbl_800C4000
lbl_800C3FF4:
/* 800C3FF4 000BFF14  3C 60 00 08 */	lis r3, 8
/* 800C3FF8 000BFF18  48 00 24 65 */	bl __OSMaskInterrupts
/* 800C3FFC 000BFF1C  48 00 00 40 */	b lbl_800C403C
lbl_800C4000:
/* 800C4000 000BFF20  3C 60 00 08 */	lis r3, 8
/* 800C4004 000BFF24  48 00 24 E1 */	bl __OSUnmaskInterrupts
/* 800C4008 000BFF28  48 00 00 34 */	b lbl_800C403C
lbl_800C400C:
/* 800C400C 000BFF2C  38 60 00 19 */	li r3, 0x19
/* 800C4010 000BFF30  48 00 21 15 */	bl __OSGetInterruptHandler
/* 800C4014 000BFF34  28 03 00 00 */	cmplwi r3, 0
/* 800C4018 000BFF38  41 82 00 10 */	beq lbl_800C4028
/* 800C401C 000BFF3C  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 800C4020 000BFF40  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 800C4024 000BFF44  41 82 00 10 */	beq lbl_800C4034
lbl_800C4028:
/* 800C4028 000BFF48  38 60 00 40 */	li r3, 0x40
/* 800C402C 000BFF4C  48 00 24 31 */	bl __OSMaskInterrupts
/* 800C4030 000BFF50  48 00 00 0C */	b lbl_800C403C
lbl_800C4034:
/* 800C4034 000BFF54  38 60 00 40 */	li r3, 0x40
/* 800C4038 000BFF58  48 00 24 AD */	bl __OSUnmaskInterrupts
lbl_800C403C:
/* 800C403C 000BFF5C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C4040 000BFF60  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800C4044 000BFF64  38 21 00 18 */	addi r1, r1, 0x18
/* 800C4048 000BFF68  7C 08 03 A6 */	mtlr r0
/* 800C404C 000BFF6C  4E 80 00 20 */	blr 