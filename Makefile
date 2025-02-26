CC=gcc
CXX=g++
LD=g++
CXXFLAGS=-fdiagnostics-color -O2 -g $(shell geant4-config --cflags) -I/home/gmsh/include -I$(shell geant4-config --prefix)/include
LDLIBS=-Wl,--copy-dt-needed-entries -fdiagnostics-color -lm $(shell geant4-config --libs) -L/home/gmsh/lib -lgmsh

PWD=$(shell pwd)

PREFIX?=$(HOME)/local
INSTALL_BIN=$(PREFIX)/build
INSTALL=install

SRC = src_G4

# Collect all source files
SOURCECXXG4 = $(wildcard *.cc)
OBJECTCXXG4 = $(patsubst %, %,$(notdir $(SOURCECXXG4:.cc=.o))) 

SOURCECXXG4src = $(wildcard $(SRC)/*.cc)
$(info $$SOURCECXXG4src is [${SOURCECXXG4src}])
OBJECTCXXG4src =  $(patsubst %, $(SRC)/%,$(notdir $(SOURCECXXG4src:.cc=.o))) 

SOURCEFIN= $(SOURCECXXG4) $(SOURCECXXG4src)
OBJFIN = $(OBJECTCXXG4) $(OBJECTCXXG4src)
$(info $$SOURCEFIN is [${SOURCEFIN}])
$(info $$OBJFIN is [${OBJFIN}])

# Enable GEANT4 analysis module
#GEANT4_ANALYSIS_FLAGS := $(shell geant4-config --analysis)

# Targets
all: sim 

# This rule is for generating the dependencies for the source files
Makefile.dep:
	-$(CXX) $(CXXFLAGS) -MM $(SOURCECXXG4) > Makefile.dep

# Compilation rule
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking rule
sim: $(OBJFIN)
	$(LD) $(OBJFIN) -o $@ $(LDLIBS) $(GEANT4_ANALYSIS_FLAGS)

# Install rule (if required)
install: sim
	$(INSTALL) sim $(INSTALL_BIN)

clean:
	rm -f $(OBJFIN) sim Makefile.dep

# Include generated dependencies
-include Makefile.dep
