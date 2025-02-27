#define DISTANCE_PER_STEP 50  // Adjust based on calibration
#define TICKS_PER_90_DEGREE 30

void handleMove(String path) {
    Serial.print("Moving along path: ");
    Serial.println(path);

    int i = 0;
    while (i < path.length()) {
        resetDistance();
        delay(1000); 

        char command = path[i];  // Get direction (F, B, L, R)
        i++;

        int steps = 0;
        
        // Extract numeric steps if present
        while (i < path.length() && isDigit(path[i])) {
            steps = steps * 10 + (path[i] - '0');  
            i++;
        }

        int targetDistance = steps * DISTANCE_PER_STEP;

        if (command == 'F') {
            Serial.print("Moving Forward: "); Serial.println(targetDistance);
            moveForward();
         
            // Wait until the target distance is reached
            while (getDistanceTraveled() < targetDistance) {
                delay(1); 
            }

            stopMotors();
        } 
        else if (command == 'L') {
            Serial.println("Turning Left");

            int targetTicks = getCurrentTicks() + TICKS_PER_90_DEGREE;

            turnLeft();

            while (getCurrentTicks() < targetTicks) {
                delay(1);
            }
           
            stopMotors();
        } 
        else if (command == 'R') {
            Serial.println("Turning Right");
            
            int targetTicks = getCurrentTicks() + TICKS_PER_90_DEGREE;

            turnRight();

            while (getCurrentTicks() < targetTicks) {
                delay(1);
            }
           
            stopMotors();
        } 
        else {
            Serial.print("Unknown Command: "); Serial.println(command);
        }
    }
}

void handleStop() {
    Serial.println("Stopped.");
    stopMotors();
}

void handleLEDs(String type) {
  Serial.println("LEDs toggled");

  if(type == "front") toggleFrontLEDs();
  else if(type == "wheel") toggleWheelLEDs();
}

void setup() {
    Serial.begin(115200);
    setupSpeedSensors();    
    setupMotors();    
    setupWiFi(handleMove, handleStop);      
}

void loop() {
    handleWiFiRequests();
}
