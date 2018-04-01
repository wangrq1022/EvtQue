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

#ifndef _EVT_THREAD_H_
#define _EVT_THREAD_H_

#include "Macro.h"
#include "EvtData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/
#define CN_EVT_TIMER_DELAY      (   1 )      // 定时器任务挂起时长-毫秒
#define CN_EVT_TASK_DELAY       ( 200 )      // 状态机任务挂起时长-毫秒


// 多线程运行参数
typedef struct
{
    UINT32          dwFsm;                   // 状态机编号

    // 测试运行
    UINT32          dwDlt;                   // 线程执行时长-毫秒
    UINT32          dwTimer;                 // 定时器的参数-毫秒
    UINT32          dwThread;                // 0-多线程/非0-单线程运行   

}tagEvtThread;


/*================================================================================
 * 对外声明函数
 *================================================================================*/

extern void CreateSingleThread(tagEvtThread *ptPara);
extern void CreateMultiThread(tagEvtThread *ptPara);

extern void EvtThreadParaGet(tagEvtThread  *ptPara);
extern void EvtThreadParaSet(tagEvtThread *ptPara);


/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
