/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   : cc_ls_queue.c 
*
*  Description :  
*
*  Author      : Akshat K
***************************************************************************/



# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>

# include "cc_platform_abstraction.h"
# include "cc_data_types.h"
# include "xdebug_header.h"
# include "ext_mem.h"

static int non_case_strcmp(const void *str1, const void *str2)
{
    CHAR lc_word[2][MAX_FILE_PATH_SIZE],temp;
    INT32 upper_lower_diff,i,j;

    /**
     * First, make copies of the two input strings, except that in
     * the copies all upper-case letters have been changed to lower-
     * case 
     */
    strncpy(lc_word[0],(CHAR *)str1, MAX_FILE_PATH_SIZE);
    strncpy(lc_word[1],(CHAR *)str2, MAX_FILE_PATH_SIZE);
    upper_lower_diff = 'a' - 'A';
    for (i = 0; i < 2; i++)
    {
        for (j = 0; lc_word[i][j]!=0 ; j++)  
        {
            temp = lc_word[i][j];
            if (temp >= 'A' && temp <= 'Z')
            {
                lc_word[i][j] += upper_lower_diff;
            }
        }
    }

    debug(LOG_LEVEL,"STRSTR : COmparing %s and %s  ",lc_word[0],lc_word[1]);
    /** Now we can use the ordinary strcmp() function */
    return strcmp(lc_word[0],lc_word[1]);
}


/* Values for add_sorted_flag == 0 : Nothing, Non Zero: Sort,  */
void add_node_to_dir_list(DIR_NAME_LIST **ptr_to_first_node, UCHAR* dir_name, 
        UCHAR* path, UCHAR add_sorted_flag)
{
    DIR_NAME_LIST *d_start, *temp_node;
    UCHAR full_path[MAX_FILE_PATH_SIZE] = "";

    debug(LOG_LEVEL,"Entered ADD_NDE_DIR :: ");

    /* Make full path including directory */
    if(path != NULL)
    {
        strncpy(full_path,path,MAX_FILE_PATH_SIZE);
        strncat(full_path,"/",MAX_FILE_PATH_SIZE - strlen(full_path));
    }    
    strncat(full_path,dir_name,MAX_FILE_PATH_SIZE - strlen(full_path));

    /* Boundary case - empty list - This right now is not included in sorting.*/
    if(*ptr_to_first_node == NULL)
    {
        *ptr_to_first_node =  malloc(sizeof(FILE_NAME_LIST));
        strncpy((*ptr_to_first_node)->dir_name,full_path,MAX_FILE_PATH_SIZE);
        (*ptr_to_first_node)->dir_name_list = NULL;
        return;
    }

    d_start = *ptr_to_first_node;
    while(d_start->dir_name_list != NULL 
            && (add_sorted_flag && (non_case_strcmp(full_path,
            (d_start->dir_name_list)->dir_name) > 0)) )
    {
        d_start = d_start->dir_name_list;
    }

    temp_node = malloc(sizeof(DIR_NAME_LIST));
    if(temp_node == NULL)
    {
        debug(WARNING_LEVEL,"Could not allocate memory in add_node_to_dir");
        return;
    }
    temp_node->dir_name_list = d_start->dir_name_list;
    strncpy(temp_node->dir_name,full_path,MAX_FILE_PATH_SIZE);
    d_start->dir_name_list = temp_node;

    debug(LOG_LEVEL,"Exited ADD_NDE_DIR :: added dir %s ",temp_node->dir_name);
}


/* Values for add_sorted_flag == 0 : Nothing, 1: Sort, 2: Reverse sort */
void add_node_to_file_list(FILE_NAME_LIST **ptr_to_first_node, UCHAR* file_name,
        UCHAR* path, UCHAR add_sorted_flag)
{
    FILE_NAME_LIST  *temp_node, *f_start;
    UCHAR full_path[MAX_FILE_PATH_SIZE] = "";

    debug(LOG_LEVEL,"ADD_NDE_FILE :: ");

    /* Make full path including directory */
    if(path != NULL)
    {
        strncpy(full_path,path,MAX_FILE_PATH_SIZE);
        strncat(full_path,"/",MAX_FILE_PATH_SIZE - strlen(full_path));
    }    
    strncat(full_path,file_name,MAX_FILE_PATH_SIZE - strlen(full_path)); 

    /* Boundary case - empty list */
    if(*ptr_to_first_node == NULL
            ||  ((add_sorted_flag==1) && 
            (non_case_strcmp(full_path,(*ptr_to_first_node)->file_name) < 0))
            ||  ((add_sorted_flag==2) && 
            (non_case_strcmp(full_path,(*ptr_to_first_node)->file_name) > 0)) ) 
    {
        debug(LOG_LEVEL,"ADD_NDE_FILE 22AA  :: ");
        temp_node = malloc(sizeof(FILE_NAME_LIST));
        temp_node->file_name_list = *ptr_to_first_node;
        if(temp_node == NULL)
        {
            debug(WARNING_LEVEL,"Could'nt allocate memory in add_node_to_file");
            return;
        }
        strncpy(temp_node->file_name,full_path,MAX_FILE_PATH_SIZE);
        *ptr_to_first_node = temp_node;
        return;
    }


    debug(LOG_LEVEL,"ADD_NDE_FILE 22 :: ");

    f_start = *ptr_to_first_node;
    while( f_start->file_name_list!= NULL  && 
        (((add_sorted_flag==1) &&
        (non_case_strcmp(full_path,(f_start->file_name_list)->file_name) > 0))
        || 
        ((add_sorted_flag==2) && 
        (non_case_strcmp(full_path,(f_start->file_name_list)->file_name) < 0)) 
        )) 
    {
        f_start = f_start->file_name_list;
    }
    debug(LOG_LEVEL,"ADD_NDE_FILE 33 :: ");


    temp_node = malloc(sizeof(FILE_NAME_LIST));
    if(temp_node == NULL)
    {
        debug(WARNING_LEVEL,"Could'nt allocate memory in add_node_to_file ");
        return;
    }
    temp_node->file_name_list = f_start->file_name_list;
    strncpy(temp_node->file_name,full_path,MAX_FILE_PATH_SIZE);
    f_start->file_name_list = temp_node;

    debug(LOG_LEVEL,"Exit ADD_NDE_FILE  ");
}




void flush_file_queue(FILE_NAME_LIST **ptr_to_first_node, 
        OPTION_FLAGS options_flags)
{
    FILE_NAME_LIST *f_start, *temp_node;
    f_start = *ptr_to_first_node;

    debug(LOG_LEVEL,"FLSH_FILE entered ");
    debug(LOG_LEVEL," Called with %s",f_start);

    /* Display file details */
    while(f_start!=NULL)
    {
        debug(LOG_LEVEL,"FLSH_FILE :: calling file name display for %s ",
                f_start->file_name);
        LS_FILE_DISPLAY(f_start->file_name,options_flags);
        temp_node = f_start;
        f_start = f_start->file_name_list;
        /**  
         * Destroy read file ll .
         */
        free(temp_node);
    }
}



void flush_dir_queue(DIR_NAME_LIST **ptr_to_first_node, 
        OPTION_FLAGS options_flags)
{
    DIR_NAME_LIST *d_start, *temp_node;
    d_start = *ptr_to_first_node;

    /*Display directory details*/
    while(d_start!=NULL)
    {
        debug(LOG_LEVEL,"Main ;; dir loop ;; %s",d_start->dir_name);
        LS_DIR_DISPLAY(d_start,options_flags);
        temp_node = d_start;
        d_start = d_start->dir_name_list;
        free(temp_node);
    }
}
