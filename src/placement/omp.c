#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <omp.h>
#include <unistd.h>
#include <sys/param.h>

#define BUF_SIZE (MAXHOSTNAMELEN + 1)

int main(int argc, char *argv[])
{
    int id, np;
    char buf[BUF_SIZE];

#pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int cpu_num = sched_getcpu();
        gethostname(buf, BUF_SIZE);
        printf("Thread %02d is running on CPU %02d on node %s\n", thread_num, cpu_num, buf);
    }

    return 0;
}
