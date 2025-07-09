const int sensorPin = 2;
const int motorPin = 8;
const int buzzerPin = 9;

long time; // Variable to store time when eyes are closed

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT); // Set buzzerPin as an OUTPUT
  digitalWrite(motorPin, HIGH); // Turn on the motor initially
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Check if the IR sensor (sensorPin) is triggered (LOW means it's triggered)
  if (!digitalRead(sensorPin)) {
    if (time == 0) { // If time is not recorded, record the current time
      time = millis();
    }

    // Keep checking if the IR sensor is still triggered
    while (!digitalRead(sensorPin)) {
      // When the IR sensor is triggered, turn on the motor and wait for 1 second
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      digitalWrite(motorPin, HIGH);
      delay(1000);
    }
  } else {
    // If the IR sensor is not triggered (eyes open)
    if (time != 0) { // If eyes were previously closed
      long elapsedTime = millis() - time; // Calculate the elapsed time

      if (elapsedTime >= 5000) { // If eyes were closed for 5 seconds or more
        digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
      }

      if (elapsedTime >= 6000) { // If eyes were closed for 6 seconds or more
        digitalWrite(motorPin, LOW); // Turn off the motor
        time = 0; // Reset the time
      }
    }
  }
}
