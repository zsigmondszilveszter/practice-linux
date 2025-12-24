# headers location
IDIR =includes
CC=gcc
MKDIR=mkdir
CFLAGS=-I$(IDIR)
LIBS=-pthread

# source files location
SDIR=src
# store object files in this directory
ODIR=$(SDIR)/obj
# location for library functions
LDIR =$(SDIR)/lib

_DEPS = general_includes.h tcp_init.h tcp_networking.h thread_handler.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tcp_init.o tcp_networking.o main.o thread_handler.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# every object file depends on the certain .c file and the header files too
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

# the first and default make rule, this links the object files and builds the ELF file with the name of the rule
server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

#
$(OBJ): | CreateObjDir

.PHONY: clean

# clean the project directory from the object files and temporary stuffs
clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ core $(IDIR)/*~
	rm -f server_*

.PHONY: CreateObjDir
# create object directory if it doesn't exist
CreateObjDir:
	@$(MKDIR) -p $(ODIR)
