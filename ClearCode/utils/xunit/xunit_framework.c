/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   :xunit_framework.c 
*
*  Description :Contains the various functions for adding test suites
*  and case, running them - and displaying output.
*
*  Author      : Akshat K
***************************************************************************/

#include <stdio.h>
#include "xunit_header.h"

int tests_run = 0;           
static FILE* fp;


void xunit_display_init(void)
{
    fp = fopen("TestResults.html","w");

    fprintf(fp,"\n\n <TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2 WIDTH=\"80%%\" >\n");
    fprintf(fp,"<CAPTION> ... Test Case Results ... <CAPTION>\n");

}

void xunit_display_result(char *descr, char * str)
{
    fprintf(fp,"<TR><TD>Test Case Num : %d <TD> Description : %s <TD> \
            Result : %s <TD> Message : %s\n", 
            tests_run, (!descr)?"None provided":descr, (!str)?"Pass":"Fail",
            (!str)?"None":str);
}


void xunit_display_end(void)
{
    fprintf(fp,"</TABLE>\n");
    fclose(fp);
}


