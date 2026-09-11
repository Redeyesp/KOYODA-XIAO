# KOYODA notes for this board

This exact board implementation is the reason M0.1 starts from XiaoZhi rather
than manually recreating its cloud stack.

Upstream code in this directory already initializes:

- CO5300 AMOLED
- CST9217 touch
- AXP2101 PMU
- ES7210 / ES8311 audio path
- I/O expander
- Wi-Fi board integration

## M0.1 rule

Do not rewrite this board class until the stock XiaoZhi baseline has been
hardware-tested.

## Watch closely during first hardware test

The stable KOYODA firmware previously had display-DMA sensitivity.  If serial
logs show errors such as:

- `setup_dma_priv_buffer`
- `ESP_ERR_NO_MEM`
- `Draw bitmap failed`

stop and diagnose before adding KOYODA UI assets.

The XiaoZhi board implementation currently uses its own display settings and
IDF 6.x runtime, so do not assume KOYODA's old IDF 5.5 display tuning can be
copied blindly.
