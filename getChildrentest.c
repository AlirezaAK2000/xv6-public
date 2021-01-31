#include "types.h"
#include "stat.h"
#include "user.h"



int main(){
    int pid = getpid();
    for(int p = 0;p<5;p++){
        if(pid == getpid()){
            fork();  
        }
    }
    int counter = 0;
    if (pid == getpid())
    {
        int*children = malloc(sizeof(int)*64);
        if(getchildren(children) == -1){
            printf(1,"error\n");
        }
        printf(1,"children: \n");
        for(int i = 0;;i++){
            if (children[i]==-1)
                break;
            printf(1 , "%d \n" , children[i]);
            counter++;
        }
        for(int i=0 ; i<counter;i++)
            wait();
    }   
    exit();
}