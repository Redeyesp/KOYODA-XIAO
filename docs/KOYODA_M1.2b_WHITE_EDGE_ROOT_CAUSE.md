# KOYODA-XIAO M1.2b — White Edge Root-Cause Fix

## Why M1.1 / M1.2 did not remove the white edge

Those attempts worked at the LVGL object layer:

- black root background
- overscan parent
- exclusive screen ownership
- root scrolling lock

But the white pixels were created **below LVGL**.

The generic `SpiLcdDisplay` constructor in:

`main/display/lcd_display.cc`

contains an initial panel clear:

```cpp
std::vector<uint16_t> buffer(width_, 0xFFFF);
for (int y = 0; y < height_; y++) {
    esp_lcd_panel_draw_bitmap(panel_, 0, y, width_, y + 1, buffer.data());
}
```

`0xFFFF` is RGB565 white.

If the CO5300 + 270° LVGL path later leaves a thin physical edge outside its
refresh regions, those pixels are never overwritten and therefore remain
white permanently.

That explains why changing the KOYODA layer, root background, and overscan
did not solve it.

## M1.2b fix

Do not modify XiaoZhi's generic display class for every board.

Instead, on the exact Waveshare 1.75 board:

1. construct `CustomLcdDisplay` normally
2. the generic constructor performs its white clear
3. immediately repaint the entire 466x466 physical active area black using
   `esp_lcd_panel_draw_bitmap`
4. only then restore panel brightness

Any physical pixels missed by later LVGL refreshes now remain BLACK, not white.

## Expected serial log

```text
M1.2b clearing physical CO5300 active area BLACK after generic white clear
M1.2b physical panel BLACK clear complete
```

## Test

After flash and activation:

- KOYODA idle should still be upright at 270°
- touch mapping should remain unchanged
- face should not drag/scroll
- stock power save should remain disabled
- left white edge should be gone
- bottom white edge should be gone

If a colored/black geometric offset remains after this patch, the next target
is the CO5300 panel window/gap configuration rather than LVGL styling.
