#
# C compiler and options
#
CC = cc -O3 -qopenmp 
LDFLAGS = 
#
# Object files
#
OBJ=	stream_d.o second_wall.o

#
# Compile
#
stream_d:	$(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

.c.o:
	$(CC) -c $< 

#
# Clean out object files and the executable.
#
clean:
	rm -fr *.o stream_d
