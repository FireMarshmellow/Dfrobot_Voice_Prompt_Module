from machine import Pin, UART
import time

# Initialize UART with the default baud rate of 9600
uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))

# Helper function to send a command to the MP3 module
def send_command(command):
    uart.write(bytes(command))

# Playback Control Functions
def play_track(track_number):
    command = [0x7E, 0x03, 0x00, 0x02, 0x00, track_number, 0xEF]
    send_command(command)

def next_track():
    command = [0x7E, 0x01, 0x00, 0x02, 0x00, 0x00, 0xEF]
    send_command(command)

def previous_track():
    command = [0x7E, 0x02, 0x00, 0x02, 0x00, 0x00, 0xEF]
    send_command(command)

def pause_playback():
    command = [0x7E, 0x0E, 0x00, 0x02, 0x00, 0x00, 0xEF]
    send_command(command)

def resume_playback():
    command = [0x7E, 0x0D, 0x00, 0x02, 0x00, 0x00, 0xEF]
    send_command(command)

def stop_playback():
    command = [0x7E, 0x16, 0x00, 0x02, 0x00, 0x00, 0xEF]
    send_command(command)

# Volume Control Functions
def set_volume(level):
    if level < 0 or level > 30:
        print("Volume level must be between 0 and 30.")
        return
    command = [0x7E, 0x06, 0x00, 0x02, 0x00, level, 0xEF]
    send_command(command)

def increase_volume():
    command = [0x7E, 0x04, 0x00, 0x02, 0x00, 0x00, 0xEF]
    send_command(command)

def decrease_volume():
    command = [0x7E, 0x05, 0x00, 0x02, 0x00, 0x00, 0xEF]
    send_command(command)

# Playback Mode Functions
def repeat_playback(track_number):
    command = [0x7E, 0x08, 0x00, 0x02, 0x00, track_number, 0xEF]
    send_command(command)

def random_playback():
    command = [0x7E, 0x18, 0x00, 0x02, 0x00, 0x00, 0xEF]
    send_command(command)

# Folder/File Control Functions
def play_specific_folder(folder_number, file_number):
    command = [0x7E, 0x0F, 0x00, 0x02, folder_number, file_number, 0xEF]
    send_command(command)

def composite_playback(file_sequence):
    # file_sequence is a list of file numbers to play, e.g., [0x01, 0x03, 0x02]
    length = len(file_sequence)
    command = [0x7E, 0x21, 0x00, length] + file_sequence + [0xEF]
    send_command(command)

# Power Management Functions
def reset_module():
    command = [0x7E, 0x0C, 0x00, 0x02, 0x00, 0x00, 0xEF]
    send_command(command)

def enter_low_power_mode():
    command = [0x7E, 0x0A, 0x00, 0x02, 0x00, 0x01, 0xEF]
    send_command(command)

try:
    print("MP3 Module Control Script")
    time.sleep(1)

    # Example: Play a specific track
    print("Playing track 1...")
    play_track(1)
    time.sleep(3)

    # Example: Set volume to 20
    print("Setting volume to 20...")
    set_volume(20)
    time.sleep(2)

    # Example: Enter low power mode
    print("Entering low power mode...")
    enter_low_power_mode()
    time.sleep(1)

except Exception as e:
    print("Error occurred:", e)
