/* 80035438 00031358  C0 63 00 00 */	lfs f3, 0(r3)
/* 8003543C 0003135C  C0 04 00 00 */	lfs f0, 0(r4)
/* 80035440 00031360  EC 41 18 28 */	fsubs f2, f1, f3
/* 80035444 00031364  C1 03 00 08 */	lfs f8, 8(r3)
/* 80035448 00031368  EC E0 18 28 */	fsubs f7, f0, f3
/* 8003544C 0003136C  C0 24 00 08 */	lfs f1, 8(r4)
/* 80035450 00031370  C8 02 8B 28 */	lfd f0, 0.033333333333333333
/* 80035454 00031374  EC A2 38 24 */	fdivs f5, f2, f7
/* 80035458 00031378  C0 83 00 04 */	lfs f4, 4(r3)
/* 8003545C 0003137C  C0 44 00 04 */	lfs f2, 4(r4)
/* 80035460 00031380  EC C5 01 72 */	fmuls f6, f5, f5
/* 80035464 00031384  FC E7 00 32 */	fmul f7, f7, f0
/* 80035468 00031388  EC 65 01 B2 */	fmuls f3, f5, f6
/* 8003546C 0003138C  EC 06 28 28 */	fsubs f0, f6, f5
/* 80035470 00031390  EC 28 08 2A */	fadds f1, f8, f1
/* 80035474 00031394  EC A3 30 28 */	fsubs f5, f3, f6
/* 80035478 00031398  EC 44 10 28 */	fsubs f2, f4, f2
/* 8003547C 0003139C  EC 08 00 32 */	fmuls f0, f8, f0
/* 80035480 000313A0  EC 65 28 2A */	fadds f3, f5, f5
/* 80035484 000313A4  EC 25 00 72 */	fmuls f1, f5, f1
/* 80035488 000313A8  FC E0 38 18 */	frsp f7, f7
/* 8003548C 000313AC  EC 63 30 28 */	fsubs f3, f3, f6
/* 80035490 000313B0  EC 01 00 28 */	fsubs f0, f1, f0
/* 80035494 000313B4  EC 23 00 B2 */	fmuls f1, f3, f2
/* 80035498 000313B8  EC 07 00 32 */	fmuls f0, f7, f0
/* 8003549C 000313BC  EC 24 08 2A */	fadds f1, f4, f1
/* 800354A0 000313C0  EC 21 00 2A */	fadds f1, f1, f0
/* 800354A4 000313C4  4E 80 00 20 */	blr
