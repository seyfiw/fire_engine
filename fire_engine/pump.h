
void pump_close();

void pump_setup(){
  pinMode(PUMP_PIN, OUTPUT);
  pump_close();
}

void pump_open() {
  digitalWrite(PUMP_PIN, LOW);
}

void pump_close() {
  digitalWrite(PUMP_PIN, HIGH);
}
