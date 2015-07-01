CC = g++
CFLAGS = -O3 -pipe -fomit-frame-pointer -funroll-all-loops -s

EASYBMP_DIR = $(shell realpath $(shell pwd)/../../libeasybmp-1.06)

all: $(EASYBMP_DIR)/EasyBMP.cpp
	$(CC) $(CFLAGS) -c $(EASYBMP_DIR)/EasyBMP.cpp
	cp $(EASYBMP_DIR)/EasyBMP.h .
	cp $(EASYBMP_DIR)/EasyBMP_BMP.h .
	cp $(EASYBMP_DIR)/EasyBMP_DataStructures.h .
	cp $(EASYBMP_DIR)/EasyBMP_VariousBMPutilities.h .

clean:
	rm -f *.o *.h
