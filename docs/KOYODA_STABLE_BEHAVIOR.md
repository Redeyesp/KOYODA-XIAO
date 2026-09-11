# Stable KOYODA behavior to preserve later

This is the functional reference for migration.  It is not compiled in M0.1.

- Hardware: Waveshare ESP32-S3 Touch AMOLED 1.75
- Display: CO5300
- Touch: CST9217
- PMU: AXP2101
- Audio: ES7210 mic + ES8311 speaker
- AI boot behavior: OFF
- AI trigger: face long-press
- Long press ON confirmation: one beep
- Long press OFF confirmation: two beeps
- Volume default: 90%
- AI visual states:
  - Idle
  - Listening/ready
  - Thinking
  - Speaking
- Charge animation uses a compact/shared-PSRAM composition strategy
- Blink optimization uses compact eye data/shared composition
- Battery / Wi-Fi / Volume pages exist in the stable firmware
- KOYODA should not automatically send speech to AI at boot

This file is a migration checklist.  XiaoZhi defaults are allowed during
M0.1/M0.2 only for baseline verification.
