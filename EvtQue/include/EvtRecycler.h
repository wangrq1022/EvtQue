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

#ifndef _EVT_RECYCLER_H_
#define _EVT_RECYCLER_H_

#include "Macro.h"
#include "EvtData.h" 
#include "EvtKit.h"

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
 * 事件队列定义 
 *==============================================================================*/
enum _EVT_QUE_TYPE_
{
    EN_EVT_QUE_NONE = 0,                     //--不可修改
    EN_EVT_QUE_ISR,                          //--不可修改
    EN_EVT_QUE_FSM,                          //--不可修改
    
};

/*================================================================================*/



/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern void * EvtQueGet(tagFsmObj *pMe, UINT32 *pdwQue);
extern UINT32 EvtQuePut(void *pEvt, UINT32 dwQue);

/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
