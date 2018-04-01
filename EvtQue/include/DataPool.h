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

#ifndef _DATA_POOL_H_
#define _DATA_POOL_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

// 内存池控制结构体
typedef struct
{
    void            *pPool;                 // 内存池指针
    void            *pFree;                 // 空闲块指针
 
    UINT32          dwNum;                  // 数据块个数
    UINT32          dwSize;                 // 数据块长度
                 
    UINT32          dwEmpty;                // 空闲数据块个数
    UINT32          dwUsed;                 // 当前使用块个数
    UINT32          dwMax;                  // 最大使用块个数

#if(CN_OS_TYPE==1)
    pthread_mutex_t Mutex;                  // 互斥信号量-避免多线程读写风险
#endif

}tagPoolCtrl;

/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern UINT32 DataPoolCreat(tagPoolCtrl *ptPoolCtrl, void *pPool, UINT32 dwNum, UINT32 dwSize);
extern void * DataPoolGet(tagPoolCtrl *ptPoolCtrl, UINT32 *pdwErr);
extern UINT32 DataPoolPut(tagPoolCtrl *ptPoolCtrl, void *pData);

extern void DataPoolShow(tagPoolCtrl *ptPoolCtrl);
extern void DataPoolInfo(tagPoolCtrl *ptPoolCtrl);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
