#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"


// Keycodes
#define BSPC_PRV_WRD LALT(KC_BSPC)
#define BSPC_PRV_LN LGUI(KC_BSPC)
#define MAC_MSTP KC_MPLY // KC_MSTP does't work on macOS
#define DISP_DIM KC_F18
#define DISP_BRI KC_F19

// Window Management (Rectangle)
#define WNDW_SMLLR LCA(KC_MINS) // Smaller
#define WNDW_LRGR LCA(KC_EQL) // Larger
#define WNDW_MV_UP HYPR(KC_Y) // Move up
#define WNDW_MV_DWN HYPR(KC_I) // Move down
#define WNDW_MV_LFT HYPR(KC_E) // Move left
#define WNDW_MV_RGHT HYPR(KC_O) // Move right
#define WNDW_LFT_HLF LCA(KC_LEFT) // Left half
#define WNDW_CNTR_HLF HYPR(KC_C) // Center
#define WNDW_RGHT_HLF LCA(KC_RGHT) // Right half
#define WNDW_TOP_HLF LCA(KC_UP) // Top half
#define WNDW_BTTM_HLF LCA(KC_DOWN) // Bottom half
#define WNDW_CNTR LCA(KC_C) // Center
#define WNDW_RSTR LCA(KC_BSPC) // Restore
#define WNDW_ALMST_MAX HYPR(KC_M) // Almost Maximize
#define WNDW_MAX LCA(KC_ENT) // Maximize
#define WNDW_VRT_MAX MEH(KC_UP) // Vertical Maximize


// OS (MacOS)
#define OS_PRV_SPC LCTL(KC_LEFT) // Previous Space
#define OS_NXT_SPC LCTL(KC_RGHT) // Next Space
#define OS_APP_WNDWS LCTL(KC_DOWN) // App Windows
#define OS_MSN_CNTRL LCTL(KC_UP) // Mission Control
#define OS_DSKTP KC_F11 // Show Desktop
#define OS_SCRN_SHT_OPT SGUI(KC_5) // Screenshot Options
#define OS_SCRN_SHT_SLCT SGUI(KC_4) // Screenshot of selected area
#define OS_SCRN_SHT SGUI(KC_3) // Screenshot
#define OS_SCRN_SHT_CLP_SLCT LCTL(SGUI(KC_4)) // Screenshot of selected area to clipboard
#define OS_SCRN_SHT_CLP LCTL(SGUI(KC_3)) // Screenshot to clipboard
#define OS_SPC5 LCTL(KC_5) // Space 5
#define OS_SPC4 LCTL(KC_4) // Space 4
#define OS_SPC3 LCTL(KC_3) // Space 3
#define OS_SPC2 LCTL(KC_2) // Space 2
#define OS_SPC1 LCTL(KC_1) // Space 1
// #define OS_NXT_APP LGUI(KC_TAB) // Next App Window
// #define OS_PRVS_APP SGUI(KC_TAB) // Previous App Window
#define OS_NXT_APP_WNDW LGUI(KC_GRV) // Next (Same)App Window
#define OS_PRVS_APP_WNDW LGUI(KC_TILD) // Previous (Same)App Window
#define OS_FLLSCRN LCTL(LGUI(KC_F)) // Fullscreen
#define OS_SPTLGHT LGUI(KC_SPC) // Spotlight
// custom (non-default) in OS
#define OS_SIRI HYPR(KC_S) // Siri
#define OS_LNCHPD HYPR(KC_L) // Launchpad
#define OS_SDBR HYPR(KC_N) // Sidebar

// App Shortcuts
#define APP1 LALT(KC_SPC) // App Shortcut
#define APP2 LCTL(KC_SPC) // App Shortcut
#define APP3 KC_NO // App Shortcut
#define APP4 KC_NO // App Shortcut


// Layer declarations
#if defined HOME_ROW_MODS
    enum layers { BASE_HRM, BASE, SFT_BASE, LOWER, MOUR, MEDR_HRM, MEDR, NSL, NSSL, FUNL, OS, WNDW };
#else
    enum layers { BASE, BASE_HRM, SFT_BASE, LOWER, LOW, LOWEST, HIGHER, HIGHER_HRM, HIGH, HIGHEST, OS, WNDW };
#endif



enum planck_keycodes {
  CMD_TAB_PRV = SAFE_RANGE,
  CMD_TAB_NXT,
  PRV_APP,
  OOPS,
  DISP_FDIM,
  DISP_FBRI,
  OSHR,
  VOL_JUP,
  XOSM_LSFT,
  XOSM_LGUI,
  XOSM_LALT,
  XOSM_LCTL,
  XOSM_RSFT,
  XOSM_RGUI,
  XOSM_RALT,
  XOSM_RCTL
};

// Tap Dance declarations
enum {
    TD_TGL_SEL, // Toggle Select (similar to double, triple, and quadruple mouse click)
    TD_CAPS_WORD,
    TD_CAPS_SENTENCE,
    TD_LGUI,
    TD_SFT_LGUI,
    TD_RGUI,
    TD_SFT_RGUI,
    TD_LALT,
    TD_SFT_LALT,
    TD_RALT,
    TD_SFT_RALT,
    TD_LCTL,
    TD_SFT_LCTL,
    TD_RCTL,
    TD_SFT_RCTL,
    // TD_G_DOT
};

// For use with cur_dance()
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    TRIPLE_TAP,
    TRIPLE_HOLD,
    QUADRUPLE_TAP,
    QUADRUPLE_HOLD,
    TAP,
    HOLD,
    ABORT,
    OTHER
};

// Combos
// enum combos {
//   COMBO_OSHR
// };

// enum combo_events {
//   COMBO_OSHR,
//   COMBO_OOPS
// };

#endif
