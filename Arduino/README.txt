=== Arduino ===

--> First steps under Ubuntu 12.10 - 32 bit
(tested and working also under Ubuntu 14.04 and Ubuntu 16.04 - 64 bit)

1) Install the IDE
sudo apt-get update
sudo apt-get install arduino arduino-core

2) You should see /dev/ttyACM0 (for Arduino UNO). The permissions at the moment are like:
crw-rw---- 1 root dialout 166, 0 mar 29 13:24 /dev/ttyACM0

3) Add your linux user (e.g. "fabio") to the "dialout" group:
sudo usermod -a -G dialout fabio

Check that you have been really added with the command:
fabio@fabio-laptop:~$ groups fabio
fabio : fabio adm dialout cdrom sudo dip plugdev lpadmin sambashare

4) Change the permissions on /dev/ttyACM0 to world readable and writeable:
sudo chmod a+rw /dev/ttyACM0
NB: perhaps this step is not really necessary: after rebooting it seems that the serial port is visible even without changing the permissions.

5) Reboot the computer

See also: http://blog.markloiseau.com/2012/05/install-arduino-ubuntu/


=== Fritzing ===
1) Download the *tar file from the website
2) Execute following commands (require sudo rights)

mkdir /usr/share/fritzing
mv fritzing-0.8.7b.linux.i386.tar.bz2 /usr/share/fritzing/
cd /usr/share/fritzing
tar xvjf fritzing-0.8.7b.linux.i386.tar.bz2
ln -s /usr/share/fritzing/fritzing-0.8.7b.linux.i386/Fritzing /usr/bin/fritzing

3) Execute the programm simply typing "fritzing" in the shell

3.1) In case of problems with Qt libraries
e.g.: cannot mix incompatible Qt library (version 0x40803) with this library (version 0x40805)

* Open /usr/share/fritzing/fritzing-0.8.7b.linux.i386/Fritzing with an editor
* LD_LIBRARY_PATH= points to libraries attached in the fritzing package. Change the path to local libraries:
LD_LIBRARY_PATH="usr/lib"

* Save the file and try again
