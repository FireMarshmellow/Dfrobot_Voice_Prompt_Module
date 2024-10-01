#include <HardwareSerial.h>

// Define RX and TX pins for the ESP32
#define RXD2 16
#define TXD2 17

// Initialize UART on Serial2 (use appropriate pins)
HardwareSerial mySerial(2);

// Helper function to send a command to the MP3 module
void send_command(uint8_t command[], size_t length) {
  for (size_t i = 0; i < length; i++) {
    mySerial.write(command[i]);
  }
}

// Playback Control Functions
void play_track(uint8_t track_number) {
  uint8_t command[] = {0x7E, 0x03, 0x00, 0x02, 0x00, track_number, 0xEF};
  send_command(command, sizeof(command));
}

void next_track() {
  uint8_t command[] = {0x7E, 0x01, 0x00, 0x02, 0x00, 0x00, 0xEF};
  send_command(command, sizeof(command));
}

void previous_track() {
  uint8_t command[] = {0x7E, 0x02, 0x00, 0x02, 0x00, 0x00, 0xEF};
  send_command(command, sizeof(command));
}

void pause_playback() {
  uint8_t command[] = {0x7E, 0x0E, 0x00, 0x02, 0x00, 0x00, 0xEF};
  send_command(command, sizeof(command));
}

void resume_playback() {
  uint8_t command[] = {0x7E, 0x0D, 0x00, 0x02, 0x00, 0x00, 0xEF};
  send_command(command, sizeof(command));
}

void stop_playback() {
  uint8_t command[] = {0x7E, 0x16, 0x00, 0x02, 0x00, 0x00, 0xEF};
  send_command(command, sizeof(command));
}

// Volume Control Functions
void set_volume(uint8_t level) {
  if (level > 30) {
    Serial.println("Volume level must be between 0 and 30.");
    return;
  }
  uint8_t command[] = {0x7E, 0x06, 0x00, 0x02, 0x00, level, 0xEF};
  send_command(command, sizeof(command));
}

void increase_volume() {
  uint8_t command[] = {0x7E, 0x04, 0x00, 0x02, 0x00, 0x00, 0xEF};
  send_command(command, sizeof(command));
}

void decrease_volume() {
  uint8_t command[] = {0x7E, 0x05, 0x00, 0x02, 0x00, 0x00, 0xEF};
  send_command(command, sizeof(command));
}

// Playback Mode Functions
void repeat_playback(uint8_t track_number) {
  uint8_t command[] = {0x7E, 0x08, 0x00, 0x02, 0x00, track_number, 0xEF};
  send_command(command, sizeof(command));
}

void random_playback() {
  uint8_t command[] = {0x7E, 0x18, 0x00, 0x02, 0x00, 0x00, 0xEF};
  send_command(command, sizeof(command));
}

// Folder/File Control Functions
void play_specific_folder(uint8_t folder_number, uint8_t file_number) {
  uint8_t command[] = {0x7E, 0x0F, 0x00, 0x02, folder_number, file_number, 0xEF};
  send_command(command, sizeof(command));
}

void composite_playback(uint8_t file_sequence[], size_t length) {
  uint8_t command[4 + length];
  command[0] = 0x7E;
  command[1] = 0x21;
  command[2] = 0x00;
  command[3] = length;
  for (size_t i = 0; i < length; i++) {
    command[4 + i] = file_sequence[i];
  }
  command[4 + length] = 0xEF;
  send_command(command, sizeof(command));
}

// Power Management Functions
void reset_module() {
  uint8_t command[] = {0x7E, 0x0C, 0x00, 0x02, 0x00, 0x00, 0xEF};
  send_command(command, sizeof(command));
}

void enter_low_power_mode() {
  uint8_t command[] = {0x7E, 0x0A, 0x00, 0x02, 0x00, 0x01, 0xEF};
  send_command(command, sizeof(command));
}

void setup() {
  // Begin Serial communication for debugging
  Serial.begin(115200);
  // Begin communication with the MP3 module on Serial2
  mySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);

  delay(1000); // Give the module some time to initialize
}

void loop() {
  Serial.println("MP3 Module Control Script");

  delay(1000);

  // Example usage:
  Serial.println("Setting volume to 20...");
  set_volume(5);
  delay(2000);

  Serial.println("Playing track 1...");
  play_track(3);
  delay(6000);

  Serial.println("Entering low power mode...");
  enter_low_power_mode();
  delay(5000);
}
