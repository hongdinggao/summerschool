ifneq ($(PUHTI),1)

CC=cc
FC=ftn
LINKER=$(CC)
FLAGS=-O2 -fopenmp -I/appl/lumi/SW/LUMI-22.08/L/EB/libpng/1.6.37-cpeCray-22.08/include -L/appl/lumi/SW/LUMI-22.08/L/EB/libpng/1.6.37-cpeCray-22.08/lib

else

CC=nvc
FC=nvfortran
LINKER=$(FC)
FLAGS=-O2 -mp=gpu -gpu=cc70

endif

LDFLAGS=-lpng

EXE=mandelbrot

OBJS=mandelbrot.o constants.o kernel.o pngwriter_mod.o pngwriter.o

all: $(EXE)

mandelbrot.o: mandelbrot.F90 kernel.o pngwriter_mod.o

kernel.o: kernel.F90 constants.o

mandelbrot: $(OBJS)
	$(LINKER) -o $@ $(FLAGS) $(OBJS) $(LDFLAGS)

%.o: %.F90
	$(FC) $(FLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	-/bin/rm -f $(EXE) a.out *.o *.mod *.png *.s
