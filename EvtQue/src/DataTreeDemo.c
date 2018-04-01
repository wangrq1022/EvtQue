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

#define CN_DATA_TREE_NUM            ( 4 )    // 静态分配模式支持节点数量

static tagTreeNode g_tRam[CN_DATA_TREE_NUM];

static UINT32      g_dwData[]={0,1,2,3,4,5,6,7,8,9,10};
 
static void DataTreePostOrder(tagTreeNode *ptTree)
{
    tagTreeNode*  pWalk;
     
    pWalk = ptTree;
    if(!pWalk)
    {
        return;
    }    
    DataTreePostOrder(pWalk->pLeft);
    DataTreePostOrder(pWalk->pRight);
    printf("%d ",*((UINT32*)pWalk->pData));
    return;   
}

static void DataTreePreOrder(tagTreeNode *ptTree)
{
    tagTreeNode*  pWalk;
     
    pWalk = ptTree;
    if(!pWalk)
    {
        return;
    }    

    printf("%d ",*((UINT32*)pWalk->pData));
    DataTreePreOrder(pWalk->pLeft);
    DataTreePreOrder(pWalk->pRight);
    return;   
}

static void DataTreeInOrder(tagTreeNode *ptTree)
{
    tagTreeNode*  pWalk;
     
    pWalk = ptTree;
    if(!pWalk)
    {
        return;
    }    

    DataTreeInOrder(pWalk->pLeft);
    printf("%d ",*((UINT32*)pWalk->pData));
    DataTreeInOrder(pWalk->pRight);
    return;   
}

void DataTreeShow(tagTreeCtrl *ptTreeCtrl)
{
    tagTreeNode*  pRoot;
 
    printf("DataTree: Addr=%p,Num=%d\n",ptTreeCtrl->pRoot,ptTreeCtrl->dwNum);
    
    pRoot = ptTreeCtrl->pRoot;
      
    printf("DataTree: PreOrder \n");
    DataTreePreOrder(pRoot);
    printf("\n");

    printf("DataTree: InOrder \n");
    DataTreeInOrder(pRoot);
    printf("\n");
    
    printf("DataTree: PostOrder \n");
    DataTreePostOrder(pRoot);
    printf("\n");

    return;   
}

void DataTreeShowNode(tagTreeNode*  pRoot)
{
    printf("DataTree: DataTreeShowNode Addr=%p\n",pRoot);
    
    printf("DataTree: PreOrder \n");
    DataTreePreOrder(pRoot);
    printf("\n");

    printf("DataTree: InOrder \n");
    DataTreeInOrder(pRoot);
    printf("\n");
    
    printf("DataTree: PostOrder \n");
    DataTreePostOrder(pRoot);
    printf("\n");

    return;   
}


int DataTreeDemo(void)
{
    tagTreeCtrl     g_tCtrl; 
    
    // Initial 
    DataTreeBuild(&g_tCtrl, &g_tRam[0], CN_DATA_TREE_NUM);
    
    // main 
    DataTreeAddRoot(&g_tCtrl, &g_dwData[1]);
    
    DataTreeAddLeft(&g_tCtrl, &g_dwData[2]);
    DataTreeAddRight(&g_tCtrl, &g_dwData[3]);
    DataTreeAddRight(&g_tCtrl, &g_dwData[4]);
    
    DataTreeAddLeft(&g_tCtrl, &g_dwData[5]);
    DataTreeAddLeft(&g_tCtrl, &g_dwData[6]);
    DataTreeAddLeft(&g_tCtrl, &g_dwData[0]);
    DataTreeShow(&g_tCtrl);

    DataTreeCutLeft(&g_tCtrl, &g_dwData[2]);
    DataTreeShow(&g_tCtrl);



    DataTreeDestory(&g_tCtrl);
    DataTreeShow(&g_tCtrl);

    DataTreeAddRoot(&g_tCtrl, &g_dwData[1]);
    DataTreeAddLeft(&g_tCtrl, &g_dwData[0]);
    DataTreeShow(&g_tCtrl);

    DataTreeAddRight(&g_tCtrl, &g_dwData[2]);
    DataTreeShow(&g_tCtrl);

    
    return 0;
}
