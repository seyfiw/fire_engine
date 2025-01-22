
#include <avr/wdt.h>

#include "config.h"
#include "struct.h"
#include "flame_sensor.h"
#include "motor.h"
#include "pump.h"
#include "servo.h"

unsigned long lastErrorTime = 0;
unsigned long erroreDelay = 2000;

unsigned long lastStartTime = 0;
unsigned long startDelay = 1000;

int count = 0, verifyCount = 0;
bool distanceVerify = false, distanceState = false;

int whileState = false;
int error = 9999;

void setup() {
  //    Serial.begin(9600);
  
  wdt_enable(WDTO_2S);
  
  flame_sensor_setup();
  motor_setup();
  pump_setup();
  servo_setup();
}

void loop() {
  //  flameDigitalValue fdv = flame_digital_read();
  //  Serial.println("flame digital sensor: | " + String(fdv.f_1) + " | " + String(fdv.f_2) + " | " + String(fdv.f_3) + " | " + String(fdv.f_4) + " | " + String(fdv.f_5) + " | ");
  //  delay(100);

  //  flameAnalogValue fav = flame_analog_read();
  //  Serial.println("flame digital sensor: | " + String(fav.f_1) + " | " + String(fav.f_2) + " | " + String(fav.f_3) + " | " + String(fav.f_4) + " | " + String(fav.f_5) + " | ");
  //  delay(100);

  wdt_reset();

  flameErrorCalculate();

  if (error == 9999) {
    pump_close();
    motorStop();
  } else if (error >= -4 && error < -1) {
    motorMoveRight(MOVE_SPEED);
  } else if (error > 1 && error <= 4) {
    motorMoveLeft(MOVE_SPEED);
  } else if (error == -1 || error == 0 || error == 1) {
    whileState = true;
    motorMoveForward(MOVE_SPEED);
    delay(MOVE_FORWARD_DELAY);
    while (whileState) {
      int distance = flameDistanceCalculate();
      if (distanceState == false) {
        if ((distance >= 800 && distance <= 1023)) {
          if (verifyCount == 20) {
            distanceVerify = true;
            distanceState = true;
          }
          verifyCount ++;
        } else {
          verifyCount = 0;
          distanceVerify = false;
          distanceState = false;
        }
      }

      if (distanceVerify && distanceState) {
        motorStop();
        servo_run();
        pump_open();
      }

      if (distance >= 0 && distance < 200) {
        if (millis() > lastStartTime) {
          lastStartTime = millis() + startDelay;
          count++;
          if (count == 3) {
            distanceVerify = true;
            distanceState = true;
          }
          if (count == 5) {
            pump_close();
            servo_set_position();
            delay(100);
            motorStop();

            error = 9999;
            whileState = false;
            count = 0;

            verifyCount = 0;
            distanceVerify = false;
            distanceState = false;

            return;
          }
        }
      } else {
        lastStartTime = millis();
        count = 0;
      }
    }
  }
}

int flameDistanceCalculate() {
  flameAnalogValue fav = flame_analog_read();
  return fav.f_3;
}

void flameErrorCalculate() {
  flameDigitalValue fdv = flame_digital_read();

  int errCheck;
  if (fdv.f_1 == LOW && fdv.f_2 == LOW && fdv.f_3 == LOW && fdv.f_4 == LOW && fdv.f_5 == HIGH) {            // 0 0 0 0 1
    error = 4;
    errCheck = error;
  } else if (fdv.f_1 == LOW && fdv.f_2 == LOW && fdv.f_3 == LOW && fdv.f_4 == HIGH && fdv.f_5 == HIGH) {    // 0 0 0 1 1
    error = 3;
    errCheck = error;
  } else if (fdv.f_1 == LOW && fdv.f_2 == LOW && fdv.f_3 == LOW && fdv.f_4 == HIGH && fdv.f_5 == LOW) {     // 0 0 0 1 0
    error = 2;
    errCheck = error;
  } else if (fdv.f_1 == LOW && fdv.f_2 == LOW && fdv.f_3 == HIGH && fdv.f_4 == HIGH && fdv.f_5 == LOW) {    // 0 0 1 1 0
    error = 2;
    errCheck = error;
  } else if (fdv.f_1 == LOW && fdv.f_2 == LOW && fdv.f_3 == HIGH && fdv.f_4 == LOW && fdv.f_5 == LOW) {     // 0 0 1 0 0
    error = 0;
    errCheck = error;
  } else if (fdv.f_1 == LOW && fdv.f_2 == HIGH && fdv.f_3 == HIGH && fdv.f_4 == HIGH && fdv.f_5 == LOW) {   // 0 1 1 1 0
    error = 0;
    errCheck = error;
  }  else if (fdv.f_1 == HIGH && fdv.f_2 == HIGH && fdv.f_3 == HIGH && fdv.f_4 == HIGH && fdv.f_5 == LOW) { // 1 1 1 1 0
    error = 0;
    errCheck = error;
  } else if (fdv.f_1 == LOW && fdv.f_2 == HIGH && fdv.f_3 == HIGH && fdv.f_4 == HIGH && fdv.f_5 == HIGH) {  // 0 1 1 1 1
    error = 0;
    errCheck = error;
  } else if (fdv.f_1 == HIGH && fdv.f_2 == HIGH && fdv.f_3 == HIGH && fdv.f_4 == HIGH && fdv.f_5 == HIGH) {  // 1 1 1 1 1
    error = 0;
    errCheck = error;
  } else if (fdv.f_1 == LOW && fdv.f_2 == HIGH && fdv.f_3 == HIGH && fdv.f_4 == LOW && fdv.f_5 == LOW) {    // 0 1 1 0 0
    error = -2;
    errCheck = error;
  } else if (fdv.f_1 == LOW && fdv.f_2 == HIGH && fdv.f_3 == LOW && fdv.f_4 == LOW && fdv.f_5 == LOW) {     // 0 1 0 0 0
    error = -2;
    errCheck = error;
  } else if (fdv.f_1 == HIGH && fdv.f_2 == HIGH && fdv.f_3 == LOW && fdv.f_4 == LOW && fdv.f_5 == LOW) {    // 1 1 0 0 0
    error = -3;
    errCheck = error;
  } else if (fdv.f_1 == HIGH && fdv.f_2 == LOW && fdv.f_3 == LOW && fdv.f_4 == LOW && fdv.f_5 == LOW) {     // 1 0 0 0 0
    error = -4;
    errCheck = error;
  } else {
    errCheck = 9999;
  }

  if (errCheck >= -4 && errCheck <= 4) {
    lastErrorTime = millis();
  }

  if ((millis() - lastErrorTime) >= erroreDelay) { 
    error = 9999;
  }
}
