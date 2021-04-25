# I 🖤 Shift Keys

## About

This is a QMK layout that includes dedicated right and left shift keys. Optionally home row mods can be toggled on; Home row mods are turned off by default. The Base layer uses the Colemak-DH layout. This layout is configured for use with macOS and would generally be used with a 42+ key layout.

## Features

- 6+ layers inspired from the Miryoku and Foostan layouts: Lower (Numbers/Navigation), Low (Symbols), Lowest (Mouse Mode), Higher (Cut-copy-paste/Special), High (Media/Keyboard), and Highest (Function). See below for 2 additional macOS layers.
- Home Row Mods that can be toggled on/off with a Higher+a press. Home row mods are available on all Layers for the same hand that triggers the Layer.
- One Shot Home Row Mods that can be toggled on/off with a Higher+t press. Bail out of One-shot by tapping Esc key.
- One Shot Mods on Home Row when activating any of the 6 principle layers. These are particularly useful for same hand mod presses (eg. "Command + 1..5"). 
- Two dual use keys. The Lowest_Layer and Highest_layer keys can be used as Shift keys for improved dexterity and better ergonomics. When using a multi-key combo with mods the inner adjacent key that is used for activating the Lowest (left) and Highest layer (right) can be used as a Shift mod key. It doesn't matter which order you press the sequence of mod keys. As long as 1 or more mod keys is pressed in conjunction with the adjacent Lowest/Highest Layer key, adjacent the Lowest/Highest Layer key will immediately become a Shift mod press until the key is released. See below for use case.
- Layers can be held/stuck using the "g" & "m" keys (right and left of Shift mod respectively) while activating a layer. Use cases include persistence of the Keyboard Mouse, or performing numerical data entry with the Lower_layer active for extended periods. Un-stick layers by tapping the respective layer key again.
- Easy and flexible capslock; Capslock can be toggled on/off with a Higher+r press. Additionally,
  - Caps-word can be toggled with a double left shift tap. Capslock will disable at the first occurrence of a space, comma, semi-colon, colon, period(dot), escape, tab, or enter tap.
  - Caps-sentence can be toggled with a double right shift tap. Capslock will disable at the first occurrence of a period(dot), escape, or enter tap.
- Media/Keyboard Function layer contains a hotkey for hiding active window and muting volume in one single keypress. 💍
- (macOS) An additional shortcut within the Higher layer on the "b" key doubles as a word, line, all select when single, double, and triple tapped respectively. This text select expansion functionality is reminiscent to how double, triple, and quadruple mouse clicks behaves (note - line select via double tap may not work as intended on lines that soft wrap).
- (macOS) Additional Layer for OS shortcuts, activated with escape key press and hold. See keymap.c
- (macOS) Additional Layer for Window Management shortcuts using [Rectangle](https://rectangleapp.com/), activated with backspace key press on the OS_layer. Revert back to Base_layer using "esc" key. See keymap.c
- (macOS) Shortcuts for quick access to word & line backspace and word & line delete forward. These are activated from Lower, Lowest, Higher, and Highest layers respectively. Delete forward key is located at tab position on High, Higher, and Highest layers.

## Approach

There are a couple of ways to approach this layout.

### Without Home Row Mods (default)

This approach is suitable for a 48+ key layout, eg. Planck Grid layout (MIT layout would require some tweaking). Control, Alt/Option, GUI/Command mods are mirrored, located on bottom left and right. As stated above, home row mods can be toggled on.

#### Suggested Use w/o Home Row Mods

When activating a multi-combo mod press, either move your hand in the same fashion as you would if there were an arrow cluster there towards the bottom corner. Effectively, this in turn should feel very reminiscent to using home row mods. Since mods are mirrored on both the bottom right and left use opposite hand to press key, or, use One-shot Home Row Mods feature by triggering combo using Higher+t key.

When activating single mod presses, leave your hand above the home row and lower the corresponding finger down 2 rows to activate the press and hold. This is done identically to how mods are typically activated with a standard ANSI layout. Again, since mods are mirrored on both the bottom right and left use opposite hand to press key.

### With Row Mods

This approach is suitable for a 42+ key layout, eg. Corne. Use home row mods with the added benefit of having dedicated shift keys on both the left and right.

#### Suggested Use w/ Home Row Mods

Use the dedicated Shift keys on the right and left for shifting alpha keys. For novice-intermediate (home row mod) users this can yield a faster typing experience when typing in mixed case. Since shift keys mirrored on both the right and left use opposite hand to press shifted key. Use the shift keys located on the home rows for keyboard shortcuts and multi-combo mod presses. For a more focused typing experience, or when typing for extended periods of time (ex. Emails or Typing Speed Test) consider toggling home row mods off to prevent accidental mod presses.

## Tips

- For more information on home row mods see an extensive write-up at [https://precondition.github.io/home-row-mods](https://precondition.github.io/home-row-mods)
- While it may be tempting to change this layout to use shift when held/enter when tapped with right shift key it's worth considering the ramifications of using a mod-tap there.
- When using a keyboard flashed with this firmware/layout on a MacBook, consider using Karabiner Elements to disable the built-in Apple keyboard when QMK keyboard is plugged in.
- On macOS, using System Preferences or Karabiner Elements, consider using F keys as standard Function keys since OS and Media controls are already implemented in their respective layers.
- In order to optimize this layout for use with Windows or *nix you'll likely want to modify the mod order since this layout is primarily targeted towards use with macOS (which utilizes the Command/GUI key in a manner similar to how Windows treats the Control key). The order for mods on the left half is Control --> Option/Alt --> Command/GUI --> Shift; These mods are in reverse order on the right half.
- Keep in mind, when activating a Layer on the bottom row in conjunction with a Mod key press on the home row (ex. Shift+Arrow_Left to select text) the key sequence order is important. The layer must be held first, then home row mod can be activated.
- Note that the two mod clusters for the bottom row are 1 column shifted (outward) from the home row mods. This isn't intentional, however, an alternative approach without the column shift would likely be less ergonomic since you wouldn't want to either:
    1. Bring your elbows inward towards your torso when using the mods in the bottom row
    2. Shift the four fingers used on the home row in any other way during a Layer activation press.
- Capslock + Vim can be dizzying, I recommend using CapsLocker for MacOS for a decent notification when capslock is toggled.
