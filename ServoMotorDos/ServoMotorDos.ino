#include <Servo.h>
#define POT A0


Servo miServo;

int valor;
int angulo;

void setup() {
  // put your setup code here, to run once:

  miServo.attach(9);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  valor = analogRead(POT);
  Serial.print("valor: ");
  Serial.print(valor);

  angulo = map(valor, 0, 1023, 0, 180);

  Serial.print(", angulo: ");
  Serial.print(angulo);
  miServo.write(angulo);

  delay(15);
}
