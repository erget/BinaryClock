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

install: $(EXE) | build/real-time-clock
	mv bin/* /usr/bin/
	head -n -1 /etc/rc.local > build/rc.local
	echo $(EXE_NAME) >> build/rc.local
	tail -n 1 /etc/rc.local >> build/rc.local
	cp build/rc.local /etc/rc.local

build/up-to-date: | build
	apt-get update
	apt-get upgrade
	apt-get dist-upgrade
	touch build/up-to-date

build/real-time-clock: | build/i2c
	echo rtc-ds1307 >> /etc/modules
	head -n -1 /etc/rc.local > build/rc.local
	echo "echo ds1307 0x68 > /sys/class/i2c-adapter/i2c-1/new_device" >> build/rc.local
	echo "hwclock -s" >> build/rc.local
	tail -n 1 /etc/rc.local >> build/rc.local
	cp build/rc.local /etc/rc.local
	touch $@

build/i2c: | build/i2c-tools-installed build/bcm-unblacklisted build/i2c-tools-added
	touch $@

build/i2c-tools-added: | build/up-to-date
	echo "i2c-dev" >> /etc/modules
	adduser pi i2c
	touch $@

build/bcm-unblacklisted: | build/i2c-tools-installed
	sed s/"blacklist spi-bcm2708"/"#blacklist spi-bcm2708"/g /etc/modprobe.d/raspi-blacklist.conf | sed s/"blacklist i2c-bcm2708"/"#blacklist i2c-bcm2708"/g > build/raspi-blacklist.conf
	mv build/raspi-blacklist.conf /etc/modprobe.d/raspi-blacklist.conf
	touch $@

build/i2c-tools-installed: | build/up-to-date
	apt-get install i2c-tools
	touch $@

build:
	mkdir $@

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
	rm -rf $(EXE) $(OBJECTS) build
	rmdir bin
