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

#ifndef _EVT_DATA_H_
#define _EVT_DATA_H_

#include "Macro.h"
#include "DataKit.h"

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
 * 事件发生器配置
 *==============================================================================*/
 
/*==============================================================================*/

/*==============================================================================
 * 事件定义 
 *==============================================================================*/

/*==============================================================================*/


/*==============================================================================
 * 对外声明全局变量 
 *==============================================================================*/

/*==============================================================================*/



/*==============================================================================
 * 对外声明全局变量 
 *==============================================================================*/

extern UINT32 EvtQueInit(tagQueCtrl *ptQueCtrl, void *pQue, UINT32 dwNum, UINT32 dwSize);
extern UINT32 EvtQueRead(tagQueCtrl *ptQueCtrl, void *pDst, UINT32 dwRdNum);
extern UINT32 EvtQueWrite(tagQueCtrl *ptQueCtrl, void *pSrc, UINT32 dwWrNum);
extern void   EvtQueInfo(tagQueCtrl *ptQueCtrl);

extern UINT32 EvtPoolCreat(tagPoolCtrl *ptPoolCtrl, void *pPool, UINT32 dwNum, UINT32 dwSize);
extern void * EvtPoolGet(tagPoolCtrl *ptPoolCtrl, UINT32 *pdwErr);
extern UINT32 EvtPoolPut(tagPoolCtrl *ptPoolCtrl, void *pData);

extern UINT32 EvtRandSet(void);
extern UINT32 EvtRandGet(UINT32 dwMode);

/*===============================================================================*/


#ifdef __cplusplus
}
#endif

#endif
