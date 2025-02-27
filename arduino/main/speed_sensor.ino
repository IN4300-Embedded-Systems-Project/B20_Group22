#define SENSOR_LEFT 34
#define SENSOR_RIGHT 35

#define WHEEL_CIRCUMFERENCE 21.0
#define TICK_PER_REVOLUTION 20 

volatile int leftTicks = 0;
volatile int rightTicks = 0;

void IRAM_ATTR countLeftTicks() {
    leftTicks++;
}

void IRAM_ATTR countRightTicks() {
    rightTicks++;
}

int getCurrentTicks() {
    return (leftTicks + rightTicks) / 2;
}

float getDistanceTraveled() {
    float leftDistance = (leftTicks / (float)TICK_PER_REVOLUTION) * WHEEL_CIRCUMFERENCE;
    float rightDistance = (rightTicks / (float)TICK_PER_REVOLUTION) * WHEEL_CIRCUMFERENCE;
    return (leftDistance + rightDistance) / 2.0;
}

void resetDistance() {
  leftTicks = 0;
  rightTicks = 0;
}

void updateSpeedSensors() {
    Serial.print("Distance Traveled: ");
    Serial.println(getDistanceTraveled());
}

void setupSpeedSensors() {
    pinMode(SENSOR_LEFT, INPUT);
    pinMode(SENSOR_RIGHT, INPUT);
    attachInterrupt(digitalPinToInterrupt(SENSOR_LEFT), countLeftTicks, RISING);
    attachInterrupt(digitalPinToInterrupt(SENSOR_RIGHT), countRightTicks, RISING);
}
