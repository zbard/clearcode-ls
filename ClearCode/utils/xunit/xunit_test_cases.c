/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   : xunit_test_cases.c 
*
*  Description :  
*
*  Author      : Akshat K
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cc_common.h"
#include "xunit_header.h"


static char* test_parser_1(void)
{
    char **argv;
    OPTION_FLAGS options_flag;


    /*Create ragged array*/
    argv = malloc(sizeof(char *)* 5);
    argv[0] = malloc(sizeof(char)*20);
    argv[1] = malloc(sizeof(char)*20);
    argv[2] = malloc(sizeof(char)*20);

    strcpy(argv[0],"./run"); 
    strcpy(argv[1],"-l"); 
    strcpy(argv[2],"-a");


    xu_assert("Parser returned error!", 
            !cc_parser_getflags(3, argv, &options_flag));
    xu_assert("-l flag not set to 1",(options_flag.l_flag == 1));
    xu_assert("-a flag not set to 1",(options_flag.a_flag == 1));

    return 0;
}

static char * all_tests(void) 
{
    xu_run_test(test_parser_1);
    return 0;
}

int main(int argc, char **argv) 
{
    xunit_display_init();
    xunit_display_result("Parser Module First test",test_parser_1());
    xunit_display_end();

    return  0;
}
