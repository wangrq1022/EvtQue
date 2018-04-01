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

#include "FsmKitDemo.h"


enum _FSM01_STATE_
{
    EN_FSM01_S1 = 0,                                    // 
    EN_FSM01_S2,                                        // 
    EN_FSM01_S3,                                        // 
};


/*================================================================================
 * 
 *================================================================================*/

#define CN_EVT_BUF_01   ( 20  )    // 
#define CN_ISR_BUF_01   ( 20  )    // 

tagEvent  *ptEvtBuf01[CN_EVT_BUF_01];
tagEvent  *ptIsrBuf01[CN_ISR_BUF_01];

const UINT32 g_dwSubTable01[]={
    EN_PUB_A,                                        // 
    EN_PUB_B,                                        // 
    EN_PUB_C,                                        // 
    EN_PUB_TIMER_T15,
};
const UINT32 CN_EVT_REG_TBL01 = sizeof(g_dwSubTable01)/sizeof(UINT32); 

static UINT32 Fsm01_S1(tagEvent *ptEvt,tagFsmObj *pMe);
static UINT32 Fsm01_S2(tagEvent *ptEvt,tagFsmObj *pMe);

static UINT32 Fsm01_Init(tagFsmObj *pMe)
{
    tagEvtThread   tPara;

    // 获取运行参数
    EvtThreadParaGet(&tPara);

    // 启动测试定时器
    M_EvtTimerSet(1, EN_PUB_TIMER_T15, EN_TIMER_MS, tPara.dwTimer);
    printf("Fsm01_Init:Set Timer counting is %d(ms)\n",tPara.dwTimer);


    // 设置状态机状态
    M_FsmSet(Fsm01_S1, "Fsm01_S1");

    return 0;
} 


static UINT32 Fsm01_S1(tagEvent *ptEvt,tagFsmObj *pMe)
{
    //tagEvtA       *ptEvtA;
    tagEvtB     *ptEvtB;
    //tagEvtC       *ptEvtC;
    //UINT32      dwErr;
    

    switch(ptEvt->dwType)
    {
        case EN_PUB_TIMER_T15:
                    
            printf("Fsm01_S1:Got time event!\n");

        case EN_PUB_A:
                    
            ptEvtB = M_FsmEvtGet(tagEvtB);
            ptEvtB->fData = 10;

            M_FsmPubEvt(ptEvtB, EN_PUB_B);
            
            M_FsmJump(Fsm01_S2, "Fsm01_S2");
                            
            break;
  
        default:        
            break;      
    }

    return 0;
} 

static UINT32 Fsm01_S2(tagEvent *ptEvt,tagFsmObj *pMe)
{
    //tagEvtA       *ptEvtA;
    //tagEvtB       *ptEvtB;
    tagEvtC     *ptEvtC;
    //UINT32      dwErr;

    switch(ptEvt->dwType)
    {
        case EN_PUB_B:
                    
            ptEvtC = M_FsmEvtGet(tagEvtC);          
            ptEvtC->fData = 9;
            ptEvtC->dwData = 9;
            
            M_FsmPubEvt(ptEvtC, EN_PUB_C);
            
            M_FsmJump(Fsm01_S1, "Fsm01_S1");
                
            break;

        case EN_PUB_TIMER_T15:
                    
            printf("Fsm01_S2:Got time event!\n");
                
            break;
            
        default:        
            break;      
    }

    return 0;
} 


void Fsm01_Build(void)
{
    // 状态机构建 
    FsmBuilder(EN_FSM_1, (void *)&ptEvtBuf01[0], CN_EVT_BUF_01,\
                         (void *)&ptIsrBuf01[0], CN_ISR_BUF_01);

    // 事件订阅 
    EvtSubscriber(EN_FSM_1, (UINT32 *)&g_dwSubTable01[0], CN_EVT_REG_TBL01);

    // 初始状态
    FsmConstructor(EN_FSM_1, "Fsm01", (FUNCPTR)Fsm01_Init, NULL);

    return;
} 
