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

//===========================================================
// 函数功能: 释放链表节点
//===========================================================
static void DataListFreeNode(tagListCtrl *ptListCtrl, tagListNode* pNode)
{
    UINT32 dwErrInfo = 0;
    
#if(CN_DATA_LIST_MODE==0)
    free(pNode);
#else       
    dwErrInfo = DataPoolPut(&ptListCtrl->tPoolCtrl, (void *)pNode); 
#endif

    if(dwErrInfo)
    {
        printf("DataListFreeNode Err: pNode=%p,ErrInfo=%d\n",pNode,dwErrInfo);
    }


    return;
}

//===========================================================
// 函数功能: 申请链表节点
//===========================================================
static tagListNode* DataListCreatNode(tagListCtrl *ptListCtrl, void *pData)
{
    tagListNode*  pNode;
    UINT32        dwErrInfo = 0;
     
#if(CN_DATA_LIST_MODE==0)  
    pNode = (tagListNode *)malloc(sizeof(tagListNode));
#else   
    pNode = (tagListNode *)DataPoolGet(&ptListCtrl->tPoolCtrl, &dwErrInfo);
#endif
    if(!pNode||dwErrInfo)
    {
        printf("DataListCreatNode Err: pNode=%p,ErrInfo=%d\n",pNode,dwErrInfo);
        return NULL;
    }


    if(pNode)
    {
        pNode->pNext = NULL;
        pNode->pData = pData;
    }
    else
    {
        printf("DataListCreatNode Err!\n");
    }
  
    return pNode;
}

//===========================================================
// 函数功能: 查找链表节点
//===========================================================
static tagListNode* DataListSrchNode(tagListNode *pList, void *pData)
{
    tagListNode*  pWalk;    
         
    pWalk = pList;
    
    while(pWalk)
    {
        if(pWalk->pData==pData)
        {
            break;        
        }
        
        pWalk = pWalk->pNext;             
    }

    return pWalk;
}

//===========================================================
// 函数功能: 创建链表根节点
//===========================================================
UINT32 DataListBuild(tagListCtrl *ptListCtrl, tagListNode *pRam, UINT32 dwBlk)
{    
    UINT32  dwErrInfo = 0;
    
    ptListCtrl->pHead  = NULL; 
    ptListCtrl->dwNum  = 0;
    
#if(CN_DATA_LIST_MODE!=0)
    //ptListCtrl->pRam  = pRam;           // 静态分配内存区指针 
    ptListCtrl->dwBlk = dwBlk;          // 静态分配内存块个数 
    
    dwErrInfo = DataPoolCreat(&ptListCtrl->tPoolCtrl, (void *)pRam, dwBlk, sizeof(tagListNode));
#endif
    if(dwErrInfo)
    {
        printf("DataPoolCreat: ErrInfo=%d\n",dwErrInfo);        
        return dwErrInfo;
    }   


    return 0; 
}

//===========================================================
// 函数功能: 注册节点数据比较函数 
//===========================================================
UINT32 DataListFnCmp(tagListCtrl *ptListCtrl, FUNCPTR pfnCmp)
{    
    //ptListCtrl->pfnCmp = pfnCmp;
    return 0; 
}

//===========================================================
// 函数功能: 注册节点数据显示函数 
//===========================================================
UINT32 DataListTraverse(tagListCtrl *ptListCtrl, UINT32 dwType)
{    
    tagListNode** ppIndex;  
    
    printf("List: Len=%d,Head->",ptListCtrl->dwNum);
        
    ppIndex = &ptListCtrl->pHead;
    while(*ppIndex)
    {       
        switch(dwType)
        {
            case 0:
                printf("%d->",(int)(*ppIndex)->pData);
            break;                  
            default:
                printf("%p->",(*ppIndex)->pData);           
            break;      
        }
        ppIndex = &(*ppIndex)->pNext;           
    }           
    printf("Null\n");

    return 0; 
}

//===========================================================
// 函数功能: 添加链表尾节点
//===========================================================
UINT32 DataListAdd(tagListCtrl *ptListCtrl, void *pData)
{
    tagListNode*  pNode;
    tagListNode** ppIndex;    
     
    pNode = DataListCreatNode(ptListCtrl, pData);
    if(!pNode)
    {
        return 1;
    }
      
    ppIndex = &ptListCtrl->pHead;
    while(*ppIndex)
    {
        ppIndex = &(*ppIndex)->pNext;             
    }
    *ppIndex = pNode;

    ptListCtrl->dwNum++;
    
    return 0;
}

//===========================================================
// 函数功能: 删除链表节点
//===========================================================
UINT32 DataListDel(tagListCtrl *ptListCtrl, void *pData)
{
    tagListNode*  pNode;
    tagListNode*  pHead;
    tagListNode** ppIndex; 
    
    pHead = ptListCtrl->pHead;
    if(!pHead)
    {
        return 1;
    }
    
    pNode = DataListSrchNode(pHead, pData);
    if(!pNode)
    {
        return 2;
    }

    ppIndex = &ptListCtrl->pHead;
    
    while((*ppIndex)!=pNode)
    {
        ppIndex = &(*ppIndex)->pNext;
    }
    
    *ppIndex = pNode->pNext;   
     
    DataListFreeNode(ptListCtrl, pNode); 
 
    ptListCtrl->dwNum--;
    
    return 0;
}

//===========================================================
// 函数功能: 截断链表节点-包含参数节点 
//===========================================================
UINT32 DataListCut(tagListCtrl *ptListCtrl, void *pData)
{   
    tagListNode*  pFree;
    tagListNode*  pHead;
    tagListNode*  pNode;
    tagListNode** ppIndex; 
                
    pHead = ptListCtrl->pHead;
    if(!pHead)
    {
        return 1;
    }
    
    pNode = DataListSrchNode(pHead, pData);
    if(!pNode)
    {
        return 2;
    }

    ppIndex = &ptListCtrl->pHead;
    
    while((*ppIndex)!=pNode)
    {
        ppIndex = &(*ppIndex)->pNext;
    }
    
    *ppIndex = NULL;
    
    while(pNode)
    {
        pFree = pNode;        
        pNode = pNode->pNext;

        DataListFreeNode(ptListCtrl, pFree);

        ptListCtrl->dwNum--;

    }
    
    return 0;
}

//===========================================================
// 函数功能: 删除链表
//===========================================================
UINT32 DataListDestory(tagListCtrl *ptListCtrl)
{
    tagListNode*  pHead;    
             
    pHead = ptListCtrl->pHead;
    if(!pHead)
    {
        return 1;
    }
    
    DataListCut(ptListCtrl, pHead->pData); 
    
    ptListCtrl->pHead = NULL;
    
    return 0;

}

//===========================================================
// 函数功能: 查找链表节点
//===========================================================
tagListNode* DataListSrch(tagListCtrl *ptListCtrl, void *pData)
{        
    return DataListSrchNode(ptListCtrl->pHead, pData);
}
