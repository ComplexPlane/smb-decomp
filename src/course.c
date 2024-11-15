#include <string.h>
#include <dolphin.h>

#include "global.h"
#include "course.h"
#include "game.h"
#include "info.h"
#include "input.h"
#include "mode.h"
#include "sound.h"
#include "sprite.h"
#include "stage.h"
#include "textbox.h"
#include "window.h"

// Super Monkey Ball levels are organized into 3 "difficulties", which are
// Beginner, Advanced, and Expert.
// These difficulties are further subdivided into "courses", which are a sequence
// of floors. Each difficulty consists of 2 or 3 courses. All three difficulties
// have a "main" course and an "extra" course. Expert has these two plus an
// additional "master" course.

static struct CourseCommand *s_courseScriptPtr;
static s32 u_jumpFloors;  // number of floors to jump (or -1 if not jumping floors)
static u32 courseMesgTimer;

u32 g_playPointsEarned;
s8 g_currFloorStreak;  // number of floors cleared since last continue
u32 g_totalPlayPoints;
u32 g_recordPlayPoints;
u32 lbl_802F1FB4;  // not used in this file
int lbl_802F1FB0;
u32 lbl_802F1FAC;  // not used in this file
u32 lbl_802F1FA8;  // not used in this file
int u_isCompetitionModeCourse;

// g_unlockFlags bits
#define UNLOCKED_BILLIARDS (1 << 0)  // bit 0 set if billiards unlocked
#define UNLOCKED_BOWLING   (1 << 1)  // bit 1 set if bowling unlocked
#define UNLOCKED_GOLF      (1 << 2)  // bit 2 set if golf unlocked
#define UNLOCKED_ALL_CONTINUES       (1 << 3)  // bit 3 set if all minigames and all extra continues unlocked
// bits 4-6: extra continues (up to 5) unlocked. This is in addition to the 5 continues that the
// player starts out with, for a maximum of 10 total continues
#define UNLOCKED_CONTINUES_SHIFT 4
#define UNLOCKED_CONTINUES_MASK (7 << UNLOCKED_CONTINUES_SHIFT)

// Play points awarded per floor in each course

static s16 beginnerMainPlayPoints[] =
{
    21, 22, 23, 24, 50, 26, 27, 28, 29, 100,
};

static s16 advancedMainPlayPoints[] =
{
    22, 23, 24, 25, 51, 27, 28, 29, 30, 101,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 201,
    42, 43, 44, 45, 46, 47, 48, 49, 50, 300,
};

static s16 expertMainPlayPoints[] =
{
    23, 24, 25, 26, 52, 28, 29, 30, 31, 102,
    33, 34, 35, 36, 37, 38, 39, 40, 41, 202,
    43, 44, 45, 46, 47, 48, 49, 50, 51, 302,
    53, 54, 55, 56, 57, 58, 59, 60, 61, 402,
    63, 64, 65, 66, 67, 68, 69, 70, 71, 500,
};

static s16 beginnerExtraPlayPoints[3] =
{
    40, 70, 131,
};

static s16 advancedExtraPlayPoints[] =
{
    50, 80, 110, 140, 351,
};

static s16 expertExtraPlayPoints[] =
{
    75, 90, 105, 120, 135, 150, 165, 180, 195, 601,
};

static s16 masterPlayPoints[] =
{
    250, 260, 270, 280, 290, 300, 310, 320, 330, 700,
};

static s16 *coursePlayPointLists[] =
{
    beginnerMainPlayPoints,
    advancedMainPlayPoints,
    expertMainPlayPoints,
    beginnerExtraPlayPoints,
    advancedExtraPlayPoints,
    expertExtraPlayPoints,
    masterPlayPoints,
    masterPlayPoints,
    masterPlayPoints,
};

// Play points awarded per floor in addition to the per-course ones mentioned above

static s16 basePlayPoints[] =
{
    0, 1, 1, 2, 2, 3, 3, 4, 4, 5,
    5, 6, 6, 7, 7, 8, 8, 9, 9, 10,
    10, 11, 11, 12, 12, 13, 13, 14,
    14, 15, 15, 16, 16, 17, 17, 18,
    18, 19, 19, 20, 20, 21, 21, 22,
    22, 23, 23, 24, 24, 25, 25, 26,
    26, 27, 27, 28, 28, 29, 29, 30,
    30, 31, 31, 32, 32, 33, 33, 34,
    34, 35,
};

struct Struct8027CC58_sub
{
    s32 unk0;
    s32 unk4;
};

struct Struct8027CC58
{
    struct Struct8027CC58_sub unk0[4];
    s16 unk20;
    s16 unk22;
};

static struct Struct8027CC58 rt_tbl[4][3];
static u32 s_visitedFloors[4];  // bit mask of floors that have been played on at least once
u32 playPointYieldPerDifficulty[3];

static int difficulty_to_course_id(int, u32);
static void mark_floor_visited(int, int, u32);
static void game_course_init(void);
static void game_course_next(void);
static void func_80067AD4(void);

void course_init(void)
{
    int floor;
    int count;

    for (floor = 0; floor < 4; floor++)
        s_visitedFloors[floor] = 0;
    g_totalPlayPoints = 0;
    g_recordPlayPoints = 0;

    count = 0;
    playPointYieldPerDifficulty[DIFFICULTY_BEGINNER] = 0;
    for (floor = 0; floor < 10; floor++, count++)
        playPointYieldPerDifficulty[DIFFICULTY_BEGINNER] += beginnerMainPlayPoints[floor] + basePlayPoints[count];
    for (floor = 0; floor < 3; floor++, count++)
        playPointYieldPerDifficulty[DIFFICULTY_BEGINNER] += beginnerExtraPlayPoints[floor] + basePlayPoints[count];

    count = 0;
    playPointYieldPerDifficulty[DIFFICULTY_ADVANCED] = 0;
    for (floor = 0; floor < 30; floor++, count++)
        playPointYieldPerDifficulty[DIFFICULTY_ADVANCED] += advancedMainPlayPoints[floor] + basePlayPoints[count];
    for (floor = 0; floor < 5; floor++, count++)
        playPointYieldPerDifficulty[DIFFICULTY_ADVANCED] += advancedExtraPlayPoints[floor] + basePlayPoints[count];

    count = 0;
    playPointYieldPerDifficulty[DIFFICULTY_EXPERT] = 0;
    for (floor = 0; floor < 50; floor++, count++)
        playPointYieldPerDifficulty[DIFFICULTY_EXPERT] += expertMainPlayPoints[floor] + basePlayPoints[count];
    for (floor = 0; floor < 10; floor++, count++)
        playPointYieldPerDifficulty[DIFFICULTY_EXPERT] += expertExtraPlayPoints[floor] + basePlayPoints[count];
    for (floor = 0; floor < 10; floor++, count++)
        playPointYieldPerDifficulty[DIFFICULTY_EXPERT] += masterPlayPoints[floor] + basePlayPoints[count];
}

void reset_earned_play_points(void)
{
    g_playPointsEarned = 0;
    g_currFloorStreak = 0;
    if (are_all_continues_unlocked())
        g_totalPlayPoints = 0;
}

void reset_curr_floor_streak(void)
{
    g_currFloorStreak = 0;
}

void record_play_points(void)
{
    g_totalPlayPoints = MIN(g_totalPlayPoints + g_playPointsEarned, 9999);
    if (are_all_continues_unlocked() && g_totalPlayPoints > g_recordPlayPoints)
        g_recordPlayPoints = g_totalPlayPoints;
}

#pragma force_active on
void spend_play_points(void)
{
    g_totalPlayPoints -= 2500;
}
#pragma force_active reset

// Automatically spends remaining play points on extra continues if minigames are already unlocked
void buy_extra_continues(void)
{
    int extraContinues;
    int continuesBought;

    // Extra continues can only be bought once all minigames have been unlocked
    if (!is_minigame_unlocked(GAMETYPE_MINI_BILLIARDS)
     || !is_minigame_unlocked(GAMETYPE_MINI_BOWLING)
     || !is_minigame_unlocked(GAMETYPE_MINI_GOLF))
        return;

    if (are_all_continues_unlocked() == 0 && g_totalPlayPoints >= 2500)
    {
        continuesBought = 0;
        while (g_totalPlayPoints >= 2500)
        {
            spend_play_points();
            continuesBought++;
        }
        extraContinues = continuesBought + ((g_unlockFlags >> 4) & 7);
        if (extraContinues >= 5)
        {
            g_unlockFlags |= UNLOCKED_ALL_CONTINUES;  // We have now unlocked everything!
            // Set new continues
            g_unlockFlags &= ~UNLOCKED_CONTINUES_MASK;
            g_unlockFlags |= 5 << UNLOCKED_CONTINUES_SHIFT;
            g_totalPlayPoints = 0;
        }
        else
        {
            // Set new continues
            g_unlockFlags &= ~UNLOCKED_CONTINUES_MASK;
            g_unlockFlags |= extraContinues << UNLOCKED_CONTINUES_SHIFT;
        }
    }
}

enum
{
    CMD_IF = 0,
    CMD_THEN = 1,
    CMD_FLOOR = 2,
    CMD_COURSE_END = 3,
};

enum  // CMD_IF conditions
{
    IF_FLOOR_CLEAR = 0,
    IF_GOAL_TYPE = 2,
};

enum  // CMD_THEN actions
{
    THEN_JUMP_FLOOR = 0,
};

enum  // CMD_FLOOR value types
{
    FLOOR_STAGE_ID = 0,
    FLOOR_TIME = 1,
};

struct CourseCommand
{
    u8 opcode;
    u8 type;
    s32 value;
    u8 filler8[0x1C-0x8];  // unused filler?
};

static u32 course_if_cleared_floor(struct CourseCommand *);
static u32 course_if_time_elapsed(struct CourseCommand *);
static u32 course_if_goal_type(struct CourseCommand *);
static void course_then_jump_floor(struct CourseCommand *);
static void course_sub_give_play_points(struct CourseCommand *);
static void course_sub_give_play_points_dupe(struct CourseCommand *);

static u32 (*courseIfFuncs[])(struct CourseCommand *) =
{
    course_if_cleared_floor,
    course_if_time_elapsed,
    course_if_goal_type,
    NULL,
};

static void (*courseThenFuncs[])(struct CourseCommand *) =
{
    course_then_jump_floor,
    course_sub_give_play_points,
    course_sub_give_play_points_dupe,
    NULL,
};

static struct CourseCommand s_beginnerMainScript[] =
{
    { CMD_FLOOR, FLOOR_STAGE_ID, ST_001_PLAIN },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_002_DIAMOND },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'B' },
    {    CMD_THEN, THEN_JUMP_FLOOR, 1 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'G' },
    {    CMD_THEN, THEN_JUMP_FLOOR, 3 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_003_HAIRPIN },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_004_WIDE_BRIDGE },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_091_BONUS_BASIC },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_005_SLOPES },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_006_STEPS },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_007_BLOCKS },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_008_JUMP_SINGLE },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_009_EXAM_A },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, 2, 0 },

    { CMD_COURSE_END },
};

static struct CourseCommand s_advancedMainScript[] =
{
    { CMD_FLOOR, FLOOR_STAGE_ID, ST_011_BUMP },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_012_WALKING },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_013_REPULSE },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_014_NARROW_BRIDGE },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_091_BONUS_BASIC },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_015_BREAK },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'B' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 1 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'G' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 4 },

    { CMD_FLOOR, FLOOR_STAGE_ID,   ST_016_CURVES },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_017_DOWNHILL },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID,   ST_018_BLOCKS_SLIM },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_092_BONUS_WAVE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_021_CHOICE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    {   CMD_IF, IF_FLOOR_CLEAR },
    {     CMD_IF, IF_GOAL_TYPE, 'B' },
    {       CMD_THEN, THEN_JUMP_FLOOR, 1 },
    {   CMD_IF, IF_FLOOR_CLEAR },
    {     CMD_IF, IF_GOAL_TYPE, 'G' },
    {       CMD_THEN, THEN_JUMP_FLOOR, 3 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_022_BOWL },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_023_JUMPIES },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_024_STOPPERS },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_025_FLOOR_BENT },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_026_CONVEYOR },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_027_EXAM_B },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_028_CHASER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'B' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 1 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'G' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 2 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'R' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 7 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_029_JUMP_DOUBLE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_093_BONUS_GRID },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_031_MIDDLE_JAM },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_032_ANTLION },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_033_COLLAPSE },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_034_SWING_BAR },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_035_LABYRINTH },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'B' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 1 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'G' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 3 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_036_SPIRAL },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_037_WAVY_JUMP },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_038_SPIKY },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_039_UNREST },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_040_POLAR },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, 2,    0 },

    { CMD_COURSE_END },
};

static struct CourseCommand s_expertMainScript[] =
{
    { CMD_FLOOR, FLOOR_STAGE_ID, ST_041_RUIN },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_042_BRANCH },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'B' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 1 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'R' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 3 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_043_OVERTURN },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'B' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 1 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'G' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 2 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_044_EXCURSION },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_091_BONUS_BASIC },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_045_DODECAGON },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_046_EXAM_C },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_047_SKELETON },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_048_TRACKS },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_092_BONUS_WAVE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_051_DOWNHILL_HARD },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_052_GEARS },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_053_DESTRUCTION },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_054_INVASION },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_055_DIVING },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_056_FLOOR_SLANT },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_057_TRAM },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_058_SWING_BAR_LONG },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_059_PAPERWORK },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_093_BONUS_GRID },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_061_TWIN_ATTACKER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_062_SEGA_LOGO },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_063_SNAKE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_064_WIND },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_065_WINDY_SLIDE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_066_FALL_DOWN },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_067_TWIN_CROSS },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_068_SPIRAL_HARD },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_069_CONVEYOR_PARTS },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_094_BONUS_BUMPY },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_071_GAPS },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_072_CURVATURE },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_073_ANT_LION_SUPER },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_074_DRUM },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_075_TWIST_AND_SPIN },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_076_SPEEDY_JAM },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_077_QUAKE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_078_CASSIOPEIA },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_079_PIRATES },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_095_BONUS_HUNTING },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_081_BOWL_OPEN },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_082_CHECKER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'B' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 1 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'G' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 2 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'R' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 3 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_083_CARPET },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_084_RIDGE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_085_MIXER },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_086_RINGS },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'B' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 1 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_IF, IF_GOAL_TYPE, 'G' },
    {     CMD_THEN, THEN_JUMP_FLOOR, 2 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_087_STAIRS },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_088_CLOVER },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_089_COFFEE_CUP },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_090_METAMORPHASIS },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, 2,    0 },

    { CMD_COURSE_END },
};

static struct CourseCommand s_beginnerExtraScript[] =
{
    { CMD_FLOOR, FLOOR_STAGE_ID, ST_101_BLUR_BRIDGE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_102_HITTER },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_103_AV_LOGO },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, 2,    0 },

    { CMD_COURSE_END },
};

static struct CourseCommand s_advancedExtraScript[] =
{
    { CMD_FLOOR, FLOOR_STAGE_ID, ST_101_BLUR_BRIDGE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_104_HARD_HITTER },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_105_PUZZLE },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_103_AV_LOGO },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_106_POLAR_LARGE },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, 2,    0 },

    { CMD_COURSE_END },
};

static struct CourseCommand s_expertExtraScript[] =
{
    { CMD_FLOOR, FLOOR_STAGE_ID, ST_101_BLUR_BRIDGE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_107_BREATHE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_104_HARD_HITTER },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_108_FERRIS_WHEEL },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_109_FACTORY },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_110_CURL_PIPE },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_111_MAGIC_HAND },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_103_AV_LOGO },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_112_SANCTUARY },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_113_DAA_LOO_MAA },
    { CMD_FLOOR, FLOOR_TIME,     1800 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, 2,    0 },

    { CMD_COURSE_END },
};

static struct CourseCommand s_masterScript[] =
{
    { CMD_FLOOR, FLOOR_STAGE_ID, ST_121_WAVE_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_122_FAN_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_123_STAMINA_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_124_SPRING_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_125_DANCE_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_126_ROLL_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_127_EDGE_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_128_DODGE_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_129_BRIDGE_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, ST_130_MONKEY_MASTER },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, 2,    0 },

    { CMD_COURSE_END },
};

static struct CourseCommand lbl_801BD86C[] =
{
    { CMD_FLOOR, FLOOR_STAGE_ID, 0 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, 0 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, 0 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, 0 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, THEN_JUMP_FLOOR, 1 },

    { CMD_FLOOR, FLOOR_STAGE_ID, 0 },
    { CMD_IF, IF_FLOOR_CLEAR },
    {   CMD_THEN, 2,    0 },

    { CMD_COURSE_END },
};

static struct CourseCommand *s_courseScripts[] =
{
    s_beginnerMainScript,
    s_advancedMainScript,
    s_expertMainScript,
    s_beginnerExtraScript,
    s_advancedExtraScript,
    s_expertExtraScript,
    s_masterScript,
    s_masterScript,
    s_masterScript,
    lbl_801BD86C,
    lbl_801BD86C,
    lbl_801BD86C,
};

static void play_points_textbox_callback(struct TextBox *tbox)
{
    if (tbox->unk19 == 0 && tbox->state == 20 && tbox->timer == tbox->timerMax - 1)
    {
        buy_extra_continues();
        return;
    }
    if (courseMesgTimer == 0)
    {
        if (are_all_continues_unlocked() != 0)
        {
            textbox_add_textf(1, "a/Play Point record for this time : ft/%4d", g_totalPlayPoints);
            textbox_add_textf(1, "a/Highest Play Point record c/0xffffff/a/timec/0x000000/ : ft/%4d", g_recordPlayPoints);
            courseMesgTimer++;
        }
        else if (g_playPointsEarned == 0)
        {
            textbox_add_text(1, "a/You didn't get any play points.");
            textbox_add_textf(1, "z9/a/You now have a total of %d Play Points.", g_totalPlayPoints);
            courseMesgTimer++;
        }
        else
        {
            textbox_add_textf(1, "a/You received %d Play Points.", g_playPointsEarned);
            textbox_add_textf(1, "z9/a/You now have a total of %d Play Points.", g_totalPlayPoints);
            courseMesgTimer++;
        }
        return;
    }
    if (are_all_continues_unlocked() == 0 && g_totalPlayPoints >= 2500)
    {
        if (++courseMesgTimer == 480)
        {
            if (tbox->unk19 == 0)
                courseMesgTimer = 0;
        }
        else
        {
            if (tbox->unk18 == 0 && (g_currPlayerButtons[2] & 0x100)
             && courseMesgTimer > 60 && courseMesgTimer < 180)
            {
                if (!is_minigame_unlocked(GAMETYPE_MINI_BILLIARDS)
                 || !is_minigame_unlocked(GAMETYPE_MINI_BOWLING)
                 || !is_minigame_unlocked(GAMETYPE_MINI_GOLF))
                    courseMesgTimer = 180;
                else if (tbox->unk19 != 0)
                    courseMesgTimer = 240;
                else
                    courseMesgTimer = 180;
            }
            if (courseMesgTimer == 240)
                tbox->unk18 = 1;
            if (courseMesgTimer == 180)
            {
                if (!is_minigame_unlocked(GAMETYPE_MINI_BILLIARDS)
                 || !is_minigame_unlocked(GAMETYPE_MINI_BOWLING)
                 || !is_minigame_unlocked(GAMETYPE_MINI_GOLF))
                {
                    textbox_add_text(1, "b/c/0xff8000/a/b/You can unlock a Mini Game!");
                    textbox_add_text(1, "a/Unlock a Mini Game by selecting it!");
                    tbox->unk19 = 0;
                }
                else if (tbox->unk19 == 0)
                {
                    int buyContinues;
                    if (tbox->unk17 == 0)
                    {
                        u_play_sound_1(0x16D);
                        tbox->unk17 = 1;
                    }
                    buyContinues = g_totalPlayPoints / 2500;
                    if (buyContinues + get_max_continues() > 9)
                    {
                        buyContinues = MIN(buyContinues, 10 - get_max_continues());
                        textbox_add_text(1, "b/c/0xff8000/a/b/You can get unlimited continues!");
                        textbox_add_textf(1, "a/You have used %d Play Points.", buyContinues * 2500);
                    }
                    else
                    {
                        textbox_add_textf(1, "b/c/0xff8000/a/b/Your number of continues has been increased to %d !", buyContinues + get_max_continues());
                        textbox_add_textf(1, "a/You have used %d Play Points.", buyContinues * 2500);
                    }
                }
            }
        }
        return;
    }

    if (++courseMesgTimer >= 60)
        tbox->unk18 = 1;
}

void show_play_points_textbox(int arg0, s16 x, s16 y)
{
    struct TextBox tbox;

    memset(&tbox, 0, sizeof(tbox));
    tbox.style = TEXTBOX_STYLE_PLAIN;
    tbox.x = x;
    tbox.y = y;
    tbox.numColumns = 0;
    tbox.numRows = 2;
    tbox.unk17 = 0;
    tbox.unk18 = 0;
    tbox.unk19 = arg0;
    tbox.callback = play_points_textbox_callback;
    courseMesgTimer = 0;
    if (tbox.unk19 == 2)
    {
        courseMesgTimer = 0xB3;
        tbox.unk19 = 0;
        tbox.numColumns = TEXTBOX_FONT_SIZE;
        tbox.textWidth = tbox.numColumns * TEXTBOX_FONT_SIZE;
    }
    textbox_set_properties(1, TEXTBOX_STATE_INIT, &tbox);
}

int is_play_points_textbox_done(void)
{
    if (textBoxes[1].state == TEXTBOX_STATE_INACTIVE)
        return FALSE;
    if (textBoxes[1].unk18 == 0)
        return FALSE;
    return TRUE;
}

void course_first(void)
{
    int var = difficulty_to_course_id(modeCtrl.difficulty, modeCtrl.courseFlags);

    s_courseScriptPtr = s_courseScripts[var];
    infoWork.u_currStageId = s_courseScriptPtr->value;
    s_courseScriptPtr++;
    game_course_init();
}

void ev_course_init(void)
{
    u_jumpFloors = -1;
    game_course_next();
    if (modeCtrl.gameType == GAMETYPE_MAIN_NORMAL)
        mark_floor_visited(modeCtrl.difficulty, infoWork.currFloor, modeCtrl.courseFlags);
}

void ev_course_main(void)
{
    struct CourseCommand *cmd;
    int jumpCnt;
    int prevOpcode;
    u32 condResult;
    u32 var_r4_2;

    if (debugFlags & 0xA)
        return;
    prevOpcode = -1;
    condResult = 0;
    for (cmd = s_courseScriptPtr; cmd->opcode != CMD_COURSE_END; cmd++)
    {
        // Stop processing commands if we've reached the next floor's commands
        if (cmd->opcode == CMD_FLOOR && cmd->type == FLOOR_STAGE_ID)
            return;

        // Handle conditional script logic
        switch (cmd->opcode)
        {
        case CMD_IF:
            if (prevOpcode != CMD_IF)
                condResult = courseIfFuncs[cmd->type](cmd);
            else if (condResult != 0)  // nest conditionals by logically ANDing the result with the previous
                condResult &= courseIfFuncs[cmd->type](cmd);
            break;
        case CMD_THEN:
            if (condResult)  // if previous condition was nonzero, execute the result
                courseThenFuncs[cmd->type](cmd);
            break;
        }

        if (u_jumpFloors != -1)
        {
            var_r4_2 = FALSE;
            jumpCnt = 0;
            if (infoWork.unk22 != 1)
                u_jumpFloors = infoWork.unk22;
            while (cmd->opcode != CMD_COURSE_END)
            {
                if (cmd->opcode == CMD_FLOOR && cmd->type == FLOOR_STAGE_ID)
                {
                    jumpCnt++;
                    if (jumpCnt == u_jumpFloors)
                    {
                        var_r4_2 = TRUE;
                        break;
                    }
                }
                cmd++;
            }
            if (var_r4_2)
                s_courseScriptPtr = cmd + 1;
            else
            {
                course_sub_give_play_points_dupe(cmd);
                infoWork.currFloor += 10;
                u_jumpFloors = -1;
                return;
            }
            if (modeCtrl.gameType == GAMETYPE_MAIN_NORMAL && modeCtrl.playerCount == 1)
            {
                g_currFloorStreak++;
                if ((dipSwitches & DIP_DEBUG) && (dipSwitches & DIP_PLAY_PNT_X10))
                {
                    g_playPointsEarned += coursePlayPointLists[difficulty_to_course_id(modeCtrl.difficulty, modeCtrl.courseFlags)][infoWork.currFloor - 1] * 10;
                    g_playPointsEarned += basePlayPoints[g_currFloorStreak - 1] * 10;
                }
                else
                {
                    g_playPointsEarned += coursePlayPointLists[difficulty_to_course_id(modeCtrl.difficulty, modeCtrl.courseFlags)][infoWork.currFloor - 1];
                    g_playPointsEarned += basePlayPoints[g_currFloorStreak - 1];
                }
            }
            infoWork.u_currStageId = cmd->value;
            func_80067AD4();
            infoWork.unk22 = jumpCnt;
            infoWork.currFloor += infoWork.unk22;
            u_jumpFloors = -1;
            return;
        }
        prevOpcode = cmd->opcode;
    }
}

void ev_course_dest(void) {}

static u32 course_if_cleared_floor(struct CourseCommand *cmd)
{
    if ((infoWork.flags & INFO_FLAG_GOAL) || (infoWork.flags & INFO_FLAG_BONUS_CLEAR))
        return TRUE;
    // In bonus stages or competition mode, falling out or timing over counts as completing the stage
    if (((infoWork.flags & INFO_FLAG_BONUS_STAGE) || modeCtrl.gameType == GAMETYPE_MAIN_COMPETITION)
     && ((infoWork.flags & INFO_FLAG_TIMEOVER) || (infoWork.flags & INFO_FLAG_FALLOUT)))
        return TRUE;
    return FALSE;
}

static u32 course_if_goal_type(struct CourseCommand *cmd)
{
    int i;
    struct StageGoal *goal = decodedStageLzPtr->animGroups[0].goals;

    for (i = 0; i < 3; i++, goal++)
    {
        if (i == infoWork.goalEntered)
            break;
    }
    if (goal->type == (s8)cmd->value)
        return TRUE;
    else
        return FALSE;
}

static u32 course_if_time_elapsed(struct CourseCommand *cmd)
{
    if (infoWork.timerCurr >= cmd->value)
        return 1;
    else
        return 0;
}

static void course_then_jump_floor(struct CourseCommand *cmd)
{
    u_jumpFloors = cmd->value;
}

static void course_sub_give_play_points(struct CourseCommand *cmd)
{
    if (modeCtrl.gameType == GAMETYPE_MAIN_NORMAL && modeCtrl.playerCount == 1)
    {
        g_currFloorStreak++;
        if ((dipSwitches & DIP_DEBUG) && (dipSwitches & DIP_PLAY_PNT_X10))
        {
            g_playPointsEarned += coursePlayPointLists[difficulty_to_course_id(modeCtrl.difficulty, modeCtrl.courseFlags)][infoWork.currFloor - 1] * 10;
            g_playPointsEarned += basePlayPoints[g_currFloorStreak - 1] * 10;
        }
        else
        {
            g_playPointsEarned += coursePlayPointLists[difficulty_to_course_id(modeCtrl.difficulty, modeCtrl.courseFlags)][infoWork.currFloor - 1];
            g_playPointsEarned += basePlayPoints[g_currFloorStreak - 1];
        }
    }
    infoWork.u_currStageId = -1;
}

// duplicate of course_sub_give_play_points
static void course_sub_give_play_points_dupe(struct CourseCommand *cmd)
{
    if (modeCtrl.gameType == GAMETYPE_MAIN_NORMAL && modeCtrl.playerCount == 1)
    {
        g_currFloorStreak++;
        if ((dipSwitches & DIP_DEBUG) && (dipSwitches & DIP_PLAY_PNT_X10))
        {
            g_playPointsEarned += coursePlayPointLists[difficulty_to_course_id(modeCtrl.difficulty, modeCtrl.courseFlags)][infoWork.currFloor - 1] * 10;
            g_playPointsEarned += basePlayPoints[g_currFloorStreak - 1] * 10;
        }
        else
        {
            g_playPointsEarned += coursePlayPointLists[difficulty_to_course_id(modeCtrl.difficulty, modeCtrl.courseFlags)][infoWork.currFloor - 1];
            g_playPointsEarned += basePlayPoints[g_currFloorStreak - 1];
        }
    }
    infoWork.u_currStageId = -1;
}

struct Struct8027CE24 lbl_8027CE24[6];

int u_get_stage_time_limit(void)
{
    s32 temp_r3_2;
    s32 temp_r5;
    s32 var_r6;
    s32 floorCnt;
    u8 temp_r0;
    struct CourseCommand *var_r3;

    if (u_isCompetitionModeCourse != 0)
    {
        floorCnt = 0;
        var_r6 = 0;
        if (lbl_8027CE24[infoWork.currFloor - 1].unk4 & 8)
            var_r6 = 3;
        if (lbl_8027CE24[infoWork.currFloor - 1].unk4 & 0x10)
            var_r6 = 6;
        var_r3 = s_courseScripts[var_r6 + lbl_8027CE24[infoWork.currFloor - 1].unk2];
        temp_r5 = lbl_8027CE24[infoWork.currFloor - 1].unk0;
        while (var_r3->opcode != CMD_COURSE_END)
        {
            if (var_r3->opcode == CMD_FLOOR && var_r3->type == FLOOR_STAGE_ID)
            {
                floorCnt++;
                if (floorCnt == temp_r5)
                {
                    if (var_r3[1].opcode == CMD_FLOOR && var_r3[1].type == FLOOR_TIME)
                        return var_r3[1].value;
                    break;
                }
            }
            var_r3++;
        }
        return 60 * 60;
    }
    if (s_courseScriptPtr->opcode == CMD_FLOOR && s_courseScriptPtr->type == FLOOR_TIME)
        return s_courseScriptPtr->value;
    return 60 * 60;
}

int floor_to_stage_id(int courseId, int floor, int flags)
{
    int stageId;
    int floorCnt;

    s_courseScriptPtr = &s_courseScripts[difficulty_to_course_id(courseId, flags)][0];

    // get the nth command with unk0=2 and unk1=0?
    floorCnt = 1;
    while (floorCnt <= floor && s_courseScriptPtr->opcode != CMD_COURSE_END)
    {
        if (s_courseScriptPtr->opcode == CMD_FLOOR && s_courseScriptPtr->type == FLOOR_STAGE_ID)
        {
            if (floorCnt == floor)
                break;
            floorCnt++;
        }
        s_courseScriptPtr++;
    }

    stageId = s_courseScriptPtr->value;
    if (modeCtrl.gameType == GAMETYPE_MAIN_COMPETITION)
    {
        if (stageId == ST_126_ROLL_MASTER)
            stageId = ST_116_ALTERNATE_ROLL_MASTER;
        if (stageId == ST_127_EDGE_MASTER)
            stageId = ST_115_ALTERNATE_EDGE_MASTER;
    }
    s_courseScriptPtr++;
    return stageId;
}

int difficulty_to_course_id(int difficulty, u32 flags)
{
    int index = 0;

    if (flags & COURSE_FLAG_EXTRA)
        index = 3;
    if (flags & COURSE_FLAG_MASTER)
        index = 6;
    if (u_isCompetitionModeCourse != 0)
        index = 9;
    index += difficulty;
    return index;
}

static const int s_bonusStages[] =
{
    ST_091_BONUS_BASIC,
    ST_092_BONUS_WAVE,
    ST_093_BONUS_GRID,
    ST_094_BONUS_BUMPY,
    ST_095_BONUS_HUNTING,
    ST_134_RACE_ICE,  //! How is this a bonus stage?
    0,
};

static const int s_courseFloorCounts[] =
{
    10,  // beginner
    30,  // advanced
    50,  // expert
    3,   // beginner ex
    5,   // advanced ex
    10,  // expert ex
    10,
    10,
    10,  // master
    0,
    0,
    0,
    0,
};

#pragma force_active on
int course_floor_count(int difficulty, int flags)
{
    if (u_isCompetitionModeCourse != 0)
        return lbl_802F1FB0;
    return s_courseFloorCounts[difficulty_to_course_id(difficulty, flags)];
}
#pragma force_active reset

u32 is_final_floor(int difficulty, int floor, int flags)
{
    int final = course_floor_count(difficulty, flags);

    if (floor == final)
        return TRUE;
    else
        return FALSE;
}

u32 is_bonus_stage(int stageId)
{
    int isBonus = FALSE;
    const volatile int *id;

    for (id = s_bonusStages; *id != 0; id++)
    {
        if (*id == stageId)
        {
            isBonus = TRUE;
            break;
        }
    }
    return isBonus;
}

#pragma force_active on
void func_80067310(void)
{
    int i;

    for (i = 0; i < lbl_802F1FB0; i++)
    {
        lbl_801BD86C[i * 3].value = floor_to_stage_id(lbl_8027CE24[i].unk2, lbl_8027CE24[i].unk0, lbl_8027CE24[i].unk4);
        lbl_801BD86C[i * 3 + 2].type = FLOOR_STAGE_ID;
    }
    lbl_801BD86C[(lbl_802F1FB0 - 1) * 3 + 2].type = 2;
}
#pragma force_active reset

int func_800673BC(void)
{
    struct CourseCommand *r3 = s_courseScriptPtr;

    while (r3->opcode != CMD_COURSE_END)
    {
        //! why the nested while loop?
        while (r3->opcode != CMD_COURSE_END)
        {
            if (r3->opcode == CMD_FLOOR && r3->type == FLOOR_STAGE_ID)
                return r3->value;
            r3++;
        }
    }
    return -1;
}

#pragma force_active on
// Returns TRUE if the floor has been played at least once. This determines whether the floor can be
// selected in Practice Mode.
int is_floor_visited(int difficulty, int floor, u32 flags)
{
    int bit = 0;

    if ((dipSwitches & DIP_DEBUG) && (dipSwitches & DIP_PLAY_STG_ALL))
        return TRUE;

    if (flags & COURSE_FLAG_MASTER)
        bit = 110;
    else if (flags & COURSE_FLAG_EXTRA)
    {
        switch (difficulty)
        {
        case DIFFICULTY_BEGINNER:
            bit = 90;
            break;
        case DIFFICULTY_ADVANCED:
            bit = 95;
            break;
        case DIFFICULTY_EXPERT:
            bit = 100;
            break;
        }
    }
    else
    {
        switch (difficulty)
        {
        case DIFFICULTY_BEGINNER:
            bit = 0;
            break;
        case DIFFICULTY_ADVANCED:
            bit = 10;
            break;
        case DIFFICULTY_EXPERT:
            bit = 40;
            break;
        }
    }
    bit += floor - 1;
    if ((1 << (bit % 32)) & s_visitedFloors[bit / 32])
        return TRUE;
    else
        return FALSE;
}
#pragma force_active reset

// Marks the floor as having been played on at least once
static void mark_floor_visited(int difficulty, int floor, u32 flags)
{
    int bit = 0;

    if (flags & COURSE_FLAG_MASTER)
        bit = 110;
    else if (flags & COURSE_FLAG_EXTRA)
    {
        switch (difficulty)
        {
        case DIFFICULTY_BEGINNER:
            bit = 90;
            break;
        case DIFFICULTY_ADVANCED:
            bit = 95;
            break;
        case DIFFICULTY_EXPERT:
            bit = 100;
            break;
        }
    }
    else
    {
        switch (difficulty)
        {
        case DIFFICULTY_BEGINNER:
            bit = 0;
            break;
        case DIFFICULTY_ADVANCED:
            bit = 10;
            break;
        case DIFFICULTY_EXPERT:
            bit = 40;
            break;
        }
    }
    bit += floor - 1;
    s_visitedFloors[bit / 32] |= (1 << (bit % 32));
}

// Returns TRUE if the specified minigame (modeCtrl.gameType value) is unlocked
int is_minigame_unlocked(int minigame)
{
    int isUnlocked = FALSE;

    if ((dipSwitches & DIP_DEBUG) && (dipSwitches & DIP_PLAY_STG_ALL))
        return TRUE;

    switch (minigame)
    {
    case GAMETYPE_MINI_BILLIARDS:
        if (g_unlockFlags & UNLOCKED_BILLIARDS)
            isUnlocked = TRUE;
        break;
    case GAMETYPE_MINI_BOWLING:
        if (g_unlockFlags & UNLOCKED_BOWLING)
            isUnlocked = TRUE;
        break;
    case GAMETYPE_MINI_GOLF:
        if (g_unlockFlags & UNLOCKED_GOLF)
            isUnlocked = TRUE;
        break;
    }
    return isUnlocked;
}

// Returns the total maximum number of continues that the player has. This includes 5 which the
// player starts out with plus an additional 5 unlockable continues.
int get_max_continues(void)
{
    return 5 + (g_unlockFlags >> UNLOCKED_CONTINUES_SHIFT);
}

// Returns the number of continues the player has left in the current run.
int get_available_continues(void)
{
    // If the player has unlocked all extra continues, continues are unlimited,
    // so we always return 10 here.
    if (are_all_continues_unlocked())
        return 10;
    return get_max_continues() - infoWork.continuesUsed;
}

// Returns nonzero if the player has unlocked all continues
int are_all_continues_unlocked(void)
{
    if ((dipSwitches & DIP_DEBUG) && (dipSwitches & DIP_PLAY_STG_ALL))
        return TRUE;
    return g_unlockFlags & UNLOCKED_ALL_CONTINUES;
}

static void game_course_init(void)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        struct Struct8027CC58 *r4 = rt_tbl[i];

        for (j = 0; j < 3; j++, r4++)
        {
            r4->unk0[0].unk0 = 0;
            r4->unk0[0].unk4 = -1;
            r4->unk0[1].unk0 = 0;
            r4->unk0[1].unk4 = -1;
            r4->unk0[2].unk0 = 0;
            r4->unk0[2].unk4 = -1;
            r4->unk0[3].unk0 = 0;
            r4->unk0[3].unk4 = -1;
            r4->unk20 = -1;
            r4->unk22 = -1;
        }
    }
}

static void inline1(void)
{
    int temp_r27_3;
    int var_r3_3;
    struct Struct8027CC58 *temp_r3_3;

    temp_r27_3 = modeCtrl.currPlayer;
    if (modeCtrl.gameType == 0)
        var_r3_3 = get_next_player();
    else
        var_r3_3 = temp_r27_3;
    temp_r3_3 = rt_tbl[var_r3_3];
    if (temp_r27_3 == var_r3_3)
        infoWork.unk32 = rt_tbl[temp_r27_3][0].unk0[1].unk4;
    else if (temp_r3_3->unk22 == -1)
        infoWork.unk32 = temp_r3_3->unk0[0].unk4;
    else
        infoWork.unk32 = temp_r3_3->unk0[temp_r3_3->unk22 + 1].unk4;
}

static inline void inline3(struct Struct8027CC58 *temp_r28)
{
    struct CourseCommand *var_r8;
    int i;
    struct Struct8027CC58_sub *var_r6;
    int var_r5;
    int var_r4;
    struct CourseCommand *var_r3_2;

    var_r6 = temp_r28->unk0;
    var_r8 = s_courseScriptPtr;
    for (i = 0; i < 3 && var_r8->opcode != CMD_COURSE_END; var_r8++)
    {
        if (var_r8->opcode == CMD_FLOOR && var_r8->type == FLOOR_STAGE_ID)
            break;
        if (var_r8->opcode == CMD_THEN)
        {
            switch (var_r8->type)
            {
            case 0:
            default:

                var_r6[1].unk0 = infoWork.currFloor + var_r8->value;
                var_r5 = var_r8->value;
                var_r3_2 = s_courseScriptPtr;
                var_r4 = -1;
                while (var_r3_2->opcode != CMD_COURSE_END)
                {
                    if (var_r3_2->opcode == CMD_FLOOR && var_r3_2->type == FLOOR_STAGE_ID
                     && --var_r5 <= 0)
                    {
                        var_r4 = var_r3_2->value;
                        break;
                    }
                    var_r3_2++;
                }
                var_r6[1].unk4 = var_r4;
                break;
            case 1:
            case 2:
                var_r6[1].unk0 = -1;
                var_r6[1].unk4 = -1;
                break;
            }
            var_r6++;
            i++;
        }
    }
    temp_r28->unk20 = i;
    temp_r28->unk22 = -1;

}

static void game_course_next(void)
{
    int temp_r27_2;
    struct Struct8027CC58 *temp_r28;
    int i;
    struct Struct8027CC58 *var_r25;
    u8 unused[0x18];

    temp_r27_2 = modeCtrl.currPlayer;
    if (modeCtrl.gameType == 0)
        get_next_player();  // return value not used

    if (infoWork.currFloor == rt_tbl[temp_r27_2][0].unk0[0].unk0)
    {
        inline1();
        return;
    }

    temp_r28 = rt_tbl[temp_r27_2];

    for (i = 1, var_r25 = &temp_r28[1]; i >= 0; i--, var_r25--)
    {
        if (var_r25->unk0[0].unk0 != 0)
            memcpy(&var_r25[1], var_r25, sizeof(var_r25[1]));
    }


    temp_r28->unk0[0].unk0 = infoWork.currFloor;
    temp_r28->unk0[0].unk4 = currStageId;
    temp_r28->unk0[1].unk0 = 0;
    temp_r28->unk0[1].unk4 = -1;
    temp_r28->unk0[2].unk0 = 0;
    temp_r28->unk0[2].unk4 = -1;
    temp_r28->unk0[3].unk0 = 0;
    temp_r28->unk0[3].unk4 = -1;

    inline3(temp_r28);

    inline1();
}

void func_80067AD4(void)
{
    struct Struct8027CC58 *temp_r8 = rt_tbl[modeCtrl.currPlayer];
    int i;

    for (i = 0; i < 3; i++)
    {
        int var = temp_r8->unk0[i+1].unk4;

        if (var == infoWork.u_currStageId || infoWork.u_currStageId == -1)
        {
            temp_r8->unk22 = i;
            if (infoWork.u_currStageId == -1)
                temp_r8->unk0[temp_r8->unk22 + 1].unk4 = -1;
            break;
        }
    }

    inline1();
}

void game_sprint_course(struct Sprite *sprite)
{
    struct Struct8027CC58_sub *var_r31;
    int var_r0;
    int var_r4;
    int j;
    int i;
    struct Struct8027CC58 *var_r27;
    int x;
    int y;

    reset_text_draw_settings();
    set_text_font(sprite->fontId);
    set_text_scale(sprite->scaleX, sprite->scaleY);
    x = sprite->x;
    y = sprite->y;

    var_r27 = &rt_tbl[modeCtrl.currPlayer][2];
    for (i = 2; i >= 0; i--, var_r27--)
    {
        if (var_r27->unk0[0].unk0 != 0)
        {
            if (i == 0)
                set_text_mul_color(RGBA(0, 255, 0, 0));
            set_text_pos(x, y);
            sprite_printf("%d(%03d)", var_r27->unk0[0].unk0, var_r27->unk0[0].unk4);
            if (i == 0)
                set_text_mul_color(RGBA(255, 255, 255, 0));
            var_r0 = var_r27->unk0[0].unk0;
            var_r4 = 6;
            while (var_r0 != 0)
            {
                var_r0 /= 10;
                if (var_r0 > 0)
                    var_r4++;
            }

            for (j = 0; j < 3; j++)
            {
                var_r31 = var_r27->unk0 + j;
                if (i > 0 && j > 0)
                    break;
                if (var_r31[1].unk0 == 0)
                    break;

                set_text_pos(
                    x + sprite->scaleX * (var_r4 * 8),
                    y + sprite->scaleY * (j * 8));
                if (i > 0)
                    sprite_puts("\x16>");
                else if ((var_r27->unk20 > 1) && (j == 0))
                    sprite_puts("\x13>");
                else if ((var_r27->unk20 > 1) && (j == (s32) (var_r27->unk20 - 1)))
                    sprite_puts("\x1A>");
                else if (var_r27->unk20 > 1)
                    sprite_puts("\x11>");
                else
                    sprite_puts("\x16>");

                if (i > 0)
                    break;

                if (var_r31[1].unk0 == infoWork.currFloor && globalAnimTimer % 60 < 45)
                    set_text_mul_color(RGBA(0, 255, 0, 0));
                set_text_pos(
                    x + sprite->scaleX * (var_r4 * 8) + sprite->scaleX * 16.0f,
                    y + sprite->scaleY * (j * 8));
                if (var_r31[1].unk4 == -1)
                    sprite_puts("CLEAR");
                else if (var_r31[1].unk4 == -1)  //! typo?
                    sprite_puts("END");
                else
                    sprite_printf("%d(%03d)", var_r31[1].unk0, var_r31[1].unk4);
                set_text_mul_color(RGBA(255, 255, 255, 0));
            }
            x += sprite->scaleX * (var_r4 * 8) + sprite->scaleX * 16.0f;
        }
    }
}

void save_course_completion_data(struct MemcardContents *mcdata)
{
    mcdata->gameData.visitedFloors[0] = s_visitedFloors[0];
    mcdata->gameData.visitedFloors[1] = s_visitedFloors[1];
    mcdata->gameData.visitedFloors[2] = s_visitedFloors[2];
    mcdata->gameData.visitedFloors[3] = s_visitedFloors[3];
    mcdata->gameData.totalPlayPoints  = g_totalPlayPoints;
    mcdata->gameData.recordPlayPoints = g_recordPlayPoints;
}

void load_course_completion_data(struct MemcardContents *mcdata)
{
    s_visitedFloors[0] = mcdata->gameData.visitedFloors[0];
    s_visitedFloors[1] = mcdata->gameData.visitedFloors[1];
    s_visitedFloors[2] = mcdata->gameData.visitedFloors[2];
    s_visitedFloors[3] = mcdata->gameData.visitedFloors[3];
    g_totalPlayPoints  = mcdata->gameData.totalPlayPoints;
    g_recordPlayPoints = mcdata->gameData.recordPlayPoints;
}
