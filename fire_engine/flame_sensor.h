
void flame_sensor_setup() {
  pinMode(FLAME_DIGITAL_PIN_1, INPUT);
  pinMode(FLAME_DIGITAL_PIN_2, INPUT);
  pinMode(FLAME_DIGITAL_PIN_3, INPUT);
  pinMode(FLAME_DIGITAL_PIN_4, INPUT);
  pinMode(FLAME_DIGITAL_PIN_5, INPUT);
}

flameDigitalValue flame_digital_read() {
  flameDigitalValue fdv;
  
  fdv.f_1 = digitalRead(FLAME_DIGITAL_PIN_1);
  fdv.f_2 = digitalRead(FLAME_DIGITAL_PIN_2);
  fdv.f_3 = digitalRead(FLAME_DIGITAL_PIN_3);
  fdv.f_4 = digitalRead(FLAME_DIGITAL_PIN_4);
  fdv.f_5 = digitalRead(FLAME_DIGITAL_PIN_5);
  
  return fdv;
}

flameAnalogValue flame_analog_read() {
  flameAnalogValue fav;
  
  fav.f_1 = analogRead(FLAME_ANALOG_PIN_1);
  fav.f_2 = analogRead(FLAME_ANALOG_PIN_2);
  fav.f_3 = analogRead(FLAME_ANALOG_PIN_3);
  fav.f_4 = analogRead(FLAME_ANALOG_PIN_4);
  fav.f_5 = analogRead(FLAME_ANALOG_PIN_5);
  
  return fav;
}
