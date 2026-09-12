# KOYODA-XIAO M1.2 — Root Scroll + Power Fix

## What the hardware video/log proved

Touch is not actually slow.

The KOYODA face moves immediately with the finger, which proves CST9217 and
LVGL receive touch promptly.

The delayed-looking serial test is not the important symptom. The real bug is:

**the XiaoZhi root screen is scrollable, so the whole KOYODA full-screen layer
can move.**

That movement can expose XiaoZhi's light root background at the left/bottom,
which explains why the white edge survived the M1.1 overscan attempt.

## M1.2 display fix

Whenever KOYODA idle owns the screen:

1. root scroll position is reset to `(0,0)`
2. root `LV_OBJ_FLAG_SCROLLABLE` is cleared
3. root elastic/momentum/scroll-chain flags are cleared
4. root scroll direction is set to `LV_DIR_NONE`
5. root background is black
6. XiaoZhi stock container/status bar remain hidden
7. KOYODA idle layer is shown

The KOYODA idle layer and the invisible touch zones are also explicitly
non-scrollable/non-chainable.

When leaving idle for Wi-Fi/system/conversation:

- KOYODA is hidden first
- stock root background is restored
- stock root scroll direction/scrollability are restored
- stock XiaoZhi UI is restored

## Power-save fix

The original Waveshare XiaoZhi board configured:

- dim/power-save after 60 seconds
- PMIC power-off after 300 seconds

That is inappropriate during KOYODA integration and conflicts with KOYODA's
planned custom sleep animation/behavior.

M1.2 therefore does **not start** XiaoZhi's stock PowerSaveTimer.

Expected boot log:

`M1.2 stock PowerSaveTimer DISABLED (no auto-dim, no auto-shutdown)`

KOYODA-specific sleeping will be implemented later instead of inheriting the
stock XiaoZhi timer.

## Test

1. Leave KOYODA idle for > 60 seconds:
   - brightness must NOT drop to 20
2. Leave it running > 5 minutes:
   - PMIC must NOT auto-power-off
3. Drag/swipe anywhere on KOYODA idle:
   - face must NOT move at all
4. Check physical left and bottom:
   - white seam should be gone
5. Enter a stock XiaoZhi system/Wi-Fi state later:
   - stock UI should still work
