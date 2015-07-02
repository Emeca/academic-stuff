SRC = fat.cc diretorio.cc vfs.cc main.cc
OUT = vitual-fs

CPPFLAGS = -Wall -W -Werror

all: $(OUT)

$(OUT): main.o vfs.o diretorio.o fat.o
	$(CXX) $(CPPFLAGS) -o $(OUT) $^

main.o: main.cc
	$(CXX) $(CPPFLAGS) -c $<

vfs.o: vfs.cc vfs.hh
	$(CXX) $(CPPFLAGS) -c $<

diretorio.o: diretorio.cc fat.hh
	$(CXX) $(CPPFLAGS) -c $<

fat.o: fat.cc fat.hh
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -f $(OUT) *.o
