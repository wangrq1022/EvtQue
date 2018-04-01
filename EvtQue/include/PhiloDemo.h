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

#ifndef _PHILO_DEMO_H_
#define _PHILO_DEMO_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"
#include "EvtKit.h" 
#include "FsmKit.h" 

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/
// 哲学家数量
#define  CN_PHILO_NUM       ( EN_FSM_TBL - EN_FSM_P1 )



// 哲学家获取叉子
typedef struct
{
    tagEvent    tEvent;     // 事件头
    UINT32      dwForks[2]; 
    
}tagPhiloGet;

// 哲学家放回叉子
typedef struct
{
    tagEvent    tEvent;     // 事件头
    UINT32      dwForks[2]; 
    
}tagPhiloPut;

// 桌子允许使用叉子
typedef struct
{
    tagEvent    tEvent;     // 事件头
    UINT32      dwPhilo; 
    
}tagTblAccept;

// 桌子拒绝提供叉子
typedef struct
{
    tagEvent    tEvent;     // 事件头
    UINT32      dwPhilo; 
    
}tagTblRefuse;


/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern void FsmBuild_Philo(void);
extern void FsmBuild_Table(void);
/*================================================================================*/

#ifdef __cplusplus
}
#endif

#endif
