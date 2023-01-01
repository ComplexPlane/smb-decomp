#include <stddef.h>

#define ARRAY_COUNT(arr) ((int)(sizeof(arr)/sizeof(arr[0])))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef s32 (*SND_COMPARE)(u16 *, u8 *);

extern SND_HOOKS salHooks;

extern struct
{
    u32 freq;
    u32 unk4;
    u8 filler8[0x210-0x8];
    /*0x210*/ u8 voices;
} synthInfo;

struct DSPVoice_sub
{
    u8 filler0[4];
    u32 unk4;
    u8 filler8[0x1C-0x8];
    u8 unk1C;
};

extern struct DSPVoice
{
    u8 filler0[0x18];
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 unk24[5];
    u32 unk38[5];
    u16 unk4C;
    u16 unk4E;
    u16 unk50;
    u16 unk52;
    u16 unk54;
    u16 unk56;
    u16 unk58;
    u16 unk5A;
    u16 unk5C;
    u8 filler5E[0x70-0x5E];
    u16 unk70;
    struct DSPVoice_sub unk74;
    u8 filler94[0xA0-0x94];
    u8 unkA0;
    u8 fillerA1[3];
    u8 unkA4;
    u8 fillerA5[0xB8-0xA5];
    u32 unkB8;
    u32 unkBC;
    u16 unkC0;
    u32 unkC4;
    u8 fillerC8[4];
    u16 unkCC;
    u16 unkCE;
    u16 unkD0;
    u16 unkD2;
    u8 unkD4;
    u8 fillerD5[0xE4-0xD5];
    u8 unkE4;
    u8 unkE5;
    u8 unkE6;
    u8 unkE7;
    u8 unkE8;
    u8 unkE9;
    u8 unkEA;
    u32 unkEC;
} *dspVoice;

extern u32 dspCmdList;
extern u16 dspCmdFirstSize;
extern void *salMessageCallback;
extern u8 sndActive_2;
extern u32 dspHRTFOn;

extern struct DSPStudio
{
    u8 filler0[0x54];
    u32 unk54;
    u8 filler58[0xAC-0x58];
    SND_AUX_CALLBACK unkAC;
    void *unkB0;
    SND_AUX_CALLBACK unkB4;
    void *unkB8;
} dspStudio[];

// ? ResetNotes();
// ? AllocateNote();
// ? seqFreeKeyOffNote();
// ? GetPublicId();
int seqGetPrivateId(int);
// ? seqStartPlay();
// ? HandleMasterTrack();
// ? StartPause();
// ? seqPause();
// ? seqStop();
// ? seqKillInstancesByGroupID();
// ? seqSpeed();
// ? seqContinue();
// ? seqMute();
// ? seqVolume();
// ? seqCrossFade();
// ? GetStreamValue();
// ? GenerateNextTrackEvent();
// ? InsertGlobalEvent();
// ? HandleEvent();
// ? InitTrackEvents();
// ? InitTrackEventsSection();
// ? HandleTrackEvents();
void seqHandle(int);
// ? seqInit();
// ? synthSetBpm();
u32 synthGetTicksPerSecond(u32 seconds);
// ? synthInitPortamento();
// ? do_voice_portamento();
// ? StartLayer();
// ? StartKeymap();
// ? synthStartSound();
// ? LowPrecisionHandler();
// ? ZeroOffsetHandler();
// ? EventHandler();
// ? synthAddJob();
// ? synthStartSynthJobHandling();
// ? synthForceLowPrecisionUpdate();
// ? synthKeyStateUpdate();
// ? HandleJobQueue();
// ? HandleFaderTermination();
void synthHandle(int);
u32 synthFXStart(SND_FXID fid, u8 vol, u8 pan, u8 studio, u8);
bool synthFXSetCtrl(SND_VOICEID vid, u8 ctrl, u8 value);
bool synthFXSetCtrl14(SND_VOICEID vid, u8 ctrl, u16 value);
// ? synthFXCloneMidiSetup();
int synthSendKeyOff(int);
void synthVolume(u8 volume, u16 time, u8 volgroup, int, int);
// ? synthIsFadeOutActive();
// ? synthSetMusicVolumeType();
// ? synthHWMessageHandler();
// ? synthInit();
// ? sndSeqSpeed();
// ? sndSeqContinue();
// ? sndSeqMute();
// ? sndSeqVolume();
// ? seqGetMIDIPriority();
// ? sndFXCtrl();
// ? sndFXCtrl14();
// ? sndFXKeyOff();
// ? sndFXStartParaInfo();
// ? sndFXCheck();
// ? sndVolume();
// ? sndMasterVolume();
// ? sndOutputMode();
// ? sndSetAuxProcessingCallbacks();
// ? synthActivateStudio();
// ? synthDeactivateStudio();
// ? synthAddStudioInput();
// ? synthRemoveStudioInput();
// ? streamInit();
void streamHandle(void);
void streamCorrectLoops(void);
// ? streamKill();
// ? GetPrivateIndex();
// ? sndStreamAllocEx();
// ? sndStreamAllocLength();
// ? sndStreamFree();
// ? sndStreamActivate();
// ? sndStreamDeactivate();
// ? dataInsertKeymap();
// ? dataRemoveKeymap();
// ? dataInsertLayer();
// ? dataRemoveLayer();
// ? dataInsertCurve();
// ? dataRemoveCurve();
// ? dataInsertSDir();
// ? dataRemoveSDir();
// ? dataAddSampleReference();
// ? dataRemoveSampleReference();
// ? dataInsertFX();
// ? dataRemoveFX();
// ? dataInsertMacro();
// ? dataRemoveMacro();
// ? maccmp();
// ? dataGetMacro();
// ? smpcmp();
// ? dataGetSample();
// ? curvecmp();
// ? dataGetCurve();
// ? dataGetKeymap();
// ? layercmp();
// ? dataGetLayer();
// ? fxcmp();
// ? dataGetFX();
// ? dataInit();
// ? mcmdWait();
// ? mcmdLoop();
// ? mcmdPlayMacro();
// ? mcmdStartSample();
// ? mcmdVibrato();
// ? DoSetPitch();
// ? mcmdSetADSR();
// ? mcmdSetPitchADSR();
// ? DoPanningSetup();
// ? TranslateVolume();
// ? DoEnvelopeCalculation();
// ? mcmdRandomKey();
// ? SelectSource();
// ? mcmdPortamento();
// ? varGet32();
// ? varGet();
// ? varSet32();
// ? mcmdVarCalculation();
// ? mcmdSendMessage();
// ? mcmdSetKeyGroup();
// ? macHandleActive();
// ? def_800F421C();
// ? macHandle();
// ? macSampleEndNotify();
// ? macSetExternalKeyoff();
// ? macSetPedalState();
// ? TimeQueueAdd();
// ? UnYieldMacro();
// ? macMakeActive();
// ? macMakeInactive();
// ? macStart();
// ? macInit();
// ? vidInit();
// ? get_vidlist();
// ? vidRemoveVoiceReferences();
// ? vidMakeRoot();
// ? vidMakeNew();
u32 vidGetInternalId(SND_VOICEID);
// ? voiceRemovePriority();
// ? voiceSetPriority();
// ? voiceAllocate();
// ? voiceFree();
// ? synthInitAllocationAids();
// ? voiceBlock();
// ? voiceUnblock();
// ? voiceKill();
void voiceKillSound(int);
// ? synthKillVoicesByMacroReferences();
// ? voiceIsLastStarted();
// ? voiceSetLastStarted();
// ? voiceResetLastStarted();
// ? voiceInitLastStarted();
// ? sndPitchUpOne();
// ? sndGetPitch();
u16 adsrConvertTimeCents();
// ? salChangeADSRState();
// ? adsrSetup();
// ? adsrStartRelease();
// ? adsrRelease();
// ? adsrHandle();
// ? adsrHandleLowPrecision();
// ? dataInitStack();
// ? InsertData();
// ? ScanIDList();
// ? ScanIDListReverse();
// ? sndPushGroup();
// ? sndPopGroup();
// ? seqPlaySong();
// ? sndSeqPlayEx();
extern u32 salInitDspCtrl(u8, int);
// ? salInitHRTFBuffer();
void salActivateStudio(u8 studio, u32 arg1, u32 arg2);
void salDeactivateStudio(u8 studio);
// ? HandleDepopVoice();
// ? SortVoices();
int salBuildCommandList(void *, int);
// ? salSynthSendMessage();
void salActivateVoice(struct DSPVoice *, int);
void salDeactivateVoice(struct DSPVoice *);
bool salAddStudioInput(struct DSPStudio *, void *);
bool salRemoveStudioInput(struct DSPStudio *, void *);
void salHandleAuxProcessing(void);
void salCalcVolume(u8, SND_FVECTOR *, int, int, int, int, float, float, float);
// ? UpdateRoomDistances();
// ? CheckRoomStatus();
// ? CheckDoorStatus();
// ? CalcEmitter();
// ? SetFXParameters();
// ? EmitterShutdown();
// ? s3dKillEmitterByFXID();
// ? AddRunningEmitter();
// ? AddStartingEmitter();
// ? StartContinousEmitters();
void s3dHandle(void);
// ? s3dInit();
// ? sndActive();
// ? salApplyMatrix();
// ? salNormalizeVector();
// ? inpSetGlobalMIDIDirtyFlag();
// ? inpSetMidiCtrl();
// ? inpSetMidiCtrl14();
// ? inpResetMidiCtrl();
// ? inpGetMidiCtrl();
// ? inpGetChannelDefaults();
// ? inpResetChannelDefaults();
// ? inpAddCtrl();
// ? inpFXCopyCtrl();
// ? inpSetMidiLastNote();
// ? inpGetMidiLastNote();
// ? inpSetMidiPortState();
// ? inpGetMidiPortState();
// ? _GetInputValue();
// ? inpGetVolume();
// ? inpGetPanning();
// ? inpGetSurPanning();
// ? inpGetPitchBend();
// ? inpGetDoppler();
// ? inpGetModulation();
// ? inpGetPedal();
// ? inpGetPortamento();
// ? inpGetPreAuxA();
// ? inpGetReverb();
// ? inpGetPreAuxB();
// ? inpGetPostAuxB();
// ? inpGetTremolo();
// ? inpGetAuxA();
// ? inpGetAuxB();
// ? inpInit();
// ? inpTranslateExCtrl();
// ? func_800FF248();
// ? func_800FF250();
// ? func_800FF258();
// ? func_800FF260();
// ? func_800FF268();
// ? func_800FF270();
// ? func_800FF278();
// ? func_800FF280();
// ? inpGetExCtrl();
// ? inpSetExCtrl();
// ? sndRand();
// ? sndSin();
// ? sndBSearch();
// ? sndConvertMs();
// ? sndConvertTicks();
// ? sndConvert2Ms();

/* HARDWARE.c */

extern u8 salFrame;
extern u8 salAuxFrame;
extern u8 salNumVoices;
extern SND_HOOKS salHooks;

// ? snd_handle_irq();
// ? hwInit();
// ? hwSetTimeOffset();
// ? hwGetTimeOffset();
u32 hwIsActive(int);
// ? hwSetMesgCallback();
// ? hwSetPriority();
// ? hwInitSamplePlayback();
// ? hwRelease();
// ? hwBreak();
// ? hwSetADSR();
// ? hwSetStreamLoopPS();
// ? hwStart();
// ? hwKeyOff();
// ? hwSetPitch();
// ? hwSetSRCType();
// ? hwSetPolyPhaseFilter();
// ? hwSetITDMode();
// ? hwSetVolume();
void hwOff(int);
void hwSetAUXProcessingCallbacks(u8 studio, SND_AUX_CALLBACK auxA, void *userA, SND_AUX_CALLBACK auxB, void *userB);
void hwActivateStudio(u8 studio, u32 arg1, u32 arg2);
void hwDeactivateStudio(u8 studio);
bool hwAddInput(u8 studio, void *arg1);
bool hwRemoveInput(u8 studio, void *arg1);
// ? hwGetPos();
// ? hwFlushStream();
// ? hwInitStream();
// ? hwExitStream();
// ? hwGetStreamPlayBuffer();
// ? hwTransAddr();
// ? hwFrq2Pitch();
// ? hwInitSampleMem();
// ? hwSaveSample();
// ? hwRemoveSample();
// ? hwSyncSampleMem();
// ? hwFrameDone();
// ? sndSetHooks();
void hwDisableHRTF(void);

// ? aramQueueCallback();
void aramUploadData(void *source, u32 dest, size_t size, u32 arg3);
void aramSyncTransferQueue(void);
void aramInit(int);
// ? aramGetZeroBuffer();
void *aramStoreData(void *, int);
void aramRemoveData(int, u32);
// ? InitStreamBuffers();
u8 aramAllocateStreamBuffer(u32);
u32 aramGetStreamBufferAddress(u8, u32 *);
void aramFreeStreamBuffer(u8);

/* hw_dolphin.c */

// ? salCallback();
// ? dspInitCallback();
// ? dspResumeCallback();
u32 salInitAi(void (*arg0)(void), int arg1, int *arg2);
void salStartAi(void);
void *salAiGetDest(void);
extern u32 salInitDsp(int);
void salCtrlDsp(void *arg0);
// ? salGetStartDelay();
void hwInitIrq(void);
void hwEnableIrq(void);
void hwDisableIrq(void);
void hwIRQEnterCritical(void);
void hwIRQLeaveCritical(void);

/* hw_memory.c */

void *salMalloc(size_t len);
void salFree(void *addr);

/* reverb_fx.c */
void sndAuxCallbackReverbHI(u8 reason, SND_AUX_INFO *info, void *user);
bool sndAuxCallbackPrepareReverbHI(SND_AUX_REVERBHI *rev);

bool ReverbHICreate(_SND_REVHI_WORK *rev, f32 coloration, f32 time, f32 mix, f32 damping, f32 preDelay, f32 crosstalk);
// ? DoCrossTalk();
// ? HandleReverb();
void ReverbHIFree(_SND_REVHI_WORK *rev);
void ReverbHICallback(void *, void *, void *, void *);
// ? do_src1();
// ? do_src2();
// ? sndAuxCallbackChorus();
// ? sndAuxCallbackPrepareChorus();

extern u8 dspScale2IndexTab[];

typedef struct VoiceID VoiceID;

struct VoiceID
{
    VoiceID *next;
    VoiceID *prev;
    s32 pubId;
    s32 privId;
};

typedef struct SynthVoice
{
    char data1[0xf4];
    u32 _f4;
    VoiceID *voiceId;
    char data2[0x18];
    u32 _114[2];
    u8 _11c;
    u8 _11d;
    u8 _11e;
    u8 studio;
    char data3[0x408 - 0x120];
} SynthVoice;

extern SynthVoice *synthVoice;

extern u8 synthITDDefault[4][2];
extern u8 synthFlags;
extern u8 lbl_802F261D;
extern SND_AUX_CALLBACK synthAuxACallback[];
extern SND_AUX_CALLBACK synthAuxBCallback[];
extern u8 synthAuxAMIDI[8];
extern u8 synthAuxBMIDI[8];
extern void *synthAuxAUser[];
extern void *synthAuxBUser[];
extern u8 synthAuxAMIDISet[8];
extern u8 synthAuxBMIDISet[8];
