#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 9
#define ENB 6

#define BASE_SPEED 220
#define TURN_SPEED 150

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopMotors();
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    switch (cmd) {
      case 'F':
        forward(BASE_SPEED, BASE_SPEED);
        break;
      case 'B':
        backward(BASE_SPEED, BASE_SPEED);
        break;
      case 'L':
        forward(TURN_SPEED, BASE_SPEED);
        break;
      case 'R':
        forward(BASE_SPEED, TURN_SPEED);
        break;
      case 'S':
        stopMotors();
        break;
    }
  }
}

void forward(int leftSpeed, int rightSpeed) {
  Serial.println("Going Forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
}

void backward(int leftSpeed, int rightSpeed) {
  Serial.println("Going Backward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
}

void stopMotors() {
  Serial.println("Stopping");
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
