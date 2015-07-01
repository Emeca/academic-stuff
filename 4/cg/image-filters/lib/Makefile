CC = g++
CFLAGS = -O3 -pipe -fomit-frame-pointer -funroll-all-loops -s

EASYBMP_DIR = easybmp

all: $(EASYBMP_DIR)/EasyBMP.cpp
	$(CC) $(CFLAGS) -c $(EASYBMP_DIR)/EasyBMP.cpp

clean:
	rm -f *.o
