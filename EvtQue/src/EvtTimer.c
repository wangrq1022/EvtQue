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
#include "EvtKit.h"


//===========================================================
// 函数功能: 任务挂起
//===========================================================
inline UINT32 EvtTimerDelay(UINT32 dwMicroSecond)
{    
    //睡眠微秒      
    return usleep(dwMicroSecond);  
}

//===========================================================
// 函数功能: 任务挂起
//===========================================================
inline UINT32 EvtTimerSleep(UINT32 dwSecond)
{
    //睡眠秒  
    return sleep(dwSecond);    
}


//===========================================================
// 函数功能: 获取当前毫秒计数
//===========================================================
inline UINT32 EvtTimerNow(void)
{           
    // 获取当前时间
    struct timeval tv;
    gettimeofday(&tv,NULL);

    // 当前毫秒计数
    return (tv.tv_sec*1000 + tv.tv_usec/1000);
}


//===========================================================
// 函数功能: 定时器初始化
//===========================================================
UINT32 EvtTimerInit(tagEvtTimer *pMe, UINT32 dwNum)
{
    UINT32      dwLoop;
    tagEvtTimer *pTimer;

    for(pTimer=&pMe[0],dwLoop=0; dwLoop<dwNum; pTimer++,dwLoop++)
    {
        // 将定时器数量的上限值作为停止标志
        pTimer->dwFlag = dwNum;

        // 设置定时器对应的事件类型
        pTimer->dwType = dwLoop;
    }

    return 0;    
}

//===========================================================
// 函数功能: 定时器启动
//===========================================================
UINT32 EvtTimerStart(tagEvtTimer *pMe,UINT32 dwTimer,UINT32 dwAttr,UINT32 dwEnd,UINT32 dwDlt)
{

    pMe->dwFlag = dwTimer;  
    pMe->dwAttr = dwAttr; 
       
    pMe->dwEnd  = dwEnd; 
    pMe->dwDlt  = dwDlt; 
        
    return 0;
}

//===========================================================
// 函数功能: 定时器停止
//===========================================================
UINT32 EvtTimerStop(tagEvtTimer *pMe)
{

    pMe->dwFlag = CN_EVT_TIMER;  
    pMe->dwAttr = 0; 
       
    pMe->dwEnd  = 0; 
    pMe->dwDlt  = 0 ; 
        
    return 0;
}

//===========================================================
// 函数功能: 统一转换为毫秒单位计数
//===========================================================
UINT32 EvtTimerCnvt(UINT32 dwType, UINT32 dwCnt, UINT32 *pdwEnd, UINT32 *pdwDlt)
{      
    UINT32      dwEnd, dwDlt;

    // 检查
    if((!pdwEnd)||(!pdwDlt))
    {
        return 1;
    }

    
    // 获取当前时间
    struct timeval tv;
    gettimeofday(&tv,NULL);

    // 统一转换为毫秒单位计数
    switch(dwType)
    {
        case EN_TIMER_MS:
            dwDlt = dwCnt;
            dwEnd = dwDlt + tv.tv_sec*1000 + tv.tv_usec/1000;
            break;
        case EN_TIMER_S:
            dwDlt = dwCnt*1000;
            dwEnd = dwDlt + tv.tv_sec*1000;
            break;
        case EN_TIMER_M:      
            dwDlt = dwCnt*1000*60;    
            dwEnd = dwDlt + tv.tv_sec*1000;
            break;
        case EN_TIMER_H:           
            dwDlt = dwCnt*1000*60*60;  
            dwEnd = dwDlt + tv.tv_sec*1000;
            break;
        case EN_TIMER_D:           
            dwDlt = dwCnt*1000*60*60*24;
            dwEnd = dwDlt + tv.tv_sec*1000;
            break;
        
        default:
            return 3;    
    }         
         
    // 转换后的时间
    *pdwEnd = dwEnd;
    *pdwDlt = dwDlt;

    return 0;
} 

//===========================================================
// 函数功能: 定时器更新
//===========================================================
UINT32 EvtTimerUpdt(tagEvtTimer *pMe, UINT32 dwNow)
{
    UINT32      dwRst = 0;


    // 定时器属性
    switch(pMe->dwAttr)
    {
        case 0:
            // 检查是否到时
            if(dwNow > pMe->dwEnd)
            {
                // 定时器停止标志
                pMe->dwFlag = CN_EVT_TIMER;

                dwRst = 1;
            }
            break;
        case 1:
            // 检查是否到时

                // 更新定时器结束计时
            
            break;
        default:
            break;               
    }

            
    return dwRst;
}

