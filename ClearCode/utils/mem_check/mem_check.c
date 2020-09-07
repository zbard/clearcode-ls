# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# include "xdebug_header.h"

# define MAX_ALLOC 1000
# define FNAME_SIZE 16


int state=0;
pthread_mutex_t mutex;   /*init exit*/
pthread_cond_t cond;

pthread_mutex_t mutex_1; /*start and stop*/
pthread_cond_t cond_1;


pthread_mutex_t mutex_2; /*entry restriction*/
pthread_cond_t cond_2;

unsigned long int counter=0;


struct node
{
    int valid;/*0 - empty,1-malloc,2-free anamoly */
    int fid;
    char fname[FNAME_SIZE];/*for '/0' char */
    int line;
    int size;
    unsigned long int stamp;
    void * addr; /*address*/
} arr[MAX_ALLOC];


void ftruncate( char * input, char* output)
{
    int i,j=0;


    for(i=0;input[i]!='\0';i++)
    {
        if(input[i]=='/')
            j=-1;
        else if(j<FNAME_SIZE)
            output[j]=input[i];


        if(j<FNAME_SIZE)
            j++;
    }
    output[j]='\0';


}


void PrintSortData(void) /*BAd - i am sorting(bubble) and printing , ll better */
{
    int x,y,val1,val2;
    struct node holder;

    debug(MEM_LEVEL,"\n == > \n");
    /* sort by fileid*/
    for(x = 0; x < MAX_ALLOC; x++)
        for(y = 0; y < MAX_ALLOC-1; y++)
        {
            if(arr[y].valid==0)
                val1=10000;
            else 
                val1=arr[y].fid;

            if(arr[y+1].valid==0)
                val2=10001;
            else
                val2=arr[y+1].fid;


            if(val1 > val2 || (val1==val2 && arr[y].stamp>arr[y+1].stamp)) 
            {
                holder = arr[y+1];
                arr[y+1] = arr[y];
                arr[y] = holder;
            }
        }

    for(x=0;x<MAX_ALLOC;x++)
    {
        if(arr[x].valid!=0)
            debug(MEM_LEVEL," Mem: Name: %s  File id:%4d stamp:%lu Mem or free:%2d Line: %d\n",
                    arr[x].fname,arr[x].fid,arr[x].stamp,arr[x].valid,arr[x].line); 
    }

}

void* mem_thread(void* args)
{
    pthread_mutex_lock (&mutex);
    debug(MEM_LEVEL,"\n Thread starting\n");
    pthread_cond_signal (&cond);
    pthread_mutex_unlock (&mutex);


    while (state != 2)
    {

        pthread_mutex_lock (&mutex_1);
        switch (state)
        {
            case 0:
                /* Wait for Start  */
                pthread_cond_wait (&cond_1, &mutex_1);
                break;

            case 1:
                /* Start - used timed */
                PrintSortData();
                sleep(1);
                break;
        }
        pthread_mutex_unlock (&mutex_1);
    }

    pthread_mutex_lock (&mutex);
    debug(MEM_LEVEL,"Thread exiting\n");
    pthread_cond_signal (&cond);
    pthread_mutex_unlock (&mutex);

    debug(MEM_LEVEL,"Thread exited\n");
    return NULL;
}


void mem_play(void)
{

    debug(MEM_LEVEL,"\n2 Playing lock2 \n");
    pthread_mutex_lock (&mutex_1);
    debug(MEM_LEVEL,"\n2 Playing \n");

    state = 1;
    pthread_cond_signal (&cond_1);
    pthread_mutex_unlock (&mutex_1);
}	

void mem_pause(void)
{

    debug(MEM_LEVEL,"\n2 Pausing lock2\n");
    pthread_mutex_lock (&mutex_1);
    state = 0;
    debug(MEM_LEVEL,"\n2 Pausing state%d bobob\n",state);
    pthread_cond_signal (&cond_1);
    pthread_mutex_unlock (&mutex_1);
}	

void mem_init(unsigned long int val)
{
    int i;
    pthread_t tid;

    pthread_mutex_init (&mutex, NULL);
    pthread_cond_init (&cond, NULL);

    pthread_mutex_init (&mutex_1, NULL);
    pthread_cond_init (&cond_1, NULL);


    pthread_mutex_lock (&mutex);
    state = 0;
    i= pthread_create (&tid, NULL, mem_thread, NULL);
    debug(MEM_LEVEL,"\n Thrd Created status (0) :: %d\n",i); /*error handle cant create thread */

    pthread_cond_wait (&cond, &mutex);
    pthread_mutex_unlock (&mutex);


    counter=val;
    for(i=0;i<MAX_ALLOC;i++)
    {
        arr[i].valid=0;
        arr[i].fid=0;
        arr[i].fname[0]='\0';
        arr[i].line=0;
        arr[i].size=0;
        arr[i].stamp=0;
        arr[i].addr=NULL;
    }
    /* Starting task*/

    debug(MEM_LEVEL,"Mem:_Task_Starting_...\n"); 
}


void* mem_malloc_wrapper(size_t size,  char* file,int line,int fileid)
{
    int i,x=0;
    int ctr=0; 
    void* ptr =NULL ;
    char temp[FNAME_SIZE+1];

    debug(MEM_LEVEL,"in MAllocWrapper");

    for(i=0;i<MAX_ALLOC;i++)/*find valid place to put it*/
    {
        if(arr[i].valid==0)
        { break; }
        else  if(arr[i].stamp<arr[ctr].stamp)/*what if ctr=0 invalid with different data ?????*/
        {ctr=i;}
    }

    if(size==0)
        ptr=NULL;
    else
        ptr=malloc(size);



    if(i!=MAX_ALLOC) /*found vacant place */
        ctr=i;           /*store in that vacant place*/

    debug(MEM_LEVEL,"Mem : Malloc called -- put in index %d",i);

    /* Store in array */
    arr[ctr].valid=1;
    arr[ctr].fid=fileid;

    ftruncate(file,temp);

    for(x=0;x<(FNAME_SIZE+1);x++) 
        arr[ctr].fname[x]=temp[x];/*check if 2 smaet*/


    arr[ctr].line=line;
    arr[ctr].size=size;
    arr[ctr].addr=ptr;
    arr[ctr].stamp=++counter;

    return ptr;
}



void mem_free_wrapper(void* ptr,char * file,int  line,int fileid)
{
    int i,x=0,empty=-1,ctr=0;
    char temp[FNAME_SIZE+1];



    for(i=0;i<MAX_ALLOC; i++)
    {
        if(arr[i].valid==1)
            if(arr[i].addr==ptr) /*found match*/
                break;

        if(arr[i].valid==0 && empty==-1)/*find vacant spot but dont break*/
            empty=i;

        if(arr[i].valid!=0)
            if(arr[i].stamp<arr[ctr].stamp)/*earliest stamp*/
                ctr=i;
    }


    if(ptr==NULL || i==MAX_ALLOC) /*Null exception or no match*/
    {
        if(empty==-1) /*didnt found vacant spot*/
            empty=ctr;    /*first stamp*/

        /*store in array*/
        arr[empty].valid=2;
        arr[empty].fid=fileid;

        ftruncate(file,temp);

        for(x=0;x<(FNAME_SIZE+1);x++) 
            arr[empty].fname[x]=temp[x];/*check if 2 smaet*/


        arr[empty].line=line;
        arr[empty].size=0;
        arr[empty].addr=ptr;
        arr[empty].stamp=++counter;

        return;
    }
    else /* De allocation unless ptr not found or ptr is NULL*/
    {
        arr[i].valid=0;
        free(ptr);
        debug(MEM_LEVEL,"Mem : Successfull free -- index %d",i);
    }
}






void mem_shutdown(void)
{

    pthread_mutex_lock (&mutex);
    state=2;
    pthread_cond_signal (&cond_1); /*release any waits*/
    pthread_cond_wait (&cond, &mutex);
    pthread_mutex_unlock (&mutex);

    PrintSortData();
    debug(MEM_LEVEL,"Mem:_Task_Stopping_...\n"); 
} 






