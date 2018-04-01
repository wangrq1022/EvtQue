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

#ifndef _FSM_BOJ_H_
#define _FSM_BOJ_H_

#include "Macro.h"
#include "EvtData.h"


#ifdef __cplusplus
extern "C" {
#endif


/*================================================================================*/

// 状态机的状态
typedef struct
{   
    char *          cName;                  // 状态机名称
    FUNCPTR         pHandle;                // 状态执行函数指针 
    
}tagState;

// 状态机的私有数据
typedef struct
{   
    FUNCPTR         pInit;                  // 私有数据的初始化函数
    void *          pData;                  // 私有数据结构体

}tagPrivate;


// 状态机定义结构体
typedef struct
{   
    UINT32          dwFsm;                  // 状态机的编号 
    char *          cName;                  // 状态机名称

    tagState        tNow;                   // 状态机的状态
    tagState        tNext;                  // 状态机的状态

    tagPrivate      tPrivate;               // 状态机的私有数据

    tagQueCtrl      tIsrQue;                // 事件接收缓冲区-由中断执行函数写入 
    tagQueCtrl      tFsmQue;                // 事件接收缓冲区-由其他状态机写入 
    tagQueCtrl      tJmpQue;                // 事件接收缓冲区-由状态机本机写入 

    UINT32          dwJump;

}tagFsmObj;

/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern UINT32 FsmObjInit(tagFsmObj *pMe, UINT32 dwNum);
extern UINT32 FsmPrivtInit(tagFsmObj *pMe, UINT32 dwNum);
extern UINT32 FsmObjBuild(tagQueCtrl *ptQueCtrl,void *pQue,UINT32 dwNum);
extern UINT32 FsmObjRun(tagFsmObj *pMe);

extern UINT32 FsmObjNow(tagFsmObj *pMe, FUNCPTR pHandle, char *cName);
extern UINT32 FsmObjNext(tagFsmObj *pMe, FUNCPTR pHandle, char *cName);

extern UINT32 FsmObjRdy(tagFsmObj *pMe);


/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
