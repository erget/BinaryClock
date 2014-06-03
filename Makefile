CXXFLAGS=-O3 -std=c++11
EXE=bin/piclock
RPI_RGB=external/rpi-rgb-led-matrix
EXTERNAL_OBJECTS=$(RPI_RGB)/led-matrix.o $(RPI_RGB)/gpio.o $(RPI_RGB)/thread.o
OBJECTS=src/clock.o src/led-clock.o $(EXTERNAL_OBJECTS)
LDFLAGS=-lpthread

all: $(EXE)

bin/piclock: $(OBJECTS) src/main.cpp | bin
	$(CXX) $(CXXFLAGS) $(OBJECTS) src/main.cpp -o $@ $(LDFLAGS)
	
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
	rm -f $(EXE) $(OBJECTS)
	rmdir bin
	cd $(RPI_RGB) && $(MAKE) clean
