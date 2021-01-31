#include "types.h"
#include "stat.h"
#include "user.h"


int main(){

    printf(1, "before fork:\n\n");
    for(int i = 0; i < 5; i++)
        getpid();
    printf(1, "counts of system call getpid calls : %d\n", getsyscallcounter(11));

    for(int j = 0; j < 7; j++)
        getparentid();
    printf(1, "counts of system call getparentid calls : %d\n", getsyscallcounter(22));

    printf(1, "================================\n");
    
    int pid = fork();
    if(pid == 0){
        for(int i=0; i < 4; i++)
            getpid();
        printf(1, "child process:\n");    
        printf(1, "counts of system call getpid calls : %d\n", getsyscallcounter(11));
        printf(1, "counts of system call fork calls : %d\n", getsyscallcounter(1));
    }

    else if(pid > 0)
    {
        wait();
        printf(1, "parent process:\n");
        printf(1, "counts of system call fork calls : %d\n", getsyscallcounter(1));
        printf(1, "counts of system call wait calls : %d\n", getsyscallcounter(3));
    }
    else
    {
        printf(1, "fork failed\n");
        exit();
    }
    

    for(int i = 0 ; i < 10; i++)
        getpid();
        
    if(pid == 0){
        printf(1, "child process:\n");
        printf(1, "counts of system call getpid calls : %d\n", getsyscallcounter(11));   
    }
    else{
        printf(1, "parent process:\n");
        printf(1, "counts of system call getpid calls : %d\n", getsyscallcounter(11));  
    }

    return 0;
}