#include "types.h"
#include "stat.h"
#include "user.h"

#define PROCESS_NUM 10
#define MAX 1000

void print_metrics(metrics *m, int pd)
{
    printf(1, "_____________________________________________\n");
    printf(1, "metrics for /%d/ : \n", pd);
    printf(1, "turnaround time : %d\n", m->turn_around);
    printf(1, "wait time : %d\n", m->wait);
    printf(1, "cpu burst time : %d\n", m->cbt);
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

void wait_for_children()
{
    int pids[PROCESS_NUM];
    metrics **mat;
    metrics *sum = malloc(sizeof(metrics));
    mat = malloc(sizeof(metrics *) * PROCESS_NUM);
    for (int i = 0; i < PROCESS_NUM; i++)
        mat[i] = malloc(sizeof(metrics));
    for (int i = 0; i < PROCESS_NUM; i++)
    {
        pids[i] = waitandgetmetrics(mat[i]);
        sum->cbt += mat[i]->cbt;
        sum->turn_around += mat[i]->turn_around;
        sum->wait += mat[i]->wait;
    }
    for (int i = 0; i < PROCESS_NUM; i++)
        print_metrics(mat[i], pids[i]);
    print_averages(sum);
}

void create_children(int pid)
{
    for (int i = 0; i < PROCESS_NUM; i++)
    {
        if (pid == getpid())
            fork();
        else
            break;
    }
}

void do_work()
{
    int child_pid = getpid();
    for (int i = 0; i < MAX; i++)
        printf(1, "/%d/ : /%d/\n", child_pid, i);
}

int main()
{
    int pid = getpid();
    create_children(pid);

    if (pid == getpid())
        wait_for_children();
    else
        do_work();
    exit();
}