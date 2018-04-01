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

#ifndef _DATA_QUE_H_
#define _DATA_QUE_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

//#define CN_NUM_CAN_DATA                 ( 2 )      // CAN数据区个数（1个数据区=1个接收缓存区+1个发送缓存区）

//#define CN_LEN_DATA_FRAME               ( 13  )    // 每个数据帧的长度
//#define CN_NUM_BUF_RECV                 ( 100 )    // 接收缓存区的帧数
//#define CN_NUM_BUF_SEND                 ( 30  )    // 发送缓存区的帧数

// 环形队列控制结构体
typedef struct
{
    void            *pQue;                  // 队列指针
    UINT32          dwNum;                  // 数据个数
    UINT32          dwSize;                 // 数据长度
                                            
    UINT32          dwWr;                   // 数据写入
    UINT32          dwRd;                   // 数据读出
                 
    UINT32          dwEmpty;                // 空闲数据个数
    UINT32          dwUsed;                 // 当前写入个数
    UINT32          dwMax;                  // 最大写入个数      

#if(CN_OS_TYPE==1)
    pthread_mutex_t Mutex;                  // 互斥信号量-避免多线程读写风险
#endif

}tagQueCtrl;                                
                                            
              
/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern BOOL DataQueIsFull(tagQueCtrl *ptQueCtrl);
extern void DataQueInfo(tagQueCtrl *ptQueCtrl); 
extern void DataQueShow(tagQueCtrl *ptQueCtrl); 
extern UINT32 DataQueInit(tagQueCtrl *ptQueCtrl, void *pQue, UINT32 dwNum, UINT32 dwSize);
extern UINT32 DataQueRead(tagQueCtrl *ptQueCtrl, void *pDst, UINT32 dwRdNum);
extern UINT32 DataQueWrite(tagQueCtrl *ptQueCtrl, void *pSrc, UINT32 dwWrNum);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
