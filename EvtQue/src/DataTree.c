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
#include "DataTree.h"

//===========================================================
// 函数功能: 释放二叉树节点
//===========================================================
static void DataTreeFreeNode(tagTreeCtrl *ptTreeCtrl, tagTreeNode* pNode)
{
    UINT32 dwErrInfo = 0;
    
#if(CN_DATA_TREE_MODE==0)
    free(pNode);
#else       
    dwErrInfo = DataPoolPut(&ptTreeCtrl->tPoolCtrl, (void *)pNode);     
#endif
    if(dwErrInfo)
    {
        printf("DataTreeFreeNode Err: pNode=%p,ErrInfo=%d\n",pNode,dwErrInfo);
    }


    return;
}

//===========================================================
// 函数功能: 申请二叉树节点
//===========================================================
static tagTreeNode* DataTreeCreatNode(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pNode;
    UINT32        dwErrInfo = 0;
     
#if(CN_DATA_TREE_MODE==0)  
    pNode = (tagTreeNode *)malloc(sizeof(tagTreeNode));
#else
    pNode = (tagTreeNode *)DataPoolGet(&ptTreeCtrl->tPoolCtrl, &dwErrInfo);
#endif
    if(!pNode||dwErrInfo)
    {
        printf("DataTreeCreatNode Err: pNode=%p,ErrInfo=%d\n",pNode,dwErrInfo);
        return NULL;
    }


    if(pNode)
    {
        pNode->pRight = NULL;
        pNode->pLeft  = NULL;
        pNode->pData  = pData;
    }
    else
    {
        printf("DataTreeCreatNode Err!\n");
    }
   
    return pNode;
}


//===========================================================
// 函数功能: 查找二叉树节点
//===========================================================
static tagTreeNode* DataTreeSrchNode(tagTreeNode *pTree, void *pData)
{
    tagTreeNode*  pWalk;
    tagTreeNode*  pNode;
    
    pWalk = pTree;
    if(!pWalk)
    {
        return NULL;
    }
    if(pWalk->pData==pData)
    {
        return pWalk;       
    }
    
    pNode = DataTreeSrchNode(pWalk->pRight, pData);
    if(pNode)
    {
        return pNode;       
    }   
    
    pNode = DataTreeSrchNode(pWalk->pLeft, pData);
    if(pNode)
    {
        return pNode;       
    }
        
    return pNode;
}

//===========================================================
// 函数功能: 删除二叉树节点
//===========================================================
static void DataTreeRmvTree(tagTreeCtrl *ptTreeCtrl, tagTreeNode *pTree)
{
    tagTreeNode*  pWalk;
    
    pWalk = pTree;
    if(!pWalk)
    {
        return;
    }
    
    DataTreeRmvTree(ptTreeCtrl, pWalk->pRight);

    DataTreeRmvTree(ptTreeCtrl, pWalk->pLeft);

    DataTreeFreeNode(ptTreeCtrl, pWalk);
    
    ptTreeCtrl->dwNum--;
        
    return ;
}

//===========================================================
// 函数功能: 创建二叉树根节点
//===========================================================
UINT32 DataTreeBuild(tagTreeCtrl *ptTreeCtrl, tagTreeNode *pRam, UINT32 dwBlk)
{
    UINT32  dwErrInfo = 0;
        
    ptTreeCtrl->pRoot  = NULL; 
    //ptTreeCtrl->pfnCmp = pfnCmp;
    
    ptTreeCtrl->dwNum  = 0;
#if(CN_DATA_TREE_MODE!=0)
    //ptTreeCtrl->pRam  = pRam;           // 静态分配内存区指针 
    ptTreeCtrl->dwBlk = dwBlk;          // 静态分配内存块个数 
    
    dwErrInfo = DataPoolCreat(&ptTreeCtrl->tPoolCtrl, (void *)pRam, dwBlk, sizeof(tagTreeNode));
#endif
    if(dwErrInfo)
    {
        printf("DataTreeBuild: ErrInfo=%d\n",dwErrInfo);        
        return dwErrInfo;
    }


    return 0; 
}

//===========================================================
// 函数功能: 添加二叉树根节点
//===========================================================
UINT32 DataTreeAddRoot(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pNode;
    
    pNode = DataTreeCreatNode(ptTreeCtrl, pData);
    if(!pNode)
    {
        return 1;
    }
         
    ptTreeCtrl->pRoot = pNode;

    ptTreeCtrl->dwNum++;
    
    return 0;
}

//===========================================================
// 函数功能: 添加二叉树叶子节点
//===========================================================
UINT32 DataTreeAddRight(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pNode;
    tagTreeNode*  pWalk;    
     
    pNode = DataTreeCreatNode(ptTreeCtrl, pData);
    if(!pNode)
    {
        return 1;
    }
         
    pWalk = ptTreeCtrl->pRoot;
    if(!pWalk)
    {
        return 2;
    }
    
    while(pWalk->pRight)
    {
        pWalk = pWalk->pRight;             
    }
    pWalk->pRight = pNode;
    
    ptTreeCtrl->dwNum++;
    
    return 0;
}


//===========================================================
// 函数功能: 添加二叉树叶子节点
//===========================================================
UINT32 DataTreeAddLeft(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pNode;
    tagTreeNode*  pWalk;    
     
    pNode = DataTreeCreatNode(ptTreeCtrl, pData);
    if(!pNode)
    {
        return 1;
    }
         
    pWalk = ptTreeCtrl->pRoot;
    if(!pWalk)
    {
        return 2;
    }
    
    while(pWalk->pLeft)
    {
        pWalk = pWalk->pLeft;             
    }
    pWalk->pLeft = pNode;
    
    ptTreeCtrl->dwNum++;
    
    return 0;
}


//===========================================================
// 函数功能: 截断二叉树节点
//===========================================================
UINT32 DataTreePruning(tagTreeCtrl *ptTreeCtrl, void *pData)
{   
    tagTreeNode*  pFree;
    tagTreeNode*  pRoot;

                
    pRoot = ptTreeCtrl->pRoot;
    if(!pRoot)
    {
        return 1;
    }
    
    pFree = DataTreeSrchNode(pRoot, pData);
    if(!pFree)
    {
        return 2;
    }
    
    printf("DataTreeTrunc:%d\n",*((UINT32*)pFree->pData));
    
    DataTreeRmvTree(ptTreeCtrl, pFree->pLeft);
    DataTreeRmvTree(ptTreeCtrl, pFree->pRight);

    pFree->pLeft  = NULL;
    pFree->pRight = NULL;
    
    return 0;
}

//===========================================================
// 函数功能: 删除二叉树
//===========================================================
UINT32 DataTreeDestory(tagTreeCtrl *ptTreeCtrl)
{
    tagTreeNode*  pRoot;    
             
    pRoot = ptTreeCtrl->pRoot;
    if(!pRoot)
    {
        return 1;
    }
      
    DataTreeRmvTree(ptTreeCtrl, pRoot);
    
    ptTreeCtrl->pRoot = NULL ;
    
    return 0;

}

//===========================================================
// 函数功能: 删除二叉树叶子节点
//===========================================================
UINT32 DataTreeCutLeft(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pFree;
    tagTreeNode*  pRoot;
    tagTreeNode*  pNode;
    tagTreeNode** ppIndex; 

      
    pRoot = ptTreeCtrl->pRoot;
    if(!pRoot)
    {
        return 1;
    }
    
    pNode = DataTreeSrchNode(pRoot->pLeft, pData);
    if(!pNode)
    {
        return 2;
    }
    
    ppIndex = &ptTreeCtrl->pRoot->pLeft;
    
    while((*ppIndex)!=pNode)
    {
        ppIndex = &(*ppIndex)->pLeft;
    }
    
    *ppIndex = NULL;
    
    while(pNode)
    {
        pFree = pNode;        
        pNode = pNode->pLeft;

        DataTreeFreeNode(ptTreeCtrl, pFree);

        ptTreeCtrl->dwNum--;

    }    
       
    return 0;
}

//===========================================================
// 函数功能: 删除二叉树叶子节点
//===========================================================
UINT32 DataTreeCutRight(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pFree;
    tagTreeNode*  pRoot;
    tagTreeNode*  pNode;
    tagTreeNode** ppIndex; 

      
    pRoot = ptTreeCtrl->pRoot;
    if(!pRoot)
    {
        return 1;
    }
    
    pNode = DataTreeSrchNode(pRoot->pRight, pData);
    if(!pNode)
    {
        return 2;
    }
    
    ppIndex = &ptTreeCtrl->pRoot->pRight;
    
    while((*ppIndex)!=pNode)
    {
        ppIndex = &(*ppIndex)->pRight;
    }
    
    *ppIndex = NULL;
    
    while(pNode)
    {
        pFree = pNode;        
        pNode = pNode->pRight;

        DataTreeFreeNode(ptTreeCtrl, pFree);

        ptTreeCtrl->dwNum--;

    }    
     
    return 0;
}
//===========================================================
// 函数功能: 查找二叉树节点
//===========================================================
tagTreeNode* DataTreeSrch(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    return DataTreeSrchNode(ptTreeCtrl->pRoot, pData);
}
//===========================================================
// 函数功能: 查找二叉树节点
//===========================================================
tagTreeNode* DataTreeSrchLeft(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    if(!ptTreeCtrl->pRoot)
    {
        return NULL;
    }
    
    return DataTreeSrchNode(ptTreeCtrl->pRoot->pLeft, pData);
}
//===========================================================
// 函数功能: 查找二叉树节点
//===========================================================
tagTreeNode* DataTreeSrchRight(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    if(!ptTreeCtrl->pRoot)
    {
        return NULL;
    }

    return DataTreeSrchNode(ptTreeCtrl->pRoot->pRight, pData);
}
//===========================================================
// 函数功能: 查找二叉树叶子节点 
//===========================================================
tagTreeNode* DataTreeLeftLeaf(tagTreeCtrl *ptTreeCtrl)
{
    tagTreeNode** ppIndex; 
    
    if(!ptTreeCtrl->pRoot)
    {
        return NULL;
    }
    
    ppIndex = &ptTreeCtrl->pRoot;
    
    while((*ppIndex)->pLeft)
    {
        ppIndex = &(*ppIndex)->pLeft; 
    }
    
    return *ppIndex;
}
//===========================================================
// 函数功能: 查找二叉树叶子节点 
//===========================================================
tagTreeNode* DataTreeRightLeaf(tagTreeCtrl *ptTreeCtrl)
{
    tagTreeNode** ppIndex; 
    
    if(!ptTreeCtrl->pRoot)
    {
        return NULL;
    }
    
    ppIndex = &ptTreeCtrl->pRoot;
    
    while((*ppIndex)->pRight)
    {
        ppIndex = &(*ppIndex)->pRight; 
    }
    
    return *ppIndex;
}
