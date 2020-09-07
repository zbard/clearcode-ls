/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   : 
*
*  Description :  
*
*  Author      : Akshat K
***************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


#include "cc_data_types.h"
#include "cc_platform_abstraction.h"
#include "cc_common.h"
#include "xdebug_header.h"
#include "ext_mem.h"


static UCHAR is_expression(CHAR *name)
{
    UCHAR is_exp = 0;

    while(*name && !is_exp)
    {
        switch(*name)
        {
            case '*':
            case '?':
            case '[':
            case ']':
                is_exp = 1;
                break;
            default:
                break;
        }
        name++;
    }

    return is_exp;
}


/* Routine for expanding and validating expressions -
   and filling them in the file and dir link list */
void linux_expand_expressions(INT32 argc, CHAR **argv, 
        FILE_NAME_LIST **file_name_list_start, 
        DIR_NAME_LIST **dir_name_list_start)
{
    /* Currently only considering current path */    
    struct dirent *dp;
    struct stat st;
    UINT32 i=0;
    UINT32 valid_match=0;
    UINT32 entries=0;
    UINT32 ptr_filename=0;
    UCHAR *file_name;
    UCHAR path[MAX_FILE_PATH_SIZE];
    UCHAR temp_path[MAX_FILE_PATH_SIZE];
    DIR *dfd ;


    for(i=1;i<argc;i++)
    {
        if(argv[i][0] != '-')
        {  
            entries++;
            valid_match=0;
            if(!is_expression(argv[i]))
            {
                if(stat(argv[i],&st))
                {
                    printf("File name does not exist : %s\n",argv[i]);
                }
                else
                {
                    if(S_ISREG(st.st_mode))
                    {
                        add_node_to_file_list(file_name_list_start,argv[i],NULL,
                                FALSE); 
                    }
                    else if(S_ISDIR(st.st_mode))
                    {
                        add_node_to_dir_list(dir_name_list_start,argv[i],NULL,
                                FALSE); 
                    }    
                }     
                continue;
            }

            /* For every expression which is not a flag browse  current dir*/
            STRIP_PATH(&file_name,argv[i]);
            strncpy(path,argv[i],MAX_FILE_PATH_SIZE);

            while((CHAR *)file_name != &argv[i][ptr_filename])
                ptr_filename++;

            *(path + ptr_filename) = '\0';

            debug(LOG_LEVEL,"WALKTHROUGH :: path %s, filename %s, original %s",
                    path, file_name,argv[i]);
            if(path[0] == 0)
            {
                dfd = opendir(".");
            }
            else
            {
                dfd = opendir(path);
            }

            if(dfd != NULL) 
            {
                while((dp = readdir(dfd)) != NULL)
                {
                    if(!FNMATCH(file_name,dp->d_name, 0))
                    {
                        debug(LOG_LEVEL,"Success in comparing %s(Given) and %s",
                                argv[i], dp->d_name); 
                        valid_match++;
                        strncpy(temp_path, path, 
                                MAX_FILE_PATH_SIZE);
                        strncat(temp_path, dp->d_name, 
                                MAX_FILE_PATH_SIZE-strlen(path));

                        if(!stat(temp_path,&st))
                        {
                            if(S_ISREG(st.st_mode))
                            {
                                add_node_to_file_list(file_name_list_start,
                                        dp->d_name, path, FALSE); 
                            }
                            else if(S_ISDIR(st.st_mode))
                            {
                                add_node_to_dir_list(dir_name_list_start,
                                        dp->d_name, path, FALSE); 
                            }    
                        }
                        else
                        {
                            debug(WARNING_LEVEL,"Coul'nt get stat of file : %s",
                                    dp->d_name);
                        }
                    }
                }

                if(valid_match==0)
                {
                    printf("There are no matching entries for : %s\n",argv[i]);
                }
            }
            else
            {   
                printf(" Could not open directory %s .\n",path);
                debug(WARNING_LEVEL,"Could not open current directory");
            }

            closedir(dfd);
        } /*End if !'-'*/
    } /*End loop*/

    /*Default directory := current */
    if(entries==0)
    {
        add_node_to_dir_list(dir_name_list_start,".",NULL,FALSE);
    }

    /*End routine*/
}
