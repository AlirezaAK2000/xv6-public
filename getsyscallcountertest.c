#include "types.h"
#include "stat.h"
#include "user.h"


int main(){

    for(int i = 0; i < 5; i++)
        getpid();
    printf(1, "counts of system call getpid calls : %d\n", getsyscallcounter(11));

    for(int j = 0; j < 7; j++)
        getparentid();
    printf(1, "counts of system call getparentid calls : %d\n", getsyscallcounter(22));

    for(int i = 0 ; i < 10; i++)
        getpid();
    printf(1, "counts of system call getpid calls : %d\n", getsyscallcounter(11));   

    return 0;
}