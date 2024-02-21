from pynput.keyboard import Key, Controller
import serial

keyboard = Controller()

# Open the serial connection to the device on port '/dev/ttyUSB0'
ser = serial.Serial('/dev/ttyUSB0', 9600)  # Assuming 9600 is the baud rate
print("Start Serial")

while True:
    line = ser.readline().decode('utf-8').strip()
    if line == "#":
        keyboard.press(Key.space)
        keyboard.release(Key.space)
        print("Space pressed")

