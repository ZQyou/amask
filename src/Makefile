OMPFLAG = -fopenmp
CC      = $(OSC_CXX) 
MPICC   = $(OSC_MPI_CXX) 
LOAD_X  = -xHost
ifeq ($(LMOD_FAMILY_COMPILER),pgi)
    OMPFLAG = -mp
    LOAD_X  =
endif
ifeq ($(LMOD_FAMILY_COMPILER),gnu)
    LOAD_X  = -march=native
endif

CC_SER  =    $(CC) -g
CC_MPI  = $(MPICC) -g
CC_OMP  =    $(CC) -g $(OMPFLAG)
CC_HYB  = $(MPICC) -g $(OMPFLAG)
LD_MPI  = $(MPICC) -g
LD_OMP  =    $(CC) -g $(OMPFLAG)
LD_HYB  = $(MPICC) -g $(OMPFLAG)

AR      = ar

DRIVER_SOURCES = amask_mpi.c amask_omp.c amask_hybrid.c 
DRIVER_OBJECTS = $(DRIVER_SOURCES:.c=.o)

#LIB_SOURCES=boundto.c cmdln_args.c load.c map_to_procid.c print_mask.c timers.c mpi_report_mask.c omp_report_mask.c hybrid_report_mask.c opts.cpp
 LIB_SOURCES=boundto.c              load.c map_to_procid.c print_mask.c timers.c mpi_report_mask.c omp_report_mask.c hybrid_report_mask.c opts.cpp
#LIB_OBJECTS = $(LIB_SOURCES:.c=.o)
 LIB_OBJECTS =boundto.o             load.o map_to_procid.o print_mask.o timers.o mpi_report_mask.o omp_report_mask.o hybrid_report_mask.o opts.o


LIB     = amask.a
EXES	= $(DRIVER_SOURCES:.c=)
#EXES = amask_mpi amask_omp amask_hybrid 

all: $(EXES)

amask_mpi    :            amask_mpi.o                       $(LIB)
	$(LD_MPI) $(LDFLAGS_MPI)  amask_mpi.o    -o amask_mpi    $(LIB)
	mkdir -p ../bin
	cp -p  amask_mpi ../bin
amask_omp    :            amask_omp.o                       $(LIB)
	$(LD_OMP) $(LDFLAGS_OMP)  amask_omp.o    -o amask_omp    $(LIB)
	mkdir -p ../bin
	cp -p  amask_omp ../bin
amask_hybrid :            amask_hybrid.o                    $(LIB)
	$(LD_HYB) $(LDFLAGS_HYB)  amask_hybrid.o -o amask_hybrid $(LIB)
	mkdir -p ../bin
	cp -p  amask_hybrid ../bin


$(LIB) : $(LIB_OBJECTS)
	$(AR) -csr  $@  $^
	mkdir -p ../lib
	cp -p $(LIB) ../lib

amask_mpi.o    : amask_mpi.c 
	$(CC_MPI) $(CFLAGS) -c $< -o $@
mpi_report_mask.o : mpi_report_mask.c
	$(CC_MPI) $(CFLAGS) -c $< -o $@

amask_omp.o    :  amask_omp.c
	$(CC_OMP) $(CFLAGS) -c $< -o $@
omp_report_mask.o :  omp_report_mask.c
	$(CC_OMP) $(CFLAGS) -c $< -o $@

amask_hybrid.o    :  amask_hybrid.c
	$(CC_HYB) $(CFLAGS) -c $< -o $@
hybrid_report_mask.o :  hybrid_report_mask.c
	$(CC_HYB) $(CFLAGS) -c $< -o $@


load.o  : load.c
	$(CC_SER) $(LOAD_X) -DCMASK_LOAD -O3  -c $< -o $@

boundto.o  : boundto.c
	$(CC_SER)  -D _GNU_SOURCE -c $< -o $@
map_to_procid.o  : map_to_procid.c
	$(CC_SER)  -D _GNU_SOURCE -c $< -o $@
timers.o  : timers.c
	$(CC_SER)  -D _GNU_SOURCE -c $< -o $@
opts.o  : opts.cpp
	$(CC_SER)                 -c $< -o $@


%.o : %.c
	$(CC_SER) $(CFLAGS) -c $< -o $@


.PHONY: install clean cleanall
install:
	mkdir -p -v ../bin ../lib
	cp -p $(LIB)  ../lib
	cp -p $(EXES) ../bin

clean :
	echo EXES: $(EXES) 
	echo DRIVER_OBJECTS: $(DRIVER_OBJECTS) 
	echo LIB_OBJECTS: $(LIB_OBJECTS) 
	echo LIB: $(LIB) *.mod
	rm -fr $(EXES) $(DRIVER_OBJECTS) $(LIB_OBJECTS) $(LIB) *.mod

cleanall :
	rm -fr $(EXES) $(DRIVER_OBJECTS) $(LIB_OBJECTS) $(LIB) *.mod
	rm -fr $(addprefix ../bin/, $(EXES))  ../lib/$(LIB)
	rmdir  ../bin/        ../lib/


#http://stackoverflow.com/questions/15195087/how-to-make-static-library-in-makefile
#other information
