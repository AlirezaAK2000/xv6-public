#include "types.h"
#include "stat.h"
#include "user.h"


int main(){
    int a[10];
    for (int i = 0; i < 10; i++)
    {
        printf(1,"%d\n",a[i]);
    }
    
    int pid = getpid();
    int child_id = fork();
    if (child_id == 0)
    {   
        if(pid == getparentid()){
            printf(1,"our system call works well!!\n");
            printf(1 , "parent id : %d \n child id : %d\n" , getparentid() , getpid() );
        }else{
            printf(1,"it does not work properly!!!\n");
        }
        exit();
    }else{
        wait();
    }
    

    exit();
}