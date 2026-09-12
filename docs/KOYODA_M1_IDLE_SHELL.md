# KOYODA-XIAO M1 — Idle Shell + UI Arbitration

## Why M1 is designed this way

A full-screen KOYODA idle face cannot simply be added on top of XiaoZhi's UI.

On a fresh boot with no saved SSID, XiaoZhi enters Wi-Fi configuration mode.
If both layers are left active, the KOYODA face and Wi-Fi instructions can
overlap/stack.

M1 therefore establishes explicit **screen ownership**.

## Screen ownership table

| Device state | Screen owner |
|---|---|
| Starting | XiaoZhi system UI |
| Wi-Fi configuring | XiaoZhi Wi-Fi UI |
| Activating / OTA | XiaoZhi system UI |
| Idle | **KOYODA idle face** |
| Connecting AI | XiaoZhi UI (temporary, until later milestone) |
| Listening | XiaoZhi UI (temporary) |
| Speaking | XiaoZhi UI (temporary) |
| Critical Alert | XiaoZhi system UI |

The KOYODA idle layer is created **hidden by default**.

It is shown only after the application actually transitions to
`kDeviceStateIdle`.

## Fresh boot with no Wi-Fi credentials

Expected flow:

1. boot
2. XiaoZhi system screen
3. Wi-Fi configuration mode
4. Wi-Fi instructions only — **NO KOYODA face underneath/on top**
5. device connects / activates
6. application enters Idle
7. XiaoZhi system layer is covered by the KOYODA idle face

## Touch verification

M0.2 had no meaningful touch target, so "touch works" could not be verified.

M1 fixes the test methodology without adding visible UI.

While KOYODA idle is visible, four invisible corner touch zones are active:

- TOP_LEFT
- TOP_RIGHT
- BOTTOM_LEFT
- BOTTOM_RIGHT

Tap each **physical** corner while serial monitor is open.

Expected example:

`M1 TOUCH logical-zone=TOP_LEFT`

If physical top-left reports another corner, we know exactly how the CST9217
mapping must be corrected for the 270-degree display orientation.

These test zones disappear automatically whenever the idle layer is hidden,
so they cannot interfere with Wi-Fi provisioning.

## M1 pass criteria

- display remains upright at 270 degrees
- fresh/no-Wi-Fi boot shows only Wi-Fi setup UI
- no KOYODA/Wi-Fi stacking
- after Wi-Fi + activation, KOYODA idle face appears
- idle face fills the whole 466x466 screen
- tapping physical corners produces the expected logical-corner logs
- no white screen
- no DMA allocation flood
- no reboot loop
- XiaoZhi audio/network core remains functional

## Not in M1

- blink
- AI ON/OFF long press
- listening notice
- thinking animation
- speaking animation
- charge animation
- KOYODA battery/Wi-Fi/volume pages
- wake word

Those are intentionally deferred until the idle/UI ownership baseline is proven.
