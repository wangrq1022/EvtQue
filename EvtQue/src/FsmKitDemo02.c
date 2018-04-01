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


enum _FSM02_STATE_
{
    EN_FSM02_S1 = 0,                                    // 
    EN_FSM02_S2,                                        // 
    EN_FSM02_S3,                                        // 
};

/*================================================================================
 * 
 *================================================================================*/

#define CN_EVT_BUF_02   ( 20 )    // 
#define CN_ISR_BUF_02   ( 20 )    // 

tagEvent  *ptEvtBuf02[CN_EVT_BUF_02];
tagEvent  *ptIsrBuf02[CN_ISR_BUF_02];

const UINT32 g_dwSubTable02[]={
    EN_PUB_A,                                        // 
    EN_PUB_B,                                        // 
    EN_PUB_C,                                        // 
};
const UINT32 CN_EVT_REG_TBL02 = sizeof(g_dwSubTable02)/sizeof(UINT32); 

static UINT32 Fsm02_S1(tagEvent *ptEvt,tagFsmObj *pMe);
static UINT32 Fsm02_S2(tagEvent *ptEvt,tagFsmObj *pMe);

static UINT32 Fsm02_Init(tagFsmObj *pMe)
{

    // 设置状态机状态
    M_FsmSet(Fsm02_S1, "Fsm02_S1");

    return 0;
} 


static UINT32 Fsm02_S1(tagEvent *ptEvt,tagFsmObj *pMe)
{
    //tagEvtA       *ptEvtA;
    //tagEvtB       *ptEvtB;
    tagEvtC     *ptEvtC;
    //UINT32      dwErr;

    switch(ptEvt->dwType)
    {
        case EN_PUB_B:
                    
            ptEvtC = M_FsmEvtGet(tagEvtC);
            ptEvtC->fData = 100;
                        
            M_FsmPubEvt(ptEvtC, EN_PUB_C);
            
            M_FsmJump(Fsm02_S2, "Fsm02_S2");
                            

            break;                      
        default:        
            break;      
    }

    return 0;
} 

static UINT32 Fsm02_S2(tagEvent *ptEvt,tagFsmObj *pMe)
{
    //tagEvtA       *ptEvtA;
    //tagEvtB       *ptEvtB;
    tagEvtC     *ptEvtC;
    //UINT32      dwErr;

    switch(ptEvt->dwType)
    {
        case EN_PUB_C:
                    
            ptEvtC = M_FsmEvtGet(tagEvtC);
            ptEvtC->dwData = 101;
                        
            M_FsmPubEvt(ptEvtC, EN_PUB_C);
            
            M_FsmJump(Fsm02_S1, "Fsm02_S1");
                            
            break;                      
        default:        
            break;      
    }

    return 0;
} 


void Fsm02_Build(void)
{
    // 状态机构建
    FsmBuilder(EN_FSM_2, (void *)&ptEvtBuf02[0], CN_EVT_BUF_02,\
                         (void *)&ptIsrBuf02[0], CN_ISR_BUF_02);

    // 事件订阅
    EvtSubscriber(EN_FSM_2, (UINT32 *)&g_dwSubTable02[0], CN_EVT_REG_TBL02);

    // 初始状态
    FsmConstructor(EN_FSM_2, "Fsm02", (FUNCPTR)Fsm02_Init, NULL);

    return;
} 
