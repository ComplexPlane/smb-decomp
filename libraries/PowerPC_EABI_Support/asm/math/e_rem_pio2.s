.include "macros.inc"

.section .text, "ax"  # 0x800065A0 - 0x8010F860

.global fabs__Fd
fabs__Fd:
/* 80106D80 00102CA0  FC 20 0A 10 */	fabs f1, f1
/* 80106D84 00102CA4  4E 80 00 20 */	blr

.global scalbn
scalbn:
/* 80106D88 00102CA8  7C 08 02 A6 */	mflr r0
/* 80106D8C 00102CAC  90 01 00 04 */	stw r0, 4(r1)
/* 80106D90 00102CB0  94 21 FF F8 */	stwu r1, -8(r1)
/* 80106D94 00102CB4  48 00 19 DD */	bl ldexp
/* 80106D98 00102CB8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80106D9C 00102CBC  38 21 00 08 */	addi r1, r1, 8
/* 80106DA0 00102CC0  7C 08 03 A6 */	mtlr r0
/* 80106DA4 00102CC4  4E 80 00 20 */	blr

.global __ieee754_rem_pio2
__ieee754_rem_pio2:
/* 80106DA8 00102CC8  7C 08 02 A6 */	mflr r0
/* 80106DAC 00102CCC  3C 80 3F E9 */	lis r4, 0x3FE921FB@ha
/* 80106DB0 00102CD0  90 01 00 04 */	stw r0, 4(r1)
/* 80106DB4 00102CD4  38 04 21 FB */	addi r0, r4, 0x3FE921FB@l
/* 80106DB8 00102CD8  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 80106DBC 00102CDC  93 E1 00 6C */	stw r31, 0x6c(r1)
/* 80106DC0 00102CE0  93 C1 00 68 */	stw r30, 0x68(r1)
/* 80106DC4 00102CE4  93 A1 00 64 */	stw r29, 0x64(r1)
/* 80106DC8 00102CE8  3B A3 00 00 */	addi r29, r3, 0
/* 80106DCC 00102CEC  D8 21 00 08 */	stfd f1, 8(r1)
/* 80106DD0 00102CF0  83 E1 00 08 */	lwz r31, 8(r1)
/* 80106DD4 00102CF4  57 FE 00 7E */	clrlwi r30, r31, 1
/* 80106DD8 00102CF8  7C 1E 00 00 */	cmpw r30, r0
/* 80106DDC 00102CFC  41 81 00 1C */	bgt lbl_80106DF8
/* 80106DE0 00102D00  C8 01 00 08 */	lfd f0, 8(r1)
/* 80106DE4 00102D04  38 60 00 00 */	li r3, 0
/* 80106DE8 00102D08  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80106DEC 00102D0C  C8 02 C2 B0 */	lfd f0, lbl_802F6AB0@sda21(r2)
/* 80106DF0 00102D10  D8 1D 00 08 */	stfd f0, 8(r29)
/* 80106DF4 00102D14  48 00 03 8C */	b lbl_80107180
lbl_80106DF8:
/* 80106DF8 00102D18  3C 60 40 03 */	lis r3, 0x4002D97C@ha
/* 80106DFC 00102D1C  38 03 D9 7C */	addi r0, r3, 0x4002D97C@l
/* 80106E00 00102D20  7C 1E 00 00 */	cmpw r30, r0
/* 80106E04 00102D24  40 80 01 0C */	bge lbl_80106F10
/* 80106E08 00102D28  2C 1F 00 00 */	cmpwi r31, 0
/* 80106E0C 00102D2C  40 81 00 84 */	ble lbl_80106E90
/* 80106E10 00102D30  C8 21 00 08 */	lfd f1, 8(r1)
/* 80106E14 00102D34  3C 1E C0 07 */	addis r0, r30, 0xc007
/* 80106E18 00102D38  C8 02 C2 B8 */	lfd f0, lbl_802F6AB8@sda21(r2)
/* 80106E1C 00102D3C  28 00 21 FB */	cmplwi r0, 0x21fb
/* 80106E20 00102D40  FC 01 00 28 */	fsub f0, f1, f0
/* 80106E24 00102D44  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80106E28 00102D48  41 82 00 2C */	beq lbl_80106E54
/* 80106E2C 00102D4C  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80106E30 00102D50  C8 42 C2 C0 */	lfd f2, lbl_802F6AC0@sda21(r2)
/* 80106E34 00102D54  FC 00 10 28 */	fsub f0, f0, f2
/* 80106E38 00102D58  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80106E3C 00102D5C  C8 21 00 38 */	lfd f1, 0x38(r1)
/* 80106E40 00102D60  C8 1D 00 00 */	lfd f0, 0(r29)
/* 80106E44 00102D64  FC 01 00 28 */	fsub f0, f1, f0
/* 80106E48 00102D68  FC 00 10 28 */	fsub f0, f0, f2
/* 80106E4C 00102D6C  D8 1D 00 08 */	stfd f0, 8(r29)
/* 80106E50 00102D70  48 00 00 38 */	b lbl_80106E88
lbl_80106E54:
/* 80106E54 00102D74  C8 21 00 38 */	lfd f1, 0x38(r1)
/* 80106E58 00102D78  C8 02 C2 C8 */	lfd f0, lbl_802F6AC8@sda21(r2)
/* 80106E5C 00102D7C  C8 42 C2 D0 */	lfd f2, lbl_802F6AD0@sda21(r2)
/* 80106E60 00102D80  FC 01 00 28 */	fsub f0, f1, f0
/* 80106E64 00102D84  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80106E68 00102D88  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80106E6C 00102D8C  FC 00 10 28 */	fsub f0, f0, f2
/* 80106E70 00102D90  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80106E74 00102D94  C8 21 00 38 */	lfd f1, 0x38(r1)
/* 80106E78 00102D98  C8 1D 00 00 */	lfd f0, 0(r29)
/* 80106E7C 00102D9C  FC 01 00 28 */	fsub f0, f1, f0
/* 80106E80 00102DA0  FC 00 10 28 */	fsub f0, f0, f2
/* 80106E84 00102DA4  D8 1D 00 08 */	stfd f0, 8(r29)
lbl_80106E88:
/* 80106E88 00102DA8  38 60 00 01 */	li r3, 1
/* 80106E8C 00102DAC  48 00 02 F4 */	b lbl_80107180
lbl_80106E90:
/* 80106E90 00102DB0  C8 22 C2 B8 */	lfd f1, lbl_802F6AB8@sda21(r2)
/* 80106E94 00102DB4  3C 1E C0 07 */	addis r0, r30, 0xc007
/* 80106E98 00102DB8  C8 01 00 08 */	lfd f0, 8(r1)
/* 80106E9C 00102DBC  28 00 21 FB */	cmplwi r0, 0x21fb
/* 80106EA0 00102DC0  FC 01 00 2A */	fadd f0, f1, f0
/* 80106EA4 00102DC4  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80106EA8 00102DC8  41 82 00 2C */	beq lbl_80106ED4
/* 80106EAC 00102DCC  C8 42 C2 C0 */	lfd f2, lbl_802F6AC0@sda21(r2)
/* 80106EB0 00102DD0  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80106EB4 00102DD4  FC 02 00 2A */	fadd f0, f2, f0
/* 80106EB8 00102DD8  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80106EBC 00102DDC  C8 21 00 38 */	lfd f1, 0x38(r1)
/* 80106EC0 00102DE0  C8 1D 00 00 */	lfd f0, 0(r29)
/* 80106EC4 00102DE4  FC 01 00 28 */	fsub f0, f1, f0
/* 80106EC8 00102DE8  FC 02 00 2A */	fadd f0, f2, f0
/* 80106ECC 00102DEC  D8 1D 00 08 */	stfd f0, 8(r29)
/* 80106ED0 00102DF0  48 00 00 38 */	b lbl_80106F08
lbl_80106ED4:
/* 80106ED4 00102DF4  C8 21 00 38 */	lfd f1, 0x38(r1)
/* 80106ED8 00102DF8  C8 02 C2 C8 */	lfd f0, lbl_802F6AC8@sda21(r2)
/* 80106EDC 00102DFC  C8 42 C2 D0 */	lfd f2, lbl_802F6AD0@sda21(r2)
/* 80106EE0 00102E00  FC 01 00 2A */	fadd f0, f1, f0
/* 80106EE4 00102E04  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80106EE8 00102E08  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80106EEC 00102E0C  FC 02 00 2A */	fadd f0, f2, f0
/* 80106EF0 00102E10  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80106EF4 00102E14  C8 21 00 38 */	lfd f1, 0x38(r1)
/* 80106EF8 00102E18  C8 1D 00 00 */	lfd f0, 0(r29)
/* 80106EFC 00102E1C  FC 01 00 28 */	fsub f0, f1, f0
/* 80106F00 00102E20  FC 02 00 2A */	fadd f0, f2, f0
/* 80106F04 00102E24  D8 1D 00 08 */	stfd f0, 8(r29)
lbl_80106F08:
/* 80106F08 00102E28  38 60 FF FF */	li r3, -1
/* 80106F0C 00102E2C  48 00 02 74 */	b lbl_80107180
lbl_80106F10:
/* 80106F10 00102E30  3C 60 41 39 */	lis r3, 0x413921FB@ha
/* 80106F14 00102E34  38 03 21 FB */	addi r0, r3, 0x413921FB@l
/* 80106F18 00102E38  7C 1E 00 00 */	cmpw r30, r0
/* 80106F1C 00102E3C  41 81 01 40 */	bgt lbl_8010705C
/* 80106F20 00102E40  C8 21 00 08 */	lfd f1, 8(r1)
/* 80106F24 00102E44  4B FF FE 5D */	bl fabs__Fd
/* 80106F28 00102E48  C8 42 C2 E0 */	lfd f2, lbl_802F6AE0@sda21(r2)
/* 80106F2C 00102E4C  3C 00 43 30 */	lis r0, 0x4330
/* 80106F30 00102E50  C8 02 C2 D8 */	lfd f0, lbl_802F6AD8@sda21(r2)
/* 80106F34 00102E54  C8 82 C3 00 */	lfd f4, lbl_802F6B00@sda21(r2)
/* 80106F38 00102E58  FC 62 00 7A */	fmadd f3, f2, f1, f0
/* 80106F3C 00102E5C  C8 42 C2 B8 */	lfd f2, lbl_802F6AB8@sda21(r2)
/* 80106F40 00102E60  C8 02 C2 C0 */	lfd f0, lbl_802F6AC0@sda21(r2)
/* 80106F44 00102E64  FC 60 18 1E */	fctiwz f3, f3
/* 80106F48 00102E68  D8 61 00 58 */	stfd f3, 0x58(r1)
/* 80106F4C 00102E6C  80 61 00 5C */	lwz r3, 0x5c(r1)
/* 80106F50 00102E70  6C 64 80 00 */	xoris r4, r3, 0x8000
/* 80106F54 00102E74  90 81 00 54 */	stw r4, 0x54(r1)
/* 80106F58 00102E78  2C 03 00 20 */	cmpwi r3, 0x20
/* 80106F5C 00102E7C  90 01 00 50 */	stw r0, 0x50(r1)
/* 80106F60 00102E80  C8 61 00 50 */	lfd f3, 0x50(r1)
/* 80106F64 00102E84  FC A3 20 28 */	fsub f5, f3, f4
/* 80106F68 00102E88  FC 82 09 7C */	fnmsub f4, f2, f5, f1
/* 80106F6C 00102E8C  FC 20 01 72 */	fmul f1, f0, f5
/* 80106F70 00102E90  40 80 00 2C */	bge lbl_80106F9C
/* 80106F74 00102E94  3C 80 80 17 */	lis r4, npio2_hw@ha
/* 80106F78 00102E98  38 84 21 78 */	addi r4, r4, npio2_hw@l
/* 80106F7C 00102E9C  54 60 10 3A */	slwi r0, r3, 2
/* 80106F80 00102EA0  7C 84 02 14 */	add r4, r4, r0
/* 80106F84 00102EA4  80 04 FF FC */	lwz r0, -4(r4)
/* 80106F88 00102EA8  7C 1E 00 00 */	cmpw r30, r0
/* 80106F8C 00102EAC  41 82 00 10 */	beq lbl_80106F9C
/* 80106F90 00102EB0  FC 04 08 28 */	fsub f0, f4, f1
/* 80106F94 00102EB4  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80106F98 00102EB8  48 00 00 88 */	b lbl_80107020
lbl_80106F9C:
/* 80106F9C 00102EBC  FC 04 08 28 */	fsub f0, f4, f1
/* 80106FA0 00102EC0  7F C4 A6 70 */	srawi r4, r30, 0x14
/* 80106FA4 00102EC4  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80106FA8 00102EC8  80 1D 00 00 */	lwz r0, 0(r29)
/* 80106FAC 00102ECC  54 00 65 7E */	rlwinm r0, r0, 0xc, 0x15, 0x1f
/* 80106FB0 00102ED0  7C 00 20 50 */	subf r0, r0, r4
/* 80106FB4 00102ED4  2C 00 00 10 */	cmpwi r0, 0x10
/* 80106FB8 00102ED8  40 81 00 68 */	ble lbl_80107020
/* 80106FBC 00102EDC  C8 02 C2 C8 */	lfd f0, lbl_802F6AC8@sda21(r2)
/* 80106FC0 00102EE0  FC 40 20 90 */	fmr f2, f4
/* 80106FC4 00102EE4  C8 22 C2 D0 */	lfd f1, lbl_802F6AD0@sda21(r2)
/* 80106FC8 00102EE8  FC 60 01 72 */	fmul f3, f0, f5
/* 80106FCC 00102EEC  FC 84 18 28 */	fsub f4, f4, f3
/* 80106FD0 00102EF0  FC 02 20 28 */	fsub f0, f2, f4
/* 80106FD4 00102EF4  FC 00 18 28 */	fsub f0, f0, f3
/* 80106FD8 00102EF8  FC 21 01 78 */	fmsub f1, f1, f5, f0
/* 80106FDC 00102EFC  FC 04 08 28 */	fsub f0, f4, f1
/* 80106FE0 00102F00  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80106FE4 00102F04  80 1D 00 00 */	lwz r0, 0(r29)
/* 80106FE8 00102F08  54 00 65 7E */	rlwinm r0, r0, 0xc, 0x15, 0x1f
/* 80106FEC 00102F0C  7C 00 20 50 */	subf r0, r0, r4
/* 80106FF0 00102F10  2C 00 00 31 */	cmpwi r0, 0x31
/* 80106FF4 00102F14  40 81 00 2C */	ble lbl_80107020
/* 80106FF8 00102F18  C8 02 C2 E8 */	lfd f0, lbl_802F6AE8@sda21(r2)
/* 80106FFC 00102F1C  FC 40 20 90 */	fmr f2, f4
/* 80107000 00102F20  C8 22 C2 F0 */	lfd f1, lbl_802F6AF0@sda21(r2)
/* 80107004 00102F24  FC 60 01 72 */	fmul f3, f0, f5
/* 80107008 00102F28  FC 84 18 28 */	fsub f4, f4, f3
/* 8010700C 00102F2C  FC 02 20 28 */	fsub f0, f2, f4
/* 80107010 00102F30  FC 00 18 28 */	fsub f0, f0, f3
/* 80107014 00102F34  FC 21 01 78 */	fmsub f1, f1, f5, f0
/* 80107018 00102F38  FC 04 08 28 */	fsub f0, f4, f1
/* 8010701C 00102F3C  D8 1D 00 00 */	stfd f0, 0(r29)
lbl_80107020:
/* 80107020 00102F40  C8 1D 00 00 */	lfd f0, 0(r29)
/* 80107024 00102F44  2C 1F 00 00 */	cmpwi r31, 0
/* 80107028 00102F48  FC 04 00 28 */	fsub f0, f4, f0
/* 8010702C 00102F4C  FC 00 08 28 */	fsub f0, f0, f1
/* 80107030 00102F50  D8 1D 00 08 */	stfd f0, 8(r29)
/* 80107034 00102F54  40 80 01 4C */	bge lbl_80107180
/* 80107038 00102F58  C8 1D 00 00 */	lfd f0, 0(r29)
/* 8010703C 00102F5C  7C 63 00 D0 */	neg r3, r3
/* 80107040 00102F60  FC 00 00 50 */	fneg f0, f0
/* 80107044 00102F64  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80107048 00102F68  C8 1D 00 08 */	lfd f0, 8(r29)
/* 8010704C 00102F6C  FC 00 00 50 */	fneg f0, f0
/* 80107050 00102F70  D8 1D 00 08 */	stfd f0, 8(r29)
/* 80107054 00102F74  48 00 01 2C */	b lbl_80107180
/* 80107058 00102F78  48 00 01 28 */	b lbl_80107180
lbl_8010705C:
/* 8010705C 00102F7C  3C 00 7F F0 */	lis r0, 0x7ff0
/* 80107060 00102F80  7C 1E 00 00 */	cmpw r30, r0
/* 80107064 00102F84  41 80 00 1C */	blt lbl_80107080
/* 80107068 00102F88  C8 01 00 08 */	lfd f0, 8(r1)
/* 8010706C 00102F8C  38 60 00 00 */	li r3, 0
/* 80107070 00102F90  FC 00 00 28 */	fsub f0, f0, f0
/* 80107074 00102F94  D8 1D 00 08 */	stfd f0, 8(r29)
/* 80107078 00102F98  D8 1D 00 00 */	stfd f0, 0(r29)
/* 8010707C 00102F9C  48 00 01 04 */	b lbl_80107180
lbl_80107080:
/* 80107080 00102FA0  7F C3 A6 70 */	srawi r3, r30, 0x14
/* 80107084 00102FA4  80 81 00 0C */	lwz r4, 0xc(r1)
/* 80107088 00102FA8  38 A3 FB EA */	addi r5, r3, -1046
/* 8010708C 00102FAC  C8 22 C3 00 */	lfd f1, lbl_802F6B00@sda21(r2)
/* 80107090 00102FB0  54 A0 A0 16 */	slwi r0, r5, 0x14
/* 80107094 00102FB4  90 81 00 3C */	stw r4, 0x3c(r1)
/* 80107098 00102FB8  7C 00 F0 50 */	subf r0, r0, r30
/* 8010709C 00102FBC  90 01 00 38 */	stw r0, 0x38(r1)
/* 801070A0 00102FC0  3C 60 43 30 */	lis r3, 0x4330
/* 801070A4 00102FC4  38 81 00 38 */	addi r4, r1, 0x38
/* 801070A8 00102FC8  C8 61 00 38 */	lfd f3, 0x38(r1)
/* 801070AC 00102FCC  38 C0 00 03 */	li r6, 3
/* 801070B0 00102FD0  FC 00 18 1E */	fctiwz f0, f3
/* 801070B4 00102FD4  D8 01 00 50 */	stfd f0, 0x50(r1)
/* 801070B8 00102FD8  80 01 00 54 */	lwz r0, 0x54(r1)
/* 801070BC 00102FDC  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 801070C0 00102FE0  90 01 00 5C */	stw r0, 0x5c(r1)
/* 801070C4 00102FE4  90 61 00 58 */	stw r3, 0x58(r1)
/* 801070C8 00102FE8  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 801070CC 00102FEC  FC 00 08 28 */	fsub f0, f0, f1
/* 801070D0 00102FF0  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 801070D4 00102FF4  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 801070D8 00102FF8  C8 42 C2 F8 */	lfd f2, lbl_802F6AF8@sda21(r2)
/* 801070DC 00102FFC  FC 03 00 28 */	fsub f0, f3, f0
/* 801070E0 00103000  FC 02 00 32 */	fmul f0, f2, f0
/* 801070E4 00103004  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 801070E8 00103008  C8 61 00 38 */	lfd f3, 0x38(r1)
/* 801070EC 0010300C  FC 00 18 1E */	fctiwz f0, f3
/* 801070F0 00103010  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 801070F4 00103014  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 801070F8 00103018  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 801070FC 0010301C  90 01 00 44 */	stw r0, 0x44(r1)
/* 80107100 00103020  90 61 00 40 */	stw r3, 0x40(r1)
/* 80107104 00103024  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 80107108 00103028  FC 00 08 28 */	fsub f0, f0, f1
/* 8010710C 0010302C  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 80107110 00103030  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 80107114 00103034  C8 22 C2 B0 */	lfd f1, lbl_802F6AB0@sda21(r2)
/* 80107118 00103038  FC 03 00 28 */	fsub f0, f3, f0
/* 8010711C 0010303C  FC 02 00 32 */	fmul f0, f2, f0
/* 80107120 00103040  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80107124 00103044  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80107128 00103048  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 8010712C 0010304C  48 00 00 0C */	b lbl_80107138
lbl_80107130:
/* 80107130 00103050  38 84 FF F8 */	addi r4, r4, -8
/* 80107134 00103054  38 C6 FF FF */	addi r6, r6, -1
lbl_80107138:
/* 80107138 00103058  C8 04 FF F8 */	lfd f0, -8(r4)
/* 8010713C 0010305C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80107140 00103060  41 82 FF F0 */	beq lbl_80107130
/* 80107144 00103064  3C 60 80 17 */	lis r3, two_over_pi@ha
/* 80107148 00103068  39 03 20 70 */	addi r8, r3, two_over_pi@l
/* 8010714C 0010306C  38 9D 00 00 */	addi r4, r29, 0
/* 80107150 00103070  38 61 00 20 */	addi r3, r1, 0x20
/* 80107154 00103074  38 E0 00 02 */	li r7, 2
/* 80107158 00103078  48 00 01 BD */	bl __kernel_rem_pio2
/* 8010715C 0010307C  2C 1F 00 00 */	cmpwi r31, 0
/* 80107160 00103080  40 80 00 20 */	bge lbl_80107180
/* 80107164 00103084  C8 1D 00 00 */	lfd f0, 0(r29)
/* 80107168 00103088  7C 63 00 D0 */	neg r3, r3
/* 8010716C 0010308C  FC 00 00 50 */	fneg f0, f0
/* 80107170 00103090  D8 1D 00 00 */	stfd f0, 0(r29)
/* 80107174 00103094  C8 1D 00 08 */	lfd f0, 8(r29)
/* 80107178 00103098  FC 00 00 50 */	fneg f0, f0
/* 8010717C 0010309C  D8 1D 00 08 */	stfd f0, 8(r29)
lbl_80107180:
/* 80107180 001030A0  80 01 00 74 */	lwz r0, 0x74(r1)
/* 80107184 001030A4  83 E1 00 6C */	lwz r31, 0x6c(r1)
/* 80107188 001030A8  83 C1 00 68 */	lwz r30, 0x68(r1)
/* 8010718C 001030AC  7C 08 03 A6 */	mtlr r0
/* 80107190 001030B0  83 A1 00 64 */	lwz r29, 0x64(r1)
/* 80107194 001030B4  38 21 00 70 */	addi r1, r1, 0x70
/* 80107198 001030B8  4E 80 00 20 */	blr

.section .rodata

.global two_over_pi
two_over_pi:
	# ROM: 0x16F070
	.byte 0x00, 0xA2, 0xF9, 0x83
	.byte 0x00, 0x6E, 0x4E, 0x44
	.byte 0x00, 0x15, 0x29, 0xFC
	.byte 0x00, 0x27, 0x57, 0xD1
	.byte 0x00, 0xF5, 0x34, 0xDD
	.byte 0x00, 0xC0, 0xDB, 0x62
	.byte 0x00, 0x95, 0x99, 0x3C
	.byte 0x00, 0x43, 0x90, 0x41
	.byte 0x00, 0xFE, 0x51, 0x63
	.byte 0x00, 0xAB, 0xDE, 0xBB
	.byte 0x00, 0xC5, 0x61, 0xB7
	.byte 0x00, 0x24, 0x6E, 0x3A
	.byte 0x00, 0x42, 0x4D, 0xD2
	.byte 0x00, 0xE0, 0x06, 0x49
	.byte 0x00, 0x2E, 0xEA, 0x09
	.byte 0x00, 0xD1, 0x92, 0x1C
	.byte 0x00, 0xFE, 0x1D, 0xEB
	.byte 0x00, 0x1C, 0xB1, 0x29
	.byte 0x00, 0xA7, 0x3E, 0xE8
	.byte 0x00, 0x82, 0x35, 0xF5
	.byte 0x00, 0x2E, 0xBB, 0x44
	.byte 0x00, 0x84, 0xE9, 0x9C
	.byte 0x00, 0x70, 0x26, 0xB4
	.byte 0x00, 0x5F, 0x7E, 0x41
	.byte 0x00, 0x39, 0x91, 0xD6
	.byte 0x00, 0x39, 0x83, 0x53
	.byte 0x00, 0x39, 0xF4, 0x9C
	.byte 0x00, 0x84, 0x5F, 0x8B
	.byte 0x00, 0xBD, 0xF9, 0x28
	.byte 0x00, 0x3B, 0x1F, 0xF8
	.byte 0x00, 0x97, 0xFF, 0xDE
	.byte 0x00, 0x05, 0x98, 0x0F
	.byte 0x00, 0xEF, 0x2F, 0x11
	.byte 0x00, 0x8B, 0x5A, 0x0A
	.byte 0x00, 0x6D, 0x1F, 0x6D
	.byte 0x00, 0x36, 0x7E, 0xCF
	.byte 0x00, 0x27, 0xCB, 0x09
	.byte 0x00, 0xB7, 0x4F, 0x46
	.byte 0x00, 0x3F, 0x66, 0x9E
	.byte 0x00, 0x5F, 0xEA, 0x2D
	.byte 0x00, 0x75, 0x27, 0xBA
	.byte 0x00, 0xC7, 0xEB, 0xE5
	.byte 0x00, 0xF1, 0x7B, 0x3D
	.byte 0x00, 0x07, 0x39, 0xF7
	.byte 0x00, 0x8A, 0x52, 0x92
	.byte 0x00, 0xEA, 0x6B, 0xFB
	.byte 0x00, 0x5F, 0xB1, 0x1F
	.byte 0x00, 0x8D, 0x5D, 0x08
	.byte 0x00, 0x56, 0x03, 0x30
	.byte 0x00, 0x46, 0xFC, 0x7B
	.byte 0x00, 0x6B, 0xAB, 0xF0
	.byte 0x00, 0xCF, 0xBC, 0x20
	.byte 0x00, 0x9A, 0xF4, 0x36
	.byte 0x00, 0x1D, 0xA9, 0xE3
	.byte 0x00, 0x91, 0x61, 0x5E
	.byte 0x00, 0xE6, 0x1B, 0x08
	.byte 0x00, 0x65, 0x99, 0x85
	.byte 0x00, 0x5F, 0x14, 0xA0
	.byte 0x00, 0x68, 0x40, 0x8D
	.byte 0x00, 0xFF, 0xD8, 0x80
	.byte 0x00, 0x4D, 0x73, 0x27
	.byte 0x00, 0x31, 0x06, 0x06
	.byte 0x00, 0x15, 0x56, 0xCA
	.byte 0x00, 0x73, 0xA8, 0xC9
	.byte 0x00, 0x60, 0xE2, 0x7B
	.byte 0x00, 0xC0, 0x8C, 0x6B

.global npio2_hw
npio2_hw:
	# ROM: 0x16F178
	.byte 0x3F, 0xF9, 0x21, 0xFB
	.byte 0x40, 0x09, 0x21, 0xFB
	.byte 0x40, 0x12, 0xD9, 0x7C
	.byte 0x40, 0x19, 0x21, 0xFB
	.byte 0x40, 0x1F, 0x6A, 0x7A
	.byte 0x40, 0x22, 0xD9, 0x7C
	.byte 0x40, 0x25, 0xFD, 0xBB
	.byte 0x40, 0x29, 0x21, 0xFB
	.byte 0x40, 0x2C, 0x46, 0x3A
	.byte 0x40, 0x2F, 0x6A, 0x7A
	.byte 0x40, 0x31, 0x47, 0x5C
	.byte 0x40, 0x32, 0xD9, 0x7C
	.byte 0x40, 0x34, 0x6B, 0x9C
	.byte 0x40, 0x35, 0xFD, 0xBB
	.byte 0x40, 0x37, 0x8F, 0xDB
	.byte 0x40, 0x39, 0x21, 0xFB
	.byte 0x40, 0x3A, 0xB4, 0x1B
	.byte 0x40, 0x3C, 0x46, 0x3A
	.byte 0x40, 0x3D, 0xD8, 0x5A
	.byte 0x40, 0x3F, 0x6A, 0x7A
	.byte 0x40, 0x40, 0x7E, 0x4C
	.byte 0x40, 0x41, 0x47, 0x5C
	.byte 0x40, 0x42, 0x10, 0x6C
	.byte 0x40, 0x42, 0xD9, 0x7C
	.byte 0x40, 0x43, 0xA2, 0x8C
	.byte 0x40, 0x44, 0x6B, 0x9C
	.byte 0x40, 0x45, 0x34, 0xAC
	.byte 0x40, 0x45, 0xFD, 0xBB
	.byte 0x40, 0x46, 0xC6, 0xCB
	.byte 0x40, 0x47, 0x8F, 0xDB
	.byte 0x40, 0x48, 0x58, 0xEB
	.byte 0x40, 0x49, 0x21, 0xFB

.section .sdata2

.global lbl_802F6AB0
lbl_802F6AB0:
	# ROM: 0x1F04D0
	.4byte 0
	.4byte 0

.global lbl_802F6AB8
lbl_802F6AB8:
	# ROM: 0x1F04D8
	.byte 0x3F, 0xF9, 0x21, 0xFB
	.byte 0x54, 0x40, 0x00, 0x00

.global lbl_802F6AC0
lbl_802F6AC0:
	# ROM: 0x1F04E0
	.byte 0x3D, 0xD0, 0xB4, 0x61
	.byte 0x1A, 0x62, 0x63, 0x31

.global lbl_802F6AC8
lbl_802F6AC8:
	# ROM: 0x1F04E8
	.byte 0x3D, 0xD0, 0xB4, 0x61
	.byte 0x1A, 0x60, 0x00, 0x00

.global lbl_802F6AD0
lbl_802F6AD0:
	# ROM: 0x1F04F0
	.byte 0x3B, 0xA3, 0x19, 0x8A
	.byte 0x2E, 0x03, 0x70, 0x73

.global lbl_802F6AD8
lbl_802F6AD8:
	# ROM: 0x1F04F8
	.byte 0x3F, 0xE0, 0x00, 0x00
	.4byte 0

.global lbl_802F6AE0
lbl_802F6AE0:
	# ROM: 0x1F0500
	.byte 0x3F, 0xE4, 0x5F, 0x30
	.byte 0x6D, 0xC9, 0xC8, 0x83

.global lbl_802F6AE8
lbl_802F6AE8:
	# ROM: 0x1F0508
	.byte 0x3B, 0xA3, 0x19, 0x8A
	.byte 0x2E, 0x00, 0x00, 0x00

.global lbl_802F6AF0
lbl_802F6AF0:
	# ROM: 0x1F0510
	.byte 0x39, 0x7B, 0x83, 0x9A
	.byte 0x25, 0x20, 0x49, 0xC1

.global lbl_802F6AF8
lbl_802F6AF8:
	# ROM: 0x1F0518
	.byte 0x41, 0x70, 0x00, 0x00
	.4byte 0

.global lbl_802F6B00
lbl_802F6B00:
	# ROM: 0x1F0520
	.byte 0x43, 0x30, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00
