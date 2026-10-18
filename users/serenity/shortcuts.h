// Named macOS / app shortcuts used by the keymaps and userspace code.
#pragma once

// F14-F15 are used with display brightness below (set in macOS preferences)
// F19-F24 are reserved for use with other devices

// Editing
#define UNDO LGUI(KC_Z)   // Undo
#define REDO SGUI(KC_Z)   // Redo
#define CUT LGUI(KC_X)    // Cut
#define COPY LGUI(KC_C)   // Copy
#define PASTE LGUI(KC_V)  // Paste

// Zoom
#define ZOOM_IN LALT(LGUI(KC_EQL))     // Zoom in
#define ZOOM_OUT LALT(LGUI(KC_MINUS))  // Zoom out
#define ZOOM_RESET LALT(LGUI(KC_8))    // Zoom reset
#define ZOOM_IN_APP LGUI(KC_PLUS)      // Zoom in app
#define ZOOM_OUT_APP LGUI(KC_MINUS)    // Zoom out app
#define ZOOM_RESET_APP LGUI(KC_P0)     // Zoom reset app

// Display brightness
// Issue with External LG Monitor/display. Karabiner seems to block Control-brightness. Easiest workaround is to map display brightness controls in macOS system preferences to a function key.
#define DISP_DIM KC_F14  // Dim Display
#define DISP_BRI KC_F15  // Brighten Display

// Spaces & Mission Control (macOS)
#define OS_PRV_SPC LCTL(KC_LEFT)  // Previous Space
#define OS_NXT_SPC LCTL(KC_RGHT)  // Next Space
#define OS_MSN_CNTRL LCTL(KC_UP)  // Mission Control
#define OS_EXPOSE LCTL(KC_DOWN)   // App Windows
#define OS_DSKTP KC_F11           // Show Desktop

// Apps, windows & tabs (macOS)
#define OS_PRV_APP LGUI(KC_TAB)             // Previous App
#define OS_NXT_APP_WNDW LGUI(KC_GRV)        // Next (Same)App Window
#define OS_PRV_APP_WNDW LGUI(KC_TILD)       // Previous (Same)App Window
#define OS_NXT_TAB LCTL(KC_TAB)             // Next Tab
#define OS_PRV_TAB LSFT(LCTL(KC_TAB))       // Previous Tab
#define OS_FLLSCRN LCTL(LGUI(KC_F))         // Fullscreen (green button)
#define OS_MIN LGUI(KC_M)                   // Minimize (yellow button)
#define OS_CLOSE LGUI(KC_W)                 // Close active app
#define OS_DOCK LCTL(KC_F3)                 // Focus Dock
#define OS_SPTLGHT LGUI(KC_SPC)             // Spotlight
#define OS_SPTLGHT_FNDR LALT(LGUI(KC_SPC))  // Spotlight in new Finder window

// Screenshots (macOS)
#define OS_SCRN_SHT SGUI(KC_3)                 // Screenshot
#define OS_SCRN_SHT_CLP LCTL(SGUI(KC_3))       // Screenshot to clipboard
#define OS_SCRN_SHT_SLCT SGUI(KC_4)            // Screenshot of selected area
#define OS_SCRN_SHT_CLP_SLCT LCTL(SGUI(KC_4))  // Screenshot of selected area to clipboard
#define OS_SCRN_SHT_OPT SGUI(KC_5)             // Screenshot Options

// Custom (non-default) macOS shortcuts, set in macOS preferences
#define OS_SIRI HYPR(KC_S)          // Siri
#define OS_LNCHPD HYPR(KC_L)        // Launchpad
#define OS_SDBR HYPR(KC_N)          // Sidebar
#define OS_DRKMD_TGL HYPR(KC_D)     // Toggle Dark Mode via AppleScript

// Window Management (Rectangle)
#define WNDW_LFT_HLF LCTL(LALT(LGUI(KC_LEFT)))   // Left half
#define WNDW_RGHT_HLF LCTL(LALT(LGUI(KC_RGHT)))  // Right half
#define WNDW_LFT_FILL LCTL(LALT(LGUI(KC_L)))     // Left Fill
#define WNDW_RGHT_FILL LCTL(LALT(LGUI(KC_R)))    // Right Fill
#define WNDW_CNTR LCA(KC_C)                      // Center
#define WNDW_MAX LCA(KC_ENT)                     // Maximize
#define WNDW_ALMST_MAX HYPR(KC_M)                // Almost Maximize
#define WNDW_VRT_MAX MEH(KC_UP)                  // Vertical Maximize
#define WNDW_RSTR LCA(KC_BSPC)                   // Restore
#define WNDW_LWP HYPR(KC_V)                      // Last
#define WNDW_SMLLR LCA(KC_MINS)                  // Smaller
#define WNDW_LRGR LCA(KC_EQL)                    // Larger
#define WNDW_PRV_SPC HYPR(KC_LEFT)               // Previous Space
#define WNDW_NXT_SPC HYPR(KC_RIGHT)              // Next Space

// Tap / long-press keys, handled in long_press.c
#define QUOT_LP LT(0, KC_QUOT)
#define DOT_LP LT(0, KC_DOT)
// The long press on these sends a non-basic keycode, so process_tap_or_long_press_key() can't be used.
// See https://getreuer.info/posts/keyboards/triggers/index.html#tap-vs.-long-press
#define OS_SCRN_SHT_LP LT(0, KC_A)
#define OS_SCRN_SHT_SLCT_LP LT(0, KC_B)
#define OS_SCRN_SHT_WNDW_LP LT(0, KC_C)
#define WNDW_VRT_MAX_LP LT(0, KC_2)
#define WNDW_MAX_LP LT(0, KC_D)
#define WNDW_CNTR_LP LT(0, KC_E)
#define WNDW_LFT_LP LT(0, KC_F)
#define WNDW_RGHT_LP LT(0, KC_G)
