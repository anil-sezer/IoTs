void setup() {
  // Initialize the serial communication at 9600 baudrate
  Serial.begin(9600);

  // Wait for the serial port to initialize
  while (!Serial) {
    delay(10);
  }
  Serial.println("Serial talker arduino is ready");
}

void loop() {
  // Wait for a message from the Raspberry Pi
  if (Serial.available() > 0) {
    // Read the message
    String message = Serial.readString();

    // Print the message to the serial monitor
    Serial.println("Message from Raspberry Pi: " + message);

    // Send a response to the Raspberry Pi
    Serial.println("Hello, Raspberry Pi!");
  }
}
