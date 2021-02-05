#include "types.h"
#include "stat.h"
#include "user.h"

#define PROCESS_NUM 30
#define MAX 250
#define CLASS 6
#define NUM_OF_CLASS 5 

void print_metrics(metrics *m, int pd)
{
    printf(1, "_____________________________________________\n");
    printf(1, "metrics for /%d/ : \n", pd);
    printf(1, "turnaround time : %d\n", m->turn_around);
    printf(1, "wait time : %d\n", m->wait);
    printf(1, "cpu burst time : %d\n", m->cbt);
    printf(1, "_____________________________________________\n");
}

void print_averages_per_class(metrics *sum, int p)
{
    printf(1, "\n\n\n");
    printf(1, "_____________________________________________\n");
    printf(1, "averages for priority %d: \n", p + 1);
    printf(1, "turnaround time : %d\n", sum->turn_around / NUM_OF_CLASS);
    printf(1, "wait time : %d\n", sum->wait / NUM_OF_CLASS);
    printf(1, "cpu burst time : %d\n", sum->cbt / NUM_OF_CLASS);
    printf(1, "_____________________________________________\n");
}

void print_averages(metrics *sum)
{
    printf(1, "\n\n\n");
    printf(1, "_____________________________________________\n");
    printf(1, "averages: \n");
    printf(1, "turnaround time : %d\n", sum->turn_around / PROCESS_NUM);
    printf(1, "wait time : %d\n", sum->wait / PROCESS_NUM);
    printf(1, "cpu burst time : %d\n", sum->cbt / PROCESS_NUM);
    printf(1, "_____________________________________________\n");
}

void wait_for_children(){
    int pids[PROCESS_NUM];
    metrics **mat;
    metrics **cl;
    metrics *sum = malloc(sizeof(metrics));
    int p;
    mat = malloc(sizeof(metrics *) * PROCESS_NUM);
    cl  = malloc(sizeof(metrics *) * CLASS);
    for (int i = 0; i < PROCESS_NUM; i++)
        mat[i] = malloc(sizeof(metrics));
    for (int i = 0; i < CLASS; i++)
        cl[i] = malloc(sizeof(metrics));    
    for (int i = 0; i < PROCESS_NUM; i++)
    {
        pids[i] = waitandgetmetrics(mat[i]);
        //for each class of priority
        p = (mat[i]-> priority) - 1;
        cl[p]->cbt += mat[i]->cbt;
        cl[p]->turn_around += mat[i]->turn_around;
        cl[p]->wait += mat[i]->wait;  
        //for all child
        sum->cbt += mat[i]->cbt;
        sum->turn_around += mat[i]->turn_around;
        sum->wait += mat[i]->wait;
    }
    for (int i = 0; i < PROCESS_NUM; i++)
        print_metrics(mat[i], pids[i]);
    for (int i = 0; i < CLASS; i++)
        print_averages_per_class(cl[i], i);    
    print_averages(sum);
}

int main()
{
    changepolicy(1);
    int pid = getpid();
    int pid2, j;
    for (int i = 0; i < PROCESS_NUM; i++)
    {
        if (pid == getpid()){
            pid2 = fork();
            if (pid2 == 0){
                j = 6 - ((int)i/5);
                setpriority(j);
            }
        }    
        else
            break;
    }

    if (pid == getpid())
    {
        wait_for_children();
    }
    else
    {
        int child_pid = getpid();
        for (int i = 0; i < MAX; i++)
            printf(1, "/%d/ : /%d/\n", child_pid, i);           
    }
    exit();
}