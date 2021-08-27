/*----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: LiteOS Kernel Extended LMS Demo
 * Author: Huawei LiteOS Team
 * Create: 2020-11-01
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

#include "math.h"
#include "time.h"
#include "los_task.h"
#include "lms_demo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define LMS_TASK_PRIORITY 4
STATIC UINT32 g_demoTaskId;

STATIC UINT32 LMS_Case_HeapOverflow(VOID)
{
    CHAR *buf = NULL;
    CHAR tmp;
    UINT32 ret;

    buf = LOS_MemAlloc(m_aucSysMem0, 4); /* mem size 4 */

    tmp = buf[3]; /* Array 3. No exception information is printed on the LMS. */
    tmp = buf[4]; /* Array 4. When the fourth byte overflows, the LMS prints the read error information. */

    printf("buf is %c.\n", tmp);
    ret = LOS_MemFree(m_aucSysMem0, buf);

    return ret;
}

STATIC UINT32 DemoTaskEntry(VOID)
{
    UINT32 ret;

    printf("Lms demo task start to run.\n");
    /* task delay 5 ticks, task will be suspend */
    ret = LOS_TaskDelay(5);
    if (ret != LOS_OK) {
        printf("Task delay failed.\n");
        return LOS_NOK;
    }
    LMS_Case_HeapOverflow();

    /* task resumed */
    printf("Lms task delay done.\n");

    /* suspend self */
    ret = LOS_TaskSuspend(g_demoTaskId);
    if (ret != LOS_OK) {
        return LOS_NOK;
    }

    printf("Lms task LOS_TaskResume successfully.\n");

    /* delete self */
    if (LOS_TaskDelete(g_demoTaskId) != LOS_OK) {
        printf("Delete lms task failed.\n");
        return LOS_NOK;
    }
    printf("Lms demo task finished.\n");

    return LOS_OK;
}

VOID LmsDemoTask(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S taskInitParam;

    /* lock task shcedue */
    LOS_TaskLock();

    ret = memset_s(&taskInitParam, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    if (ret != EOK) {
        return;
    }
    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)DemoTaskEntry;
    taskInitParam.usTaskPrio = LMS_TASK_PRIORITY;
    taskInitParam.pcName = "LmsDemoTask";
    taskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    /* create LMS prio task */
    ret = LOS_TaskCreate(&g_demoTaskId, &taskInitParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();
        printf("Create lms demo task failed.\n");
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
