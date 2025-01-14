#################################################
## Filename:   makefile
## Author:     Daniel Guenther
## Sources:    Dr. J's makefile, but also partly inspired
##                by the makefile used in the JJAMBA lab
## Date:       2016-02-24
## Class:      CSCI 331
## Project:    Kitty Pirateer
## 
## Purpose: 
##    compile the project
###################################################

# compiler and flags
CC = g++
CFLAGS =
LDLIBS = -lSOIL -lglut -lGLU -lGL -lX11 -lm `sdl-config --cflags --libs`  -lSDL_mixer -std=c++11

# get list of source files
SRCDIR=src
OBJDIR=obj
CPP_FILES := $(wildcard $(SRCDIR)/*.cpp)
# generate object files from source files
OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

# Executeable targets
EXE=bin/game
      
#logs all errors in compilelog

#make the target
all: bin $(OBJDIR) $(SRC) $(EXE) 
log: 
	make all 2> compilelog

#set up directories needed
bin:
	mkdir $@
obj:
	mkdir $@

#executeables
$(EXE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

#object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

#
clean:
	rm -rf bin $(OBJDIR)
