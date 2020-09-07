/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   : cc_ls_display.c 
*
*  Description :  
*
*  Author      : Akshat K
***************************************************************************/


# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <strings.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

# include "cc_common.h"
# include "cc_data_types.h"
# include "cc_platform_abstraction.h"
# include "cc_color.h"
# include "xdebug_header.h"





/* Routine to display as single file */
void ls_file_display(UCHAR *filename, OPTION_FLAGS options_flags)
{
    CHAR vals[3] = {'x','w','r'};
    CHAR date[20];
    CHAR *f_name;
    UCHAR file_name_color = 0;
    UINT32 mode ;
    INT32 i = 0;
    struct passwd *pwd;
    struct group *grp;
    struct stat statb;
    struct tm *tm;

    debug(LOG_LEVEL, "File path %s ", (CHAR*)filename);
    STRIP_PATH((UCHAR **)&f_name, filename);
    debug(LOG_LEVEL, "On stripping %s we got name %s",(CHAR*)filename,
            f_name);

    if(stat((CHAR *)filename,&statb)) 
    {
        printf("Could not open file : %s\n", filename);
        debug(WARNING_LEVEL,"Exiting file display ,stat() error for %s",
                filename);
        return ;
    }

    mode = statb.st_mode;

    /*print inode number*/
    if(options_flags.i_flag)
    {
        printf("%9ld ",statb.st_ino);  
    }

    /*print number of blocks*/
    if(options_flags.s_flag)
    {
        printf("%5ld ",(statb.st_blocks)/2);
    }


    debug(LOG_LEVEL,"entered display for l flag");
    /*print file access permissions*/
    {
        UCHAR type_of_file;
        switch (mode & S_IFMT)
        {
            /* check if directory */     
            case S_IFDIR : type_of_file = 'd';
                           file_name_color = file_name_color ? 
                           file_name_color : BLUE;
                           break;
            case S_IFCHR : type_of_file = 'c';
                           break;
            case S_IFBLK : type_of_file = 'b';
                           break;
            case S_IFREG : type_of_file = '-';
                           break;
            case S_IFLNK : type_of_file = 'l';
                           file_name_color = file_name_color ? 
                           file_name_color : MAGENTA;
                           break;
            case S_IFIFO : type_of_file = 'p';
                           file_name_color = file_name_color ? 
                           file_name_color : RED;
                           break;
            default      : type_of_file = '-';
                           break; 
        }
        if(options_flags.l_flag)
        {
            debug(LOG_LEVEL,"Printed file access info");
            printf("%c ",type_of_file);
        }
    } 

    /*only last 9 bits contain access information*/
    for( i = 8 ; i >= 0 ; i--)
    {
        if( mode & ( 1 << i) )
        {
            if(options_flags.l_flag)
                printf("%c", vals[i%3]);
            if(vals[i%3]=='x')
            {
                file_name_color = file_name_color ? file_name_color : GREEN;
            }
        }
        else
        {
            if(options_flags.l_flag)
                printf("%c",'-');
        }
    }

    debug(LOG_LEVEL,"Printed detailed file access info");

    if(options_flags.l_flag)
    {

        /*printing the number of links*/
        printf(" %6d",statb.st_nlink);
        /*printing user and group names*/
        pwd = getpwuid ( statb.st_uid );
        grp = getgrgid ( statb.st_gid );

        printf(" %10s %10s",pwd->pw_name, grp->gr_name);
        printf(" %6ld ",statb.st_size); /*print size*/

        debug(LOG_LEVEL,"Printed num of links and uid and gid");

        tm = localtime(&(statb.st_mtime));
        strftime(date,sizeof(date),"%b %d %H:%M", tm);
        printf(" %s ", date);
        if(options_flags.c_flag != 1)
        {
            COLOR_PRINT(file_name_color," %s\n", f_name);
        }
        else
        {
            printf(" %s\n", f_name);
        }    
    }
    else
    {
        /*Finally print the filename - should be made generic*/
        if(options_flags.c_flag != 1)
        {
            COLOR_PRINT(file_name_color," %s ", f_name);
        }
        else
        {
            printf(" %s ", f_name);
        }    
    }

    debug(LOG_LEVEL,"Exiting file display routine");

}




/* Routine to display contents of directory */
void ls_dir_display(DIR_NAME_LIST* dir_node, OPTION_FLAGS options_flags)
{
    struct dirent *dp;
    UCHAR dir_path[MAX_FILE_PATH_SIZE];
    UCHAR *dirname = dir_node->dir_name;
    FILE_NAME_LIST *files_in_dir = NULL;
    UINT32 num_of_files = 0;
    UINT32 err_excess_files = 0;
    INT32 i = 0;
    DIR *dfd ;
    struct stat statb;

    debug(LOG_LEVEL,"DIR_DISPLAY called with %s",dirname);

    if(options_flags.d_flag==1)
    {
        ls_file_display(dirname,options_flags);
        return;
    }

    dfd = opendir((CHAR *)dirname);
    if(dfd != NULL) 
    {
        debug(LOG_LEVEL,"DIR_DISPLAY %s successfilly opened",dirname);

        /* Store filenames */
        while((dp = readdir(dfd)) != NULL)
        {
            if(options_flags.a_flag != 1)
            {
                if(dp->d_name[0]=='.')
                    continue;
            }    

            /* Recursion for sub directories*/
            if((options_flags.R_flag == 1) && (dp->d_name[0]!='.'))
            {
                debug(LOG_LEVEL,"DIR_DISPLAY -x flag given ");
                strncpy(dir_path,dirname, MAX_FILE_PATH_SIZE);
                strncat(dir_path,"/", MAX_FILE_PATH_SIZE - strlen(dir_path));
                strncat(dir_path,dp->d_name,
                        MAX_FILE_PATH_SIZE - strlen(dir_path));
                stat((CHAR *)dir_path,&statb);

                if(S_ISDIR(statb.st_mode))
                {
                    debug(LOG_LEVEL,"DIR_DISPLAY Found dir %s: in -x mode ",
                            dir_path);
                    /* Add directory to end of dir ll */
                    add_node_to_dir_list(&dir_node,dp->d_name,dirname,FALSE);
                }
            }

            num_of_files++;

            /* Add in reverse order if -r flag is given */
            add_node_to_file_list(&files_in_dir, dp->d_name, dirname, 
                    options_flags.S_flag + options_flags.r_flag);
        }


        printf("%s :\n",dirname);
        printf("Number of files %d. \n",num_of_files);
        flush_file_queue(&files_in_dir,options_flags);

    }
    else
    {
        printf("Could not open directory :%s",dirname);
        debug(WARNING_LEVEL,"Couldnt open dir %s : in ls_dis_display",dirname);
    }

    printf("\n");
}
