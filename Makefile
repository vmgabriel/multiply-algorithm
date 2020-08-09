PROGRAM = Multi
INSTALL = opt/$(PROGRAM)

GUI = 
LIB = 
SQL = 

SRC = Multi.cxx

PKGS = 

ESPECIAL = 

VALACOPTS =

BUILT_ROOT = 1

all:
	g++ -Wall -o $(PROGRAM) $(SRC)

clean:
	@rm -v -fr *~ *.c *.h *.o $(PROGRAM)
