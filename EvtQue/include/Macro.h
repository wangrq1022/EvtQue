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


#ifndef _MACRO_H_
#define _MACRO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <setjmp.h>

#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>


#define CN_OS_TYPE              ( 1 )           // 0-无操作系统 1-Linux操作系统
#define CN_DATA_LOCATE_MODE     ( 1 )           // 0-动态分配模式 1-静态分配模式


typedef unsigned int            BOOL; 
typedef unsigned char           UINT8;
typedef unsigned int            UINT32;
typedef signed int              SINT32;
typedef float                   FLOAT32;
typedef unsigned long long      UINT64;
typedef signed   long long      SINT64;

typedef int                   (*FUNCPTR)();


#endif
