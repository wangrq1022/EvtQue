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
#include "DataQue.h"

//===========================================================
// 函数功能: 数据队列信息
//===========================================================
BOOL DataQueIsFull(tagQueCtrl *ptQueCtrl)
{
    return (ptQueCtrl->dwMax >= ptQueCtrl->dwNum);    
}

//===========================================================
// 函数功能: 数据队列信息
//===========================================================
void DataQueInfo(tagQueCtrl *ptQueCtrl)
{

    printf("DataQueInfo:\n");
    printf("Addr=%p,Num=%d,Size=%d\nWr=%d,Rd=%d,Empty=%d,Used=%d,Max=%d\n\n",
                                                ptQueCtrl->pQue   ,\
                                                ptQueCtrl->dwNum  ,\
                                                ptQueCtrl->dwSize ,\
                                                ptQueCtrl->dwWr   ,\
                                                ptQueCtrl->dwRd   ,\
                                                ptQueCtrl->dwEmpty,\
                                                ptQueCtrl->dwUsed ,\
                                                ptQueCtrl->dwMax);

    return;    
}

//===========================================================
// 函数功能: 数据队列数据
//===========================================================
void DataQueShow(tagQueCtrl *ptQueCtrl)
{
    UINT8           *pbyQue,*pbyData;
    UINT32          dwNum, dwSize, dwLen;

    // 指针初始化
    pbyQue  = (UINT8 *)ptQueCtrl->pQue;
    dwLen   = ptQueCtrl->dwNum * ptQueCtrl->dwSize;
    pbyData = &pbyQue[dwLen - 1];

    printf("Que:Top\n");
    dwNum  = ptQueCtrl->dwNum   ;
    while(dwNum)
    {
        printf("Que[%04d]:",dwNum-1);
        dwSize = ptQueCtrl->dwSize  ;   
        while(dwSize)
        {
            printf("%02x ",*pbyData);
            
            dwSize--;
            pbyData--;
        }
        
        dwNum--;
        
        if(dwNum==ptQueCtrl->dwRd)  printf("<--Rd ");
        if(dwNum==ptQueCtrl->dwWr)  printf("<--Wr ");       
        if(dwNum!=0)                printf("\n");
        
    }

    printf("\n");
    printf("Que:Bottom\n\n");


    return;    
}

//===========================================================
// 函数功能: 数据队列初始化
//===========================================================
UINT32 DataQueInit(tagQueCtrl *ptQueCtrl, void *pQue, UINT32 dwNum, UINT32 dwSize)
{
    // 检查 
    if(!dwNum)
    {
        printf("DataQueInit:Err\n");
        return 1;
    }
    
    // 队列结构
    ptQueCtrl->pQue   = pQue    ;                  // 队列指针
    ptQueCtrl->dwNum  = dwNum   ;                  // 数据个数
    ptQueCtrl->dwSize = dwSize  ;                  // 数据长度

    // 队列控制             
    ptQueCtrl->dwWr   = 0       ;                  // 数据写入
    ptQueCtrl->dwRd   = 0       ;                  // 数据读出

    // 队列信息
    ptQueCtrl->dwEmpty= dwNum   ;                  // 空闲数据个数
    ptQueCtrl->dwUsed = 0       ;                  // 当前写入个数
    ptQueCtrl->dwMax  = 0       ;                  // 最大写入个数  

    return 0;    
}

//===========================================================
// 函数功能: 数据队列读出
//===========================================================
UINT32 DataQueRead(tagQueCtrl *ptQueCtrl, void *pDst, UINT32 dwRdNum)
{
    UINT8           *pbyQue, *pbyDst, *pbySrc;
    UINT32          dwCnt1=0, dwCnt2=0;
    UINT32          dwRdCnt, dwRd;
    UINT32          dwNum, dwSize;
    //UINT32          dwEmpty;                // 空闲数据个数
    UINT32          dwUsed;                 // 当前写入个数


    // 指针初始化
    pbyQue = (UINT8 *)ptQueCtrl->pQue    ;
    pbyDst = (UINT8 *)pDst;

    // 获取队列结构信息  
    dwRd   = ptQueCtrl->dwRd    ;
    dwNum  = ptQueCtrl->dwNum   ;
    dwSize = ptQueCtrl->dwSize  ;
    
    //dwEmpty= ptQueCtrl->dwEmpty ;
    dwUsed = ptQueCtrl->dwUsed  ;

    // 已用空间是否满足
    dwRdCnt = (dwRdNum > dwUsed)? dwUsed : dwRdNum ;

    // 无数据更新
    if(!dwRdCnt)
    {
        return 0;
    }
    // 有数据更新
    if((dwRd + dwRdCnt) < dwNum)
    {
        dwCnt1 = dwRdCnt;
        pbySrc = &pbyQue[dwRd * dwSize];
        memcpy((void *)&pbyDst[0], (const void *)pbySrc, dwCnt1*dwSize);

    }
    else
    {
        dwCnt1 = dwNum - dwRd;
        pbySrc = &pbyQue[dwRd * dwSize];
        memcpy((void *)&pbyDst[0], (const void *)pbySrc, dwCnt1*dwSize);

        dwCnt2 = dwRdCnt - dwCnt1;
        pbySrc = &pbyQue[0];
        memcpy((void *)&pbyDst[dwCnt1*dwSize], (const void *)pbySrc, dwCnt2*dwSize);

    }
    
    // 计算数据读出位置
    dwRd   = (dwRd + dwRdCnt)% dwNum;
    // 计算已用空间个数
    dwUsed = dwUsed - dwRdCnt;

    // 队列结构信息更新
    ptQueCtrl->dwRd    = dwRd;       
    ptQueCtrl->dwEmpty = dwNum - dwUsed;
    ptQueCtrl->dwUsed  = dwUsed;


    return dwRdCnt;
}

//===========================================================
// 函数功能: 数据队列写入
//===========================================================
UINT32 DataQueWrite(tagQueCtrl *ptQueCtrl, void *pSrc, UINT32 dwWrNum)
{
    UINT8           *pbyQue, *pbyDst, *pbySrc;
    UINT32          dwCnt1=0, dwCnt2=0;
    UINT32          dwWrCnt, dwWr;
    UINT32          dwNum, dwSize;
    UINT32          dwEmpty;                // 空闲数据个数
    UINT32          dwUsed;                 // 当前写入个数
    UINT32          dwMax;                  // 最大写入个数

    // 指针初始化
    pbyQue = (UINT8 *)ptQueCtrl->pQue    ;
    pbySrc = (UINT8 *)pSrc;

    // 获取队列结构信息  
    dwWr   = ptQueCtrl->dwWr    ;
    dwNum  = ptQueCtrl->dwNum   ;
    dwSize = ptQueCtrl->dwSize  ;
    
    dwEmpty= ptQueCtrl->dwEmpty ;
    dwUsed = ptQueCtrl->dwUsed  ;
    dwMax  = ptQueCtrl->dwMax   ;
    
    // 剩余空间是否充足
    dwWrCnt = (dwWrNum > dwEmpty)? dwEmpty : dwWrNum ;
    
    // 写入数据
    if((dwWr + dwWrCnt) < dwNum )
    {
        dwCnt1 = dwWrCnt;
        pbyDst = &pbyQue[dwWr * dwSize];
        memcpy((UINT8 *)pbyDst, (UINT8 *)&pbySrc[0], dwCnt1*dwSize);
    }
    else
    {
        dwCnt1 = dwNum - dwWr;
        pbyDst = &pbyQue[dwWr * dwSize];
        memcpy((UINT8 *)pbyDst, (UINT8 *)&pbySrc[0], dwCnt1*dwSize);

        dwCnt2 = dwWrCnt - dwCnt1;
        pbyDst = &pbyQue[0];
        memcpy((UINT8 *)pbyDst, (UINT8 *)&pbySrc[dwCnt1*dwSize], dwCnt2*dwSize);
    }

    // 计算数据写入位置
    dwWr   = (dwWr + dwWrCnt)% dwNum;
    // 计算已用空间个数
    dwUsed = dwUsed + dwWrCnt;

    // 队列结构信息更新
    ptQueCtrl->dwWr    = dwWr;       
    ptQueCtrl->dwEmpty = dwNum - dwUsed;
    ptQueCtrl->dwUsed  = dwUsed;
    ptQueCtrl->dwMax   = (dwUsed > dwMax)? dwUsed: dwMax;


    return dwWrCnt;
}
