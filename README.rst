=================
BinaryClock 1.0.0
=================

Implementations of binary clocks, both as a hardware prototype for a standalone
device and for the Raspberry Pi with an LED array. A full description of the
library, how to build the device physically, and suggestions on how to extend
it are available on Stackable_:

The program works by parsing a string, converting it into colors and setting
the corresponding pixels in the LED array to those colors. For details see the
source code.

Author: Daniel Lee (erget2005 <at> gmail.com)

############
Installation
############

The following instructions include how to set up a hardware clock. If you are
not using one, feel free to skip them. The instructions assume you're working
with a Raspberry Pi Revision 2 board running Raspian and using the RTC Pi
Realtime Clock module from AB Electronics. If this doesn't precisely fit your
setup you can find more specific information at the original instructions_.

Installing I2C
""""""""""""""

The RTC depends on I2C. You can install it like this::

    # Install and configure I2C
    sudo apt-get install i2c-tools

    # Now comment out the following lines from
    # /etc/modprobe.d/raspi-blacklist.conf with the router symbol:
    # blacklist spi-bcm2708
    # blacklist i2c-bcm2708

    # Set the Pi to start I2C automatically by adding the following line to
    # /etc/modules:
    i2c-dev

    # Add your user to the i2c group so it can run I2C tools (in this case
    # we're working with the user pi)
    sudo adduser pi i2c

    # Now get the system up to date and reboot
    sudo apt-get update
    sudo apt-get upgrade
    sudo apt-get dist-upgrade
    sudo reboot

Setting the RTC's time
""""""""""""""""""""""

Setup the RTC for the first time like this::

    sudo i2cdetect -y 1
    # If the Pi detects the clock correctly, you should see it register it on
    # channel 68, which looks like this:
    # 0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
    # 00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
    # 10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
    # 20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
    # 30: -- -- -- -- -- -- -- -- -- -- -- UU -- -- -- -- 
    # 40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
    # 50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
    # 60: -- -- -- -- -- -- -- -- 68 -- -- -- -- -- -- -- 
    # 70: -- -- -- -- -- -- -- --      

    # Register the clock with the kernel. Note that in order to do this you
    # *must* drop into a root shell - skipping this step will result in a
    # permission denied error.
    sudo su
    echo ds1307 0x68 > /sys/class/i2c-adapter/i2c-1/new_device
    exit

    # Now you should be able to interact with the Pi. Check the time stored on
    # the RTC like this:
    sudo hwclock -r

    # Make sure the date on your Pi is set correctly (e.g. using the UNIX date
    # utility). You can check that like this:
    date
    # If it's incorrect, you can pass a string to date like this to set it:
    # date -s $CORRECT_DATE
    # Once that's done, set the RTC's clock
    sudo hwclock -w

Setting the Pi's clock from the RTC on boot
"""""""""""""""""""""""""""""""""""""""""""

Now the RTC is usable. Configure the Pi to get its time from the RTC on boot
like this::

    # Add the following line to /etc/modules:
    # rtc-ds1307

    # Add the following lines to the end of /etc/rc.local but before the last
    # line ("exit 0"):
    # echo ds1307 0x68 > /sys/class/i2c-adapter/i2c-1/new_device
    # hwclock -s

Now, on the next reboot the Pi should pull its time from the RTC.

Compiling and installing BinaryClock
""""""""""""""""""""""""""""""""""""

Before compiling ``BinaryClock``, make sure you have the dependency loaded. You
can do that and then compile and install the program like this::

    git submodule init
    git submodule update
    sudo make install

Starting BinaryClock on boot
""""""""""""""""""""""""""""

In order to start ``BinaryClock`` on boot, add the following line to
``/etc/rc.local`` before the line with ``exit 0``::

    piclock &

.. _Stackable: http://erget.wordpress.com/2014/07/13/building-a-binary-led-clock-based-on-raspberry-pi/
.. _instructions: https://www.abelectronics.co.uk/products/3/Raspberry-Pi/15/RTC-Pi-Real-time-Clock-Module
