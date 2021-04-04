#pragma once
#include QMK_KEYBOARD_H

// #include "oled_driver.h"

#define OLED_RENDER_KEYLOGGER "Keylogger: "

#define OLED_RENDER_LOCK_NAME "Lock: "
#define OLED_RENDER_LOCK_NUML "NUML"
#define OLED_RENDER_LOCK_CAPS "CAPS"
#define OLED_RENDER_LOCK_SCLK "SCLK"

#define OLED_RENDER_MODS_NAME "Mods: "
#define OLED_RENDER_MODS_SFT  "Shft"
#define OLED_RENDER_MODS_CTL  "Ctl"
#define OLED_RENDER_MODS_ALT  "Opt"
#define OLED_RENDER_MODS_GUI  "Cmd"

#define OLED_RENDER_BOOTMAGIC_NAME  "Boot  "
#define OLED_RENDER_BOOTMAGIC_NKRO  "NKRO"
#define OLED_RENDER_BOOTMAGIC_NOGUI "nGUI"
#define OLED_RENDER_BOOTMAGIC_GRV   "GRV"
#define OLED_RENDER_BOOTMAGIC_CAPS  "CAPS"

// Keycodes
#define LT_NAVR_ESC LT(NAVR, KC_ESC)
#define LT_MDR_FCS_TAB LT(MEDR_FCS, KC_TAB)
#define BSPC_PRV_WRD LALT(KC_BSPC)
#define BSPC_PRV_LN LGUI(KC_BSPC)
#define MAC_MSTP KC_MPLY // KC_MSTP does't work on macOS

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
#define OS_APP1 LALT(KC_SPC) // App Shortcut
#define OS_APP2 KC_NO // App Shortcut
#define OS_APP3 LCTL(KC_SPC) // App Shortcut

enum layers { BASE, FCS, NAVR, MOUR, MEDR, MEDR_FCS, NSL, NSSL, FUNL, OS, WNDW };

enum custom_keycodes {
  CMD_TAB_PRV = SAFE_RANGE,
  CMD_TAB_NXT,
  OOPS
};

// Combos
enum combos {
  SPC_TAB__GUI,
  ESC_SPC__ALT,
  ESC_SPC_FCS__ALT,
  A_Z__SFT,
  A_Z_FCS__SFT,
  Q_A__CTL,
  Q_A_FCS__CTL,
  ENT_BSPC__GUI,
  BSPC_DEL__ALT,
  O_SLSH__SFT,
  O_SLSH_FCS__SFT,
  QUOT_O__CTL,
  QUOT_O_FCS__CTL
};

// Tap Dance declarations
enum {
    TD_TGL_SEL,
    TD_TAB_BS,
    TD_ESC_GRV
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
    ABORT,
    OTHER
};
