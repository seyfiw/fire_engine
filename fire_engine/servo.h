
#include <Servo.h>

bool select = true;
int servoPosition = 0;
unsigned long lastServoTime = 0;
unsigned long servoDelay = 30;

Servo servo;

void servo_setup() {
  servo.attach(SERVO_PIN);
  servo.write(SERVO_POSITION_CENTER);
}

void servo_run() {
  if ((millis() - lastServoTime) >= servoDelay) {
    lastServoTime = millis();

    if (servoPosition == 0) {
      servoPosition = SERVO_POSITION_CENTER;
      select = true;
    } else if (servoPosition >= SERVO_POSITION_LEFT) {
      select = false;
    } else if (servoPosition <= SERVO_POSITION_RIGHT) {
      select = true;
    }

    if (select) {
      servoPosition++;
    } else {
      servoPosition--;
    }
    servo.write(servoPosition);
  }
}

void servo_set_position() {
  select = true;
  servoPosition = 0;
  servo.write(SERVO_POSITION_CENTER);
}
