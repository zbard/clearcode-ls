/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   : cc_ls_main.c
*
*  Description : Main file for ls program.
*
*  Author      : Akshat K
***************************************************************************/


# include <stdio.h>

# include "cc_data_types.h"
# include "cc_platform_abstraction.h"
# include "cc_common.h"
# include "xdebug_header.h"
# include "ext_mem.h"

int main(int argc, char **argv )
{
    OPTION_FLAGS   options_flags={0};
    FILE_NAME_LIST *file_name_list_start = NULL;
    DIR_NAME_LIST *dir_name_list_start = NULL;

    MEM_START;
    /*Initialization of variables*/
    debug(LOG_LEVEL,"The program has entered the main loop");

    /*Call parser - pass arguments OPTION_FLAGS to it, and FILE_NAME_LIST 
      to it. It will set respective OPTION_FLAGS*/
    if(cc_parser_getflags(argc, argv, &options_flags))
    {
        debug(ERROR_LEVEL,"Parser returned error ,exiting ..");
        printf("Invalid command line option. \n");
        return 1;
    }

    debug(LOG_LEVEL,"Parser was called .");
    debug(LOG_LEVEL,"Returned -l flag = %d, and -a flag = %d .",
            options_flags.l_flag, options_flags.a_flag);

    /* Change file list and dir list to be populated over here */
    EXPAND_EXPRESSIONS(argc, argv, &file_name_list_start, &dir_name_list_start);

    /**
     * Call walkthrough routine.(pass file_list, and options*)
     * Also calls display(takes file name and options structure - any extra
     * output has to be specified extraneously 
     */

    flush_file_queue(&file_name_list_start,options_flags);
    flush_dir_queue(&dir_name_list_start,options_flags);


    /*Flush output*/
    printf("\n");

    MEM_SHUT;
    return 0;
}
