# KOYODA → XiaoZhi Integration Plan

## Architecture decision

XiaoZhi becomes the **AI/session/network core**.

KOYODA remains the **product identity and UX**.

### Keep from XiaoZhi

- WebSocket / MQTT protocol layer
- server session lifecycle
- audio packet transport
- Opus/network audio pipeline
- activation / OTA foundations
- exact Waveshare 1.75 board support
- supported cloud service protocol

### Rebuild / port from KOYODA

- KOYODA face identity
- idle / blink / sleep / wake behavior
- explicit AI ON/OFF
- long-press touch trigger
- Listening / Thinking / Speaking visual states
- charge animation
- battery / Wi-Fi / volume UI
- KOYODA-specific power UX

## Known KOYODA hardware lessons that must not be forgotten

The stable KOYODA firmware already exposed several constraints:

1. CO5300/LVGL display DMA pressure matters.
2. Medium/large rotated LVGL image overlays caused
   `setup_dma_priv_buffer` / `ESP_ERR_NO_MEM`.
3. Compact facial parts should be composed through a reusable PSRAM frame
   rather than introducing extra full-screen image assets or unnecessary
   DMA-heavy overlays.
4. Audio must remain stable while microphone + speaker operate together.
5. UI work must stay in the correct LVGL/display context.
6. Existing KOYODA boots with AI OFF and requires an explicit user trigger.
7. Stable KOYODA behavior is the regression reference, not XiaoZhi's default UX.

## Why M0.1 is intentionally boring

The first milestone is not a visual milestone.

We need one answer first:

> Can XiaoZhi mainline build and boot reliably on this exact KOYODA hardware
> using its native Waveshare 1.75 board support?

If yes, we gain the cloud/session core without manually recreating it.

If no, we stop and fix the board/runtime layer before porting any KOYODA UI.

## M0.1 pass criteria

GitHub Actions:

- exact board variant config resolves
- IDF 6.0.2 configure succeeds
- firmware links
- `build/merged-binary.bin` is produced

No KOYODA UI changes yet.

## M0.2 hardware pass criteria

After flashing:

- AMOLED initializes
- orientation is usable
- touch initializes
- AXP2101 initializes
- ES7210 initializes
- ES8311 initializes
- Wi-Fi setup works
- no reboot loop
- no white screen
- no DMA allocation flood
- device can stay alive for at least 5 minutes

Do not begin M1 until these pass.

## M1: KOYODA face shell

Only after M0.2 passes:

- remove XiaoZhi chat-style UI from the face screen
- render KOYODA idle face
- no blink yet
- no charge animation yet
- no state animation yet

This isolates display identity from AI/network behavior.

## M2: explicit AI ON/OFF

Port the proven KOYODA behavior:

- boot: AI OFF
- long-press face: AI ON
- long-press again: AI OFF
- AI OFF must not open/send an AI utterance
- wake word remains disabled

## M3: state bridge

Map XiaoZhi states:

- `kDeviceStateIdle` + AI enabled → KOYODA Listening/Ready
- connecting / server processing → KOYODA Thinking
- `kDeviceStateSpeaking` → KOYODA Speaking
- AI disabled → KOYODA normal Idle

Do not let display code own network/audio state.

## M4: compact visuals

Port only the compact/optimized KOYODA assets.

Do not restore old duplicated full-screen animation assets.

## Non-goals for early milestones

- custom wake word
- gyro features
- MCP extras
- large UI redesign
- adding another cloud provider
- replacing stable PMU behavior without evidence
