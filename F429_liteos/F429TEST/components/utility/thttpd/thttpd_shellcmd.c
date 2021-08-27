/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Implementation For Thttpd
 * Author: Huawei LiteOS Team
 * Create: 2021-03-23
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
 * THIS SOFTWARE IS3PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
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

#ifndef _SHELL_THTTPD_H
#define _SHELL_THTTPD_H

#include "los_config.h"

#ifdef LOSCFG_SHELL
#include "shcmd.h"
#include "los_base.h"
#include "los_task.h"
#include "errno.h"
#include "stdio.h"
#include "libhttpd.h"

#define THTTPD_TASK_PRIORITY    6
#define THTTPD_TASK_STACK_SIZE  0x4000
#define FATFS_MAIN_DIR          "/fatfs"

STATIC UINT32 g_taskId;

VOID OsShellCmdThttpd()
{
    INT32 ret;
    TSK_INIT_PARAM_S taskInitParam;

    ret = memset_s(&taskInitParam, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    if (ret != EOK) {
        return;
    }

    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)ThttpdRun;
    taskInitParam.uwStackSize = THTTPD_TASK_STACK_SIZE;
    taskInitParam.pcName = "ThttpdTask";
    taskInitParam.usTaskPrio = THTTPD_TASK_PRIORITY;
    taskInitParam.uwResved = LOS_TASK_STATUS_DETACHED;
    ret = LOS_TaskCreate(&g_taskId, &taskInitParam);
    if (ret != LOS_OK) {
        printf("Create thttpd task failed.\n");
    }
}

SHELLCMD_ENTRY(thttpd_shellcmd, CMD_TYPE_EX, "thttpd", 0, (CMD_CBK_FUNC)OsShellCmdThttpd);

#endif
#endif