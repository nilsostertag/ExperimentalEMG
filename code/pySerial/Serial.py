import serial
import keyboard

# Open the serial connection to the device on port '/dev/ttyUSB0'
ser = serial.Serial('/dev/ttyUSB0')     
print("Start Serial")
print(ser.name)                         # Check which port was actually used

# Infinite loop to continuously read data from the serial connection
while True:
    # Read a line from the serial connection
    line = ser.readline()

    # Check if the read line is equal to "#"
    if line == "#":
        # Press and release the space key on the keyboard
        keyboard.press_and_release('space')

# Close the serial connection
ser.close()             

# Print "End" when the infinite loop is terminated
print("End")

