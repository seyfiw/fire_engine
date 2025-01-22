
void motorStop(void);

void motor_setup() {
  pinMode(ENABLE_A, OUTPUT);
  pinMode(PIN_A_1, OUTPUT);
  pinMode(PIN_A_2, OUTPUT);

  pinMode(ENABLE_B, OUTPUT);
  pinMode(PIN_B_1, OUTPUT);
  pinMode(PIN_B_2, OUTPUT);

  motorStop();
}

void motorMoveForward(int speedControl) {
  digitalWrite(PIN_A_1, LOW);
  digitalWrite(PIN_A_2, HIGH);

  digitalWrite(PIN_B_1, LOW);
  digitalWrite(PIN_B_2, HIGH);

  analogWrite(ENABLE_A, speedControl);
  analogWrite(ENABLE_B, speedControl);
}

void motorMoveLeft(int speedControl) {
  digitalWrite(PIN_A_1, LOW);
  digitalWrite(PIN_A_2, HIGH);

  digitalWrite(PIN_B_1, HIGH);
  digitalWrite(PIN_B_2, LOW);

  analogWrite(ENABLE_A, speedControl);
  analogWrite(ENABLE_B, speedControl);
}

void motorMoveRight(int speedControl) {
  digitalWrite(PIN_A_1, HIGH);
  digitalWrite(PIN_A_2, LOW);

  digitalWrite(PIN_B_1, LOW);
  digitalWrite(PIN_B_2, HIGH);

  analogWrite(ENABLE_A, speedControl);
  analogWrite(ENABLE_B, speedControl);
}

void motorMoveBack(int speedControl) {
  digitalWrite(PIN_A_1, HIGH);
  digitalWrite(PIN_A_2, LOW);

  digitalWrite(PIN_B_1, HIGH);
  digitalWrite(PIN_B_2, LOW);

  analogWrite(ENABLE_A, speedControl);
  analogWrite(ENABLE_B, speedControl);
}

void motorStop() {
  digitalWrite(PIN_A_1, LOW);
  digitalWrite(PIN_A_2, LOW);

  digitalWrite(PIN_B_1, LOW);
  digitalWrite(PIN_B_2, LOW);

  analogWrite(ENABLE_A, 0);
  analogWrite(ENABLE_B, 0);
}
