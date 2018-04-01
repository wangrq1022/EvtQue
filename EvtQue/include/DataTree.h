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

#ifndef _DATA_TREE_H_
#define _DATA_TREE_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"
#include "DataPool.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

#define CN_DATA_TREE_MODE   ( CN_DATA_LOCATE_MODE )    // 0-动态分配模式 1-静态分配模式

// 定义数据二叉树节点
typedef struct TreeNode
{
    struct TreeNode* pRight;        // 右侧节点指针 
    struct TreeNode* pLeft ;        // 左侧节点指针 

    void             *pData;        // 节点数据指针

}tagTreeNode;

// 数据二叉树控制结构体
typedef struct
{
    tagTreeNode     *pRoot;         // 二叉树根节点指针
    UINT32          dwNum;          // 节点个数
#if(CN_DATA_TREE_MODE!=0)
    UINT32          dwBlk;          // 静态分配内存块个数 
    tagPoolCtrl     tPoolCtrl;      // 静态分配内存池 
#endif

}tagTreeCtrl; 

/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern UINT32 DataTreeBuild(tagTreeCtrl *ptTreeCtrl, tagTreeNode *pRam, UINT32 dwBlk);
extern UINT32 DataTreeDestory(tagTreeCtrl *ptTreeCtrl);

extern UINT32 DataTreeAddRoot(tagTreeCtrl *ptTreeCtrl, void *pData);
extern UINT32 DataTreeAddLeft(tagTreeCtrl *ptTreeCtrl, void *pData);
extern UINT32 DataTreeAddRight(tagTreeCtrl *ptTreeCtrl, void *pData);

extern UINT32 DataTreeCutLeft(tagTreeCtrl *ptTreeCtrl, void *pData); 
extern UINT32 DataTreeCutRight(tagTreeCtrl *ptTreeCtrl, void *pData);

extern tagTreeNode* DataTreeSrch(tagTreeCtrl *ptTreeCtrl, void *pData);
extern tagTreeNode* DataTreeSrchLeft(tagTreeCtrl *ptTreeCtrl, void *pData);
extern tagTreeNode* DataTreeSrchRight(tagTreeCtrl *ptTreeCtrl, void *pData);

extern tagTreeNode* DataTreeLeftLeaf(tagTreeCtrl *ptTreeCtrl);
extern tagTreeNode* DataTreeRightLeaf(tagTreeCtrl *ptTreeCtrl);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
