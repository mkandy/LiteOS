/**
  ****************************************************************************************************
  * @file    fm33lc0xx_ll_wwdt.c
  * @author  FMSH Application Team
  * @brief   Src file of WWDT LL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2019] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under the Mulan PSL v1.
  * can use this software according to the terms and conditions of the Mulan PSL v1.
  * You may obtain a copy of Mulan PSL v1 at:
  * http://license.coscl.org.cn/MulanPSL
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
  * PURPOSE.
  * See the Mulan PSL v1 for more details.
  *
  ****************************************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "fm33lc0xx_ll_rcc.h"
#include "fm33lc0xx_ll_wwdt.h"
#include "fm33_assert.h"
/** @addtogroup fm33lC0xx_LL_Driver_WWDT
  * @{
  */


/** @addtogroup Private_Macros
  * @{
  */
#define         IS_WWDT_INSTANCE(INTANCE)                ((INTANCE) == WWDT)

#define         IS_LL_WWDT_OVERFLOWPERIOD(__VALUE__)            (((__VALUE__) == LL_WWDT_OVERFLOW_PERIOD_X1)||\
                                                                 ((__VALUE__) == LL_WWDT_OVERFLOW_PERIOD_X4)||\
                                                                 ((__VALUE__) == LL_WWDT_OVERFLOW_PERIOD_X16)||\
                                                                 ((__VALUE__) == LL_WWDT_OVERFLOW_PERIOD_X64)||\
                                                                 ((__VALUE__) == LL_WWDT_OVERFLOW_PERIOD_X128)||\
                                                                 ((__VALUE__) == LL_WWDT_OVERFLOW_PERIOD_X256)||\
                                                                 ((__VALUE__) == LL_WWDT_OVERFLOW_PERIOD_X512)||\
                                                                 ((__VALUE__) == LL_WWDT_OVERFLOW_PERIOD_X1024))
/**
  * @}
  */
  
/** @addtogroup WWDT_LL_EF_Init
  * @{
  */ 
  
/**
  * @brief	??????WWDT??????????????????
  *
  * @param	??????????????????
  *
  * @retval	?????????????????????????????????
  *       	-PASS ?????????????????????????????????
  *       	-FAIL ???????????????
  */
ErrorStatus LL_WWDT_DeInit(WWDT_Type* WWDTx)
{
    assert_param(IS_WWDT_INSTANCE(WWDTx));
   
    return PASS;
}
/**
  * @brief	?????? WWDT_InitStruct????????????????????????????????????????????????. 
  *         
  * @note 	WWTD??????????????????????????????????????????????????????
  *      	      
  * @param	WWDTx  ??????????????????
  *
  * @param 	LL_WWDT_InitTypeDef???????????????????????????WWDT?????????????????????	  
  *         
  * @retval	ErrorStatus?????????	
  *			-FAIL ????????????????????????        
  *			-PASS LPUART????????????        
  */
ErrorStatus LL_WWDT_Init(WWDT_Type* WWDTx, LL_WWDT_InitTypeDef *WWDT_InitStruct)
{
    ErrorStatus status = PASS;

    /* ?????????????????? */
    assert_param(IS_WWDT_INSTANCE(WWDTx));
    assert_param(IS_LL_WWDT_OVERFLOWPERIOD(WWDT_InitStruct->OverflowPeriod));
    /* ?????????????????? */
    LL_RCC_Group2_EnableBusClock(LL_RCC_BUS2_CLOCK_WWDT);
    /* ????????????????????????????????? */
    LL_WWDT_SetCounterPeriod(WWDTx,WWDT_InitStruct->OverflowPeriod);
    /* ??????????????? */
    LL_WWDT_EnableCounter(WWDTx);
    
    return status;
}
/**
  * @brief	?????? WWDT_InitStruct ???????????????
  *
  * @param 	WWDT_InitStruct ??????????????????????????????????????????????????? @ref LL_WWDT_InitTypeDef ????????? 
  *         
  * @retval	None
  */
void LL_WWDT_StructInit(LL_WWDT_InitTypeDef *WWDT_InitStruct)
{
    /* ???????????????????????? */
    WWDT_InitStruct->OverflowPeriod = LL_WWDT_OVERFLOW_PERIOD_X1024;
}
/** 
  *@} 
  */
  
/** 
  *@} 
  */
/*************************************************************END OF FILE************************************************************/
