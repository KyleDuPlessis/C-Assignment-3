# DPLKYL002
# Makefile in /libs/huffmantreelib folder to compile a shared library

CPP=g++
CPPFLAGS=-fPIC -shared -std=c++11
LIBNAME=libhuffmantree.so

# first compile - create binary object files
%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)

# then link - link binary object files together to create the shared library
$(LIBNAME): HuffmanTree.o HuffmanTree.h
	$(CPP) -o $(LIBNAME) HuffmanTree.o $(CPPFLAGS)

# other rules
# never submit binary object / shared object files
clean:
	@rm *.o *.so
