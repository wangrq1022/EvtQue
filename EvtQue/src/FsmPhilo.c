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

#include "PhiloDemo.h"

/*================================================================================
 * 状态机配置
 *================================================================================*/


// 哲学家的内部事件
enum _EVT_PHILO_PRIVATE_
{
    // 内置事件
    EN_PVT_PHILO_BEGIN = EN_JMP_END,

    EN_PVT_PHILO_TIMER = EN_PVT_PHILO_BEGIN,

    EN_PVT_PHILO_END,

};


// 哲学家私有变量
typedef struct
{
    UINT32      dwPhilo; 
    UINT32      dwTimer;

    UINT32      dwLeft;
    UINT32      dwRight;

    UINT32      dwType;
    UINT32      dwRand;
    
}tagPhiloObj;


// 哲学家私有变量
static tagPhiloObj g_tPhilo[CN_PHILO_NUM];


/*================================================================================
 * 状态机配置
 *================================================================================*/

// 缓冲区可容纳的事件数量
#define  CN_FSM_BUF_PHILO   ( 20 )
#define  CN_ISR_BUF_PHILO   ( 20 )

// 缓冲区的数组
tagEvent  *ptFsmBufPhilo[CN_PHILO_NUM][CN_FSM_BUF_PHILO];
tagEvent  *ptIsrBufPhilo[CN_PHILO_NUM][CN_ISR_BUF_PHILO];

// 订阅的事件表
const UINT32 g_dwSubPhilo[CN_PHILO_NUM][3]={
    
    {EN_PUB_TIMER_P1,    EN_PUB_TBL_ACCEPT,    EN_PUB_TBL_REFUSE},
    {EN_PUB_TIMER_P2,    EN_PUB_TBL_ACCEPT,    EN_PUB_TBL_REFUSE},
    {EN_PUB_TIMER_P3,    EN_PUB_TBL_ACCEPT,    EN_PUB_TBL_REFUSE},
    {EN_PUB_TIMER_P4,    EN_PUB_TBL_ACCEPT,    EN_PUB_TBL_REFUSE},
    {EN_PUB_TIMER_P5,    EN_PUB_TBL_ACCEPT,    EN_PUB_TBL_REFUSE},    
};
const UINT32 CN_EVT_REG_PHILO = sizeof(g_dwSubPhilo[0])/sizeof(UINT32); 

// 订阅的事件表
const char *g_cPhilo[CN_PHILO_NUM]={

    "Philo(0)",    
    "Philo(1)",    
    "Philo(2)",    
    "Philo(3)",    
    "Philo(4)",    
};


/*================================================================================
 * 状态机执行
 *================================================================================*/
UINT32 FsmPhilo_Rand(void)
{
    UINT32  dwRand;
    
    dwRand = EvtRandGet(10);    

    return (dwRand>=5)? dwRand: dwRand+5;
} 

static UINT32 FsmPhilo_Think(tagEvent *ptEvt,tagFsmObj *pMe);
static UINT32 FsmPhilo_Wait(tagEvent *ptEvt,tagFsmObj *pMe);
static UINT32 FsmPhilo_Eat(tagEvent *ptEvt,tagFsmObj *pMe);


static UINT32 FsmPhilo_Init(tagFsmObj *pMe)
{
    UINT32          dwPhilo;
    tagPhiloObj     *ptPhilo;

    // 获取私有变量指针
    ptPhilo = M_FsmGetPvt(tagPhiloObj);

    // 私有变量初始化
    dwPhilo = pMe->dwFsm - EN_FSM_P1;
    
    ptPhilo->dwPhilo = dwPhilo;
    ptPhilo->dwTimer = g_dwSubPhilo[dwPhilo][0];
    ptPhilo->dwLeft  = dwPhilo;
    ptPhilo->dwRight = (dwPhilo + 1)%CN_PHILO_NUM;
    ptPhilo->dwType  = EN_TIMER_S;

    // 设置定时器
    ptPhilo->dwRand = FsmPhilo_Rand();    
    M_EvtTimerSet(1, ptPhilo->dwTimer, ptPhilo->dwType, ptPhilo->dwRand);

    printf("Philo(%d):Set Timer(%d) counting is %d(s)\n",dwPhilo,ptPhilo->dwTimer,ptPhilo->dwRand);


    // 设置状态机状态
    M_FsmSet(FsmPhilo_Think, "THINK");

    return 0;
} 


static UINT32 FsmPhilo_Think(tagEvent *ptEvt,tagFsmObj *pMe)
{
    tagPhiloGet     *ptEvtGet;
    tagPhiloObj     *ptPhilo;

    // 获取私有变量指针
    ptPhilo = M_FsmGetPvt(tagPhiloObj);

    // 事件驱动状态机
    switch(ptEvt->dwType)
    {
        case EN_JMP_ENTER:
            printf("%s enter %s\n",pMe->cName,pMe->tNow.cName);
            break;
        case EN_JMP_EXIT:
            printf("%s exit %s\n",pMe->cName,pMe->tNow.cName);
            break;

        case EN_PUB_TIMER_P1:
        case EN_PUB_TIMER_P2:
        case EN_PUB_TIMER_P3:
        case EN_PUB_TIMER_P4:
        case EN_PUB_TIMER_P5:                    

            ptEvtGet = M_FsmEvtGet(tagPhiloGet);
            ptEvtGet->dwForks[0] = ptPhilo->dwLeft;
            ptEvtGet->dwForks[1] = ptPhilo->dwRight;

            M_FsmPubEvt(ptEvtGet, EN_PUB_PHILO_GET);

            M_FsmJump(FsmPhilo_Wait, "WAIT");

            printf("Philo(%d) is hungry!\n",ptPhilo->dwPhilo);

            break;
 
        default:        
            break;      
    }

    return 0;
} 

static UINT32 FsmPhilo_Wait(tagEvent *ptEvt,tagFsmObj *pMe)
{
    tagTblAccept    *ptAccept;
    tagTblRefuse    *ptRefuse;
    tagPhiloObj     *ptPhilo;

    // 获取私有变量指针
    ptPhilo = M_FsmGetPvt(tagPhiloObj);

    // 事件驱动状态机
    switch(ptEvt->dwType)
    {
        case EN_JMP_ENTER:
            printf("%s enter %s\n",pMe->cName,pMe->tNow.cName);
            break;
        case EN_JMP_EXIT:
            printf("%s exit %s\n",pMe->cName,pMe->tNow.cName);
            break;

        case EN_PUB_TBL_ACCEPT:

            ptAccept = (tagTblAccept *)ptEvt;
            if(ptAccept->dwPhilo==ptPhilo->dwPhilo)
            {
                // 设置定时器
                ptPhilo->dwRand = FsmPhilo_Rand();    
                M_EvtTimerSet(1, ptPhilo->dwTimer, ptPhilo->dwType, ptPhilo->dwRand);

                M_FsmJump(FsmPhilo_Eat, "EAT");

                printf("Philo(%d) is eating, set timer counting is %d(s)!\n",ptPhilo->dwPhilo,ptPhilo->dwRand);

            }
                            
            break;

        case EN_PUB_TBL_REFUSE:

            ptRefuse = (tagTblRefuse *)ptEvt;
            if(ptRefuse->dwPhilo==ptPhilo->dwPhilo)
            {
                // 设置定时器
                ptPhilo->dwRand = FsmPhilo_Rand();    
                M_EvtTimerSet(1, ptPhilo->dwTimer, ptPhilo->dwType, ptPhilo->dwRand);

                M_FsmJump(FsmPhilo_Think, "THINK");

                printf("Philo(%d) cant got forks, thinking again, set timer counting is %d(s)!\n",ptPhilo->dwPhilo,ptPhilo->dwRand);

            }
                            
            break;
            
        default:        
            break;      
    }

    return 0;
} 



static UINT32 FsmPhilo_Eat(tagEvent *ptEvt,tagFsmObj *pMe)
{
    tagPhiloPut     *ptEvtPut;
    tagPhiloObj     *ptPhilo;

    // 获取私有变量指针
    ptPhilo = M_FsmGetPvt(tagPhiloObj);

    // 事件驱动状态机
    switch(ptEvt->dwType)
    {
        case EN_JMP_ENTER:
            printf("%s enter %s\n",pMe->cName,pMe->tNow.cName);
            break;
        case EN_JMP_EXIT:
            printf("%s exit %s\n",pMe->cName,pMe->tNow.cName);
            break;

        case EN_PUB_TIMER_P1:
        case EN_PUB_TIMER_P2:
        case EN_PUB_TIMER_P3:
        case EN_PUB_TIMER_P4:
        case EN_PUB_TIMER_P5:                    

            ptEvtPut = M_FsmEvtGet(tagPhiloPut);
            ptEvtPut->dwForks[0] = ptPhilo->dwLeft;
            ptEvtPut->dwForks[1] = ptPhilo->dwRight;

            M_FsmPubEvt(ptEvtPut, EN_PUB_PHILO_PUT);

            // 设置定时器
            ptPhilo->dwRand = FsmPhilo_Rand();
            M_EvtTimerSet(1, ptPhilo->dwTimer, ptPhilo->dwType, ptPhilo->dwRand);
            
            printf("Philo(%d) is full, thinking again, set timer counting is %d(s)!\n",ptPhilo->dwPhilo,ptPhilo->dwRand);

            M_FsmJump(FsmPhilo_Think, "THINK");
                
            break;
            
        default:        
            break;      
    }

    return 0;
} 


static UINT32 FsmPhilo_Sta(tagEvent *ptEvt,tagFsmObj *pMe)
{
    UINT32          dwLoop, dwFsm;
    tagPhiloObj     *ptPhilo;

    // 获取私有变量指针
    ptPhilo = M_FsmGetPvt(tagPhiloObj);
    
    // 获取状态信息表
    printf("Philo(%d):%s \n",ptPhilo->dwPhilo,pMe->tNow.cName);
    
    for(dwFsm=EN_FSM_P1,dwLoop=0;dwLoop<CN_PHILO_NUM;dwLoop++,dwFsm++)
    {
        if(ptPhilo->dwPhilo==dwLoop)
        {
            //continue;
        }
        printf("Philo(%d):%s |",dwLoop,M_FsmObjSta(dwFsm));
    }
    
    printf("\n");

    return 0;
} 


void FsmBuild_Philo(void)
{
    UINT32  dwLoop, dwFsm;

    // 设置随机数种子
    EvtRandSet();

    // 全体哲学家状态机
    for(dwFsm=EN_FSM_P1,dwLoop=0;dwLoop<CN_PHILO_NUM;dwLoop++,dwFsm++)

   {
        // 状态机构建 
        FsmBuilder(dwFsm, (void *)&ptFsmBufPhilo[dwLoop][0], CN_FSM_BUF_PHILO,\
                          (void *)&ptIsrBufPhilo[dwLoop][0], CN_ISR_BUF_PHILO);

        // 事件订阅 
        EvtSubscriber(dwFsm, (UINT32 *)&g_dwSubPhilo[dwLoop], CN_EVT_REG_PHILO);


        // 初始状态构建
        FsmConstructor(dwFsm,(char *)g_cPhilo[dwLoop],(FUNCPTR)FsmPhilo_Init, (void *)&g_tPhilo[dwLoop]);
        
    }

    return;
} 
