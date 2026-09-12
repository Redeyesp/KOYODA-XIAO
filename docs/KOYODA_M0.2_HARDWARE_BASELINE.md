# KOYODA-XIAO M0.2 — Hardware Baseline

## What M0.1 already proved on real hardware

The firmware boots on the Waveshare ESP32-S3 Touch AMOLED 1.75 hardware.

The user's observed blocker was display orientation: the UI was upside-down.

## M0.2 change

The display is now explicitly set to:

`LV_DISPLAY_ROTATION_270`

in the board's `CustomLcdDisplay::SetupUI()`.

The touch configuration is intentionally **not changed yet**. M0.2 is the
hardware baseline and should tell us whether LVGL's rotated display coordinate
handling is sufficient on this board. If touch coordinates are wrong after the
screen is corrected, touch mapping becomes the next isolated fix.

## Diagnostics added

Serial output now marks:

1. power-save timer
2. I2C bus
3. TCA9554
4. AXP2101 PMU
5. SPI/QSPI
6. CO5300 display
7. CST9217 touch
8. button + MCP tools
9. ES7210 + ES8311 codec creation
10. NVS / Application initialization

It also prints free/largest blocks for:

- internal RAM
- DMA-capable internal RAM
- PSRAM

This is diagnostic logging only; no buffer/queue tuning is done in M0.2.

## Important: display DMA setting

XiaoZhi's native board currently uses:

- QSPI: 40 MHz
- `trans_queue_depth = 10`

M0.2 leaves those upstream values untouched because the user's hardware is
already booting. We should not import KOYODA's old IDF 5.5.4 queue-depth tuning
until there is evidence that XiaoZhi/IDF 6 needs it.

## Hardware pass checklist

After flashing M0.2:

- [ ] UI is physically upright at 270°
- [ ] touch works
- [ ] touch direction matches screen orientation
- [ ] AXP2101 initializes
- [ ] Wi-Fi setup/connect works
- [ ] microphone initializes
- [ ] speaker initializes
- [ ] device can hear/send audio when XiaoZhi interaction is triggered
- [ ] speaker can play reply audio
- [ ] no reboot loop
- [ ] no white screen
- [ ] no repeating `ESP_ERR_NO_MEM`
- [ ] no repeating `setup_dma_priv_buffer`
- [ ] no repeating LVGL draw/bitmap allocation failures
- [ ] survives at least 5 minutes powered on

## Pass rule

Do not start M1 (KOYODA face) until display orientation and touch orientation
are both confirmed.

Once M0.2 passes, M1 will replace only the visual identity with the KOYODA
idle face while retaining the working XiaoZhi core.
