config LOSCFG_PLATFORM
    string
    default "GD32E103C_START"       if LOSCFG_PLATFORM_GD32E103C_START
    default "GD32F303RGT6_BearPi"   if LOSCFG_PLATFORM_GD32F303RGT6_BEARPI
    default "GD32VF103V_EVAL"       if LOSCFG_PLATFORM_GD32VF103V_EVAL

choice
    prompt "Board"
    depends on LOSCFG_FAMILY_GD
    default LOSCFG_PLATFORM_GD32E103C_START
    help
      GD32E103C_START
      GD32F303RGT6_BearPi
      GD32VF103V_EVAL

config LOSCFG_PLATFORM_GD32E103C_START
    bool "GD32E103C_START"
    select LOSCFG_USING_BOARD_LD
    select LOSCFG_ARCH_CORTEX_M4
    select LOSCFG_CORTEX_M_NVIC
    select LOSCFG_CORTEX_M_SYSTICK
    select LOSCFG_DRIVER_GD_LIB

config LOSCFG_PLATFORM_GD32F303RGT6_BEARPI
    bool "GD32F303RGT6_BearPi"
    select LOSCFG_USING_BOARD_LD
    select LOSCFG_ARCH_CORTEX_M4
    select LOSCFG_CORTEX_M_NVIC
    select LOSCFG_CORTEX_M_SYSTICK
    select LOSCFG_DRIVER_GD_LIB

config LOSCFG_PLATFORM_GD32VF103V_EVAL
    bool "GD32VF103V_EVAL"
    select LOSCFG_USING_BOARD_LD
    select LOSCFG_ARCH_RISCV_RV32IMC
    select LOSCFG_RISCV32_M_TIMER
    select LOSCFG_PLATFORM_BSP_RISCV_ECLIC
    select LOSCFG_DRIVER_GD_LIB

endchoice
