#!/usr/bin/python3
#
# Read serial port and print to file
import serial
import time

serialPort = '/dev/ttyACM0'
serialBaud = 9600

serialFound = False

while not serialFound:
	
	# Try to connect to the serial port
	try:
		ser = serial.Serial(serialPort, serialBaud)
		print("Reading serial port {}. Interrupt with Ctrl-C".format(serialPort))
		serialFound = True
	
	# If the port is not available, catch the exception
	# and re-try after a few seconds
	except serial.serialutil.SerialException:
		print("Serial port {} not found. Retrying in 10 seconds...".format(serialPort))
		time.sleep(10)

timestamp = time.strftime("%Y-%m-%d_%H-%M", time.localtime())
outFile = open('DHT22_output_{}.txt'.format(timestamp),'w')

# Read the serial port and print to file
try:
	while serialFound:
		readLine = ser.readline().decode('UTF-8')
	
		# Read the status, temperature and humidity from
		# serial port, removing commas
		status      = readLine.split()[0].replace(',','')
		temperature = readLine.split()[1].replace(',','')
		humidity    = readLine.split()[2].replace(',','')
	
		# If the sensor works properly, write the output to a file
		if status == 'OK':
			outFile.write('{0},{1}\n'.format(temperature, humidity))

except KeyboardInterrupt:
	pass


