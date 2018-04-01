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

#include "EvtData.h"
#include "Random.h" 

#if(CN_OS_TYPE==1)
    pthread_mutex_t RandMutex;                  // 互斥信号量-避免多线程读写风险
#endif



//===========================================================
// 函数功能: 事件缓冲区初始化
//===========================================================
UINT32 EvtQueInit(tagQueCtrl *ptQueCtrl, void *pQue, UINT32 dwNum, UINT32 dwSize)
{
    // 互斥信号量初始化
#if(CN_OS_TYPE==1)
    pthread_mutex_init(&ptQueCtrl->Mutex, 0);
#endif

    return DataQueInit(ptQueCtrl, pQue, dwNum, dwSize);
} 

//===========================================================
// 函数功能: 事件缓冲区读出
//===========================================================
UINT32 EvtQueRead(tagQueCtrl *ptQueCtrl, void *pDst, UINT32 dwRdNum)
{
    UINT32  dwRst;    

    // 上锁
#if(CN_OS_TYPE==1)
    pthread_mutex_lock(&ptQueCtrl->Mutex);
#endif

    // 操作
    dwRst = DataQueRead(ptQueCtrl, pDst, dwRdNum);

    // 释放
#if(CN_OS_TYPE==1)
    pthread_mutex_unlock(&ptQueCtrl->Mutex);
#endif

    return dwRst;
}

//===========================================================
// 函数功能: 事件缓冲区写入
//===========================================================
UINT32 EvtQueWrite(tagQueCtrl *ptQueCtrl, void *pSrc, UINT32 dwWrNum)
{
    UINT32  dwRst;    

    // 上锁
#if(CN_OS_TYPE==1)
    pthread_mutex_lock(&ptQueCtrl->Mutex);
#endif

    // 操作
    dwRst = DataQueWrite(ptQueCtrl, pSrc, dwWrNum);

    // 释放
#if(CN_OS_TYPE==1)
    pthread_mutex_unlock(&ptQueCtrl->Mutex);
#endif

    return dwRst;
}


//===========================================================
// 函数功能: 事件缓冲区信息
//===========================================================
void EvtQueInfo(tagQueCtrl *ptQueCtrl)
{
    // 上锁
#if(CN_OS_TYPE==1)
    pthread_mutex_lock(&ptQueCtrl->Mutex);
#endif

    // 操作
    DataQueInfo(ptQueCtrl);

    // 释放
#if(CN_OS_TYPE==1)
    pthread_mutex_unlock(&ptQueCtrl->Mutex);
#endif

    return;
}

//===========================================================
// 函数功能: 事件内存池初始化
//===========================================================
UINT32 EvtPoolCreat(tagPoolCtrl *ptPoolCtrl, void *pPool, UINT32 dwNum, UINT32 dwSize)
{
    // 互斥信号量初始化
#if(CN_OS_TYPE==1)
    pthread_mutex_init(&ptPoolCtrl->Mutex, 0);
#endif

    return DataPoolCreat(ptPoolCtrl, pPool, dwNum, dwSize);
} 

//===========================================================
// 函数功能: 事件内存池获取
//===========================================================
void * EvtPoolGet(tagPoolCtrl *ptPoolCtrl, UINT32 *pdwErr)
{
    void *pData;    

    // 上锁
#if(CN_OS_TYPE==1)
    pthread_mutex_lock(&ptPoolCtrl->Mutex);
#endif

    // 操作
    pData = DataPoolGet(ptPoolCtrl, pdwErr);

    // 释放
#if(CN_OS_TYPE==1)
    pthread_mutex_unlock(&ptPoolCtrl->Mutex);
#endif

    return pData;
}

//===========================================================
// 函数功能: 事件内存池放回
//===========================================================
UINT32 EvtPoolPut(tagPoolCtrl *ptPoolCtrl, void *pData)
{
    UINT32  dwRst;    

    // 上锁
#if(CN_OS_TYPE==1)
    pthread_mutex_lock(&ptPoolCtrl->Mutex);
#endif

    // 操作
    dwRst = DataPoolPut(ptPoolCtrl, pData);

    // 释放
#if(CN_OS_TYPE==1)
    pthread_mutex_unlock(&ptPoolCtrl->Mutex);
#endif

    return dwRst;
}

//===========================================================
// 函数功能: 事件内存池放回
//===========================================================
UINT32 EvtRandSet(void)
{
    // 互斥信号量初始化
#if(CN_OS_TYPE==1)
    pthread_mutex_init(&RandMutex, 0);
#endif

    M_SetRandomSeed();

    return 0;
}

//===========================================================
// 函数功能: 事件内存池放回
//===========================================================
UINT32 EvtRandGet(UINT32 dwRange)
{
    UINT32  dwRst;    

    // 上锁
#if(CN_OS_TYPE==1)
    pthread_mutex_lock(&RandMutex);
#endif

    // 操作
    dwRst = M_GetRandom(dwRange);

    // 释放
#if(CN_OS_TYPE==1)
    pthread_mutex_unlock(&RandMutex);
#endif

    return dwRst;
}

