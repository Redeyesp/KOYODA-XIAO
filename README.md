# KOYODA-XIAO

Separate integration repository for bringing the XiaoZhi AI core into KOYODA
without risking the stable KOYODA repository.

## Current milestone: M1.2 root-scroll + power fix

**M1 now ports only the KOYODA idle face.**

M0.1 has now booted on the real hardware. M0.2 fixes the physical display orientation to **270°** and adds hardware-init diagnostics.

First prove that the current XiaoZhi core can build for the exact hardware:

- Waveshare ESP32-S3-Touch-AMOLED-1.75
- ESP32-S3
- CO5300 AMOLED
- CST9217 touch
- AXP2101 PMU
- ES7210 microphone
- ES8311 speaker

This source already contains native board support for this exact Waveshare
1.75-inch board.  M0.1 deliberately keeps that upstream board implementation
intact so we can establish a clean XiaoZhi baseline before transplanting
KOYODA's UI/state behavior.

## Important separation

The existing **KOYODA** repository remains the stable product.

This new **KOYODA-XIAO** repository is experimental.

Do not overwrite or merge it into KOYODA yet.

## Build target

M0.1 builds only:

`waveshare/esp32-s3-touch-amoled-1.75`

with:

- ESP-IDF **v6.0.2**
- Thai UI locale: `th-TH`
- XiaoZhi wake word: **disabled**

Wake word is deliberately disabled because KOYODA's intended interaction is
explicit AI ON/OFF, ultimately via the long-press behavior already proven in
the stable KOYODA firmware.

## GitHub Actions

A single-board workflow is included:

`.github/workflows/build-koyoda-xiao.yml`

It does not build XiaoZhi's full board matrix.

Successful builds upload:

`build/merged-binary.bin`

## Local build

Use an ESP-IDF 6.0.2 terminal:

```powershell
.\scripts\build_koyoda_xiao.ps1
```

or directly:

```powershell
python scripts/build.py waveshare/esp32-s3-touch-amoled-1.75 `
  --name esp32-s3-touch-amoled-1.75 `
  --language th-TH `
  --wake-word disabled
```

## Roadmap

See:

`docs/KOYODA_PORTING_PLAN.md`

The intended direction is:

1. M0.1 — XiaoZhi exact-board build baseline
2. M0.2 — boot/flash and hardware regression
3. M1 — replace XiaoZhi display identity with KOYODA idle face only
4. M2 — port KOYODA AI ON/OFF long-press
5. M3 — map XiaoZhi device states to KOYODA Listening / Thinking / Speaking
6. M4 — port compact KOYODA face assets and shared-PSRAM compositor
7. M5 — battery / Wi-Fi / volume pages
8. M6 — sleep / charge / final polish

The rule is: **one subsystem at a time, hardware test before the next step.**

## Upstream

This repository starts from the XiaoZhi ESP32 source supplied for the project.
The original upstream README is preserved as:

`UPSTREAM_XIAOZHI_README.md`

The upstream project is MIT licensed; the original `LICENSE` is retained.


## M1 screen arbitration

The KOYODA idle face is **not** displayed during startup or Wi-Fi provisioning.
It appears only after XiaoZhi reaches `kDeviceStateIdle`.

This prevents the Wi-Fi setup page and KOYODA face from stacking.
See `docs/KOYODA_M1_IDLE_SHELL.md`.


## M1.1 cleanup

Real-hardware M1 testing confirmed the 270° touch mapping is correct on all four
corners. M1.1 changes the touch probe to immediate press logging and closes the
remaining static-idle white edge using exclusive screen ownership and a black
overscan surface.


## M1.2 root-scroll + power fix

Real-hardware video showed that touch is immediate, but the stock XiaoZhi root
screen was scrolling the entire KOYODA idle layer. M1.2 locks root scrolling
while KOYODA owns the screen and disables XiaoZhi's 60-second dim /
300-second shutdown timer during integration.
