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

#ifndef _EVT_TIMER_H_
#define _EVT_TIMER_H_

#include "Macro.h"
#include "EvtData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
 * 定时器类型定义 
 *==============================================================================*/
enum _TIMER_TYPE_INDEX_
{
    EN_TIMER_MS = 0,                        // 定时器-毫秒
    EN_TIMER_S,                             // 定时器-秒
    EN_TIMER_M,                             // 定时器-分
    EN_TIMER_H,                             // 定时器-时
    EN_TIMER_D,                             // 定时器-天
};

/*================================================================================*/

// 定时器结构体
typedef struct
{
    UINT32          dwFlag;                  // 定时器启动标志
    UINT32          dwType;                  // 时间事件类型
    UINT32          dwAttr;                  // 定时器属性1-周期性0-非周期性

    UINT32          dwEnd;                   // 结束计时
    UINT32          dwDlt;                   // 定时周期
    
}tagEvtTimer;

/*================================================================================
 * 对外声明函数-函数的执行顺序 Build、Map、Destory 
 *================================================================================*/

extern UINT32 EvtTimerInit(tagEvtTimer *pMe, UINT32 dwNum);
extern UINT32 EvtTimerStart(tagEvtTimer *pMe,UINT32 dwFsm,UINT32 dwAttr,UINT32 dwStart,UINT32 dwStop);
extern UINT32 EvtTimerStop(tagEvtTimer *pMe);
extern UINT32 EvtTimerCnvt(UINT32 dwType, UINT32 dwCnt, UINT32 *pdwEnd, UINT32 *pdwDlt);
extern UINT32 EvtTimerUpdt(tagEvtTimer *pMe, UINT32 dwNow);

extern UINT32 EvtTimerNow(void);
extern UINT32 EvtTimerDelay(UINT32 dwMicroSecond);
extern UINT32 EvtTimerSleep(UINT32 dwSecond);

/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
