OMPFLAG = -fopenmp
CC      = $(OSC_CC) 
MPICC   = $(OSC_MPI_CC) 
ifeq ($(LMOD_FAMILY_COMPILER),pgi)
    OMPFLAG = -mp
endif

CC_SER  =    $(CC) -g
CC_MPI  = $(MPICC) -g
CC_OMP  =    $(CC) -g $(OMPFLAG)
CC_HYB  = $(MPICC) -g $(OMPFLAG)
LD_MPI  = $(MPICC) -g
LD_OMP  =    $(CC) -g $(OMPFLAG)
LD_HYB  = $(MPICC) -g $(OMPFLAG)

AR      = ar

DRIVER_SOURCES = mpi.c omp.c hybrid.c 
DRIVER_OBJECTS = $(DRIVER_SOURCES:.c=.o)
EXES	= $(DRIVER_SOURCES:.c=)

all: $(EXES)

mpi    :            mpi.o                       $(LIB)
	$(LD_MPI) $(LDFLAGS_MPI)  mpi.o    -o mpi    $(LIB)
	mkdir -p ../../bin
	cp -p  mpi ../../bin
omp    :            omp.o                       $(LIB)
	$(LD_OMP) $(LDFLAGS_OMP)  omp.o    -o omp    $(LIB)
	mkdir -p ../../bin
	cp -p  omp ../../bin
hybrid :            hybrid.o                    $(LIB)
	$(LD_HYB) $(LDFLAGS_HYB)  hybrid.o -o hybrid $(LIB)
	mkdir -p ../../bin
	cp -p  hybrid ../../bin

mpi.o    : mpi.c 
	$(CC_MPI) $(CFLAGS) -c $< -o $@

omp.o    :  omp.c
	$(CC_OMP) $(CFLAGS) -c $< -o $@

hybrid.o    :  hybrid.c
	$(CC_HYB) $(CFLAGS) -c $< -o $@

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

#http://stackoverflow.com/questions/15195087/how-to-make-static-library-in-makefile
#other information
