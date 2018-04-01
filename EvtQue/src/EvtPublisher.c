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

#include "FsmKit.h"
#include "EvtKit.h"


//===========================================================
// 函数功能: 状态机发送事件
//===========================================================
UINT32 FsmPubEvt(void *pEvt, UINT32 dwType)
{
    UINT32          dwFsm;
    tagEvent        *ptEvt;
    tagListCtrl     *ptList;
    tagListNode     **ppIndex;          // 链表头部指针  
    tagQueCtrl      *ptQue;             // 事件接收缓冲区 
    tagFsmObj       *ptFsm;
    tagEvtTable     *ptTable;
    
    if(dwType >= CN_EVT_TABLE)
    {
        return 1;
    }

    // 事件指针
    ptEvt = (tagEvent *)pEvt;

    // 标记事件类型
    ptEvt->dwType = dwType;
    
    // 事件总表     
    ptTable = &g_tEvtTable[dwType];
    ptList  = &ptTable->tList;
    
    
    if(!ptList->dwNum)
    {
        return 2;       
    }       

    // 标记事件注册次数 
    ptEvt->dwCnt = ptList->dwNum;

    // 遍历链表 
    ppIndex = &ptList->pHead;
    while(*ppIndex)
    {

        // 状态机编号           
        dwFsm = (int)(*ppIndex)->pData;             
        if(dwFsm >= EN_FSM_END)
        {
            return 3;   
        }
        ptFsm = &g_tFsmTable[dwFsm]; 

        // 状态机事件缓冲区指针
        if(ptEvt->dwType < CN_EVT_TIMER)
        {
            ptQue = &ptFsm->tIsrQue;                        
        }
        else
        {
            ptQue = &ptFsm->tFsmQue;                        
        }

        // 写入事件缓冲区
        if(EvtQueWrite(ptQue, (void *)&ptEvt, 1))
        {
            //--wangrq for test @ 20180306
            //printf("FsmSigEvt: E%d,F%d\n",ptEvt->dwType,dwFsm);
            
            // 遍历指针更新 
            ppIndex = &(*ppIndex)->pNext;

        }
        else
        {
            //--need fix 运行到此处要保存异常告警信息
            //--抛出异常提醒
            printf("FsmPubEvt: Fsm(%d) buffer is full, queue info is \n",dwFsm);

            EvtQueInfo(&ptFsm->tIsrQue);
            EvtQueInfo(&ptFsm->tFsmQue);
            longjmp(g_ErrBuf, 3);
            
        }
        
    }
        
    return 0;    
}

