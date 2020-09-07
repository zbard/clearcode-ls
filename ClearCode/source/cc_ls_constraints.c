/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   :cc_ls_constraints.c 

*  Description :Contains the parser module, the expand_file_dir_list, and
*               free_file_dir_list
*
*  Author      : Akshat K
***************************************************************************/

# include "xdebug_header.h"
# include "cc_data_types.h"


/*  Parser module : Returns 0 on no errors*/    
UCHAR cc_parser_getflags(INT32 argc, CHAR **argv,OPTION_FLAGS *options_flags) 
{
    UINT16 i=0,j=0;
    UCHAR error=0;

    for(i = 1;i<argc;i++)
    {
        switch(argv[i][0])
        {
            case '-':
                {
                    debug(LOG_LEVEL,"Found some a - , string %s",argv[i]);
                    j = 1;
                    while(argv[i][j]!=0)
                    {
                        switch(argv[i][j])
                        {
                            case 'l':
                                options_flags->l_flag = 1;
                                break;
                            case 'a':
                                options_flags->a_flag = 1;
                                break;
                            case 's':
                                options_flags->s_flag = 1;
                                break;
                            case 'i':
                                options_flags->i_flag = 1;
                                break;
                            case 'h':
                                options_flags->h_flag = 1;
                                break;
                            case 'd':
                                options_flags->d_flag = 1;
                                break;
                            case 'c':
                                options_flags->c_flag = 1;
                                break;
                            case 'r':
                                options_flags->r_flag = 1;
                                break;
                            case 'S':
                                options_flags->S_flag = 1;
                                break;
                            case 'R':
                                options_flags->R_flag = 1;
                                break;
                            default :
                                error = 1;
                        }
                        j++;
                    }
                }
                break;

            default:
                break;
        } 
    }

    return error;
    /* End parser */
}





