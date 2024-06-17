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
#define WNDW_LWP HYPR(KC_V)         // Last
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
#define WNDW_NXT_SPC HYPR(KC_RIGHT) // Next Space
#define WNDW_PRV_SPC HYPR(KC_LEFT)  // Previous Space
// #define WNDW_FST_FRTH HYPR(KC_?)    // First fourth
// #define WNDW_SCND_FRTH HYPR(KC_?)   // Second fourth
// #define WNDW_THRD_FRTH HYPR(KC_?)   // Third fourth
// #define WNDW_FRTH_FRTH HYPR(KC_?)   // Fourth fourth
// #define WNDW_FST_TFRTH HYPR(KC_?)   // First three-fourth
// #define WNDW_LWP_TFRTH HYPR(KC_?)   // Last three-fourth

// OS (MacOS)
#define OS_PRV_SPC LCTL(KC_LEFT)               // Previous Space
#define OS_NXT_SPC LCTL(KC_RGHT)               // Next Space
#define OS_EXPOSE LCTL(KC_DOWN)                // App Windows
#define OS_MSN_CNTRL LCTL(KC_UP)               // Mission Control
#define OS_DSKTP KC_F11                        // Show Desktop
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
#define OS_PRV_APP_WNDW LGUI(KC_TILD)   // Previous (Same)App Window
#define OS_NXT_WNDW LCTL(KC_F4)         // Next Window
#define OS_PRVS_WNDW LSFT(LCTL(KC_F4))  // Previous Window
#define OS_SPTLGHT LGUI(KC_SPC)         // Spotlight
#define OS_SPTLGHT_FNDR LALT(LGUI(KC_SPC))    // Spotlight in new Finder window
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
// #define OS_CODE HYPR(KC_C)                   // Show VSCode via Service
#define OS_WEB_DEV HYPR(KC_F)                // Show Firefox Developer Edition via Service
#define OS_FLLSCRN LCTL(LGUI(KC_F))          // Fullscreen (green button)
#define OS_MIN LGUI(KC_M)                    // Minimize (yellow button)
#define OS_TL_WNDW_L HYPR(KC_LBRC)           // Tile Window Left (split screen)
#define OS_TL_WNDW_R HYPR(KC_RBRC)           // Tile Window Right (split screen)
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

// Long taps
#define QUOT_LP LT(0, KC_QUOT)
#define DOT_LP LT(0, KC_DOT)
#define MSN_LP_FLLSCRN LT(0, KC_1) // Using non-basic keycode with long press so utility func will not work here, see https://getreuer.info/posts/keyboards/triggers/index.html#tap-vs.-long-press for more info
#define WNDW_LP_VRT_MAX LT(0, KC_2)
#define WNDW_LP_LWP LT(0, KC_3)
#define WNDW_LP_ALMST_MAX LT(0, KC_4)
#define WNDW_LP_SMLR LT(0, KC_5)
#define WNDW_LP_LGR LT(0, KC_6)
#define PRV_SPC_LP LT(0, KC_7)
#define NXT_SPC_LP LT(0, KC_8)
#define TGL_SELECT_LP LT(0, KC_9)

enum layers { BASE, QWRTY, NUMNAV, SYMBL, AUX, HRDWR, FUNC, OS, MOUSE };

enum custom_keycodes {
    CMD_TAB_PRV = SAFE_RANGE, TGL_LYT, CMD_TAB_NXT, DISP_FDIM, DISP_FBRI, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL,
    XOSM_RSFT, XOSM_RGUI, XOSM_RALT, XOSM_RCTL, WNDW_FSCRN, OS_BSPC, OS_DEL, OS_BCK_FWD, LLOCK, ENC_BTN, SHAKE_MOUSE, NO_VOL
};

bool process_tap_or_long_press_key(keyrecord_t* record, uint16_t long_press_keycode);
void tap_code_no_mod(uint8_t);
void tap_code16_no_mod(uint16_t);
void tap_code_unset_mod(uint8_t);
void tap_code16_unset_mod(uint16_t);
bool encoder_update_keymap(uint8_t index, bool clockwise);


#endif
