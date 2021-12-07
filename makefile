CC=gcc
CFLAGS=-Wall -std=c99 -O0 -msse
BINEXT=out

all: faxpy1 myblas.o faxpy2 faxpy3 faxpy4 faxpy5 faxpy6 faxpy7 faxpy8 faxpy9 faxpy10 faxpy11 faxpy12

# Target to create our BLAS library
myblas.o:   myblas.c 
	$(CC) $(CFLAGS) -c $< -o $@

# Target to create test function for unoptimized version of FAXPY
faxpy1: faxpy1.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy1.o: faxpy1.c
	$(CC) $(CFLAGS) -c $< -o $@

faxpy2: faxpy2.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy2.o: faxpy2.c
	$(CC) $(CFLAGS) -c $< -o $@
	
faxpy3: faxpy3.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy3.o: faxpy3.c
	$(CC) $(CFLAGS) -c $< -o $@

faxpy4: faxpy4.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy4.o: faxpy4.c
	$(CC) $(CFLAGS) -c $< -o $@

faxpy5: faxpy5.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy5.o: faxpy5.c
	$(CC) $(CFLAGS) -c $< -o $@
	
faxpy6: faxpy6.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy6.o: faxpy6.c
	$(CC) $(CFLAGS) -c $< -o $@
	
faxpy7: faxpy7.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy7.o: faxpy7.c
	$(CC) $(CFLAGS) -c $< -o $@
	
faxpy8: faxpy8.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy8.o: faxpy8.c
	$(CC) $(CFLAGS) -c $< -o $@
	
faxpy9: faxpy9.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy9.o: faxpy9.c
	$(CC) $(CFLAGS) -c $< -o $@
	
faxpy10: faxpy10.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy10.o: faxpy10.c
	$(CC) $(CFLAGS) -c $< -o $@

faxpy11: faxpy11.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy11.o: faxpy11.c
	$(CC) $(CFLAGS) -c $< -o $@

faxpy12: faxpy12.o myblas.o
	$(CC) $(CFLAGS) -o $@.$(BINEXT) $^
faxpy12.o: faxpy12.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean: 
	rm -f *.o *.out
