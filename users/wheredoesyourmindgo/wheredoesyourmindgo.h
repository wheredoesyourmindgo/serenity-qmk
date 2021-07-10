#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Keycodes
#define BSPC_PRV_WRD LALT(KC_BSPC)  // Backspace previous word
#define BSPC_PRV_LN LGUI(KC_BSPC)   // Backspace previous line
#define MAC_MSTP KC_MPLY            // KC_MSTP does't work on macOS
#define DISP_DIM KC_F18             // Dim Display
#define DISP_BRI KC_F19             // Brighten Display
#define ZOOM_IN LGUI(KC_PLUS)       // Zoom In
#define ZOOM_OUT LGUI(KC_MINUS)     // Zoom Out
#define ZOOM_RESET LGUI(KC_P0)      // Zoom Reset
#define PASTE LGUI(KC_V)
#define COPY LGUI(KC_C)
#define CUT LGUI(KC_X)
#define UNDO LGUI(KC_Z)
#define REDO SGUI(KC_Z)

// Window Management (Rectangle)
#define WNDW_SMLLR LCA(KC_MINS)     // Smaller
#define WNDW_LRGR LCA(KC_EQL)       // Larger
#define WNDW_MV_UP HYPR(KC_Y)       // Move up
#define WNDW_MV_DWN HYPR(KC_I)      // Move down
#define WNDW_MV_LFT HYPR(KC_E)      // Move left
#define WNDW_MV_RGHT HYPR(KC_O)     // Move right
#define WNDW_LFT_TTHRD LCA(KC_E)    // Left two-thirds
#define WNDW_RGHT_TTHRD LCA(KC_T)   // Right two-thirds
#define WNDW_LFT_THRD LCA(KC_D)     // Right third
#define WNDW_RGNT_THRD LCA(KC_G)    // Left third
#define WNDW_LFT_HLF LCA(KC_LEFT)   // Left half
#define WNDW_CNTR_HLF HYPR(KC_C)    // Center
#define WNDW_RGHT_HLF LCA(KC_RGHT)  // Right half
#define WNDW_TOP_HLF LCA(KC_UP)     // Top half
#define WNDW_BTTM_HLF LCA(KC_DOWN)  // Bottom half
#define WNDW_CNTR LCA(KC_C)         // Center
#define WNDW_RSTR LCA(KC_BSPC)      // Restore
#define WNDW_ALMST_MAX HYPR(KC_M)   // Almost Maximize
#define WNDW_MAX LCA(KC_ENT)        // Maximize
#define WNDW_VRT_MAX MEH(KC_UP)     // Vertical Maximize

// OS (MacOS)
#define OS_PRV_SPC LCTL(KC_LEFT)               // Previous Space
#define OS_NXT_SPC LCTL(KC_RGHT)               // Next Space
#define OS_APP_WNDWS LCTL(KC_DOWN)             // App Windows
#define OS_MSN_CNTRL LCTL(KC_UP)               // Mission Control
#define OS_DSKTP KC_F11                        // Show Desktop
#define OS_SCRN_SHT_OPT SGUI(KC_5)             // Screenshot Options
#define OS_SCRN_SHT_SLCT SGUI(KC_4)            // Screenshot of selected area
#define OS_SCRN_SHT SGUI(KC_3)                 // Screenshot
#define OS_SCRN_SHT_CLP_SLCT LCTL(SGUI(KC_4))  // Screenshot of selected area to clipboard
#define OS_SCRN_SHT_CLP LCTL(SGUI(KC_3))       // Screenshot to clipboard
#define OS_SPC5 LCTL(KC_5)                     // Space 5
#define OS_SPC4 LCTL(KC_4)                     // Space 4
#define OS_SPC3 LCTL(KC_3)                     // Space 3
#define OS_SPC2 LCTL(KC_2)                     // Space 2
#define OS_SPC1 LCTL(KC_1)                     // Space 1
// #define OS_NXT_APP LGUI(KC_TAB) // Next App Window
// #define OS_PRVS_APP SGUI(KC_TAB) // Previous App Window
#define OS_NXT_APP_WNDW LGUI(KC_GRV)    // Next (Same)App Window
#define OS_PRVS_APP_WNDW LGUI(KC_TILD)  // Previous (Same)App Window
#define OS_SPTLGHT LGUI(KC_SPC)         // Spotlight
#define OS_BCK LGUI(KC_LBRC)            // Back
#define OS_FWD LGUI(KC_RBRC)            // Forward
#define OS_BCK_FLDR LGUI(KC_UP)         // Back Folder
#define OS_FWD_FLDR LGUI(KC_DOWN)       // Forward Folder
// custom (non-default) in OS
#define OS_SIRI HYPR(KC_S)       // Siri
#define OS_LNCHPD HYPR(KC_L)     // Launchpad
#define OS_SDBR HYPR(KC_N)       // Sidebar
#define OS_DRKMD_TGL HYPR(KC_D)  // Toggle Dark Mode via AppleScript
#define OS_MAIL HYPR(KC_J)       // Show Mail via Service
#define OS_WEB HYPR(KC_W)        // Show Web Browser via Service
#define OS_CODE HYPR(KC_V)       // Show VSCode via Service
#define OS_WEB_DEV HYPR(KC_F)    // Show Firefox Developer Edition via Service
#define OS_FLLSCRN LCTL(LGUI(KC_F))     // Fullscreen (green button)
#define OS_MIN LGUI(KC_M)       // Minimize (yellow button)
#define OS_CLOSE LGUI(LSFT(KC_W))      // Close active app (red button)
#define OS_CLOSE_ALL LGUI(LSFT(LALT(KC_W)))      // Close All App Windows active app

// App Shortcuts
#define APP1 OS_MAIL       // App Shortcut
#define APP2 OS_WEB        // App Shortcut
#define APP3 LALT(KC_SPC)  // App Shortcut
#define APP4 LCTL(KC_SPC)  // App Shortcut
#define APP5 OS_CODE       // App Shortcut
#define APP6 OS_WEB_DEV    // App Shortcut
#define APP7 KC_NO         // App Shortcut
#define APP8 KC_NO         // App Shortcut

// Placeholder for bailing out of retro tap
#define VOID KC_NO

#define PRV_APP LGUI(KC_TAB)

enum layers { BASE, BASE_HRM, LOWER, LOWER_ALT, LOW, LOWEST, HIGHER, HIGHER_HRM, HIGH, HIGHEST, OS, WNDW };

enum keycodes { CMD_TAB_PRV = SAFE_RANGE, CMD_TAB_NXT, OOPS, DISP_FDIM, DISP_FBRI, OSHR, VOL_JUP, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, XOSM_RSFT, XOSM_RGUI, XOSM_RALT, XOSM_RCTL, TRY_BSPACE_WORD };

// Tap Dance declarations
enum {
    TD_TGL_SEL,  // Toggle Select (similar to double, triple, and quadruple mouse click)
    TD_LOWER_ESC,
    TD_LOW_ENT,
    TD_CAPS_WORD,
    TD_CAPS_SENTENCE,
    TD_OOPSY,
    TD_OS_GRV_OSHR
};

// Tap dance state
typedef enum { TD_NONE, TD_INTERRUPTED, TD_NOT_INTERRUPTED } td_state_t;

#if defined PLANCK_KEYBOARD
#define LAYOUT_4x12( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k39, k3a, k3b }, \
    { k06, k07, k08, k09, k0a, k0b }, \
    { k16, k17, k18, k19, k1a, k1b }, \
    { k26, k27, k28, k29, k2a, k2b }, \
    { k36, k37, k38, k33, k34, k35 } \
}
#elif defined TECHNIK_KEYBOARD
#define LAYOUT_4x12( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, \
    K12, K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, \
    K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, \
    K36, K37, K38, K39, K40, K41, K42, K43, K44, K45, K46, K47 \
    ) { \
        {K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11}, \
        {K12, K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23}, \
        {K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, K34, K35}, \
        {K36, K37, K38, K39, K40, K41, K42, K43, K44, K45, K46, K47} \
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
#define LAYOUT_4x12( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311 \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009, K010, K011 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109, K110, K111 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209, K210, K211 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309, K310, K311 } \
}
#elif defined BOARDWALK_KEYBOARD
#define LAYOUT_boardwalk_hs( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, k011, k012, k013, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, k112, k113, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, k212, k213, \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, k312, k313, \
  k40, k41, k42, k43, k44,   k45,     k47,     k49, k410, k411, k412, k413  \
) \
{ \
  { k00,   k01, k02, k03, k04, k05, k06,   k07, k08,   k09, k010, k011, k012, k013   }, \
  { k10,   k11, k12, k13, k14, k15, k16,   k17, k18,   k19, k110, k111, k112, k113   }, \
  { k20,   k21, k22, k23, k24, k25, k26,   k27, k28,   k29, k210, k211, k212, k213   }, \
  { k30,   k31, k32, k33, k34, k35, k36,   k37, k38,   k39, k310, k311, k312, k313   }, \
  { k40,   k41, k42, k43, k44, k45, KC_NO, k47, KC_NO, k49, k410, k411, k412, k413   } \
}
#endif



#endif
