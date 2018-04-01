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

     
/*================================================================================
 * 内部结构体声明
 *================================================================================*/
 


/*================================================================================
 * 内部常量声明
 *================================================================================*/
                    
                          


/*================================================================================
 * 内部数据声明
 *================================================================================*/

//===========================================================
// 函数功能: 内存池信息
//===========================================================
void EvtGenInfo(tagEvtGenObj *pMe)
{
    UINT32      dwLoop; 

    printf("EvtGenInfo:\n");

    for(dwLoop=0;dwLoop<pMe->dwPoolNum;dwLoop++)
    {
        DataPoolInfo(pMe->ptPoolTable[dwLoop].ptPoolCtrl);
        //DataPoolShow(pMe->ptPoolTable[dwLoop].ptPoolCtrl);
    }

    return;    
}

//===========================================================
// 函数功能: 事件生成器初始化
//===========================================================
UINT32 EvtGenCreat(tagEvtGenObj *pMe, tagPoolTable *ptPoolTable, UINT32 dwPoolNum)
{
    UINT32          dwErr, dwLoop;
    
    // 检查 
    if(dwPoolNum < 3)
    {
        printf("EvtGenCreat:Num Err\n");
        return 1;
    }
    if(!ptPoolTable)
    {
        printf("EvtGenCreat:Pool Err\n");
        return 2;
    }

    // 初始化内存池     
    for(dwLoop=0;dwLoop<dwPoolNum;dwLoop++)
    {
        dwErr = EvtPoolCreat(ptPoolTable[dwLoop].ptPoolCtrl,\
                             ptPoolTable[dwLoop].pPool,     \
                             ptPoolTable[dwLoop].dwNum,     \
                             ptPoolTable[dwLoop].dwSize      );
                                            
        if(dwErr)
        {
            printf("EvtGenCreat: Err=%d,Loop=%d\n",dwErr,dwLoop);       
            return 3;
        }
    }

    // 事件生成器信息 
    pMe->ptPoolTable = ptPoolTable;         // 内存池
    pMe->dwPoolNum   = dwPoolNum;           // 内存池数量

    return 0;    
}

//===========================================================
// 函数功能: 内存池获取数据块指针
//===========================================================
void * EvtGenGet(tagEvtGenObj *pMe, UINT32 dwSize)
{
    UINT32          dwErr, dwLoop;
    tagEvent        *ptEvt = NULL;

    // 选择大小合适的内存块作为事件指针   
    for(dwLoop=0;dwLoop<pMe->dwPoolNum;dwLoop++)
    {
        if(pMe->ptPoolTable[dwLoop].dwSize >= dwSize)
        {   
            ptEvt = (tagEvent *)EvtPoolGet(pMe->ptPoolTable[dwLoop].ptPoolCtrl, &dwErr); 
            if(ptEvt)
            {
                // 新生成的事件需要标记内存池编号
                ptEvt->dwPool = dwLoop;
                
                return ptEvt;
            }
        }
    }

    //--need fix 运行到此处要保存异常告警信息
    //--抛出异常提醒
    printf("EvtGenGet: Pool buffer is empty, pool info is : \n");

    M_EvtGenInfo();
    longjmp(g_ErrBuf, 1);
    
    return ptEvt;
}

//===========================================================
// 函数功能: 内存池放回数据块指针
//===========================================================
UINT32 EvtGenPut(tagEvtGenObj *pMe, void *pData)
{
    UINT32          dwErr=0, dwLoop;
    tagEvent        *ptEvt;
    
    // 事件指针
    ptEvt = (tagEvent *)pData;

    // 根据事件的内存池编号回收内存块
    for(dwLoop=0;dwLoop<pMe->dwPoolNum;dwLoop++)
    {
        if(ptEvt->dwPool == dwLoop)
        {
            //printf("EvtGenPut:Loop=%d,PS=%d,ES=%d\n",dwLoop,pMe->ptPoolTable[dwLoop].dwSize,dwSize);
            dwErr = EvtPoolPut(pMe->ptPoolTable[dwLoop].ptPoolCtrl, pData);

            return dwErr;
        }
    }
    
    //--need fix 运行到此处要保存异常告警信息
    //--抛出异常提醒
    printf("EvtGenPut: Pool buffer is unnormal, pool info is \n");

    M_EvtGenInfo();
    longjmp(g_ErrBuf, 2);

    return dwErr;
}
