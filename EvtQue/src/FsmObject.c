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

#include "FsmKit.h"
#include "EvtKit.h"


//===========================================================
// 函数功能: 判断状态机是否就绪
//===========================================================
inline UINT32 FsmObjRdy(tagFsmObj *pMe)
{
    return (pMe->tFsmQue.dwUsed + pMe->tIsrQue.dwUsed);
}

//===========================================================
// 函数功能: 状态机变换 
//===========================================================
inline UINT32 FsmObjNext(tagFsmObj *pMe, FUNCPTR pHandle, char *cName)
{

    // 状态变换
    pMe->tNext.pHandle = pHandle;
    pMe->tNext.cName   = cName;

    pMe->dwJump = 1;
    
    return 0;
}

//===========================================================
// 函数功能: 状态机变换 
//===========================================================
inline UINT32 FsmObjNow(tagFsmObj *pMe, FUNCPTR pHandle, char *cName)
{
    tagEvent    tEvt;

    // 状态变换
    pMe->tNow.pHandle = pHandle;
    pMe->tNow.cName   = cName;

    tEvt.dwType = EN_JMP_ENTER;
    pMe->tNow.pHandle(&tEvt, pMe);    
    
    return 0;
}


//===========================================================
// 函数功能: 状态机初始化 
//===========================================================
UINT32 FsmObjInit(tagFsmObj *pMe, UINT32 dwNum)
{
    UINT32      dwLoop;
    tagFsmObj   *ptFsm;

    for(ptFsm=&pMe[0],dwLoop=0;dwLoop<dwNum;dwLoop++,ptFsm++)
    {
        memset( ptFsm, 0, sizeof(tagFsmObj));        
    }

    return 0;    
}


//===========================================================
// 函数功能: 状态机初始化 
//===========================================================
UINT32 FsmPrivtInit(tagFsmObj *pMe, UINT32 dwNum)
{
    UINT32      dwLoop;
    tagFsmObj   *ptFsm;

    for(ptFsm=&pMe[0],dwLoop=0;dwLoop<dwNum;dwLoop++,ptFsm++)
    {
        if(ptFsm->tPrivate.pInit)
        {
            ptFsm->tPrivate.pInit(ptFsm);
        }
    }

    return 0;    
}


//===========================================================
// 函数功能: 状态机构建 
//===========================================================
UINT32 FsmObjBuild(tagQueCtrl *ptQueCtrl,void *pQue,UINT32 dwNum)
{
    UINT32      dwErr;
    
    
    // 检查 
    if(dwNum < 2)
    {
        printf("FsmObjBuild:Num Err\n");
        return 1;
    }
    if(!pQue)
    {
        printf("FsmObjBuild:Pool Err\n");
        return 2;
    }
    if(!ptQueCtrl)
    {
        printf("FsmObjBuild:QueCtrl Err\n");
        return 3;
    }

    // 事件缓冲区初始化 
    if((dwErr = EvtQueInit(ptQueCtrl, pQue, dwNum, sizeof(tagEvent *))))
    {
        printf("FsmObjBuild:QueInit dwErr=%d\n",dwErr);
    }
    
    return dwErr;    
}


//===========================================================
// 函数功能: 状态机运行 
//===========================================================
inline UINT32 FsmObjRun(tagFsmObj *pMe)
{
    void        *pEvt;
    UINT32      dwErr, dwQue;
    //tagEvent    tEvt;
    tagState    tState;

    // 获取事件
    if(!(pEvt=EvtQueGet(pMe, &dwQue)))
    {
        return 0;
    }
    
    // 状态机执行 
    if(pMe->tNow.pHandle)
    {
        pMe->tNow.pHandle(pEvt, pMe);
    }

    // 状态机跳转
    if(pMe->dwJump)
    {
        //tEvt.dwType = EN_JMP_EXIT;
        //pMe->tNow.pHandle(&tEvt, pMe);
        M_FsmExit();


        memcpy(&pMe->tNow, &pMe->tNext, sizeof(tagState));

        //tEvt.dwType = EN_JMP_ENTER;
        //pMe->tNow.pHandle(&tEvt, pMe);
        M_FsmEnter();
        
        pMe->dwJump = 0;
    }
    
    
    // 内存回收 
    if((dwErr = EvtQuePut(pEvt, dwQue)))
    {
        printf("EvtQuePut:Err=%d,Que=%d\n",dwErr,dwQue);           
        M_EvtGenInfo();
    }

    return dwErr;
}

