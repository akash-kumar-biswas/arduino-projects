int tp = 10;
int ep = 6;

long duration;
float distance, min_dist = 10000, max_dist = 0;
unsigned long lastReportTime = 0;
int obstacleCount = 0;
unsigned long programExeTime = 0;
bool objectPresent = false; 
float detectionThreshold = 40;

void setup() {
  pinMode(tp, OUTPUT);
  pinMode(ep, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(tp, LOW);
  delayMicroseconds(3);
  digitalWrite(tp, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp, LOW);

  duration = pulseIn(ep, HIGH);
  distance = (0.017 * duration);
  if (distance != 0) {
    if (distance > max_dist)
      max_dist = distance;
    if (distance < min_dist)
      min_dist = distance;

    if (distance <= detectionThreshold && !objectPresent) {
      obstacleCount++;
      objectPresent = true;
    } 
    else if (distance > detectionThreshold) {
      objectPresent = false;
    }
  }

  programExeTime = millis();
  if (programExeTime - lastReportTime >= 10000) {
    Serial.println("------ For Last 10s ------");
    Serial.println("Min. dist: " + String(min_dist));
    Serial.println("Max. dist: " + String(max_dist));
    Serial.println("Obstacles count: " + String(obstacleCount));
    Serial.println("------------------------");

    min_dist = 1000;
    max_dist = 0;
    obstacleCount = 0;
    lastReportTime = programExeTime;
  }

  delay(100);
}
