#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <omp.h>
#include "mpi.h"
#include <unistd.h>
#include <sys/param.h>

#define BUF_SIZE (MAXHOSTNAMELEN + 1)

int main(int argc, char *argv[])
{
    int id, np;
    char buf[BUF_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

#pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int cpu_num = sched_getcpu();
        gethostname(buf, BUF_SIZE);
        printf("Rank %02d: Thread %02d is running on CPU %02d on node %s\n", id, thread_num, cpu_num, buf);
    }
    MPI_Finalize();

    return 0;
}
