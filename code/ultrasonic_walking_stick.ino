// Pin Definitions
const int trigPin = 9;     // HC-SR04 Trigger Pin
const int echoPin = 10;    // HC-SR04 Echo Pin
const int buzzerPin = 5;   // Active Buzzer Pin
const int motorPin = 6;    // Optional Vibration Motor or LED Pin

// Distance threshold in centimeters (100 cm = 1 meter)
const int maxDistance = 100; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  
  Serial.begin(9600); // For debugging distance in Serial Monitor
}

void loop() {
  long duration;
  int distance;

  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond HIGH pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin (timeout after 30,000 us to prevent freezing)
  duration = pulseIn(echoPin, HIGH, 30000);

  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Trigger alerts if an obstacle is within range (ignoring 0/invalid readings)
  if (distance > 0 && distance <= maxDistance) {
    // Map distance (2cm to 100cm) to beep delay (30ms to 500ms)
    int beepDelay = map(distance, 2, maxDistance, 30, 500);
    beepDelay = constrain(beepDelay, 30, 500);

    digitalWrite(buzzerPin, HIGH);
    digitalWrite(motorPin, HIGH);
    delay(50); // Short pulse duration

    digitalWrite(buzzerPin, LOW);
    digitalWrite(motorPin, LOW);
    delay(beepDelay); // Pause gets shorter as obstacle gets closer
  } else {
    // Keep alerts off when path is clear
    digitalWrite(buzzerPin, LOW);
    digitalWrite(motorPin, LOW);
    delay(50);
  }
}
