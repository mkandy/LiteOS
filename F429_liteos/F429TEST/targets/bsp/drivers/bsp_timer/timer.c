/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2021. All rights reserved.
 * Description: LiteOS timer driver
 * Author: Huawei LiteOS Team
 * Create: 2013-01-01
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------- */

#include "timer.h"

UINT64 GetTimerCpupCycles(VOID)
{
#if defined LOSCFG_ARCH_ARM_CORTEX_M
#if defined LOSCFG_FAMILY_APM32
    return ApmGetTimerCycles(CPUP_TIMER);
#else
    return StmGetTimerCycles(CPUP_TIMER);
#endif
#elif defined LOSCFG_ARCH_RISCV_RV32IMC
    return GdGetTimerCycles(CPUP_TIMER);
#endif
}

UINT64 GetTimerCycles(Timer_t num)
{
#if defined LOSCFG_ARCH_ARM_CORTEX_M
#if defined LOSCFG_FAMILY_APM32
    return ApmGetTimerCycles(num);
#else
    return StmGetTimerCycles(num);
#endif
#elif defined LOSCFG_ARCH_RISCV_RV32IMC
    return GdGetTimerCycles((num));
#endif
}

VOID TimerHwiCreate (VOID)
{
#if defined LOSCFG_ARCH_ARM_CORTEX_M
#if defined LOSCFG_FAMILY_APM32
    ApmTimerHwiCreate();
#else
    StmTimerHwiCreate();
#endif
#elif defined LOSCFG_ARCH_RISCV_RV32IMC
    GdTimerHwiCreate();
#endif
}

VOID TimerInitialize(VOID)
{
#if defined LOSCFG_ARCH_ARM_CORTEX_M
#if defined LOSCFG_FAMILY_APM32
    ApmTimerInit();
#else
    StmTimerInit();
#endif
#elif defined LOSCFG_ARCH_RISCV_RV32IMC
    GdTimerInit();
#endif
}