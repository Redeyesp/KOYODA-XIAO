# KOYODA-XIAO M1.1 — Idle Cleanup

## Confirmed from M1 hardware test

- Wi-Fi provisioning works
- activation works
- device appears Online in XiaoZhi Console
- KOYODA idle appears only after activation/Idle
- Wi-Fi page does not stack with KOYODA idle
- all four touch corners map correctly after the 270-degree display rotation
- no obvious RAM leak in the supplied logs

Therefore **touch orientation is PASS**. No CST9217 mirror/swap change is made.

## Why touch logs felt slow

M1 used `LV_EVENT_CLICKED`.

That event is generated only after a full press/release is accepted as a click.
It was useful for initial testing but is not the right event for measuring raw
touch-down responsiveness.

M1.1 changes the diagnostic zones to `LV_EVENT_PRESSED`, so serial should log
as soon as the first press is recognized.

SystemInfo is unrelated. Its log is simply periodic (roughly every 10 seconds).

## White edge fix

M1 showed a light seam at the physical left/bottom edge.

M1.1 attacks that in two ways without changing the 466x466 face pixels:

1. KOYODA idle's black parent extends 2 pixels beyond all four edges.
2. The root LVGL screen background is forced black while KOYODA owns the
   screen.

The 466x466 face remains aligned to screen coordinate (0,0).

## Stronger UI arbitration

M1 already hid the KOYODA layer during Wi-Fi.

M1.1 goes further: idle has **exclusive ownership**.

### Idle

- stock XiaoZhi `container_` hidden
- stock XiaoZhi `status_bar_` hidden
- root background black
- KOYODA face shown and moved to foreground

### Wi-Fi / activation / listening / speaking / alert

- KOYODA face hidden first
- stock root background restored
- stock `container_` restored
- stock `status_bar_` restored

This reduces unnecessary underlying UI drawing during the static idle screen and
makes the Wi-Fi/Idle separation explicit rather than relying only on z-order.

## M1.1 pass criteria

- no white line on physical left edge
- no white line on physical bottom edge
- KOYODA face position unchanged
- Wi-Fi/system pages still appear normally
- touch corner logs appear immediately on touch-down
- all four touch corners remain correctly mapped
- no DMA/NO_MEM errors
- no reboot loop

If these pass, M1 is closed and the next milestone can add KOYODA animation.
