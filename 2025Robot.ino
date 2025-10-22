#include <ps5Controller.h>

const int RED_PIN = 2;    // up
const int ORANGE_PIN = 4; // down
const int BLUE_PIN = 5;   // left
const int YELLOW_PIN = 21; // right

bool connected = false;

const int DEADZONE = 40;

// change MAC here for different controllers 
const char* TARGET_MAC = "ac:36:1b:28:34:c5"; // black ds

void onConnect() {
  if (!connected) {
    Serial.println("Controller paired!");
    connected = true;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(ORANGE_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);

  // initialise controller using MAC address
  ps5.begin(TARGET_MAC);
  ps5.attach(onConnect);

  Serial.print("Looking for PS5 controller, MAC Address: ");
  Serial.println(TARGET_MAC);

}

void loop() {
  if (!ps5.isConnected()) {
    connected = false; 
    return;
  }

  int x = ps5.LStickX(); // -128 to 127
  int y = ps5.LStickY(); // -128 to 127

  // reset LEDs
  digitalWrite(RED_PIN, LOW);
  digitalWrite(ORANGE_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);

  if (y < -DEADZONE) digitalWrite(RED_PIN, HIGH);       // up
  else if (y > DEADZONE) digitalWrite(ORANGE_PIN, HIGH); // down

  if (x < -DEADZONE) digitalWrite(BLUE_PIN, HIGH);       // left
  else if (x > DEADZONE) digitalWrite(YELLOW_PIN, HIGH); // right

  if (ps5.Up()) digitalWrite(RED_PIN, HIGH);
  if (ps5.Down()) digitalWrite(ORANGE_PIN, HIGH);
  if (ps5.Left()) digitalWrite(BLUE_PIN, HIGH);
  if (ps5.Right()) digitalWrite(YELLOW_PIN, HIGH);

  if (ps5.Square()) Serial.println("Square pressed");
  if (ps5.Cross())  Serial.println("Cross pressed");
  if (ps5.Circle()) Serial.println("Circle pressed");
  if (ps5.Triangle()) Serial.println("Triangle pressed");

  if (ps5.L1()) Serial.println("L1 pressed");
  if (ps5.R1()) Serial.println("R1 pressed");

  if (ps5.L2()) {
    Serial.printf("L2 val: %d\n", ps5.L2Value());
  }

  if (ps5.R2()) {
    Serial.printf("R2 val: %d\n", ps5.R2Value());
  }

  // Serial.printf("Stick: (%d, %d)\n", x, y);

  delay(50);  
}
