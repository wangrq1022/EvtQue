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


#include "Demo.h"


int main(int argc, char *argv[])
{       
    UINT32          i;
    tagEvtThread   tPara;

    // translate shell command into thread parameter
    memset( &tPara, 0, sizeof(tagEvtThread));
    for(i=0;i<argc;i++)
    {
        
        printf("argv(%d):%s\n",i,argv[i]);
        if(i==1)
        {
            tPara.dwDlt = atoi(argv[i]);
        }
        if(i==2)
        {
            tPara.dwTimer = atoi(argv[i]);
        }
        if(i==3)
        {
            tPara.dwThread = atoi(argv[i]);
        }
    }


    switch(setjmp(g_ErrBuf)) 
    {
        case 0:
            // SaveThreadPara
            EvtThreadParaSet(&tPara);

            // EvtQueKit
            EvtGenerator();
            EvtRegister();

            // FsmObj & EvtTimer Init
            FsmObjInitAll();
            EvtTimerInitAll();
           
            // FsmBuild
            FsmObjBuildAll();

            // FsmPrivt
            FsmPrivtInitAll();

            // Creat Threads
            if(!tPara.dwThread)
            {
                CreateMultiThread(&tPara);
            }
            else
            {
                CreateSingleThread(&tPara);
            }

            // ShowGenInfo
            M_EvtGenInfo();
            
            break;
        
        case 1:
            printf("Detected an Err1 condition\n");
            break;

        case 2:
            printf("Detected an Err2 condition\n");
            break;

        case 3:
            printf("Detected an Err3 condition\n");
            break;

        default:
            printf("Unknown error condition\n");

    }

    return 0;
}
