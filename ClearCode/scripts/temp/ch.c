# include <stdio.h>




int main(void)
{
    int i=0x08004034;

    int off=0x18;
    int t=0xA2A7;


    while(t<i)
    {
    t+=off;
    }

   printf(" \033[32m Aksjat %x \033[0m",t);
    return 0;


}
