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
#include "DataList.h"


#define CN_DATA_LIST_NUM            ( 4 )    // 静态分配模式支持节点数量

static tagListNode g_tRam[CN_DATA_LIST_NUM];

static UINT32      g_dwData[]={0,1,2,3,4,5,6,7,8,9,10};

void DataListShow(tagListCtrl *ptListCtrl)
{
    tagListNode*  pNode;
 
    printf("DataList: Addr=%p,Num=%d\n",ptListCtrl->pHead,ptListCtrl->dwNum);
    
    pNode = ptListCtrl->pHead;
    
    while(pNode)
    {
        printf("DataList: Addr=%p,Next=%p,Data=%d\n",pNode,         \
                                                     pNode->pNext,  \
                                                     *((UINT32*)pNode->pData));
    
        pNode = pNode->pNext;   
    }
#if(CN_DATA_LIST_MODE!=0)
    printf("/*****DataPoolShow*****/\n");
    DataPoolInfo(&ptListCtrl->tPoolCtrl);
    DataPoolShow(&ptListCtrl->tPoolCtrl);   
#endif
    return;   
}
void DataListShowNode(tagListNode*  pNode)
{ 
    printf("DataList: DataListShowNode Addr=%p\n",pNode);
       
    while(pNode)
    {
        printf("DataList: Addr=%p,Next=%p,Data=%d\n",pNode,         \
                                                     pNode->pNext,  \
                                                     *((UINT32*)pNode->pData));
    
        pNode = pNode->pNext;   
    }


    return;   
}


int DataListDemo(void)
{
    tagListCtrl     g_tListCtrl; 
    
    // Initial 
    DataListBuild(&g_tListCtrl, &g_tRam[0], CN_DATA_LIST_NUM);
    
    // main 
    DataListAdd(&g_tListCtrl, &g_dwData[1]);
    DataListAdd(&g_tListCtrl, &g_dwData[2]);
    DataListAdd(&g_tListCtrl, &g_dwData[3]);
    DataListAdd(&g_tListCtrl, &g_dwData[4]);
    DataListAdd(&g_tListCtrl, &g_dwData[5]);
    DataListAdd(&g_tListCtrl, &g_dwData[6]);

    DataListAdd(&g_tListCtrl, &g_dwData[0]);
    DataListShow(&g_tListCtrl);


    DataListDel(&g_tListCtrl, &g_dwData[1]);    
    DataListShow(&g_tListCtrl);
    
    DataListAdd(&g_tListCtrl, &g_dwData[1]);    
    DataListShow(&g_tListCtrl);


    DataListCut(&g_tListCtrl, &g_dwData[4]);    
    DataListShow(&g_tListCtrl);

    
    DataListDestory(&g_tListCtrl);
    DataListShow(&g_tListCtrl);

    DataListAdd(&g_tListCtrl, &g_dwData[1]);    
    DataListShow(&g_tListCtrl);
    DataListAdd(&g_tListCtrl, &g_dwData[2]);    
    DataListShow(&g_tListCtrl);
    
    return 0;
}
