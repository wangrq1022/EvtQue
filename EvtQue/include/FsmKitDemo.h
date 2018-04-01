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

#ifndef _FSMKIT_DEMO_H_
#define _FSMKIT_DEMO_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"
#include "EvtKit.h" 
#include "FsmKit.h" 

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/
// 应用事件定义结构体
typedef struct
{
    tagEvent    tEvent;     // 事件头
    UINT32      dwData; 
    
}tagEvtA;

// 应用事件定义结构体
typedef struct
{
    tagEvent    tEvent;     // 事件头
    FLOAT32     fData; 
    
}tagEvtB;

// 应用事件定义结构体
typedef struct
{
    tagEvent    tEvent;     // 事件头
    FLOAT32     fData; 
    UINT32      dwData;
    
}tagEvtC;

/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern void Fsm01_Build(void);
extern void Fsm02_Build(void);
/*================================================================================*/

#ifdef __cplusplus
}
#endif

#endif
