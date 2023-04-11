#include <Servo.h>
#define POT A0


Servo miServo;

void setup() {
  // put your setup code here, to run once:

  miServo.attach(9);

}

void loop() {
  // put your main code here, to run repeatedly:

  miServo.write(0);
  delay(1000);
  miServo.write(90);
  delay(1000);
  miServo.write(180);
  delay(1000);
  
  miServo.write(90);
  delay(1000);
}
