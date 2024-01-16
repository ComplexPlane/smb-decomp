#ifndef _SRC_FUNCTIONS_H_
#define _SRC_FUNCTIONS_H_

#include "types.h"

// ? main();
void initialize(void);
void init_gx(void);
void init_tv(void);
void init_vi(void);
void init_gx_2(void);
void init_dvd(void);
void init_heaps(void);
void init_rel(void);
void init_cache(void);
void init_cache_ptrs(void);

// ? title_screen_debug_menu();
void u_menu_input_debug(void);
void u_menu_input_notdebug(void);
void submode_dummy_func(void);
int should_open_pause_menu(void);
// ? u_open_pause_menu();
// ? u_handle_pause_menu_navigation();
// ? u_pause_menu_load_how_to_play();
// ? u_activate_pause_menu_item();
// ? unkFunc8000AECC();
void u_menu_input_game_notdebug(void);

void polydisp_init(void);
void polydisp_main(void);
void draw_3d_scene(void);
void draw_adv_3d_scene(void);
void draw_intro_av_logo(void);
void draw_adv_demo_scene(void);
void u_draw_tutorial_button_and_joystick(void);
// ? func_8000C144();
void func_8000C388(void);
void draw_normal_game_scene(void);
void func_8000C7A4(void);
void func_8000C8D4(void);
void draw_continue_scene(void);
void draw_extra_scene(void);
void draw_results_scene(void);
void draw_test_camera_target(void);
void func_8000D5B8(void);
void draw_timer_bomb_fuse(void);
void set_backdrop_color(void);
void draw_monkey(void);
void func_8000E134(void);
void func_8000E180(void);
void func_8000E1A4(float);
void func_8000E338(int);
void u_reset_post_mult_color(void);
void func_8000E428(float a, float b, float c);
float func_8000E444(Vec *);
float func_8000E4D0(Vec *);
float func_8000E53C(Vec *pos);

void u_reset_gamedata(void);
void u_store_gamedata();
void u_load_gamedata();

void mode_sel_func(void);
void func_800123DC(void);
void submode_sel_ngc_dest_func(void);
void func_80012434(int);
void func_80012510(void (*a)(void), void (*b)(void), BallCallback ballcb, CameraCallback cameracb);
void submode_sel_init_func(void);
void submode_sel_main_func(void);
void func_800125A4(void);

void func_80020AB8(Vec *, S16Vec *, float, float, float, float);
// ? func_80020DB4();
BOOL test_sphere_in_frustum(Point3d *p, float radius);
BOOL test_scaled_sphere_in_frustum(Point3d *p, float radius, float scale);

void init_wait_vblank(void);
void beginframe_main(void);
void gpwait_main(void);
void syncwait_main(void);

int load_common_graphics(void);
void func_800249D4(void);
void u_free_minigame_graphics(void);

// ? func_8002DC54();
// ? func_8002DD5C();
// ? func_8002DE38();
// ? func_8002E06C();
// ? func_8002E284();
// ? func_8002EA40();
// ? func_8002EF0C();
void func_8002F0E4(void);
void window_init(void);
void window_main(void);
void u_debug_set_cursor_pos(int, int);
void func_8002FC90(int, int);
// ? func_8002FCAC();
void func_8002FCC0(int, char *, ...);
void u_debug_set_text_color(int);
void func_8002FD68(int, const char *);
void func_8002FFEC(void);
// ? func_80030030();
void u_debug_printf(const char *, ...);
void u_debug_print();
void func_8003026C(int, char *, ...);
// ? func_80030310();
// ? func_800304E0();
void debug_main(void);

void u_create_joints_from_skeleton(struct AnimJoint *a, struct MotSkeletonEntry1 *b, u16 c);
void u_load_new_anim_into_joints(struct AnimJoint *a, u16 b);
// ? u_reset_channels_in_joints();
// ? u_load_channels_from_dat_into_joints();
// ? u_read_channel_from_dat();
int init_ape_model_info(char *, char *, char *, char *);
void adjust_motdat_pointers(struct MotDat *);
void adjust_motlabel_pointers(u32 *);
void adjust_motskl_pointers(struct MotSkeleton *);
void adjust_motinfo_pointers(struct MotInfo *);
u16 u_get_motdat_unk0(u16 index);

// motload_2.c
void u_interpolate_joint_motion(struct AnimJoint *a, const struct Struct80034F5C_3 *b, const struct Struct80034F5C_2 *c, float e, u32 d);
void func_800355B8(struct Struct8003699C_child *);
void func_800355FC(struct Struct8003699C_child *);

void func_80035648(struct Struct8003699C_child *);
void u_joint_tree_calc_some_matrix();
// ? u_joint_tree_calc_some_other_matrix();
// ? func_80035DEC();
// ? func_80035E7C();
void u_init_something_joints_from_something(struct Struct8003699C_child_sub *arg0, struct Struct8003699C_child *arg1, s32 arg2, u16 arg3);
void func_80035FDC(struct Struct8003699C_child *);
void func_80036064(struct Struct8003699C_child *);
void func_80036510(struct Struct8003699C_child_sub *);
// ? func_80036544();
// ? func_800366F8();
// ? func_80036720();
void u_create_joints_from_hardcoded_arrays(struct AnimJoint *arg0, u16 arg1, u16 arg2);

float interpolate_keyframes(int count, struct Keyframe *frames, float time);

void draw_stage_preview(void);
void u_apply_func_to_nl_model_vertices(struct NlModel *model, void (*b)(struct NlVtxTypeB *), void (*c)(struct NlVtxTypeA *));
void u_apply_func_to_nl_disp_list_type_b(struct NlDispList *dl, void *end, void (*func)(struct NlVtxTypeB *));
void u_apply_func_to_nl_disp_list_type_a(struct NlDispList *dl, void *end, void (*func)(struct NlVtxTypeA *));
// ? func_80048084();
void func_80048420();

void monkey_sprite_draw(struct Sprite *);
int u_get_monkey_bitmap_id(int, int, int);
// ? func_80081D34();
// ? func_80081D64();
// ? func_80081D90();
// ? func_80081DBC();
// ? func_80081DEC();
// ? func_80081E1C();
// ? func_80081E4C();
// ? func_80081E58();
// ? func_80081E84();
// ? func_80081EB4();
// ? func_80081EC4();
// ? func_80081EF0();
// ? func_80081F20();
void func_80081F30(void);
void func_80082024(int, struct Sprite *);
// ? func_80082C6C();
// ? func_80083138();

// ? func_80085C0C();
// ? draw_aiai_hair();
void func_80085DB0(struct Ape *);
// ? draw_eye();
// ? draw_baby_hand();
// ? draw_left_hand();
// ? draw_right_hand();
// ? func_800862F4();
// ? func_8008638C();
// ? func_80086434();
// ? func_80086538();
// ? draw_baby_head();
// ? func_8008669C();
// ? draw_head();
// ? draw_ear();

/*
// ? func_80086794();
// ? func_80086F2C();
// ? func_800870EC();
// ? func_800874B0();
// ? func_80087B10();
// ? func_80088230();
void func_800885EC(void);
void func_800886E0(int);
void func_8008897C(int);
void func_80088A10(void);
// ? func_80088AF4();
int func_80088C18(void);
void func_80088C28(void);
// ? func_80088D44();
void func_80088E90(void);
void func_80088F18(void);
void func_80088FD4(int);
// ? func_800890D4();
// ? func_8008923C();
// ? load_character_resources();
// ? func_80089A04();
// ? u_create_joints_probably();
// ? u_iter_joints_80089BD4();
// ? func_80089CBC();
// ? func_80089CF4();
// ? ape_dummy_1();
// ? ape_dummy_2();
// ? ape_dummy_3();
// ? ape_dummy_4();
// ? u_iter_joints_8008A124();
// ? u_iter_joints_8008A2C4();
// ? u_iter_joints_8008A3A4();
void func_8008A55C(u32 a, struct Struct802B39C0_B0_child *b, int c, int d);
// ? func_8008A7F0();
// ? u_free_character_graphics();
// ? u_load_character_graphics();
//struct GMAShape *next_shape(struct GMAShape *);
void mot_ape_init(void);
void func_8008B0AC(void);
void u_ape_free(struct Ape *);
// ? u_make_ape_sub();
struct Ape *u_make_ape(int);
void func_8008BA24(int);
// ? func_8008BA2C();
void u_set_ape_anim(struct Ape *, int, int, int, float);
void func_8008BEF8(int);
void u_switch_ape_character_lod_maybe(struct Ape *, int);
// ? func_8008BFB4();
void func_8008BFDC(struct Ape *, u16, u16);
void func_8008C090(struct Ape *, Vec *);
void func_8008C408(struct Ape *, Vec *);
void func_8008C4A0(float);
void u_do_ape_anim(struct Ape *);
// ? u_draw_ape_transformed();
void func_8008C924(struct Ape *ape, int b);
void func_8008CAAC(struct Ape *, float);
void func_8008CBD0(int, int, struct GMAModel *, struct GMAModel *);
void func_8008CCB8(struct Ape *ape, struct GMAModel *unused);
*/

// code_2.c
float func_8008CDC0(float, struct Struct80176434 *);
void func_8008CF00(struct Struct8008CF00 *arg0, int arg1);
void func_8008D158(u32 arg0);
int func_8008D1DC(void (*)(struct Ape *, int), struct Ape *, int);
void func_8008D240(void);
void func_8008D29C(int);
void func_8008D330(struct NlModel *arg0, u32 arg1, u32 arg2);
void func_8008D36C(struct NlModel *arg0, u32 arg1, u32 arg2);
void func_8008D3A8(struct NlModel *arg0, u32 arg1, u32 arg2);

int lzs_decompress(u8 *, void *);
// ? func_8008D6BC();
// ? set_tev_material_ambient_colors();
void avdisp_init(void);
// ? u_avdisp_alloc_matrix_lists();
// ? func_8008D6D4();
void func_8008D788(void);
void *u_avdisp_alloc_matrix_lists(int count);
// ? u_get_stitching_model_mtx();
// ? load_model();
// ? free_model();
struct GMA *load_gma(char *fileName, struct TPL *tpl);
struct GMA *load_gma_from_aram(u32 aramSrc, u32 size, struct TPL *tpl);
void free_gma(struct GMA *gma);
struct TPL *load_tpl(char *fileName);
struct TPL *load_tpl_from_aram(u32 aramSrc, u32 size);
GXTexObj *create_tpl_tex_objs(struct TPL *tpl);
void free_tpl(struct TPL *tpl);
void avdisp_set_bound_sphere_scale(float);
void avdisp_set_ambient(float, float, float);
void avdisp_draw_model_culled_sort_translucent(struct GMAModel *);
void avdisp_draw_model_culled_sort_none(struct GMAModel *);
void avdisp_draw_model_culled_sort_all();
void avdisp_set_alpha(float alpha);
void avdisp_set_light_mask(u32 lightMask);
void avdisp_set_inf_light_dir(Vec *a);
void avdisp_set_inf_light_color(float, float, float);
void avdisp_set_z_mode(GXBool compareEnable, GXCompare compareFunc, GXBool updateEnable);
BallEnvFunc u_avdisp_set_some_func_1(BallEnvFunc);
Func802F20F0 u_avdisp_set_some_func_2(Func802F20F0);
// ? func_8008E5F8();
// ? func_8008E64C();
// ? set_shape_flags_in_model();
void avdisp_draw_model_unculled_sort_translucent(struct GMAModel *a);
// ? skip_mesh();
void avdisp_draw_model_unculled_sort_none(struct GMAModel *a);
void avdisp_draw_model_unculled_sort_all(struct GMAModel *a);
// ? u_avdisp_draw_model_4();
int get_texture_max_lod(int width, int height);
// ? init_material();
GXTexObj *init_model(struct GMAModel *a, struct TPL *b, GXTexObj *c);
void u_iteratively_multiply_model_matrices(struct GMAModel *a);
void draw_shape_deferred_callback(struct DrawShapeDeferredNode *a);
u32 avdisp_enable_custom_tex_mtx(u32);
void avdisp_set_custom_tex_mtx(int unused, Mtx mtx);
void avdisp_set_post_mult_color(float, float, float, float);
void avdisp_set_post_add_color(float, float, float, float);
void avdisp_enable_fog(int a);
void avdisp_set_fog_params(int, float, float);
void avdisp_set_fog_color(u8 a, u8 b, u8 c);
void u_set_transform_matrices(u8 *a);
struct GMAShape *draw_shape(struct GMAModel *model, struct GMAShape *mesh, struct GMATevLayer *c);
// ? func_8008FBB0();
// ? draw_shape_reflection_maybe();
void draw_indexed_model(struct GMAModel *model, struct GMAShape *b, struct GMATevLayer *mtrl);
void init_tev_material_cache(struct GMAModel *model, struct GMAShape *b);
// ? u_compute_texmtx0();
// ? u_compute_texmtx1and2();
void init_some_texture(void);
void build_post_multiply_tev_stage(GXTevStageID a);
void build_post_add_tev_stage(GXTevStageID a);
void build_diffuse_layer_uncached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg, GXTexGenSrc texGenSrc);
void build_diffuse_layer_cached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg);
void diffuse_layer_next(struct TevStageInfo *a);
void build_alpha_blend_layer_uncached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg, GXTexGenSrc texGenSrc);
void build_alpha_blend_layer_cached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg);
void alpha_blend_layer_next(struct TevStageInfo *a);
void build_view_specular_layer_uncached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg, u32 d);
void build_view_specular_layer_cached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg);
void view_specular_layer_next(struct TevStageInfo *a);
void build_world_specular_layer_uncached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg, u32 d);
void build_world_specular_layer_cached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg);
void world_specular_layer_next(struct TevStageInfo *a);
void build_unk3_layer_uncached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg, GXTexGenSrc texGenSrc);
void build_unk3_layer_cached(struct TevStageInfo *a, GXTevColorArg colorArg, GXTevAlphaArg alphaArg);
void unk3_layer_next(struct TevStageInfo *a);

void func_80092498(void);
void func_800924CC(void);
void shadowerase_main(void);
void u_init_shadow_stuff_probably(struct Struct80092B98 *);
int func_80092D34(void);
void u_draw_ball_shadow(void);
void func_80092F90(void *);
// ? func_800934B0();
// ? func_80093920();
void mode_mini_func(void);
void set_minigame_callbacks(void (*arg0)(), void (*arg1)(), void (*ballCb)(struct Ball *), void (*cameraCb)(struct Camera *, struct Ball *));
void submode_mini_game_init_func(void);
void submode_mini_game_main_func(void);
void u_minigame_draw(void);
void func_80093B84(void);
void func_80093BB4(void);
void submode_mini_select_init_func(void);
void submode_mini_select_main_func(void);
void submode_mini_test0_init_func(void);
void submode_mini_test0_main_func(void);
void func_80093E28(void);
void submode_mini_ending_init_func(void);
void submode_mini_ending_main_func(void);
void u_draw_ending_viewer_text(void);
void func_800940B8(void);
void func_800940E0(void);
void u_something_with_lens_flare_2();
void u_something_with_lens_flare_1();
void func_800946BC(Vec *);
void func_800946DC(int, int);
void func_80094748(float);
void func_80094750(int);
void func_800947B0(void);
int func_800947F8(void);
void func_80094840(void);
void *func_80094870(void);
void func_800948D0(struct Struct80094870 *);
void func_800948F4(void);
void func_80094914(void);
int func_8009492C(struct Struct8009492C *);
void func_80094A34(void);

void submode_mini_commend_init_func(void);
void submode_mini_commend_main_func(void);
void func_8009BEF8(void);
// ? func_8009BF74();
// ? func_8009C178();
// ? func_8009C5E4();
// ? func_8009CAE0();
// ? func_8009CC34();
// ? func_8009CD5C();
int func_8009D5D8(void);
// ? func_8009D5F4();
// ? func_8009D794();
int func_8009D7CC(void);
int func_8009D7E8(void);
void func_8009D7FC(int, Vec *);
void func_8009D98C(Vec *);
// ? func_8009DB40();
void func_8009DB6C(Mtx);
int func_8009DBB0(Vec *, struct Struct8009DBB0 *, Vec *);
void func_8009F49C(int);
int memcard_is_write_in_progress(void);
u8 func_8009F4C4(void);
// ? init_gamedata_file();
// ? init_replay_file_data();
// ? probe_memcard();
// ? mount_memcard();
// ? check_mount_memcard_result();
// ? verify_filesystem();
// ? check_verify_filesystem_result();
// ? open_memcard_file();
// ? check_card_free_space();
// ? create_memcard_file();
// ? check_create_memcard_file_result();
// ? write_memcard_file();
// ? check_write_memcard_file_result();
// ? set_memcard_file_metadata();
// ? check_set_memcard_file_metadata_result();
// ? read_memcard_file();
// ? check_read_memcard_file_result();
// ? get_memcard_file_metadata();
// ? format_memcard();
// ? check_format_memcard_result();
// ? get_memcard_file_metadata_2();
// ? replay_list_open_and_read();
// ? open_replay_file();
// ? delete_memcard_file();
// ? check_delete_memcard_file_result();
// ? delete_gamedata_file();
// ? check_delete_gamedata_file_result();
// ? rename_gamedata_file();
// ? check_rename_gamedata_file_result();
// ? load_sequence();
// ? save_sequence();
// ? replay_save_sequence();
// ? replay_list_sequence();
// ? replay_load_sequence();
void memcard_init(void);
void ev_memcard_init(void);
void ev_memcard_main(void);
void ev_memcard_dest(void);
// ? draw_memcard_msg();
void memcard_draw_ui(void);
void func_800A4CEC(void);
void func_800A4E70();
void func_800A4F04(void);
// ? DEMOInitCaption();
// ? DEMOInitROMFont();
// ? DEMOSetROMFontSize();
// ? DrawFontChar();
// ? DEMORFPuts();
// ? DEMORFPrintf();
// ? DEMOGetRFTextWidth();
void func_800A5704(void);
void ev_view_init(void);
void ev_view_main(void);
void ev_view_dest(void);
void view_draw(void);
void func_800A5F28(void);
void view_create_text_sprites(void);
void view_destroy_text_sprites(void);
void view_init_stage_anim(void);
void view_animate_stage(void);
void func_800A66CC(void);
void func_800A66E4(void);
void func_800A66FC(void);
void func_800A671C(void);
void draw_items(void);
void draw_banana_shadows(void);
void draw_stage_geometry(void);
void draw_stage_objects(void);
void get_curr_stage_view_bounds(struct Sphere *);
void view_apply_camera(struct Camera *);
void submode_mini_ranking_init_func(void);
void submode_mini_ranking_main_func(void);
// ? func_800A7A8C();
// ? func_800A7B7C();
// ? func_800A82D0();
// ? func_800A83C4();
// ? func_800A85F8();
// ? func_800A8828();
// ? func_800A8C44();
// ? func_800A8FCC();
// ? func_800A916C();
// ? func_800AADC4();
// ? func_800AAE80();
// ? func_800AAF40();
// ? func_800AB174();
// ? func_800AB2A0();
// ? func_800AB444();
// ? func_800AB720();
// ? func_800AB830();
// ? func_800AB8D8();
// ? func_800AB974();
// ? func_800ABA10();
// ? func_800ABAE0();
// ? func_800ABCF4();
// ? func_800ABE80();
// ? func_800AC064();
// ? func_800AC248();
// ? func_800AC43C();

void func_800ACA40(void);
int u_read_dvd_file(DVDFileInfo *file, void *arg1, u32 arg2, int arg3);
void init_loading_gct(void);

void credits_finish(void);
void credits_init(void);
void credits_main(void);
void func_800B0B48(void);
// ? func_800B340C();
// ? func_800B34B4();
// ? func_800B361C();
// ? func_800B3784();
// ? func_800B38EC();
// ? func_800B3CC8();
// ? func_800B3DCC();
// ? func_800B3ECC();
// ? func_800B42EC();
// ? func_800B4710();
// ? func_800B4A50();
// ? func_800B5020();
// ? func_800B55E4();
// ? func_800B5B5C();
// ? func_800B5C54();
void ev_vibration_init(void);
void ev_vibration_main(void);
void ev_vibration_dest(void);
void func_800B60F4(int, int, int);
// ? func_800B6224();
// ? func_800B622C();
void func_800B6234(void);
int func_800B62FC(void);
void func_800B6430(void);
void func_800B64B0(void);
// ? func_800B65B4();
// ? func_800B6608();
// ? func_800B6848();
// ? func_800B69F8();
// ? func_800B6C14();
// ? func_800B6EA4();
// ? func_800B6F9C();
// ? func_800B7078();
// ? func_800B72D4();
// ? func_800B7B6C();
// ? func_800B7D38();
// ? func_800B7F6C();
// ? func_800B7FB4();
// ? func_800B83EC();
// ? func_800B86E0();
// ? func_800B8780();
// ? func_800B8AA4();
// ? func_800B8D7C();
// ? func_800B8E1C();
// ? func_800B9444();
// ? func_800B9724();
// ? func_800B9920();
// ? func_800B9A8C();
// ? func_800B9EA4();
// ? func_800B9FDC();
// ? func_800BA124();
// ? func_800BA160();
// ? func_800BA4F4();
// ? func_800BA51C();
// ? func_800BA928();
// ? func_800BA950();
// ? func_800BB050();
// ? func_800BB064();
// ? func_800BB068();
// ? func_800BB084();
// ? func_800BBA54();
// ? func_800BBA58();
// ? func_800BBB10();
// ? func_800BBB78();
// ? func_800BBBA8();
// ? func_800BC820();
// ? func_800BC8B8();
// ? func_800BCE54();
// ? func_800BD470();
// ? func_800BD4B8();
// ? func_800BEEE8();
// ? func_800BF2D0();
// ? func_800BF2D4();
// ? func_800BF4F4();
// ? func_800BF658();
// ? func_800BF774();
// ? func_800BF8C4();
// ? func_800BF948();
// ? func_800BF9CC();
// ? func_800BFA2C();
// ? func_800BFC2C();
// ? func_800C008C();
// ? func_800C00F0();
// ? func_800C013C();
// ? func_800C0354();
// ? func_800C09B0();
// ? func_800C09B4();
// ? effect_ending_ballfrag_init();
// ? effect_ending_ballfrag_main();
// ? effect_ending_ballfrag_draw();
// ? effect_ending_ballfrag_destroy();
// ? func_800C0DC0();
// ? func_800C0F94();
// ? func_800C122C();
// ? func_800C1418();

// mkbe.sel_stage.rel functions
void create_sel_stage_sprites(void);
void dummy_func_C90(void);
void dummy_func_C94(void);
void dummy_func_C98(void);
void sel_stage_draw(void);

// ? PPCMfmsr();
// ? PPCMtmsr();
// ? PPCMfhid0();
// ? PPCMfl2cr();
// ? PPCMtl2cr();
// ? PPCMtdec();
// ? PPCSync();
// ? PPCHalt();
// ? PPCMtmmcr0();
// ? PPCMtmmcr1();
// ? PPCMfpmc1();
// ? PPCMtpmc1();
// ? PPCMtpmc2();
// ? PPCMfpmc3();
// ? PPCMtpmc3();
// ? PPCMfpmc4();
// ? PPCMtpmc4();
// ? PPCMfhid2();
// ? PPCMthid2();
// ? PPCMtwpar();
// ? OSGetConsoleType();
// ? OSInit();
// ? OSExceptionInit();
// ? __OSDBINITSTART();
// ? __OSDBJUMPSTART();
// ? __OSDBJUMPEND();
// ? __OSGetExceptionHandler();
// ? __OSEVStart();
// ? __OSEVEnd();
// ? OSDefaultExceptionHandler();
// ? __OSPSInit();
// ? __OSGetDIConfig();
// ? OSInitAlarm();
// ? OSCreateAlarm();
// ? InsertAlarm();
// ? OSSetAlarm();
// ? OSSetAbsAlarm();
// ? OSSetPeriodicAlarm();
// ? OSCancelAlarm();
// ? DecrementerExceptionCallback();
// ? DecrementerExceptionHandler();
// ? DLInsert();
// ? OSAllocFromHeap();
// ? OSFreeToHeap();
// ? OSSetCurrentHeap();
// ? OSInitAlloc();
// ? OSCreateHeap();
// ? OSCheckHeap();
// ? OSGetArenaHi();
// ? OSGetArenaLo();
// ? OSSetArenaHi();
// ? OSSetArenaLo();
// ? __OSInitAudioSystem();
// ? __OSStopAudioSystem();
// ? DCEnable();
// ? DCInvalidateRange();
// ? DCFlushRange();
// ? DCStoreRange();
// ? DCFlushRangeNoSync();
// ? DCZeroRange();
// ? ICInvalidateRange();
// ? ICFlashInvalidate();
// ? ICEnable();
// ? __LCEnable();
// ? LCEnable();
// ? L2GlobalInvalidate();
// ? DMAErrorHandler();
// ? __OSCacheInit();
// ? __OSLoadFPUContext();
// ? __OSSaveFPUContext();
// ? OSSetCurrentContext();
// ? OSGetCurrentContext();
// ? OSSaveContext();
// ? OSLoadContext();
// ? OSGetStackPointer();
// ? OSClearContext();
// ? OSDumpContext();
// ? OSSwitchFPUContext();
// ? __OSContextInit();
// ? OSReport();
// ? OSPanic();
// ? OSSetErrorHandler();
// ? __OSUnhandledException();
// ? SetExiInterruptMask();
// ? EXIImm();
// ? EXIImmEx();
// ? EXIDma();
// ? EXISync();
// ? EXIClearInterrupts();
// ? EXISetExiCallback();
// ? EXIProbe();
// ? EXIProbeEx();
// ? EXIAttach();
// ? EXIDetach();
// ? EXISelect();
// ? EXIDeselect();
// ? EXIInterruptHandler();
// ? TCInterruptHandler();
// ? EXTInterruptHandler();
// ? EXIInit();
// ? EXILock();
// ? EXIUnlock();
// ? EXIGetState();
// ? EXIGetID();
// ? GetFontCode();
// ? Decode();
// ? OSGetFontEncode();
// ? ReadROM();
// ? ExpandFontSheet();
// ? OSInitFont();
// ? OSGetFontTexture();
// ? OSGetFontWidth();
// ? OSDisableInterrupts();
// ? OSEnableInterrupts();
// ? OSRestoreInterrupts();
// ? __OSSetInterruptHandler();
// ? __OSGetInterruptHandler();
// ? __OSInterruptInit();
// ? SetInterruptMask();
// ? __OSMaskInterrupts();
// ? __OSUnmaskInterrupts();
// ? __OSDispatchInterrupt();
// ? ExternalInterruptHandler();
// ? func_800C68DC();
// ? OSNotifyLink();
// ? OSSetStringTable();
// ? Relocate();
// ? OSLink();
// ? Undo();
// ? OSUnlink();
// ? __OSModuleInit();
// ? OSGetPhysicalMemSize();
// ? __OSUnlockAllMutex();
// ? Run();
// ? Callback();
// ? __OSReboot();
// ? OSRegisterResetFunction();
// ? Reset();
// ? __OSDoHotReset();
// ? OSResetSystem();
// ? __OSResetSWInterruptHandler();
// ? OSGetResetButtonState();
// ? WriteSramCallback();
// ? WriteSram();
// ? __OSInitSram();
// ? __OSLockSram();
// ? __OSLockSramEx();
// ? UnlockSram();
// ? __OSUnlockSram();
// ? __OSUnlockSramEx();
// ? __OSSyncSram();
// ? __OSReadRom();
// ? OSGetSoundMode();
// ? OSSetSoundMode();
// ? SIBusy();
// ? CompleteTransfer();
// ? SIInterruptHandler();
// ? SIInit();
// ? __SITransfer();
// ? SIGetCommand();
// ? SISetCommand();
// ? SITransferCommands();
// ? SISetXY();
// ? SIEnablePolling();
// ? SIDisablePolling();
// ? SIGetResponse();
// ? AlarmHandler();
// ? SITransfer();
// ? __OSSystemCallVectorStart();
// ? __OSSystemCallVectorEnd();
// ? __OSInitSystemCall();
// ? __OSThreadInit();
// ? OSInitThreadQueue();
// ? OSGetCurrentThread();
// ? OSDisableScheduler();
// ? OSEnableScheduler();
// ? UnsetRun();
// ? __OSGetEffectivePriority();
// ? SetEffectivePriority();
// ? SelectThread();
// ? __OSReschedule();
// ? OSCancelThread();
// ? OSResumeThread();
// ? OSSuspendThread();
// ? OSSleepThread();
// ? OSWakeupThread();
// ? OSGetTime();
// ? OSGetTick();
// ? __OSGetSystemTime();
// ? GetDates();
// ? OSTicksToCalendarTime();
// ? InitializeUART();
// ? ReadUARTN();
// ? WriteUARTN();
// ? __init_user();
// ? __init_cpp();
// ? _ExitProcess();
// ? DBInit();
// ? __DBExceptionDestinationAux();
// ? __DBExceptionDestination();
// ? __DBIsExceptionMarked();
// ? DBPrintf();
// ? PSMTXIdentity();
// ? C_MTXScale();
// ? C_MTXQuat();
// ? C_MTXLookAt();
// ? C_MTXFrustum();
// ? C_MTXPerspective();
// ? C_MTXOrtho();
// ? PSVECNormalize();
// ? PSVECCrossProduct();
// ? __DVDInitWA();
// ? __DVDInterruptHandler();
// ? AlarmHandler_2();
// ? AlarmHandlerForTimeout();
// ? Read();
// ? SeekTwiceBeforeRead();
// ? DVDLowRead();
// ? DVDLowSeek();
// ? DVDLowWaitCoverClose();
// ? DVDLowReadDiskID();
// ? DVDLowStopMotor();
// ? DVDLowRequestError();
// ? DVDLowInquiry();
// ? DVDLowAudioStream();
// ? DVDLowRequestAudioStatus();
// ? DVDLowAudioBufferConfig();
// ? DVDLowReset();
// ? DVDLowBreak();
// ? DVDLowClearCallback();
// ? __DVDLowSetWAType();
// ? __DVDFSInit();
// ? DVDConvertPathToEntrynum();
// ? DVDFastOpen();
// ? DVDOpen();
// ? DVDClose();
// ? entryToPath();
// ? DVDGetCurrentDir();
// ? DVDChangeDir();
// ? DVDReadAsyncPrio();
// ? cbForReadAsync();
// ? DVDOpenDir();
// ? DVDReadDir();
// ? DVDCloseDir();
// ? DVDPrepareStreamAsync();
// ? cbForPrepareStreamAsync();
// ? DVDInit();
// ? stateReadingFST();
// ? cbForStateReadingFST();
// ? cbForStateError();
// ? stateTimeout();
// ? stateGettingError();
// ? CategorizeError();
// ? cbForStateGettingError();
// ? cbForUnrecoveredError();
// ? cbForUnrecoveredErrorRetry();
// ? stateGoToRetry();
// ? cbForStateGoToRetry();
// ? stateCheckID();
// ? stateCheckID3();
// ? stateCheckID2();
// ? cbForStateCheckID1();
// ? cbForStateCheckID2();
// ? cbForStateCheckID3();
// ? AlarmHandler_3();
// ? stateCoverClosed();
// ? stateCoverClosed_CMD();
// ? cbForStateCoverClosed();
// ? stateMotorStopeped();
// ? cbForStateMotorStopped();
// ? stateReady();
// ? stateBusy();
// ? cbForStateBusy();
// ? DVDReadAbsAsyncPrio();
// ? DVDReadAbsAsyncForBS();
// ? DVDReadDiskID();
// ? DVDPrepareStreamAbsAsync();
// ? DVDCancelStreamAsync();
// ? DVDStopStreamAtEndAsync();
// ? DVDGetStreamErrorStatusAsync();
// ? DVDGetStreamPlayAddrAsync();
// ? DVDReset();
// ? DVDGetDriveStatus();
// ? DVDCancelAsync();
// ? DVDCancel();
// ? cbForCancelSync();
// ? DVDGetCurrentDiskID();
// ? DVDCheckDisk();
// ? __DVDPrepareResetAsync();
// ? __DVDClearWaitingQueue();
// ? __DVDPushWaitingQueue();
// ? __DVDPopWaitingQueue();
// ? __DVDCheckWaitingQueue();
// ? __DVDDequeueWaitingQueue();
// ? __DVDStoreErrorCode();
// ? cb();
// ? __fstLoad();
// ? __VIRetraceHandler();
// ? getTiming();
// ? func_800CF02C();
// ? func_800CF034();
// ? func_800CF03C();
// ? func_800CF044();
// ? func_800CF04C();
// ? func_800CF054();
// ? __VIInit();
// ? VIInit();
// ? VIWaitForRetrace();
// ? setFbbRegs();
// ? setVerticalRegs();
// ? VIConfigure();
// ? VIFlush();
// ? VISetNextFrameBuffer();
// ? VISetBlack();
// ? getCurrentFieldEvenOdd();
// ? VIGetNextField();
// ? VIGetTvFormat();
// ? DoReset();
// ? PADProbeCallback();
// ? UpdateOrigin();
// ? PADOriginCallback();
// ? PADOriginUpdateCallback();
// ? PADFixCallback();
// ? PADResetCallback();
// ? PADReset();
// ? PADRecalibrate();
// ? PADInit();
// ? PADReceiveCheckCallback();
// ? PADRead();
// ? PADSetSamplingRate();
// ? PADControlAllMotors();
// ? PADControlMotor();
// ? PADSetSpec();
// ? SPEC0_MakeStatus();
// ? SPEC1_MakeStatus();
// ? SPEC2_MakeStatus();
// ? PADSetAnalogMode();
// ? OnReset();
// ? AIRegisterDMACallback();
// ? AIInitDMA();
// ? AIStartDMA();
// ? AIRegisterStreamCallback();
// ? AIGetStreamSampleCount();
// ? AIResetStreamSampleCount();
// ? AISetStreamTrigger();
// ? AISetStreamPlayState();
// ? AIGetStreamPlayState();
// ? AISetDSPSampleRate();
// ? AIGetDSPSampleRate();
// ? AISetStreamSampleRate();
// ? __AI_set_stream_sample_rate();
// ? AIGetStreamSampleRate();
// ? AISetStreamVolLeft();
// ? AIGetStreamVolLeft();
// ? AISetStreamVolRight();
// ? AIGetStreamVolRight();
// ? AIInit();
// ? __AISHandler();
// ? __AIDHandler();
// ? __AICallbackStackSwitch();
// ? __AI_SRC_INIT();
// ? ARRegisterDMACallback();
// ? ARGetDMAStatus();
// ? ARStartDMA();
// ? ARInit();
// ? ARGetBaseAddress();
// ? ARGetSize();
// ? __ARHandler();
// ? __ARChecksize();
// ? __ARQServiceQueueLo();
// ? __ARQCallbackHack();
// ? __ARQInterruptServiceRoutine();
// ? ARQInit();
// ? ARQPostRequest();
// ? DSPCheckMailToDSP();
// ? DSPCheckMailFromDSP();
// ? DSPReadMailFromDSP();
// ? DSPSendMailToDSP();
// ? DSPInit();
// ? DSPAddTask();
// ? __DSP_debug_printf();
// ? __DSPHandler();
// ? __DSP_exec_task();
// ? __DSP_boot_task();
// ? __DSP_insert_task();
// ? __DSP_remove_task();
// ? __CARDDefaultApiCallback();
// ? __CARDSyncCallback();
// ? __CARDExtHandler();
// ? __CARDExiHandler();
// ? __CARDTxHandler();
// ? __CARDUnlockedHandler();
// ? __CARDReadNintendoID();
// ? __CARDEnableInterrupt();
// ? __CARDReadStatus();
// ? __CARDClearStatus();
// ? TimeoutHandler();
// ? Retry();
// ? UnlockedCallback();
// ? __CARDStart();
// ? __CARDReadSegment();
// ? __CARDWritePage();
// ? __CARDEraseSector();
// ? CARDInit();
// ? __CARDSetDiskID();
// ? __CARDGetControlBlock();
// ? __CARDPutControlBlock();
// ? CARDGetResultCode();
// ? CARDFreeBlocks();
// ? __CARDSync();
// ? func_800D64B8();
// ? bitrev();
// ? ReadArrayUnlock();
// ? DummyLen();
// ? __CARDUnlock();
// ? InitCallback();
// ? DoneCallback();
// ? BlockReadCallback();
// ? __CARDRead();
// ? BlockWriteCallback();
// ? __CARDWrite();
// ? __CARDGetFatBlock();
// ? WriteCallback();
// ? EraseCallback();
// ? __CARDAllocBlock();
// ? __CARDFreeBlock();
// ? __CARDUpdateFatBlock();
// ? __CARDGetDirBlock();
// ? WriteCallback_2();
// ? EraseCallback_2();
// ? __CARDUpdateDir();
// ? __CARDCheckSum();
// ? VerifyID();
// ? VerifyDir();
// ? VerifyFAT();
// ? __CARDVerify();
// ? CARDCheckExAsync();
// ? CARDCheckAsync();
// ? CARDProbeEx();
// ? DoMount();
// ? __CARDMountCallback();
// ? CARDMountAsync();
// ? CARDMount();
// ? DoUnmount();
// ? CARDUnmount();
// ? FormatCallback();
// ? __CARDFormatRegionAsync();
// ? __CARDCompareFileName();
// ? __CARDAccess();
// ? __CARDIsPublic();
// ? __CARDGetFileNo();
// ? CARDFastOpen();
// ? CARDOpen();
// ? CARDClose();
// ? __CARDIsOpened();
// ? CreateCallbackFat();
// ? CARDCreateAsync();
// ? __CARDSeek();
// ? ReadCallback();
// ? CARDReadAsync();
// ? CARDCancel();
// ? WriteCallback_3();
// ? EraseCallback_3();
// ? CARDWriteAsync();
// ? DeleteCallback();
// ? CARDFastDeleteAsync();
// ? CARDDeleteAsync();
// ? CARDDelete();
// ? UpdateIconOffsets();
// ? CARDGetStatus();
// ? CARDSetStatusAsync();
// ? CARDRenameAsync();
// ? CARDRename();
// ? HIOReadMailbox();
// ? HIOWriteMailbox();
// ? HIORead();
// ? HIOWrite();
// ? __GXDefaultTexRegionCallback();
// ? __GXDefaultTlutRegionCallback();
// ? GXInit();
// ? GXCPInterruptHandler();
// ? GXInitFifoBase();
// ? GXInitFifoPtrs();
// ? GXInitFifoLimits();
// ? GXSetCPUFifo();
// ? GXSetGPFifo();
// ? GXSaveCPUFifo();
// ? __GXSaveCPUFifoAux();
// ? GXGetGPStatus();
// ? GXGetFifoPtrs();
// ? __GXFifoInit();
// ? __GXFifoReadEnable();
// ? __GXFifoReadDisable();
// ? __GXFifoLink();
// ? __GXWriteFifoIntEnable();
// ? __GXWriteFifoIntReset();
// ? GXGetCPUFifo();
// ? GXGetGPFifo();
// ? __GXXfVtxSpecs();
// ? GXSetVtxDesc();
// ? GXSetVtxDescv();
// ? __GXSetVCD();
// ? GXGetVtxDesc();
// ? GXGetVtxDescv();
// ? GXClearVtxDesc();
// ? GXSetVtxAttrFmt();
// ? GXSetVtxAttrFmtv();
// ? __GXSetVAT();
// ? GXGetVtxAttrFmt();
// ? func_800DEB2C();
// ? func_800DEB70();
// ? func_800DEB94();
// ? func_800DEBB8();
// ? func_800DEBE0();
// ? func_800DEC08();
// ? func_800DEC30();
// ? func_800DEC58();
// ? func_800DEC80();
// ? func_800DECA8();
// ? func_800DECD0();
// ? GXGetVtxAttrFmtv();
// ? GXInvalidateVtxCache();
// ? GXSetTexCoordGen2();
// ? GXSetNumTexGens();
// ? GXFlush();
// ? GXSetDrawSync();
// ? GXSetDrawDone();
// ? GXDrawDone();
// ? GXPokeAlphaMode();
// ? GXPokeAlphaRead();
// ? GXPokeAlphaUpdate();
// ? GXPokeBlendMode();
// ? GXPokeColorUpdate();
// ? GXPokeDstAlpha();
// ? GXPokeDither();
// ? GXPokeZMode();
// ? GXSetDrawSyncCallback();
// ? GXTokenInterruptHandler();
// ? GXSetDrawDoneCallback();
// ? GXFinishInterruptHandler();
// ? __GXPEInit();
void __GXSetDirtyState(void);
// ? GXBegin();
// ? __GXSendFlushPrim();
// ? GXSetLineWidth();
// ? GXSetPointSize();
// ? GXEnableTexOffsets();
// ? GXSetCullMode();
// ? GXSetCoPlanar();
// ? __GXSetGenMode();
// ? GXAdjustForOverscan();
// ? GXSetDispCopySrc();
// ? GXSetTexCopySrc();
// ? GXSetDispCopyDst();
// ? GXSetTexCopyDst();
// ? GXSetDispCopyFrame2Field();
// ? GXSetCopyClamp();
// ? GXSetDispCopyYScale();
// ? GXSetCopyClear();
// ? GXSetCopyFilter();
// ? GXSetDispCopyGamma();
// ? GXCopyDisp();
// ? GXCopyTex();
// ? GXClearBoundingBox();
// ? GXInitLightAttnK();
// ? GXInitLightSpot();
// ? GXInitLightDistAttn();
// ? GXInitLightPos();
// ? GXGetLightPos();
// ? GXInitLightDir();
// ? GXInitLightColor();
// ? GXGetLightColor();
// ? GXLoadLightObjImm();
// ? GXSetChanAmbColor();
// ? GXSetChanMatColor();
// ? GXSetNumChans();
// ? GXSetChanCtrl();
// ? GXGetTexBufferSize();
// ? __GetImageTileCount();
// ? GXInitTexObj();
// ? GXInitTexObjLOD();
// ? GXInitTexObjWrapMode();
// ? GXGetTexObjData();
// ? GXGetTexObjWidth();
// ? GXGetTexObjHeight();
// ? GXGetTexObjFmt();
// ? GXGetTexObjWrapS();
// ? GXGetTexObjWrapT();
// ? GXGetTexObjMipMap();
// ? GXLoadTexObjPreLoaded();
// ? GXLoadTexObj();
// ? GXInitTexCacheRegion();
// ? GXInitTlutObj();
// ? GXInvalidateTexAll();
// ? GXSetTexRegionCallback();
// ? GXSetTlutRegionCallback();
// ? __SetSURegs();
// ? __GXSetSUTexSize();
// ? GXSetTevIndirect();
// ? GXSetIndTexMtx();
// ? GXSetIndTexCoordScale();
// ? GXSetIndTexOrder();
// ? GXSetNumIndStages();
// ? GXSetTevDirect();
// ? __GXUpdateBPMask();
// ? __GXFlushTextureState();


// ? GXDrawCylinder();
// ? GXDrawSphere();
// ? GXDrawCubeFace();
// ? GXDrawCube();
// ? __GXSetRange();
// ? GXBeginDisplayList();
// ? GXEndDisplayList();
// ? GXCallDisplayList();
// ? GXSetProjection();
// ? GXGetProjectionv();
// ? WriteMTXPS4x3();
// ? WriteMTXPS3x3from3x4();
// ? WriteMTXPS4x2();
// ? GXLoadPosMtxImm();
// ? GXLoadNrmMtxImm();
// ? GXSetCurrentMtx();
// ? GXLoadTexMtxImm();
// ? GXSetViewportJitter();
// ? GXSetViewport();
// ? GXSetScissor();
// ? GXSetScissorBoxOffset();
// ? GXSetClipMode();
// ? __GXSetMatrixIndex();
// ? GXClearGPMetric();
// ? GXInitXfRasMetric();
// ? GXReadXfRasMetric();
// ? PERFResetAllMemMetrics();
// ? PERFGetAllMemMetrics();
// ? PERFTokenCallback();
// ? PERFInit();
// ? PERFSetEvent();
// ? PERFStartFrame();
// ? PERFEndFrame();
// ? PERFEventStart();
// ? PERFEventEnd();
// ? PERFStartAutoSample();
// ? PERFEndAutoSample();
// ? PERFTimerCallback();
// ? PERFStartAutoSampling();
// ? PERFStopAutoSampling();
// ? __PERFDrawInit();
// ? PERFPreDraw();
// ? DrawBWBar();
// ? DrawKey();
// ? PERFDumpScreen();
// ? PERFPostDraw();
// ? PERFSetDrawBWBarKey();

// ? __DTKCallbackForStreamStatus();
// ? __DTKCallbackForRun();
// ? __DTKCallbackForPreparePaused();
// ? __DTKCallbackForPlaylist();
// ? __DTKCallbackForAIInterrupt();
// ? __DTKCallbackForStop();
// ? __DTKCallbackForNextTrack();
// ? __DTKCallbackForPrevTrack();
// ? DTKInit();
// ? DTKQueueTrack();
// ? DTKRemoveTrack();
// ? DTKSetRepeatMode();
// ? DTKSetState();
// ? DTKNextTrack();
// ? DTKPrevTrack();
// ? DTKGetState();
// ? DTKSetVolume();
// ? __va_arg();
// ? __destroy_global_chain();
// ? __unregister_fragment();
// ? __register_fragment();
// ? __cvt_fp2unsigned();
// ? __div2u();
// ? __div2i();
// ? __mod2u();
// ? __mod2i();
// ? __shl2i();
// ? __shr2u();
// ? __shr2i();
// ? __cvt_sll_flt();
// ? __cvt_dbl_usll();
// ? GetR2__Fv();
// ? exit();
// ? __num2dec();
// ? __flush_buffer();
// ? __prep_buffer();
// ? puts();
// ? __put_char();
// ? __kill_critical_regions();
// ? tolower();
// ? fwrite();
// ? wcstombs();
// ? memcmp();
// ? memchr();
// ? memmove();
// ? __copy_longs_rev_unaligned();
// ? __copy_longs_unaligned();
// ? __copy_longs_rev_aligned();
// ? __copy_longs_aligned();
// ? __stdio_atexit();
// ? sprintf();
// ? vsprintf();
// ? vprintf();
// ? printf();
// ? __StringWrite();
// ? __FileWrite();
// ? __pformatter();
// ? float2str();
// ? round_decimal();
// ? longlong2str();
// ? long2str();
// ? parse_format();
// ? srand();
// ? rand();
// ? strchr();
// ? strncmp();
// ? strcmp();
// ? strncat();
// ? strncpy();
// ? strcpy();
// ? strlen();
// ? func_80106B80();
// ? func_80106B88();
// ? func_80106C20();
// ? fwide();
// ? fabs__Fd();
// ? scalbn();
// ? __ieee754_rem_pio2();
// ? __fpclassifyd__Fd();
// ? __kernel_cos();
// ? __kernel_rem_pio2();
// ? __kernel_sin();
// ? copysign();
// ? cos();
// ? floor();
// ? frexp();
// ? ldexp();
// ? sin();
// ? fabsf__Ff();
// ? atanf();
// ? atan__Ff();
// ? _inv_sqrtf();
// ? acosf();
// ? tanf();
// ? cos__Ff();
// ? sin__Ff();
// ? cosf();
// ? sinf();
// ? powf();

// ? AmcEXIImm();
// ? AmcEXISync();
// ? AmcEXIClearInterrupts();
// ? AmcEXISetExiCallback();
// ? AmcEXISelect();
// ? AmcEXIDeselect();
// ? AmcDebugIntHandler();
// ? AmcEXIEnableInterrupts();
// ? AmcEXIInit();
// ? EXI2_CallBack();
// ? EXI2_Init();
// ? EXI2_EnableInterrupts();
// ? EXI2_Poll();
// ? EXI2_ReadN();
// ? EXI2_WriteN();
// ? EXI2_Reserve();
// ? EXI2_Unreserve();
// ? DBGEXIImm();
// ? DBGReadMailbox();
// ? DBGRead();
// ? DBGWrite();
// ? DBGReadStatus();
// ? MWCallback();
// ? DBGHandler();
// ? DBInitComm();
// ? DBInitInterrupts();
// ? DBQueryData();
// ? DBRead();
// ? DBWrite();
// ? DBOpen();
// ? DBClose();
// ? AMC_IsStub();
// ? Hu_IsStub();

#endif
