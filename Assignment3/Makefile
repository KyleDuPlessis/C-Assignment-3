# DPLKYL002
# Makefile in ./Assignment3_DPLKYL002 project folder to compile the driver and link it against the newly created shared libraries

CPP=g++ 
INCLUDES=-I./libs/huffmantreelib
LIBDIRS=-L./libs/huffmantreelib
LIBS= -lhuffmantree
CPPFLAGS=-std=c++11 $(INCLUDES) $(LIBDIRS) $(LIBS)
TARGET=Huffencode

# first compile - IMPLICIT PATTERN RULE for creating binary object files
%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)

# then link - LINKING RULE for linking binary object files together to create an executable
$(TARGET): Huffencode.o 
	$(CPP) -o $(TARGET) Huffencode.o $(CPPFLAGS)
  
# other rules
Test.o: Test.cpp
		$(CPP) -c -o $@ $< $(CPPFLAGS)

Test: 
	make compile_test
	
compile_test:Test.o
		$(CPP) -o Test Test.o $(CPPFLAGS)



# never submit binary object / executable files
clean:
	@rm *.o Huffencode Test
	@rm ./libs/*.so
	cd ./libs/huffmantreelib && make clean

# build entire project
all:
	
	cd ./libs/huffmantreelib && make
	@cp -f ./libs/huffmantreelib/*.so ./libs
	make
	make Test


	

# run program
run huffencode:
	chmod 700 Huffencode
	export LD_LIBRARY_PATH=./libs && ./Huffencode $(args)


run_unit_tests:
	chmod 700 Huffencode
	export LD_LIBRARY_PATH=./libs && ./Test
