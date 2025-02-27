#define MOTOR_LEFT_PWM 5
#define MOTOR_RIGHT_PWM 23
#define MOTOR_LEFT_IN1 18
#define MOTOR_LEFT_IN2 19 
#define MOTOR_RIGHT_IN1 21
#define MOTOR_RIGHT_IN2 22


void setupMotors() {
    pinMode(MOTOR_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_LEFT_IN2, OUTPUT);
    pinMode(MOTOR_RIGHT_IN1, OUTPUT);
    pinMode(MOTOR_RIGHT_IN2, OUTPUT);
    pinMode(MOTOR_LEFT_PWM, OUTPUT);
    pinMode(MOTOR_RIGHT_PWM, OUTPUT);
}

void moveForward() {
    Serial.println("Moving Forward");

    int speed = 100;
    analogWrite(MOTOR_LEFT_PWM, speed);
    analogWrite(MOTOR_RIGHT_PWM, speed);

    digitalWrite(MOTOR_LEFT_IN1, HIGH); //18

    digitalWrite(MOTOR_LEFT_IN2, LOW);

    digitalWrite(MOTOR_RIGHT_IN1, LOW);
    digitalWrite(MOTOR_RIGHT_IN2, HIGH);
}

void turnRight() {
    Serial.println("Turn Left");

    int speed = 100;
    analogWrite(MOTOR_LEFT_PWM, speed);
    analogWrite(MOTOR_RIGHT_PWM, speed);
    digitalWrite(MOTOR_LEFT_IN1, HIGH);
    digitalWrite(MOTOR_LEFT_IN2, LOW);
    digitalWrite(MOTOR_RIGHT_IN1, HIGH);
    digitalWrite(MOTOR_RIGHT_IN2, LOW);
}

void turnLeft() {
    Serial.println("Turn Right");
    int speed = 100;
    analogWrite(MOTOR_LEFT_PWM, speed);
    analogWrite(MOTOR_RIGHT_PWM, speed);
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, HIGH);
    digitalWrite(MOTOR_RIGHT_IN1, LOW);
    digitalWrite(MOTOR_RIGHT_IN2, HIGH);
}

void stopMotors() {
    Serial.println("Stop motors");
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, LOW);
    digitalWrite(MOTOR_RIGHT_IN1, LOW);
    digitalWrite(MOTOR_RIGHT_IN2, LOW);
}
