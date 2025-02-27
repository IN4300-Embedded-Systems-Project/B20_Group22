#define FRONT_LEDS_PIN  2  
#define WHEEL_LEDS_PIN  4

bool frontLedsState = false;

void setupLEDs() {
    pinMode(FRONT_LEDS_PIN, OUTPUT);
    pinMode(WHEEL_LEDS_PIN, OUTPUT);
    Serial.begin(115200);
}

void toggleFrontLEDs() {
  frontLedsState = !frontLedsState;
  digitalWrite(FRONT_LEDS_PIN, frontLedsState ? HIGH : LOW);
  Serial.println("Front LEDs Toggled");
}

void toggleWheelLEDs() {
  wheelLedsState = !wheelLedsState;
  digitalWrite(WHEEL_LEDS_PIN, wheelLedsState ? HIGH : LOW);
  Serial.println("Wheel LEDs Toggled");
}