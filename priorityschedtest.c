#include "types.h"
#include "stat.h"
#include "user.h"


int main(){

for(int i = 0; i < 30; i++){
   int pid = fork();
   
   if(pid == 0){
      int j = 6 - ((int)i/5);       
      setpriority(j); // set priority

      exit();

   } 
   else if(pid < 0){
      printf(1, "fork failed\n");
      exit();
   }

   wait();
}

}