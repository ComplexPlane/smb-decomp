#include <dolphin/card.h>

#include <stddef.h>

#include "__card.h"

static void BlockReadCallback(s32 chan, s32 result)
{
	CARDControl *card = &__CARDBlock[chan];
	CARDCallback callback;

	if (result < 0)
		goto error;

	card->xferred += CARD_SEG_SIZE;
	card->addr += CARD_SEG_SIZE;
	card->buffer = (u8*)card->buffer + CARD_SEG_SIZE;

	if (--card->repeat <= 0)
		goto error;

	result = __CARDReadSegment(chan, BlockReadCallback);
	if (result < 0)
		goto error;
	return;

error:
    if (card->apiCallback == NULL)
        __CARDPutControlBlock(card, result);
    callback = card->xferCallback;
    if (callback)
    {
        card->xferCallback = NULL;
        callback(chan, result);
    }
}

s32 __CARDRead(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback)
{
	CARDControl *card = &__CARDBlock[chan];

	if (!card->attached)
		return CARD_RESULT_NOCARD;

	card->xferCallback = callback;
	card->repeat = (u32)length / CARD_SEG_SIZE;
	card->addr = addr;
	card->buffer = dst;

	return __CARDReadSegment(chan, BlockReadCallback);
}

static void BlockWriteCallback(s32 chan, s32 result)
{
	CARDControl *card = &__CARDBlock[chan];
	CARDCallback callback;

	if (result < 0)
		goto error;

	card->xferred += CARD_PAGE_SIZE;
	card->addr += CARD_PAGE_SIZE;
	card->buffer = (u8*)card->buffer + CARD_PAGE_SIZE;

	if (--card->repeat <= 0)
		goto error;

	result = __CARDWritePage(chan, BlockWriteCallback);
	if (result < 0)
		goto error;
	return;

error:
	if (card->apiCallback == NULL)
		__CARDPutControlBlock(card, result);
	callback = card->xferCallback;
	if (callback)
	{
		card->xferCallback = NULL;
		callback(chan, result);
	}
}

s32 __CARDWrite(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback)
{
	CARDControl *card = &__CARDBlock[chan];

	if (!card->attached)
		return CARD_RESULT_NOCARD;

	card->xferCallback = callback;
	card->repeat = (u32)length / CARD_PAGE_SIZE;
	card->addr = addr;
	card->buffer = dst;

	return __CARDWritePage(chan, BlockWriteCallback);
}
