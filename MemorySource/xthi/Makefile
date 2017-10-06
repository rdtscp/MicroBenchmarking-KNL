#
# C compiler and options
#
CC = cc -O3 -qopenmp

#
# Object files
#
OBJ=	xthi.o 

#
# Compile
#
xthi:	$(OBJ)
	$(CC) -o $@ $(OBJ) 

.c.o:
	$(CC) -c $< 

#
# Clean out object files and the executable.
#
clean:
	rm -fr *.o xthi
