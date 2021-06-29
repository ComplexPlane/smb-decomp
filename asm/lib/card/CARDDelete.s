.include "macros.inc"

.section .text, "ax"  # 0x800065A0 - 0x8010F860

.global DeleteCallback
DeleteCallback:
/* 800DB0F8 000D7018  7C 08 02 A6 */	mflr r0
/* 800DB0FC 000D701C  90 01 00 04 */	stw r0, 4(r1)
/* 800DB100 000D7020  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800DB104 000D7024  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800DB108 000D7028  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800DB10C 000D702C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800DB110 000D7030  7C 9D 23 79 */	or. r29, r4, r4
/* 800DB114 000D7034  93 81 00 10 */	stw r28, 0x10(r1)
/* 800DB118 000D7038  3B 83 00 00 */	addi r28, r3, 0
/* 800DB11C 000D703C  1C BC 01 08 */	mulli r5, r28, 0x108
/* 800DB120 000D7040  3C 60 80 2C */	lis r3, __CARDBlock@ha
/* 800DB124 000D7044  38 03 7C 60 */	addi r0, r3, __CARDBlock@l
/* 800DB128 000D7048  7F E0 2A 14 */	add r31, r0, r5
/* 800DB12C 000D704C  83 DF 00 D0 */	lwz r30, 0xd0(r31)
/* 800DB130 000D7050  38 00 00 00 */	li r0, 0
/* 800DB134 000D7054  90 1F 00 D0 */	stw r0, 0xd0(r31)
/* 800DB138 000D7058  41 80 00 1C */	blt lbl_800DB154
/* 800DB13C 000D705C  A0 9F 00 BE */	lhz r4, 0xbe(r31)
/* 800DB140 000D7060  38 7C 00 00 */	addi r3, r28, 0
/* 800DB144 000D7064  38 BE 00 00 */	addi r5, r30, 0
/* 800DB148 000D7068  4B FF CB 11 */	bl __CARDFreeBlock
/* 800DB14C 000D706C  7C 7D 1B 79 */	or. r29, r3, r3
/* 800DB150 000D7070  40 80 00 2C */	bge lbl_800DB17C
lbl_800DB154:
/* 800DB154 000D7074  38 7F 00 00 */	addi r3, r31, 0
/* 800DB158 000D7078  38 9D 00 00 */	addi r4, r29, 0
/* 800DB15C 000D707C  4B FF B1 25 */	bl __CARDPutControlBlock
/* 800DB160 000D7080  28 1E 00 00 */	cmplwi r30, 0
/* 800DB164 000D7084  41 82 00 18 */	beq lbl_800DB17C
/* 800DB168 000D7088  39 9E 00 00 */	addi r12, r30, 0
/* 800DB16C 000D708C  7D 88 03 A6 */	mtlr r12
/* 800DB170 000D7090  38 7C 00 00 */	addi r3, r28, 0
/* 800DB174 000D7094  38 9D 00 00 */	addi r4, r29, 0
/* 800DB178 000D7098  4E 80 00 21 */	blrl 
lbl_800DB17C:
/* 800DB17C 000D709C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800DB180 000D70A0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800DB184 000D70A4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800DB188 000D70A8  7C 08 03 A6 */	mtlr r0
/* 800DB18C 000D70AC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800DB190 000D70B0  83 81 00 10 */	lwz r28, 0x10(r1)
/* 800DB194 000D70B4  38 21 00 20 */	addi r1, r1, 0x20
/* 800DB198 000D70B8  4E 80 00 20 */	blr 

.global CARDFastDeleteAsync
CARDFastDeleteAsync:
/* 800DB19C 000D70BC  7C 08 02 A6 */	mflr r0
/* 800DB1A0 000D70C0  90 01 00 04 */	stw r0, 4(r1)
/* 800DB1A4 000D70C4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800DB1A8 000D70C8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800DB1AC 000D70CC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800DB1B0 000D70D0  3B C5 00 00 */	addi r30, r5, 0
/* 800DB1B4 000D70D4  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800DB1B8 000D70D8  7C 9D 23 79 */	or. r29, r4, r4
/* 800DB1BC 000D70DC  93 81 00 18 */	stw r28, 0x18(r1)
/* 800DB1C0 000D70E0  3B 83 00 00 */	addi r28, r3, 0
/* 800DB1C4 000D70E4  41 80 00 0C */	blt lbl_800DB1D0
/* 800DB1C8 000D70E8  2C 1D 00 7F */	cmpwi r29, 0x7f
/* 800DB1CC 000D70EC  41 80 00 0C */	blt lbl_800DB1D8
lbl_800DB1D0:
/* 800DB1D0 000D70F0  38 60 FF 80 */	li r3, -128
/* 800DB1D4 000D70F4  48 00 00 D0 */	b lbl_800DB2A4
lbl_800DB1D8:
/* 800DB1D8 000D70F8  38 7C 00 00 */	addi r3, r28, 0
/* 800DB1DC 000D70FC  38 81 00 14 */	addi r4, r1, 0x14
/* 800DB1E0 000D7100  4B FF AF F1 */	bl __CARDGetControlBlock
/* 800DB1E4 000D7104  2C 03 00 00 */	cmpwi r3, 0
/* 800DB1E8 000D7108  40 80 00 08 */	bge lbl_800DB1F0
/* 800DB1EC 000D710C  48 00 00 B8 */	b lbl_800DB2A4
lbl_800DB1F0:
/* 800DB1F0 000D7110  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800DB1F4 000D7114  4B FF CB AD */	bl __CARDGetDirBlock
/* 800DB1F8 000D7118  57 A0 30 32 */	slwi r0, r29, 6
/* 800DB1FC 000D711C  7F E3 02 14 */	add r31, r3, r0
/* 800DB200 000D7120  38 7F 00 00 */	addi r3, r31, 0
/* 800DB204 000D7124  4B FF EE 7D */	bl __CARDAccess
/* 800DB208 000D7128  7C 64 1B 79 */	or. r4, r3, r3
/* 800DB20C 000D712C  40 80 00 10 */	bge lbl_800DB21C
/* 800DB210 000D7130  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800DB214 000D7134  4B FF B0 6D */	bl __CARDPutControlBlock
/* 800DB218 000D7138  48 00 00 8C */	b lbl_800DB2A4
lbl_800DB21C:
/* 800DB21C 000D713C  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800DB220 000D7140  7F A4 EB 78 */	mr r4, r29
/* 800DB224 000D7144  4B FF F3 9D */	bl __CARDIsOpened
/* 800DB228 000D7148  2C 03 00 00 */	cmpwi r3, 0
/* 800DB22C 000D714C  41 82 00 14 */	beq lbl_800DB240
/* 800DB230 000D7150  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800DB234 000D7154  38 80 FF FF */	li r4, -1
/* 800DB238 000D7158  4B FF B0 49 */	bl __CARDPutControlBlock
/* 800DB23C 000D715C  48 00 00 68 */	b lbl_800DB2A4
lbl_800DB240:
/* 800DB240 000D7160  A0 1F 00 36 */	lhz r0, 0x36(r31)
/* 800DB244 000D7164  7F E3 FB 78 */	mr r3, r31
/* 800DB248 000D7168  80 C1 00 14 */	lwz r6, 0x14(r1)
/* 800DB24C 000D716C  38 80 00 FF */	li r4, 0xff
/* 800DB250 000D7170  38 A0 00 40 */	li r5, 0x40
/* 800DB254 000D7174  B0 06 00 BE */	sth r0, 0xbe(r6)
/* 800DB258 000D7178  4B F2 80 C9 */	bl memset
/* 800DB25C 000D717C  28 1E 00 00 */	cmplwi r30, 0
/* 800DB260 000D7180  41 82 00 0C */	beq lbl_800DB26C
/* 800DB264 000D7184  7F C0 F3 78 */	mr r0, r30
/* 800DB268 000D7188  48 00 00 0C */	b lbl_800DB274
lbl_800DB26C:
/* 800DB26C 000D718C  3C 60 80 0D */	lis r3, __CARDDefaultApiCallback@ha
/* 800DB270 000D7190  38 03 51 C0 */	addi r0, r3, __CARDDefaultApiCallback@l
lbl_800DB274:
/* 800DB274 000D7194  80 A1 00 14 */	lwz r5, 0x14(r1)
/* 800DB278 000D7198  3C 60 80 0E */	lis r3, DeleteCallback@ha
/* 800DB27C 000D719C  38 83 B0 F8 */	addi r4, r3, DeleteCallback@l
/* 800DB280 000D71A0  90 05 00 D0 */	stw r0, 0xd0(r5)
/* 800DB284 000D71A4  7F 83 E3 78 */	mr r3, r28
/* 800DB288 000D71A8  4B FF CC B9 */	bl __CARDUpdateDir
/* 800DB28C 000D71AC  7C 7F 1B 79 */	or. r31, r3, r3
/* 800DB290 000D71B0  40 80 00 10 */	bge lbl_800DB2A0
/* 800DB294 000D71B4  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800DB298 000D71B8  7F E4 FB 78 */	mr r4, r31
/* 800DB29C 000D71BC  4B FF AF E5 */	bl __CARDPutControlBlock
lbl_800DB2A0:
/* 800DB2A0 000D71C0  7F E3 FB 78 */	mr r3, r31
lbl_800DB2A4:
/* 800DB2A4 000D71C4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800DB2A8 000D71C8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800DB2AC 000D71CC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800DB2B0 000D71D0  7C 08 03 A6 */	mtlr r0
/* 800DB2B4 000D71D4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800DB2B8 000D71D8  83 81 00 18 */	lwz r28, 0x18(r1)
/* 800DB2BC 000D71DC  38 21 00 28 */	addi r1, r1, 0x28
/* 800DB2C0 000D71E0  4E 80 00 20 */	blr 

.global CARDDeleteAsync
CARDDeleteAsync:
/* 800DB2C4 000D71E4  7C 08 02 A6 */	mflr r0
/* 800DB2C8 000D71E8  90 01 00 04 */	stw r0, 4(r1)
/* 800DB2CC 000D71EC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800DB2D0 000D71F0  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800DB2D4 000D71F4  3B E3 00 00 */	addi r31, r3, 0
/* 800DB2D8 000D71F8  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800DB2DC 000D71FC  3B C5 00 00 */	addi r30, r5, 0
/* 800DB2E0 000D7200  93 A1 00 24 */	stw r29, 0x24(r1)
/* 800DB2E4 000D7204  3B A4 00 00 */	addi r29, r4, 0
/* 800DB2E8 000D7208  38 81 00 18 */	addi r4, r1, 0x18
/* 800DB2EC 000D720C  4B FF AE E5 */	bl __CARDGetControlBlock
/* 800DB2F0 000D7210  2C 03 00 00 */	cmpwi r3, 0
/* 800DB2F4 000D7214  40 80 00 08 */	bge lbl_800DB2FC
/* 800DB2F8 000D7218  48 00 00 C0 */	b lbl_800DB3B8
lbl_800DB2FC:
/* 800DB2FC 000D721C  80 61 00 18 */	lwz r3, 0x18(r1)
/* 800DB300 000D7220  38 9D 00 00 */	addi r4, r29, 0
/* 800DB304 000D7224  38 A1 00 14 */	addi r5, r1, 0x14
/* 800DB308 000D7228  4B FF EE 35 */	bl __CARDGetFileNo
/* 800DB30C 000D722C  7C 64 1B 79 */	or. r4, r3, r3
/* 800DB310 000D7230  40 80 00 10 */	bge lbl_800DB320
/* 800DB314 000D7234  80 61 00 18 */	lwz r3, 0x18(r1)
/* 800DB318 000D7238  4B FF AF 69 */	bl __CARDPutControlBlock
/* 800DB31C 000D723C  48 00 00 9C */	b lbl_800DB3B8
lbl_800DB320:
/* 800DB320 000D7240  80 61 00 18 */	lwz r3, 0x18(r1)
/* 800DB324 000D7244  80 81 00 14 */	lwz r4, 0x14(r1)
/* 800DB328 000D7248  4B FF F2 99 */	bl __CARDIsOpened
/* 800DB32C 000D724C  2C 03 00 00 */	cmpwi r3, 0
/* 800DB330 000D7250  41 82 00 14 */	beq lbl_800DB344
/* 800DB334 000D7254  80 61 00 18 */	lwz r3, 0x18(r1)
/* 800DB338 000D7258  38 80 FF FF */	li r4, -1
/* 800DB33C 000D725C  4B FF AF 45 */	bl __CARDPutControlBlock
/* 800DB340 000D7260  48 00 00 78 */	b lbl_800DB3B8
lbl_800DB344:
/* 800DB344 000D7264  80 61 00 18 */	lwz r3, 0x18(r1)
/* 800DB348 000D7268  4B FF CA 59 */	bl __CARDGetDirBlock
/* 800DB34C 000D726C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800DB350 000D7270  38 80 00 FF */	li r4, 0xff
/* 800DB354 000D7274  80 C1 00 18 */	lwz r6, 0x18(r1)
/* 800DB358 000D7278  38 A0 00 40 */	li r5, 0x40
/* 800DB35C 000D727C  54 00 30 32 */	slwi r0, r0, 6
/* 800DB360 000D7280  7C 63 02 14 */	add r3, r3, r0
/* 800DB364 000D7284  A0 03 00 36 */	lhz r0, 0x36(r3)
/* 800DB368 000D7288  B0 06 00 BE */	sth r0, 0xbe(r6)
/* 800DB36C 000D728C  4B F2 7F B5 */	bl memset
/* 800DB370 000D7290  28 1E 00 00 */	cmplwi r30, 0
/* 800DB374 000D7294  41 82 00 0C */	beq lbl_800DB380
/* 800DB378 000D7298  7F C0 F3 78 */	mr r0, r30
/* 800DB37C 000D729C  48 00 00 0C */	b lbl_800DB388
lbl_800DB380:
/* 800DB380 000D72A0  3C 60 80 0D */	lis r3, __CARDDefaultApiCallback@ha
/* 800DB384 000D72A4  38 03 51 C0 */	addi r0, r3, __CARDDefaultApiCallback@l
lbl_800DB388:
/* 800DB388 000D72A8  80 A1 00 18 */	lwz r5, 0x18(r1)
/* 800DB38C 000D72AC  3C 60 80 0E */	lis r3, DeleteCallback@ha
/* 800DB390 000D72B0  38 83 B0 F8 */	addi r4, r3, DeleteCallback@l
/* 800DB394 000D72B4  90 05 00 D0 */	stw r0, 0xd0(r5)
/* 800DB398 000D72B8  7F E3 FB 78 */	mr r3, r31
/* 800DB39C 000D72BC  4B FF CB A5 */	bl __CARDUpdateDir
/* 800DB3A0 000D72C0  7C 7F 1B 79 */	or. r31, r3, r3
/* 800DB3A4 000D72C4  40 80 00 10 */	bge lbl_800DB3B4
/* 800DB3A8 000D72C8  80 61 00 18 */	lwz r3, 0x18(r1)
/* 800DB3AC 000D72CC  7F E4 FB 78 */	mr r4, r31
/* 800DB3B0 000D72D0  4B FF AE D1 */	bl __CARDPutControlBlock
lbl_800DB3B4:
/* 800DB3B4 000D72D4  7F E3 FB 78 */	mr r3, r31
lbl_800DB3B8:
/* 800DB3B8 000D72D8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800DB3BC 000D72DC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800DB3C0 000D72E0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800DB3C4 000D72E4  7C 08 03 A6 */	mtlr r0
/* 800DB3C8 000D72E8  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800DB3CC 000D72EC  38 21 00 30 */	addi r1, r1, 0x30
/* 800DB3D0 000D72F0  4E 80 00 20 */	blr 

.global CARDDelete
CARDDelete:
/* 800DB3D4 000D72F4  7C 08 02 A6 */	mflr r0
/* 800DB3D8 000D72F8  3C A0 80 0D */	lis r5, __CARDSyncCallback@ha
/* 800DB3DC 000D72FC  90 01 00 04 */	stw r0, 4(r1)
/* 800DB3E0 000D7300  38 A5 51 C4 */	addi r5, r5, __CARDSyncCallback@l
/* 800DB3E4 000D7304  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800DB3E8 000D7308  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800DB3EC 000D730C  3B E3 00 00 */	addi r31, r3, 0
/* 800DB3F0 000D7310  4B FF FE D5 */	bl CARDDeleteAsync
/* 800DB3F4 000D7314  2C 03 00 00 */	cmpwi r3, 0
/* 800DB3F8 000D7318  40 80 00 08 */	bge lbl_800DB400
/* 800DB3FC 000D731C  48 00 00 0C */	b lbl_800DB408
lbl_800DB400:
/* 800DB400 000D7320  7F E3 FB 78 */	mr r3, r31
/* 800DB404 000D7324  4B FF B0 1D */	bl __CARDSync
lbl_800DB408:
/* 800DB408 000D7328  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800DB40C 000D732C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800DB410 000D7330  38 21 00 18 */	addi r1, r1, 0x18
/* 800DB414 000D7334  7C 08 03 A6 */	mtlr r0
/* 800DB418 000D7338  4E 80 00 20 */	blr 