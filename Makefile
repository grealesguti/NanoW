
 CC=gcc
 CXX=g++
 LD=g++
 CXXFLAGS=-fdiagnostics-color -O2 -g $(shell geant4-config --cflags) -O2  -L/home/gmsh/lib -lgmsh
 LDLIBS=-Wl,--copy-dt-needed-entries -fdiagnostics-color -lm $(shell geant4-config --libs)  -L/home/gmsh/lib -lgmsh

PWD=$(shell pwd)

PREFIX?=$(HOME)/local
INSTALL_BIN=$(PREFIX)/build
INSTALL=install

SRC = src_G4

SOURCECXXG4 = $(wildcard *.cc)
OBJECTCXXG4 =  $(patsubst %, %,$(notdir $(SOURCECXXG4:.cc=.o))) 

SOURCECXXG4src = $(wildcard $(SRC)/*.cc)
$(info $$SOURCECXXG4src is [${SOURCECXXG4src}])
OBJECTCXXG4src =  $(patsubst %, $(SRC)/%,$(notdir $(SOURCECXXG4src:.cc=.o))) 

SOURCEFIN= $(SOURCECXXG4) $(SOURCECXXG4srcfilter)

OBJFIN = $(OBJECTCXXG4) $(OBJECTCXXG4src)
$(info $$SOURCEFIN is [${SOURCEFIN}])
$(info $$OBJFIN is [${OBJFIN}])

all: sim 

Makefile.dep:
	-$(CXX) $(CXXFLAGS) -MM $(SOURCEFIN) > Makefile.dep

-include Makefile.dep

sim: $(OBJFIN)

geant4:
	test ! -f geant4-v11.0.2.tar.gz && \
	curl -O -L http://cern.ch/geant4-data/releases/geant4-v11.0.2.tar.gz && \
	tar -xzvf geant4-v11.0.2.tar.gz || true
	cd geant4-v11.0.2 && \
	mkdir -p geant4-build && \
	mkdir -p geant4-install && \
	cd geant4-build && \
	cmake -DGEANT4_INSTALL_DATA=ON -DCMAKE_INSTALL_PREFIX=../geant4-install .. && \
	make -j4 && \
	make install

root:
	test ! -f root_v6.26.04.source.tar.gz && \
	curl -O -L https://root.cern/download/root_v6.26.04.source.tar.gz && \
	tar -xzvf root_v6.26.04.source.tar.gz || true
	cd root-6.26.04 && \
	mkdir -p root-build && \
	mkdir -p root-install && \
	cd root-build && \
	cmake -DCMAKE_INSTALL_PREFIX=../root-install .. && \
	make -j4 && \
	make install


install-deps: geant4 root
	@echo "Make sure to add the line source $(PWD)/geant4-v11.0.2/geant4-install/bin/geant4.sh to your ~/.bashrc file!"
	@echo "Make sure to add the line source $(PWD)/root-6.26.04/root-install/bin/thisroot.sh to your ~/.bashrc file!"

install:
	@mkdir -p $(INSTALL_BIN)
	$(INSTALL) sim $(INSTALL_BIN)

test: 
	@echo $(LDLIBS)

clean:
	rm -f $(OBJFIN) 

.PHONY: all clean geant4 root install-deps install test
