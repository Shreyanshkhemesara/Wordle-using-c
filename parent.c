#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>


int main() {
    char str[5];
    char * args[3];
    args[0]="./child.out";
    int cnt=0;
    for(int i = 0 ; i < 6; i++) {
        
        pid_t pid = fork();
        if(pid == 0) /* Child */
        {
            if(cnt==0){
                exit(-1);
            }
            if(execvp("./child.out", args) < 0) {
                printf("erooroorororororor\n");
            }
            exit(1);
        } 
        else /* Parent */
        {   
            if(i == 5) continue;
            int status;
            waitpid(pid, &status, 0);
            if(WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                if(exit_status == 2) {
                    return 1;
                }
            }
            printf("word %d : \n", i+1);
            gets(str);
            args[0] = str;
            args[1] = NULL;
            cnt++;
        }
    }
    return 0;    
}
