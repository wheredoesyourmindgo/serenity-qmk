#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define MODS_RSFT (get_mods() & MOD_BIT(KC_RSFT))
#define MODS_LSFT (get_mods() & MOD_BIT(KC_LSFT))
#define MODS_RCTRL (get_mods() & MOD_BIT(KC_RCTL))
#define MODS_LCTRL (get_mods() & MOD_BIT(KC_LCTL))
#define MODS_RALT (get_mods() & MOD_BIT(KC_RALT))
#define MODS_LALT (get_mods() & MOD_BIT(KC_LALT))
#define MODS_RGUI (get_mods() & MOD_BIT(KC_RGUI))
#define MODS_LGUI (get_mods() & MOD_BIT(KC_LGUI))
#define MODS_SFT (MODS_LSFT || MODS_RSFT)
#define MODS_CTRL (MODS_LCTRL || MODS_RCTRL)
#define MODS_ALT (MODS_LALT || MODS_RALT)
#define MODS_GUI (MODS_LGUI || MODS_RGUI)
// #define ACTIVE_MODS (get_mods())
// #define ONESHOT_LYR_ACTIVE (is_oneshot_layer_active())
#define ONESHOT_MODS_ACTIVE (get_oneshot_mods())
// #define ONESHOT_MODS_LSFT (get_oneshot_mods() & MOD_BIT(KC_LSFT))
// #define ONESHOT_MODS_LGUI (get_oneshot_mods() & MOD_BIT(KC_LGUI))
// #define ONESHOT_MODS_RGUI (get_oneshot_mods() & MOD_BIT(KC_RGUI))
// #define ONESHOT_MODS_LALT (get_oneshot_mods() & MOD_BIT(KC_LALT))
// #define ONESHOT_MODS_LCTL (get_oneshot_mods() & MOD_BIT(KC_LCTL))
// #define ONESHOT_MODS_RSFT (get_oneshot_mods() & MOD_BIT(KC_RSFT))
// #define ONESHOT_MODS_RALT (get_oneshot_mods() & MOD_BIT(KC_RALT))
// #define ONESHOT_MODS_RCTL (get_oneshot_mods() & MOD_BIT(KC_RCTL))
// #define ONESHOT_MODS_GUI (ONESHOT_MODS_LGUI || ONESHOT_MODS_RGUI)
// #define ONESHOT_MODS_ALT (ONESHOT_MODS_LALT || ONESHOT_MODS_RALT)
// #define ONESHOT_MODS_CTRL (ONESHOT_MODS_LCTL || ONESHOT_MODS_RCTL)
// #define ONESHOT_MODS_SFT (ONESHOT_MODS_LSFT || ONESHOT_MODS_RSFT)

// F16 is used to show deskop (set in macOS preferences)
// F17-F18 are used with display brightness below (set in macOS preferences)
// F19-F24 are reserved for use with other devices

// Keycodes
#define BSPC_PRV_WRD LALT(KC_BSPC)  // Backspace previous word
#define BSPC_PRV_LN LGUI(KC_BSPC)   // Backspace previous line
#define MAC_MSTP KC_MPLY            // KC_MSTP does't work on macOS
// Issue with External LG Monitor/display. Karabiner seems to block Control-brightness. Easiest workaround is to map display brightness controls in macOS system preferences to a function key.
#define DISP_DIM KC_F17             // Dim Display
#define DISP_BRI KC_F18             // Brighten Display
#define ZOOM_IN_APP LGUI(KC_PLUS)       // Zoom in app
#define ZOOM_OUT_APP LGUI(KC_MINUS)     // Zoom out app
#define ZOOM_RESET_APP LGUI(KC_P0)      // Zoom reset app
#define ZOOM_IN LALT(LGUI(KC_EQL))       // Zoom in
#define ZOOM_OUT LALT(LGUI(KC_MINUS))     // Zoom out
#define ZOOM_RESET LALT(LGUI(KC_8))      // Zoom reset

#define UNDO LGUI(KC_Z)             // Undo
#define CUT LGUI(KC_X)              // Cut
#define COPY LGUI(KC_C)             // Copy
#define PASTE LGUI(KC_V)            // Paste
#define REDO SGUI(KC_Z)             // Redo

// Tiling Management (Amethyst)
#define TLNG_FLT LALT(LSFT(KC_G))                   // Floating layout
#define TLNG_FSCRN LALT(LSFT(KC_D))                 // Fullscreen layout
#define TLNG_THRW_RGHT LCTL(LALT(LSFT(KC_RIGHT)))   // Throw window to right space
#define TLNG_THRW_LFT LCTL(LALT(LSFT(KC_LEFT)))     // Throw window to right space
#define TLNG_MV_FCS_CLK LALT(LSFT(KC_K))            // Move focus clockwise
#define TLNG_MV_FCS_CCLK LALT(LSFT(KC_J))           // Move focus counter clockwise
#define TLNG_MV_FCS_MN LALT(LSFT(KC_M))             // Move focus to main
#define TLNG_SWP_FCS_MN LALT(LSFT(KC_ENT))          // Swap focus to main
#define TLNG_LYT_INF LALT(LSFT(KC_I))               // Display current layout
#define TLNG_LYT_FWD LALT(LSFT(KC_SPC))             // Cycle layout forward
#define TLNG_LYT_BCK LCTL(LALT(LSFT(KC_SPC)))       // Cycle layout forward
#define TLNG_SHRNK LALT(LSFT(KC_H))                 // Shrink main
#define TLNG_EXP LALT(LSFT(KC_L))                   // Expand main
#define TLNG_RVLT LALT(LSFT(KC_Z))                  // Re-evaluate
#define TLNG_RLD LCTL(LALT(LSFT(KC_Z)))             // Reload Amethyst
#define TLNG_MSE_FCS LALT(LSFT(LCTL(KC_X)))         // Toggle focus follows mouse
#define TLNG_GLBL_TLNG LCTL(LALT(LSFT(KC_T)))       // Toggle global tiling
#define TLNG_TGL_FLT_FCS LALT(LSFT(KC_T))           // Toggle float focused
#define TLNG_INCR_MN_CT LALT(LSFT(KC_COMMA))        // Increase main count
#define TLNG_DCR_MN_CT LALT(LSFT(KC_DOT))           // Decrease main count


// Window Management (Rectangle)
#define WNDW_SMLLR LCA(KC_MINS)     // Smaller
#define WNDW_LRGR LCA(KC_EQL)       // Larger
#define WNDW_MV_UP HYPR(KC_Y)       // Move up
#define WNDW_MV_DWN HYPR(KC_I)      // Move down
#define WNDW_MV_LFT HYPR(KC_E)      // Move left
#define WNDW_MV_RGHT HYPR(KC_O)     // Move right
#define WNDW_LFT_TTHRD LCA(KC_E)    // Left two-thirds
#define WNDW_RGHT_TTHRD LCA(KC_T)   // Right two-thirds
#define WNDW_CNTR_TTHRD LCA(KC_T)   // Center two-thirds
#define WNDW_LFT_THRD LCA(KC_D)     // Left third
#define WNDW_CNTR_THRD LCA(KC_F)    // Center third
#define WNDW_RGNT_THRD LCA(KC_G)    // Right third
#define WNDW_LFT_HLF LCA(KC_LEFT)   // Left half
#define WNDW_CNTR_HLF HYPR(KC_G)    // Center
#define WNDW_RGHT_HLF LCA(KC_RGHT)  // Right half
#define WNDW_TOP_HLF LCA(KC_UP)     // Top half
#define WNDW_BTTM_HLF LCA(KC_DOWN)  // Bottom half
#define WNDW_CNTR LCA(KC_C)         // Center
#define WNDW_RSTR LCA(KC_BSPC)      // Restore
#define WNDW_ALMST_MAX HYPR(KC_M)   // Almost Maximize
#define WNDW_MAX LCA(KC_ENT)        // Maximize
#define WNDW_VRT_MAX MEH(KC_UP)     // Vertical Maximize
#define WNDW_TOP_LEFT LCA(KC_U)     // Top left
#define WNDW_TOP_RGHT LCA(KC_I)     // Top right
#define WNDW_BTM_LFT LCA(KC_J)      // Bottom left
#define WNDW_BTM_RGHT LCA(KC_K)     // Bottom right
// #define WNDW_FST_FRTH HYPR(KC_Z)    // First fourth
// #define WNDW_SCND_FRTH HYPR(KC_X)   // Second fourth
// #define WNDW_THRD_FRTH HYPR(KC_C)   // Third fourth
// #define WNDW_FRTH_FRTH HYPR(KC_D)   // Fourth fourth
// #define WNDW_FST_TFRTH HYPR(KC_LBRC)   // First three-fourth
// #define WNDW_LST_TFRTH HYPR(KC_RBRC)   // Last three-fourth

// OS (MacOS)
#define OS_PRV_SPC LCTL(KC_LEFT)               // Previous Space
#define OS_NXT_SPC LCTL(KC_RGHT)               // Next Space
#define OS_EXPOSE LCTL(KC_DOWN)                // App Windows
#define OS_MSN_CNTRL LCTL(KC_UP)               // Mission Control
#define OS_DSKTP KC_F16                        // Show Desktop
#define OS_SCRN_SHT_OPT SGUI(KC_5)             // Screenshot Options
#define OS_SCRN_SHT_SLCT SGUI(KC_4)            // Screenshot of selected area
#define OS_SCRN_SHT SGUI(KC_3)                 // Screenshot
#define OS_SCRN_SHT_CLP_SLCT LCTL(SGUI(KC_4))  // Screenshot of selected area to clipboard
#define OS_SCRN_SHT_CLP LCTL(SGUI(KC_3))       // Screenshot to clipboard
// #define OS_SPC5 LCTL(KC_5)                     // Space 5
// #define OS_SPC4 LCTL(KC_4)                     // Space 4
// #define OS_SPC3 LCTL(KC_3)                     // Space 3
// #define OS_SPC2 LCTL(KC_2)                     // Space 2
#define OS_SPC1 LCTL(KC_1)                     // Space 1
#define OS_DOCK LCTL(KC_F3)                    // Focus Dock
// #define OS_NXT_APP LGUI(KC_TAB) // Next App Window
// #define OS_PRVS_APP SGUI(KC_TAB) // Previous App Window
#define OS_NXT_APP_WNDW LGUI(KC_GRV)    // Next (Same)App Window
#define OS_PRV_APP_WNDW LGUI(KC_TILD)  // Previous (Same)App Window
#define OS_NXT_WNDW LCTL(KC_F4)         // Next Window
#define OS_PRVS_WNDW LSFT(LCTL(KC_F4))  // Previous Window
#define OS_SPTLGHT LGUI(KC_SPC)         // Spotlight
#define OS_BCK LGUI(KC_LBRC)            // Back
#define OS_FWD LGUI(KC_RBRC)            // Forward
#define OS_BCK_FLDR LGUI(KC_UP)         // Back Folder
#define OS_FWD_FLDR LGUI(KC_DOWN)       // Forward Folder
#define OS_NXT_TAB LCTL(KC_TAB)         // Next Tab
#define OS_PRV_TAB LSFT(LCTL(KC_TAB))   // Previous Tab
// custom (non-default) in OS
#define OS_SIRI HYPR(KC_S)                   // Siri
#define OS_LNCHPD HYPR(KC_L)                 // Launchpad
#define OS_SDBR HYPR(KC_N)                   // Sidebar
#define OS_DRKMD_TGL HYPR(KC_D)              // Toggle Dark Mode via AppleScript
#define OS_MAIL HYPR(KC_J)                   // Show Mail via Service
#define OS_WEB HYPR(KC_W)                    // Show Web Browser via Service
#define OS_CODE HYPR(KC_V)                   // Show VSCode via Service
#define OS_WEB_DEV HYPR(KC_F)                // Show Firefox Developer Edition via Service
#define OS_FLLSCRN LCTL(LGUI(KC_F))          // Fullscreen (green button)
#define OS_MIN LGUI(KC_M)                    // Minimize (yellow button)
#define OS_CLOSE LGUI(KC_W)                  // Close active app
#define OS_CLOSE_WIN LGUI(LSFT(KC_W))        // Close win active app (red button-ish)
#define OS_CLOSE_ALL LGUI(LSFT(LALT(KC_W)))  // Close all win active app
#define OS_TRM_VSR LCTL(KC_SPC)              // Terminal visor
#define OS_LNCHR LALT(KC_SPC)                // Launcher (Alfred)

// App Shortcuts
#define APP1 OS_MAIL       // App Shortcut
#define APP2 OS_WEB        // App Shortcut
#define APP3 LALT(KC_SPC)  // App Shortcut
#define APP4 LCTL(KC_SPC)  // App Shortcut
#define APP5 OS_CODE       // App Shortcut
#define APP6 OS_WEB_DEV    // App Shortcut
#define APP7 KC_NO         // App Shortcut
#define APP8 KC_NO         // App Shortcut

#define PRV_APP LGUI(KC_TAB)

enum layers { BASE, QWRTY, NUMNAV, SYMBL, MOUSE, AUX, HRDWR, FUNC, FUNCXTR, OS };

enum custom_keycodes { CMD_TAB_PRV = SAFE_RANGE, CAPS_SENTENCE, TGL_LYT, CMD_TAB_NXT, DISP_FDIM, DISP_FBRI, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, XOSM_RSFT, XOSM_RGUI, XOSM_RALT, XOSM_RCTL, WNDW_FSCRN, TLNG_LFT, TLNG_RGHT, XWNDW_MAX, WNDW_LFT, WNDW_RGHT, WNDW_ILFT, WNDW_IRGHT, OS_BSPC, OS_DEL, OS_BCK_FWD, LLOCK, ENC_BTN, SHAKE_MOUSE};

// Tap Dance declarations
enum {
    TD_TGL_SEL,  // Toggle Select (similar to double, triple, and quadruple mouse click)
    TD_MULTI_MAX,
    TD_MULTI_RSTR,
    TD_OOPS,
    TD_PEMDAS,
    TD_DOTEQL,
    TD_F6_F16,
    TD_F7_F17,
    TD_F8_F18,
    TD_F9_F19,
    TD_F10_F20,
    TD_F11_F21,
    TD_F12_F22,
    TD_F13_F23,
    TD_F14_F24
};

// Tap dance state
// typedef enum { TD_NONE, TD_INTERRUPTED, TD_NOT_INTERRUPTED } td_state_t;

// typedef struct {
//     bool    is_press_action;
//     uint8_t state;
// } td_tap_t;

// Functions associated with individual tap dances
void oopsy_finished(qk_tap_dance_state_t *state, void *user_data);
void oopsy_reset(qk_tap_dance_state_t *state, void *user_data);
void tgl_select(qk_tap_dance_state_t *state, void *user_data);
void multi_max_each(qk_tap_dance_state_t *state, void *user_data);
void multi_rst_each(qk_tap_dance_state_t *state, void *user_data);
void pemdas_finished(qk_tap_dance_state_t *state, void *user_data);

void tap_code_no_mod(uint8_t);
void tap_code16_no_mod(uint16_t);
bool encoder_update_keymap(uint8_t index, bool clockwise);

#if defined PLANCK_KEYBOARD
#define LAYOUT_4x12(k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b)      \
        {                                                                                                                                                                                                                                                                    \
            {k00, k01, k02, k03, k04, k05}, {k10, k11, k12, k13, k14, k15}, {k20, k21, k22, k23, k24, k25}, {k30, k31, k32, k39, k3a, k3b}, {k06, k07, k08, k09, k0a, k0b}, {k16, k17, k18, k19, k1a, k1b}, {k26, k27, k28, k29, k2a, k2b}, { k36, k37, k38, k33, k34, k35 } \
        }
#elif defined TECHNIK_KEYBOARD
#define LAYOUT_4x12(K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K40, K41, K42, K43, K44, K45, K46, K47) \
        {                                                                                                                                                                                                                                                               \
            {K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11}, {K12, K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23}, {K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, K34, K35}, { K36, K37, K38, K39, K40, K41, K42, K43, K44, K45, K46, K47 }    \
        }
#elif defined CORNELIUS_KEYBOARD
#define LAYOUT_4x12( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311 \
) \
{ \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311 } \
}
#elif defined SIGNUM_KEYBOARD
#define LAYOUT_4x12(K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311) \
        {                                                                                                                                                                                                                                                                                                               \
            {K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011}, {K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111}, {K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211}, { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311 }    \
        }
#elif defined RISTRETTO_KEYBOARD
#define LAYOUT_4x12_enc( \
		K000, K001, K002, K003, K004, K005, 	  K007, K008, K009, K010, K011, K012, \
		K100, K101, K102, K103, K104, K105,		  K107, K108, K109, K110, K111, K112, \
		K200, K201, K202, K203, K204, K205,		  K207, K208, K209, K210, K211, K212, \
		K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312  \
) { \
		{K000, K001, K002, K003, K004, K005, KC_NO, K007, K008, K009, K010, K011, K012}, \
		{K100, K101, K102, K103, K104, K105, KC_NO, K107, K108, K109, K110, K111, K112}, \
		{K200, K201, K202, K203, K204, K205, KC_NO, K207, K208, K209, K210, K211, K212}, \
		{K300, K301, K302, K303, K304, K305, K306 , K307, K308, K309, K310, K311, K312}  \
}
#elif defined VITAMINS_INCLUDED_KEYBOARD
#define LAYOUT_4x12( \
	L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
	L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
	L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
	L30, L31, L32, L33, L34, L35, R30, R31, R32, R33, R34, R35 \
	) \
	{ \
		{ L00, L01, L02, L03, L04, L05 }, \
		{ L10, L11, L12, L13, L14, L15 }, \
		{ L20, L21, L22, L23, L24, L25 }, \
		{ L30, L31, L32, L33, L34, L35 }, \
		{ R00, R01, R02, R03, R04, R05 }, \
		{ R10, R11, R12, R13, R14, R15 }, \
		{ R20, R21, R22, R23, R24, R25 }, \
		{ R30, R31, R32, R33, R34, R35 } \
  }
#elif defined QUARK_KEYBOARD
#define LAYOUT_4x12( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX } \
}

#endif


#endif
