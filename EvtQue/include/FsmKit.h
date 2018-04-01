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


#ifndef _FSM_KIT_H_
#define _FSM_KIT_H_

#include "EvtPublisher.h"
#include "FsmObject.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

enum _EVT_FSM_INDEX_
{
    EN_FSM_TIMER = 0,                                //--不可修改

    EN_FSM_1,                                        // 
    EN_FSM_2,                                        // 
    EN_FSM_3,                                        // 

    EN_FSM_P1,                                       // philosopher
    EN_FSM_P2,                                       // philosopher
    EN_FSM_P3,                                       // philosopher
    EN_FSM_P4,                                       // philosopher
    EN_FSM_P5,                                       // philosopher
    EN_FSM_TBL,                                      // table


    EN_FSM_END,
};

/*================================================================================
 * 对外声明全局变量 
 *================================================================================*/
extern tagFsmObj    g_tFsmTable[EN_FSM_END];        // 状态机总表 
/*================================================================================*/


/*================================================================================
 * 对外声明函数和宏定义 
 *================================================================================*/
extern void   FsmRunSingleThread(void);
extern void   FsmRunMultiThread(UINT32 dwFsmNo);
extern UINT32 FsmObjInitAll(void);
extern UINT32 FsmPrivtInitAll(void);
extern UINT32 FsmObjBuildAll(void);
extern UINT32 FsmBuilder(UINT32 dwFsmNo,void *pEvtQue,UINT32 dwEvtNum,void *pIsrQue,UINT32 dwIsrNum);
extern UINT32 FsmConstructor(UINT32 dwFsmNo,char *cName,FUNCPTR pInit,void *pData);
 
#define M_FsmObjSta(dwFsmNo)        (g_tFsmTable[dwFsmNo].tNow.cName)
#define M_FsmObjFlg(dwFsmNo)        (g_tFsmTable[dwFsmNo].dwFsm)

#define M_FsmGetPvt(tType)          ((tType *)pMe->tPrivate.pData)

#define M_FsmSet(pHandle, cName)    FsmObjNow(pMe, (FUNCPTR)pHandle, cName)
#define M_FsmJump(pHandle, cName)   FsmObjNext(pMe, (FUNCPTR)pHandle, cName)

#define M_FsmPubEvt(ptEvt, dwType)  FsmPubEvt((void *)ptEvt, dwType)

#define M_FsmExit()                 do{\
                                        tagEvent tEvt;\
                                        tEvt.dwType = EN_JMP_EXIT;\
                                        pMe->tNow.pHandle(&tEvt, pMe);\
                                    }while(0)

#define M_FsmEnter()                do{\
                                        tagEvent tEvt;\
                                        tEvt.dwType = EN_JMP_ENTER;\
                                        pMe->tNow.pHandle(&tEvt, pMe);\
                                    }while(0)


/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
