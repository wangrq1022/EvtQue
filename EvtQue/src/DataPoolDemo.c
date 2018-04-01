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


#include "DataPool.h"
#include "Random.h" 

#define CN_POOL_BLK_NUM     ( 10 )
#define CN_POOL_BLK_SIZE    ( 16 )


static UINT32   g_Pool[CN_POOL_BLK_NUM * CN_POOL_BLK_SIZE];


UINT32 DataPoolGetRand(void)
{
    static  UINT32  dwSetSeed, dwCnt; 
    static  UINT32  dwSetFlag[CN_POOL_BLK_NUM];
    UINT32  dwRandom;
    
    if(!dwSetSeed)
    {
        dwSetSeed = 1;
        M_SetRandomSeed();      
    }
    
    while(dwCnt<CN_POOL_BLK_NUM)
    {
        dwRandom = M_GetRandom(CN_POOL_BLK_NUM);
        if(!dwSetFlag[dwRandom])
        {
            dwSetFlag[dwRandom] = 1;
            dwCnt++;
            break;
        }
    }

    return dwRandom;
}


int DataPoolDemo(void)
{
    tagPoolCtrl     tPoolCtrl;
    UINT32          dwErrInfo=0, **ppdwData, *pdw[CN_POOL_BLK_NUM];
    UINT32          dwLoop;    
    
    //UINT32            *pdwDbg;
    
    dwErrInfo = DataPoolCreat(&tPoolCtrl, g_Pool, CN_POOL_BLK_NUM, CN_POOL_BLK_SIZE);
    
    if(dwErrInfo)
    {
        printf("DataPoolCreat: ErrInfo=%d\n",dwErrInfo);
        
        return 0;
    }


    DataPoolInfo(&tPoolCtrl);
    DataPoolShow(&tPoolCtrl);

    for(dwLoop=0;dwLoop<CN_POOL_BLK_NUM;dwLoop++)
    {
        ppdwData = &pdw[dwLoop];
        *ppdwData = (UINT32 * )DataPoolGet(&tPoolCtrl, &dwErrInfo);
        if(!*ppdwData||dwErrInfo)
        {
            printf("DataPoolGet: pData=%p,ErrInfo=%d\n",*ppdwData,dwErrInfo);
        }
        **ppdwData = dwLoop + 1;        
 
        DataPoolInfo(&tPoolCtrl);    
        DataPoolShow(&tPoolCtrl);
    }

//--test for condition
//      pdwDbg = (UINT32 * )DataPoolGet(&tPoolCtrl, &dwErrInfo);
//      if(!pdwDbg||dwErrInfo)
//      {
//          printf("DataPoolGet: pData=%p,ErrInfo=%d\n",pdwDbg,dwErrInfo);
//      }


    for(dwLoop=0;dwLoop<CN_POOL_BLK_NUM;dwLoop++)
    {
        ppdwData = &pdw[DataPoolGetRand()];
        
        dwErrInfo = DataPoolPut(&tPoolCtrl, *ppdwData);
        
        if(dwErrInfo)
        {
            printf("DataPoolPut: pData=%p,ErrInfo=%d\n",*ppdwData,dwErrInfo);
        }
        DataPoolInfo(&tPoolCtrl);
        DataPoolShow(&tPoolCtrl);
    }
    
//--test for condition
//      dwErrInfo = DataPoolPut(&tPoolCtrl, *ppdwData);
//      
//      if(dwErrInfo)
//      {
//          printf("DataPoolPut: pData=%p,ErrInfo=%d\n",*ppdwData,dwErrInfo);
//      }



    for(dwLoop=0;dwLoop<CN_POOL_BLK_NUM;dwLoop++)
    {
        ppdwData = &pdw[dwLoop];
        *ppdwData = (UINT32 * )DataPoolGet(&tPoolCtrl, &dwErrInfo);
        if(!*ppdwData||dwErrInfo)
        {
            printf("DataPoolGet: pData=%p,ErrInfo=%d\n",*ppdwData,dwErrInfo);
        }
        **ppdwData = dwLoop + 1;        
 
        DataPoolInfo(&tPoolCtrl);    
        DataPoolShow(&tPoolCtrl);
    }

    
    return 0;
}
