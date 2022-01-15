#include <dolphin.h>

static struct
{
    u8 filler0[4];
    u32 unk4;
} *__DBInterface;

static int DBVerbose;

static void __DBExceptionDestination();

void DBInit(void)
{
	__DBInterface      = (void *)0x80000040;
    // WTF??
    *(u32 *)0x80000048 = (u32)__DBExceptionDestination + 0x80000000;
	DBVerbose          = 1;
	return;
}

static void __DBExceptionDestinationAux(void)
{
    u8 dummy[8];
    OSContext *ctx = (void *)(0x80000000 + *(u32 *)0xC0);  // WTF??
    OSReport("DBExceptionDestination\n");
    OSDumpContext(ctx);
    PPCHalt();
}

#ifdef __MWERKS__
static asm void __DBExceptionDestination(void)
{
    nofralloc
    mfmsr r3
    ori r3, r3, 0x30
    mtmsr r3
    b __DBExceptionDestinationAux
}
#else
static void __DBExceptionDestination(void)
{
    asm(
        "mfmsr %r3\n"
        "ori %r3, %r3, 0x30\n"
        "mtmsr %r3\n"
        "b __DBExceptionDestinationAux\n"
    );
}
#endif

int __DBIsExceptionMarked(u8 a)
{
    return __DBInterface->unk4 & (1 << a);
}

void DBPrintf(char *str, ...) {}
