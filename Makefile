CXXFLAGS=-O3 -std=c++0x
EXE_NAME=piclock
EXE=bin/$(EXE_NAME)
RPI_RGB=external/rpi-rgb-led-matrix
EXTERNAL_OBJECTS=$(RPI_RGB)/led-matrix.o $(RPI_RGB)/gpio.o $(RPI_RGB)/thread.o
OBJECTS=src/clock.o src/led-clock.o $(EXTERNAL_OBJECTS)
LDFLAGS=-lpthread

.PHONY: clean install

all: $(EXE)

$(EXE): $(OBJECTS) src/main.cpp | bin
	$(CXX) $(CXXFLAGS) $(OBJECTS) src/main.cpp -o $@ $(LDFLAGS)

install: $(EXE)
	mv bin/* /usr/bin/

bin:
	mkdir bin

src/led-clock.o: src/led-clock.cpp src/led-clock.hpp
	$(CXX) $(CXXFLAGS) -c src/led-clock.cpp -o $@

src/clock.o: src/clock.cpp src/clock.hpp
	$(CXX) $(CXXFLAGS) -c src/clock.cpp -o $@

$(RPI_RGB)/led-matrix.o: $(RPI_RGB)/led-matrix.cc $(RPI_RGB)/led-matrix.h
	cd $(RPI_RGB) && $(MAKE)
	
$(RPI_RGB)/gpio.o: $(RPI_RGB)/gpio.cc $(RPI_RGB)/gpio.h
	cd $(RPI_RGB) && $(MAKE)

clean:
	cd $(RPI_RGB) && $(MAKE) clean
	rm -rf $(EXE) $(OBJECTS) bin
