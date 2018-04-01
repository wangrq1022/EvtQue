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

#ifndef _EVT_SUBSCRIBER_H_
#define _EVT_SUBSCRIBER_H_

#include "Macro.h"
#include "EvtData.h"
#include "FsmKit.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/
#define CN_EVT_REG_MODE   ( CN_DATA_LOCATE_MODE )   // 0-动态分配模式 1-静态分配模式


// 注册表定义结构体
typedef struct
{
//    UINT32          dwSize;                  // 事件大小 
//    UINT32          dwAttr;                  // 事件属性--广播、订阅 

    //UINT32          dwFsm;               // 事件重传标记
    
    tagListCtrl     tList;                  // 事件链表 
    
#if(CN_EVT_REG_MODE!=0)
    tagListNode     tNode[EN_FSM_END];      // 静态分配内存块
#endif

}tagEvtTable;


// 事件注册机-控制
typedef struct
{
    tagEvtTable     *ptEvtTable;            // 事件注册表 
    UINT32          dwEvtNum;               // 事件数量
    
}tagEvtSubObj;

/*================================================================================
 * 对外声明函数-函数的执行顺序 Build、Map、Destory 
 *================================================================================*/
extern UINT32 EvtSubBuild(tagEvtSubObj *pMe, tagEvtTable *ptEvtTable, UINT32 dwEvtNum);
extern UINT32 EvtSubMap(tagEvtSubObj *pMe, UINT32 *pdwSubTable, UINT32 dwSubNum, UINT32 dwFsmNo);
extern UINT32 EvtSubDestroy(tagEvtSubObj *pMe);

extern void EvtSubInfo(tagEvtSubObj *pMe);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
