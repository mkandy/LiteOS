/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Sensorhub Demo
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

#include "sensorhub_demo.h"
#include "gyro.h"
#include "los_printf.h"
#include "sensor_manager.h"
#include "sensor_commu.h"
#include "i2c.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define Item1_SAMPLE_INTERVAL     3000 // LiteOS ticks
#define Item2_SAMPLE_INTERVAL     6000
#define SENSORHUB_TASK_PRIORITY   4
#define SENSORHUB_TASK_STACK_SIZE 0x800

STATIC UINT32 g_demoTaskId;

STATIC SensorItem g_demoGyroItem1 = {
    .id = 1, // 1: gyro item 1
};
STATIC SensorItem g_demoGyroItem2 = {
    .id = 2, // 2: gyro item 2
};

STATIC VOID SensorReport(UINT32 arg, const INT8 *data, UINT32 len)
{
    (VOID)(len);
    (VOID)(data);
    printf("Tag %u report\r\n", arg);
}

STATIC VOID OpenGyro(VOID)
{
    OpenParam para;

    // period is LiteOS ticks
    para.period = Item1_SAMPLE_INTERVAL;
    SensorItemEnable(&g_demoGyroItem1, &para, g_demoGyroItem1.id, 0);

    para.period = Item2_SAMPLE_INTERVAL;
    SensorItemEnable(&g_demoGyroItem2, &para, g_demoGyroItem2.id, 0);
}

STATIC VOID CloseGyro(VOID)
{
    CloseParam para;
    SensorItemDisable(&g_demoGyroItem1, &para, g_demoGyroItem1.id, 0);
    // keep item2 working for 40000 ticks
    LOS_TaskDelay(40000);
    SensorItemDisable(&g_demoGyroItem2, &para, g_demoGyroItem2.id, 0);
}

STATIC VOID InitGyro(VOID)
{
    SensorType *sensor = NULL;
    SensorScbTable *scbTable = NULL;

    // init gyro sensor
    scbTable = SensorTableGet();
    sensor = scbTable[TAG_GYRO - TAG_BEGIN].sensorInterface;
    if ((sensor != NULL) && (sensor->sensorOp != NULL)) {
        (VOID)sensor->sensorOp->Init(sensor);
    }

    // init item
    SensorItemInit(&g_demoGyroItem1, NULL, TAG_GYRO, SensorReport, TAG_GYRO);
    SensorItemInit(&g_demoGyroItem2, NULL, TAG_GYRO, SensorReport, TAG_GYRO);
}

STATIC VOID DemoTaskEntry(VOID)
{
    printf("SensorHub demo task start to run.\n");
    MX_I2C1_Init();
    SensorManagerInit();
    LOS_TaskDelay(1000);
    GyroSensorRegister();
    InitGyro();
    OpenGyro();
    LOS_TaskDelay(20000);
    CloseGyro();
    OpenGyro();
    LOS_TaskDelay(100000);
    CloseGyro();
    printf("SensorHub demo task finished.\n");
}

VOID SensorHubDemoTask(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S taskInitParam ;

    ret = memset_s(&taskInitParam, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    if (ret != EOK) {
        return;
    }
    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)DemoTaskEntry;
    taskInitParam.uwStackSize = SENSORHUB_TASK_STACK_SIZE;
    taskInitParam.pcName = "SensorHubDemoTask";
    taskInitParam.usTaskPrio = SENSORHUB_TASK_PRIORITY;  /* 1~7 */
    taskInitParam.uwResved = LOS_TASK_STATUS_DETACHED;   /* task is detached, the task can deleteself */
    ret = LOS_TaskCreate(&g_demoTaskId, &taskInitParam);
    if (ret != LOS_OK) {
        printf("Create sensorhub demo task failed.\n");
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
