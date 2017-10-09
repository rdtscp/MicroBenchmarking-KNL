#
# Fortran compiler and options
#
FC=	ftn -O3 -qopenmp 
CC=	cc -O3 -qopenmp
LDFLAGS= 
#
# Object files
#
OBJ=	stream_d.o second_wall.o

#
# Compile
#
stream_d:	$(OBJ)
	$(FC) -o $@ $(OBJ) $(LDFLAGS)

.f.o:
	$(FC) -c $< 

#
# Clean out object files and the executable.
#
clean:
	rm -fr *.o stream_d
