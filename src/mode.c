#include <stddef.h>
#include <stdio.h>
#include <dolphin.h>

#include "global.h"
#include "adv.h"
#include "event.h"
#include "game.h"
#include "input.h"
#include "load.h"
#include "mode.h"
#include "pause_menu.h"
#include "relocation.h"
#include "sprite.h"
#include "window.h"

char *gameModeRelNames[] =
{
    "",
    "",
    "",
    "mkbe.test_mode.rel",
    "",
    "mkbe.option.rel"
};

void (*gameModeFuncs[])(void) =
{
    mode_adv_func,
    mode_sel_func,
    mode_game_func,
    NULL,
    mode_mini_func,
    NULL,
    NULL
};

void (*gameSubmodeFuncs[])(void) =
{
    submode_dummy_func,
    submode_adv_demo_init_func,
    submode_adv_demo_main_func,
    submode_adv_logo_init_func,
    submode_adv_logo_main_func,
    submode_adv_warning_init_func,
    submode_adv_warning_main_func,
    submode_adv_rating_init_func,
    submode_adv_rating_main_func,
    submode_adv_start_init_func,
    submode_adv_start_main_func,
    submode_adv_ranking_init_func,
    submode_adv_ranking_main_func,
    submode_adv_info_init_func,
    submode_adv_info_main_func,
    submode_adv_game_ready_init_func,
    submode_adv_game_ready_main_func,
    submode_adv_game_play_init_func,
    submode_adv_game_play_main_func,
    submode_adv_title_init_func,
    submode_adv_title_main_func,
    submode_adv_title_reinit_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_sel_init_func,
    submode_sel_main_func,
    submode_sel_init_func,
    submode_sel_main_func,
    submode_sel_init_func,
    submode_sel_ngc_dest_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_game_ready_init_func,
    submode_game_ready_main_func,
    submode_game_play_init_func,
    submode_game_play_main_func,
    submode_game_goal_init_func,
    submode_game_goal_main_func,
    submode_game_goal_replay_init_func,
    submode_game_goal_replay_main_func,
    submode_game_timeover_init_func,
    submode_game_timeover_main_func,
    submode_game_ringout_init_func,
    submode_game_ringout_main_func,
    submode_game_first_init_func,
    submode_game_over_init_func,
    submode_game_over_main_func,
    submode_game_nameentry_init_func,
    submode_game_nameentry_main_func,
    submode_game_continue_init_func,
    submode_game_continue_main_func,
    submode_game_restart_init_func,
    submode_game_nameentry_ready_init_func,
    submode_game_nameentry_ready_main_func,
    submode_game_bonus_clear_init_func,
    submode_game_bonus_clear_main_func,
    submode_game_ending_init_func,
    submode_game_ending_main_func,
    submode_game_extra_init_func,
    submode_game_extra_wait_func,
    submode_game_result_init_func,
    submode_game_result_main_func,
    submode_game_result_menu_func,
    submode_game_intr_sel_init_func,
    submode_game_intr_sel_main_func,
    submode_game_over_save_func,
    submode_game_over_dest_func,
    submode_game_roll_init_func,
    submode_game_roll_main_func,
    submode_game_over_point_init_func,
    submode_game_over_point_main_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_mini_select_init_func,
    submode_mini_select_main_func,
    submode_mini_test0_init_func,
    submode_mini_test0_main_func,
    submode_mini_game_init_func,
    submode_mini_game_main_func,
    submode_mini_game_init_func,
    submode_mini_game_main_func,
    submode_mini_game_init_func,
    submode_mini_game_main_func,
    submode_mini_game_init_func,
    submode_mini_game_main_func,
    submode_mini_game_init_func,
    submode_mini_game_main_func,
    submode_mini_game_init_func,
    submode_mini_game_main_func,
    submode_mini_game_init_func,
    submode_mini_game_main_func,
    submode_mini_commend_init_func,
    submode_mini_commend_main_func,
    submode_mini_ranking_init_func,
    submode_mini_ranking_main_func,
    submode_mini_ending_init_func,
    submode_mini_ending_main_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    submode_dummy_func,
    NULL,
};

void *gameModeNames[] =
{
    "MD_ADV",
    "MD_SEL",
    "MD_GAME",
    "MD_TEST",
    "MD_MINI",
    "MD_OPTION",
     NULL,
};

char *gameSubmodeNames[] =
{
    "SMD_ADV_TOP",
    "SMD_ADV_DEMO_INIT",
    "SMD_ADV_DEMO_MAIN",
    "SMD_ADV_LOGO_INIT",
    "SMD_ADV_LOGO_MAIN",
    "SMD_ADV_WARNING_INIT",
    "SMD_ADV_WARNING_MAIN",
    "SMD_ADV_RATING_INIT",
    "SMD_ADV_RATING_MAIN",
    "SMD_ADV_START_INIT",
    "SMD_ADV_START_MAIN",
    "SMD_ADV_RANKING_INIT",
    "SMD_ADV_RANKING_MAIN",
    "SMD_ADV_INFO_INIT",
    "SMD_ADV_INFO_MAIN",
    "SMD_ADV_GAME_READY_INIT",
    "SMD_ADV_GAME_READY_MAIN",
    "SMD_ADV_GAME_PLAY_INIT",
    "SMD_ADV_GAME_PLAY_MAIN",
    "SMD_ADV_TITLE_INIT",
    "SMD_ADV_TITLE_MAIN",
    "SMD_ADV_TITLE_REINIT",
    "SMD_ADV_DMY4",
    "SMD_ADV_DMY5",
    "SMD_ADV_DMY6",
    "SMD_ADV_DMY7",
    "SMD_ADV_DMY8",
    "SMD_ADV_BOTTOM",
    "SMD_SEL_TOP",
    "SMD_SEL_STAGE_INIT",
    "SMD_SEL_STAGE_MAIN",
    "SMD_SEL_NGC_INIT",
    "SMD_SEL_NGC_MAIN",
    "SMD_SEL_NGC_REINIT",
    "SMD_SEL_NGC_DEST",
    "SMD_SEL_DMY1",
    "SMD_SEL_DMY2",
    "SMD_SEL_DMY3",
    "SMD_SEL_DMY4",
    "SMD_SEL_DMY5",
    "SMD_SEL_DMY6",
    "SMD_SEL_DMY7",
    "SMD_SEL_DMY8",
    "SMD_SEL_DMY9",
    "SMD_SEL_DMYa",
    "SMD_SEL_DMYb",
    "SMD_SEL_BOTTOM",
    "SMD_GAME_TOP",
    "SMD_GAME_READY_INIT",
    "SMD_GAME_READY_MAIN",
    "SMD_GAME_PLAY_INIT",
    "SMD_GAME_PLAY_MAIN",
    "SMD_GAME_GOAL_INIT",
    "SMD_GAME_GOAL_MAIN",
    "SMD_GAME_GOAL_REPLAY_INIT",
    "SMD_GAME_GOAL_REPLAY_MAIN",
    "SMD_GAME_TIMEOVER_INIT",
    "SMD_GAME_TIMEOVER_MAIN",
    "SMD_GAME_RINGOUT_INIT",
    "SMD_GAME_RINGOUT_MAIN",
    "SMD_GAME_FIRST_INIT",
    "SMD_GAME_OVER_INIT",
    "SMD_GAME_OVER_MAIN",
    "SMD_GAME_NAMEENTRY_INIT",
    "SMD_GAME_NAMEENTRY_MAIN",
    "SMD_GAME_CONTINUE_INIT",
    "SMD_GAME_CONTINUE_MAIN",
    "SMD_GAME_RESTART_INIT",
    "SMD_GAME_NAMEENTRY_READY_INIT",
    "SMD_GAME_NAMEENTRY_READY_MAIN",
    "SMD_GAME_BONUS_CLEAR_INIT",
    "SMD_GAME_BONUS_CLEAR_MAIN",
    "SMD_GAME_ENDING_INIT",
    "SMD_GAME_ENDING_MAIN",
    "SMD_GAME_EXTRA_INIT",
    "SMD_GAME_EXTRA_WAIT",
    "SMD_GAME_RESULT_INIT",
    "SMD_GAME_RESULT_MAIN",
    "SMD_GAME_RESULT_MENU",
    "SMD_GAME_INTR_SEL_INIT",
    "SMD_GAME_INTR_SEL_MAIN",
    "SMD_GAME_OVER_SAVE",
    "SMD_GAME_OVER_DEST",
    "SMD_GAME_ROLL_INIT",
    "SMD_GAME_ROLL_MAIN",
    "SMD_GAME_OVER_POINT_INIT",
    "SMD_GAME_OVER_POINT_MAIN",
    "SMD_GAME_DMY3",
    "SMD_GAME_DMY4",
    "SMD_GAME_DMY5",
    "SMD_GAME_DMY6",
    "SMD_GAME_DMY7",
    "SMD_GAME_DMY8",
    "SMD_GAME_BOTTOM",
    "SMD_TEST_TOP",
    "SMD_TEST_SELECT_INIT",
    "SMD_TEST_SELECT_MAIN",
    "SMD_TEST_INPUT_INIT",
    "SMD_TEST_INPUT_MAIN",
    "SMD_TEST_DIP_INIT",
    "SMD_TEST_DIP_MAIN",
    "SMD_TEST_SOUND_INIT",
    "SMD_TEST_SOUND_MAIN",
    "SMD_TEST_BLUR_INIT",
    "SMD_TEST_BLUR_MAIN",
    "SMD_TEST_SHADOW_INIT",
    "SMD_TEST_SHADOW_MAIN",
    "SMD_TEST_FOCUS_INIT",
    "SMD_TEST_FOCUS_MAIN",
    "SMD_TEST_INDIRECT_INIT",
    "SMD_TEST_INDIRECT_MAIN",
    "SMD_TEST_NLOBJPUT_INIT",
    "SMD_TEST_NLOBJPUT_MAIN",
    "SMD_TEST_BITMAP_INIT",
    "SMD_TEST_BITMAP_MAIN",
    "SMD_TEST_FONT_INIT",
    "SMD_TEST_FONT_MAIN",
    "SMD_TEST_REPLAY_INIT",
    "SMD_TEST_REPLAY_MAIN",
    "SMD_TEST_MOTION_INIT",
    "SMD_TEST_MOTION_MAIN",
    "SMD_TEST_ADVREPLAY_INIT",
    "SMD_TEST_MODEL_INIT",
    "SMD_TEST_MODEL_MAIN",
    "SMD_TEST_NEWMODEL_INIT",
    "SMD_TEST_NEWMODEL_MAIN",
    "SMD_TEST_PATTERN_INIT",
    "SMD_TEST_PATTERN_MAIN",
    "SMD_TEST_ROMFONT_INIT",
    "SMD_TEST_ROMFONT_MAIN",
    "SMD_TEST_PREREND_INIT",
    "SMD_TEST_PREREND_MAIN",
    "SMD_TEST_PREVIEW_INIT",
    "SMD_TEST_PREVIEW_MAIN",
    "SMD_TEST_DMY2",
    "SMD_TEST_DMY3",
    "SMD_TEST_DMY4",
    "SMD_TEST_DMY5",
    "SMD_TEST_DMY6",
    "SMD_TEST_DMY7",
    "SMD_TEST_DMY8",
    "SMD_TEST_DMY9",
    "SMD_TEST_BOTTOM",
    "SMD_MINI_TOP",
    "SMD_MINI_SELECT_INIT",
    "SMD_MINI_SELECT_MAIN",
    "SMD_MINI_TEST0_INIT",
    "SMD_MINI_TEST0_MAIN",
    "SMD_MINI_FIGHT_INIT",
    "SMD_MINI_FIGHT_MAIN",
    "SMD_MINI_BOWLING_INIT",
    "SMD_MINI_BOWLING_MAIN",
    "SMD_MINI_RACE_INIT",
    "SMD_MINI_RACE_MAIN",
    "SMD_MINI_PILOT_INIT",
    "SMD_MINI_PILOT_MAIN",
    "SMD_MINI_BILLIARDS_INIT",
    "SMD_MINI_BILLIARDS_MAIN",
    "SMD_MINI_GOLF_INIT",
    "SMD_MINI_GOLF_MAIN",
    "SMD_MINI_REL_SAMPLE_INIT",
    "SMD_MINI_REL_SAMPLE_MAIN",
    "SMD_MINI_COMMEND_INIT",
    "SMD_MINI_COMMEND_MAIN",
    "SMD_MINI_RANKING_INIT",
    "SMD_MINI_RANKING_MAIN",
    "SMD_MINI_ENDING_INIT",
    "SMD_MINI_ENDING_MAIN",
    "SMD_MINI_DMY4",
    "SMD_MINI_DMY5",
    "SMD_MINI_DMY6",
    "SMD_MINI_DMY7",
    "SMD_MINI_BOTTOM",
    "SMD_OPTION_TOP",
    "SMD_OPTION_SELECT_INIT",
    "SMD_OPTION_SELECT_MAIN",
    "SMD_OPTION_SOUND_INIT",
    "SMD_OPTION_SOUND_MAIN",
    "SMD_OPTION_PAD_INIT",
    "SMD_OPTION_PAD_MAIN",
    "SMD_OPTION_MEMCARD_INIT",
    "SMD_OPTION_MEMCARD_MAIN",
    "SMD_OPTION_POINT_INIT",
    "SMD_OPTION_POINT_MAIN",
    "SMD_OPTION_RANKING_INIT",
    "SMD_OPTION_RANKING_MAIN",
    "SMD_OPTION_AUTOSAVE_INIT",
    "SMD_OPTION_AUTOSAVE_MAIN",
    "SMD_OPTION_REPLAY_INIT",
    "SMD_OPTION_REPLAY_MAIN",
    "SMD_OPTION_SEPARATE_INIT",
    "SMD_OPTION_SEPARATE_MAIN",
    "SMD_OPTION_REPLAY_PLAY_INIT",
    "SMD_OPTION_REPLAY_PLAY_MAIN",
    "SMD_OPTION_PAD_MENU_INIT",
    "SMD_OPTION_PAD_MENU_MAIN",
    "SMD_OPTION_PAD_VIB_INIT",
    "SMD_OPTION_PAD_VIB_MAIN",
    "SMD_OPTION_BOTTOM",
    NULL,
};

struct RelModule lbl_802F021C = {0};

struct ModeControl modeCtrl;

s16 gameMode;
s16 gameModeRequest;
s16 gameSubmode;
s16 gameSubmodeRequest;
void *modeStringPtr;
void *submodeStringPtr;
void (*unusedCallback)(void);  // always NULL
void (*submodeFinishFunc)(void);
s32 lbl_802F1B78;
void (*lbl_802F1B74)(void);
void (*lbl_802F1B70)(void);

void gm_init(void)
{
    gameMode = MD_ADV;
    gameSubmode = SMD_ADV_WARNING_INIT;
    gameModeRequest = -1;
    gameSubmodeRequest = -1;
    unusedCallback = NULL;
    submodeFinishFunc = NULL;
    modeCtrl.courseFlags = 0;
    modeCtrl.submodeTimer = 0;
    modeCtrl.splitscreenMode = 0;
    modeCtrl.unk1C = 0;
    modeCtrl.menuSel = 0;
}

void gm_main(void)
{
    if (dipSwitches & DIP_DEBUG)
        u_menu_input_debug();
    else
        u_menu_input_notdebug();

    if ((modeCtrl.courseFlags & (1 << 9))
     && gameModeRequest != -1 && gameModeRequest != gameMode)
    {
        relocation_unload_module(&lbl_802F021C);
        modeCtrl.courseFlags &= ~(1 << 9);
    }

    if (gameModeRequest != -1)
    {
        if (unusedCallback != NULL)
        {
            unusedCallback();
            unusedCallback = NULL;
        }
        gameMode = gameModeRequest;
        modeStringPtr = gameModeNames[gameMode];
        gameModeRequest = -1;
        if (gameMode == MD_TEST || gameMode == MD_OPTION)
            modeCtrl.courseFlags |= 0x200;
    }

    if (gameSubmodeRequest != -1)
    {
        gameSubmode = gameSubmodeRequest;
        submodeStringPtr = gameSubmodeNames[gameSubmode];
        gameSubmodeRequest = -1;
    }

    if (modeCtrl.courseFlags & (1 << 9))
    {
        if (lbl_802F021C.info == NULL)
        {
            event_finish_all();
            free_all_bitmap_groups_except_com();
            relocation_load_module(gameModeRelNames[gameMode], &lbl_802F021C);
        }
        if (lbl_802F1B74 != 0)
            lbl_802F1B74();
    }
    else
        gameModeFuncs[gameMode]();
}

int title_screen_debug_menu(void)
{
    static char *items[] =
    {
        "GAME START",
        "STAGE SELECT",
        "MINI MODE",
        "OPTION",
        "TEST MODE",
    };
    int chosen = FALSE;
    int i;

    if (!(analogInputs[0].held & ANALOG_TRIGGER_LEFT)
     && !(analogInputs[0].held & ANALOG_TRIGGER_RIGHT)
     && lbl_802F1ED8 == 0)
    {
        if (REPEAT_WITH_R_ACCEL_ANY(PAD_BUTTON_UP))
        {
            if (--modeCtrl.menuSel < 0)
                modeCtrl.menuSel = 4;
        }

        if (REPEAT_WITH_R_ACCEL_ANY(PAD_BUTTON_DOWN))
        {
            if (++modeCtrl.menuSel == 5)
                modeCtrl.menuSel = 0;
        }

        for (i = 0; i < 4; i++)
        {
            if ((controllerInfo[i].pressed.button & PAD_BUTTON_START)
             || (controllerInfo[i].pressed.button & PAD_BUTTON_A))
                chosen = TRUE;
        }

        if (chosen)
        {
            modeCtrl.unk1C = 0;
            switch (modeCtrl.menuSel)
            {
            case 0:  // "GAME START"
                empty_load_queue();
                modeCtrl.courseFlags |= 1;
                modeCtrl.courseFlags |= 2;
                gameSubmodeRequest = SMD_ADV_START_INIT;
                break;
            case 1:  // "STAGE SELECT"
                empty_load_queue();
                modeCtrl.courseFlags |= 2;
                gameSubmodeRequest = SMD_ADV_START_INIT;
                break;
            case 2:  // "MINI MODE"
                empty_load_queue();
                gameModeRequest = MD_MINI;
                gameSubmodeRequest = SMD_MINI_SELECT_INIT;
                break;
            case 3:  // "OPTION"
                empty_load_queue();
                modeCtrl.courseFlags |= 0x40000;
                modeCtrl.courseFlags |= 2;
                gameSubmodeRequest = SMD_ADV_START_INIT;
                break;
            case 4:  // "TEST MODE"
                empty_load_queue();
                gameModeRequest = MD_TEST;
                gameSubmodeRequest = SMD_TEST_SELECT_INIT;
                break;
            }
            return 1;
        }

        if (ANY_CONTROLLER_PRESSED(PAD_BUTTON_B))
            modeCtrl.unk1C = 0;
    }

    window_set_cursor_pos(15, 15);
    for (i = 0; i < 5; i++)
    {
        if (i == modeCtrl.menuSel)
            window_set_text_color(WINDOW_COLOR_GREEN);
        window_printf_2("%s\n", items[i]);
        if (i == modeCtrl.menuSel)
            window_set_text_color(WINDOW_COLOR_WHITE);
    }
    window_set_cursor_pos(13, 15 + modeCtrl.menuSel);
    u_debug_print("*");
    window_set_cursor_pos(11, 13);
    u_debug_print("\x18");
    for (i = 0; i < 16; i++)
        u_debug_print("\x16");
    u_debug_print("\x19");
    window_set_cursor_pos(11, 14);
    for (i = 0; i < 7; i++)
        u_debug_print("\x17\n");
    window_set_cursor_pos(28, 14);
    for (i = 0; i < 7; i++)
        u_debug_print("\x17\n");
    window_set_cursor_pos(11, 21);
    u_debug_print("\x1A");
    for (i = 0; i < 16; i++)
        u_debug_print("\x16");
    u_debug_print("\x1B");
    return 0;
}

void u_menu_input_debug(void)
{
    int bvar = FALSE;
    int i;

    if (!(analogInputs[0].held & ANALOG_TRIGGER_LEFT)
     && !(analogInputs[0].held & ANALOG_TRIGGER_RIGHT)
     && lbl_802F1ED8 == 0
     && gameMode != MD_ADV)
    {
        for (i = 0; i < 4; i++)
        {
            if (controllerInfo[i].pressed.button & PAD_BUTTON_START)
                bvar = TRUE;
        }
        if ((gameMode == MD_GAME && (modeCtrl.courseFlags & 1))
         || (gameMode == MD_MINI && gameSubmode != SMD_MINI_SELECT_MAIN))
        {
            if (!(g_currPlayerButtons[0] & PAD_TRIGGER_Z))
                bvar = FALSE;
        }

        if (bvar)
        {
            switch (gameMode)
            {
            case MD_OPTION:
                break;
            case MD_MINI:
                if (gameSubmode == SMD_MINI_SELECT_MAIN)
                {
                    gameModeRequest = MD_ADV;
                    gameSubmodeRequest = SMD_ADV_LOGO_INIT;
                }
                else
                {
                    if (submodeFinishFunc != NULL)
                    {
                        submodeFinishFunc();
                        submodeFinishFunc = NULL;
                    }
                    gameSubmodeRequest = SMD_MINI_SELECT_INIT;
                }
                break;
            case MD_TEST:
                if (gameSubmode == SMD_TEST_SELECT_MAIN)
                {
                    gameModeRequest = MD_ADV;
                    gameSubmodeRequest = SMD_ADV_LOGO_INIT;
                }
                else
                {
                    if (submodeFinishFunc != NULL)
                    {
                        submodeFinishFunc();
                        submodeFinishFunc = NULL;
                    }
                    gameSubmodeRequest = SMD_TEST_SELECT_INIT;
                }
                break;
            case MD_SEL:
                gameSubmodeRequest = SMD_SEL_NGC_DEST;
                break;
            default:
                if (submodeFinishFunc != NULL)
                {
                    submodeFinishFunc();
                    submodeFinishFunc = NULL;
                }
                gameModeRequest = MD_TEST;
                gameSubmodeRequest = SMD_TEST_SELECT_INIT;
                break;
            }
            debugFlags &= ~0xB;
            return;
        }
    }

    switch (gameMode)
    {
    case MD_ADV:
        if (modeCtrl.unk1C == 0 || !title_screen_debug_menu())
        {
            if ((analogInputs[0].held & ANALOG_TRIGGER_LEFT)
             || (analogInputs[0].held & ANALOG_TRIGGER_RIGHT)
             || lbl_802F1ED8 != 0
             || gameSubmode == SMD_ADV_START_MAIN)
                break;
            for (i = 0; i < 4; i++)
            {
                if ((controllerInfo[i].pressed.button & PAD_BUTTON_START)
                 || (controllerInfo[i].pressed.button & PAD_BUTTON_A))
                    modeCtrl.unk1C = 1;
            }
        }
        break;
    case MD_GAME:
    case MD_MINI:
        u_menu_input_game_notdebug();
        if (modeCtrl.unk1C != 0)
            modeCtrl.unk1C = 0;
        break;
    }
}

void u_menu_input_notdebug(void)
{
    switch (gameMode)
    {
    case MD_ADV:
        if (!(modeCtrl.courseFlags & (1 << 1))
         && gameSubmode == SMD_ADV_TITLE_MAIN
         && (modeCtrl.courseFlags & (1 << 2)))
        {
            struct Sprite *sprite = find_sprite_with_tag(modeCtrl.unk10 + 12);
            if (sprite != NULL && sprite->counter > 0)
                break;
            if (ANY_CONTROLLER_PRESSED(PAD_BUTTON_A))
            {
                empty_load_queue();
                if (modeCtrl.unk10 == 0)
                {
                    modeCtrl.courseFlags |= 1;
                    modeCtrl.courseFlags |= 2;
                    gameSubmodeRequest = SMD_ADV_START_INIT;
                }
                else
                {
                    modeCtrl.courseFlags |= 0x40000;
                    modeCtrl.courseFlags |= 2;
                    gameSubmodeRequest = SMD_ADV_START_INIT;
                }
            }
        }
        break;
    case MD_GAME:
    case MD_MINI:
        u_menu_input_game_notdebug();
        break;
    case MD_SEL:
    case MD_TEST:
    case MD_OPTION:
        break;
    }
}

void submode_dummy_func(void)
{
    printf("sub_mode: error %s.\n", gameSubmodeNames[gameSubmode]);
}
