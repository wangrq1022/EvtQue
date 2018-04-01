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
 
#include <stdio.h>
#include "EvtKit.h"


//===========================================================
// 函数功能: 从事件队列获取事件指针
//===========================================================
inline void * EvtQueGet(tagFsmObj *pMe, UINT32 *pdwQue)
{    
    void    *pEvt = NULL;

    //  获取事件
    if(EvtQueRead(&pMe->tJmpQue, (void *)&pEvt, 1))
    {
        *pdwQue = EN_EVT_QUE_FSM;
    }
    else if(EvtQueRead(&pMe->tIsrQue, (void *)&pEvt, 1))
    {
        *pdwQue = EN_EVT_QUE_ISR;
    }
    else if(EvtQueRead(&pMe->tFsmQue, (void *)&pEvt, 1))
    {
        *pdwQue = EN_EVT_QUE_FSM;
    }
    else
    {
        *pdwQue = EN_EVT_QUE_NONE;
    }
        
    return pEvt;;
}

//===========================================================
// 函数功能: 事件指针回收
//===========================================================
inline UINT32 EvtQuePut(void *pEvt, UINT32 dwQue)
{
    UINT32      dwErr = 0;
    tagEvent    *ptEvt;

    // 指针转换
    ptEvt = (tagEvent *)pEvt;
    
    // 内存回收 
    if(!--ptEvt->dwCnt)
    {
        if(dwQue==EN_EVT_QUE_ISR)
        {
            dwErr = M_IsrEvtPut(ptEvt);
        }
        else if(dwQue==EN_EVT_QUE_FSM)
        {
            dwErr = M_FsmEvtPut(ptEvt);
        }
    }

    return dwErr;
}



