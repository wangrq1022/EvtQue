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

#ifndef _EVT_GENERATOR_H_
#define _EVT_GENERATOR_H_

#include "Macro.h"
#include "EvtData.h" 

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/
#define CN_EVT_GEN_MODE   ( CN_DATA_LOCATE_MODE )   // 0-动态分配模式 1-静态分配模式


// 事件发生器-内存池
typedef struct
{
    tagPoolCtrl     *ptPoolCtrl;             // 内存池控制
    void            *pPool;
    UINT32          dwNum;
    UINT32          dwSize;
    
}tagPoolTable;

// 事件发生器-控制
typedef struct
{
    tagPoolTable    *ptPoolTable;            // 内存池表 
    UINT32          dwPoolNum;               // 内存池数量

}tagEvtGenObj;


/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern UINT32 EvtGenCreat(tagEvtGenObj *pMe, tagPoolTable *ptPoolTable, UINT32 dwNum);
extern void * EvtGenGet(tagEvtGenObj *pMe, UINT32 dwSize);
extern UINT32 EvtGenPut(tagEvtGenObj *pMe, void *pData);

extern void EvtGenShow(tagEvtGenObj *pMe);
extern void EvtGenInfo(tagEvtGenObj *pMe);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
