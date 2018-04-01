/*
 *MIT License
 *
 *Copyright (c) 2017-2018 Wang Ruquan. All rights reserved.
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *SOFTWARE.
*/


#ifndef _EVT_KIT_H_
#define _EVT_KIT_H_

#include "FsmObject.h"
#include "EvtGenerator.h"
#include "EvtSubscriber.h"
#include "EvtRecycler.h"
#include "EvtTimer.h"
#include "EvtThread.h"

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
 * 事件发生器配置
 *==============================================================================*/
#define CN_EVT_GEN_BLK_SIZE_S   (  2 )    // 数据块大小-S
#define CN_EVT_GEN_BLK_SIZE_M   (  4 )    // 数据块大小-M
#define CN_EVT_GEN_BLK_SIZE_L   (  8 )    // 数据块大小-L
                                                         
#define CN_EVT_GEN_BLK_NUM_S    (  12 )    // 数据块个数不能少于2个-S
#define CN_EVT_GEN_BLK_NUM_M    (  22 )    // 数据块个数不能少于2个-M
#define CN_EVT_GEN_BLK_NUM_L    (  32 )    // 数据块个数不能少于2个-L


/*==============================================================================
 * 状态机的公共事件定义 
 *==============================================================================*/
enum _EVT_TYPE_PUBLIC_
{
    // 时间事件
    EN_EVT_BEGIN = 0,                        //--不可修改、不可订阅

    EN_PUB_TIMER_T10,                        // 
    EN_PUB_TIMER_T15,                        // 

    EN_PUB_TIMER_P1,                         // 
    EN_PUB_TIMER_P2,                         // 
    EN_PUB_TIMER_P3,                         // 
    EN_PUB_TIMER_P4,                         // 
    EN_PUB_TIMER_P5,                         // 

    EN_TIM_END,                              //--不可修改、不可订阅

    // 应用事件
    EN_PUB_A,                                // 
    EN_PUB_B,                                // 
    EN_PUB_C,                                // 

    EN_PUB_PHILO_GET,                        // 
    EN_PUB_PHILO_PUT,                        // 
    EN_PUB_TBL_ACCEPT,                       // 
    EN_PUB_TBL_REFUSE,                       // 

    EN_EVT_END,                              //--不可修改、不可订阅
};
/*==============================================================================
 * 状态机的本机事件定义 
 *==============================================================================*/
enum _EVT_TYPE_JMP_
{
    // 本机事件
    EN_JMP_BEGIN = EN_EVT_END,         //--不可修改、不可订阅

    EN_JMP_ENTER,                            //--不可修改、不可订阅
    EN_JMP_EXIT,                             //--不可修改、不可订阅

    EN_JMP_END,                              //--不可修改、不可订阅

};

#define CN_EVT_TABLE    (EN_EVT_END - EN_EVT_BEGIN)
#define CN_EVT_TIMER    (EN_TIM_END - EN_EVT_BEGIN)
#define CN_EVT_JUMP     (EN_JMP_END - EN_JMP_BEGIN)


/*==============================================================================*/
// 抽象事件定义结构体
typedef struct
{
    UINT32          dwType;                  // 事件类型 
    UINT32          dwCnt;                   // 事件被注册的次数
    UINT32          dwPool;                  // 事件源于的内存池编号
    
}tagEvent;

// 时间事件定义结构体
typedef struct
{
    tagEvent        tEvent;                  // 事件头
    UINT32          dwRst;                   // 预留时间信息
  
}tagTime;

/*==============================================================================
 * 对外声明全局变量 
 *==============================================================================*/
extern jmp_buf         g_ErrBuf;                       // 抛出异常信息

extern tagEvtTable     g_tEvtTable[CN_EVT_TABLE];      // 事件注册表 
extern tagEvtTimer     g_tEvtTimer[CN_EVT_TIMER];      // 定时器数组
extern void *          g_pBuf[EN_FSM_END][CN_EVT_JUMP];// 本机事件缓冲区

extern tagEvtSubObj    g_tEvtSubObj;                   // 事件注册机 
extern tagEvtGenObj    g_tIsrGenObj;                   // 事件发生器-中断函数调用 
extern tagEvtGenObj    g_tEvtGenObj;                   // 事件发生器-线程调用 

/*==============================================================================*/



/*==============================================================================
 * 对外声明全局变量 
 *==============================================================================*/
extern UINT32 EvtGenerator(void);
extern UINT32 EvtRegister(void);
extern UINT32 EvtTimerInitAll(void);
extern UINT32 EvtTimerRun(void);
extern void   EvtSubscriber(UINT32 dwFsmNo, UINT32 *pdwSubTable, UINT32 dwSubNum);
extern UINT32 EvtTimerSet(UINT32 dwFsm, UINT32 dwSet,UINT32 dwTimer, UINT32 dwType, UINT32 dwCnt);


// 事件发生器-中断调用 
#define M_IsrEvtGet(tType)      (tType *)EvtGenGet(&g_tIsrGenObj, sizeof(tType))
#define M_IsrEvtPut(ptEvt)      EvtGenPut(&g_tIsrGenObj, (void *)ptEvt)

// 事件发生器-线程调用  
#define M_FsmEvtGet(tType)      (tType *)EvtGenGet(&g_tEvtGenObj, sizeof(tType))
#define M_FsmEvtPut(ptEvt)      EvtGenPut(&g_tEvtGenObj, (void *)ptEvt)

// 事件发生器-查询用
#define M_EvtGenInfo()          EvtGenInfo(&g_tEvtGenObj)

// 事件注册机-查询用
#define M_EvtRegInfo()          EvtSubInfo(&g_tEvtSubObj)


// 定时器设置
#define M_EvtTimerSet(dwSet, dwTimer, dwType, dwCnt)  EvtTimerSet(pMe->dwFsm, dwSet, dwTimer, dwType, dwCnt)


/*===============================================================================*/


#ifdef __cplusplus
}
#endif

#endif
