//Definimos los pines donde tenemos conectadas las bobinas
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11


// Secuencia de pasos (par maximo)
int paso [4][4] = {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1},
};

void setup() {
  // Todos los pines en modo salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i<4; i++){

    digitalWrite(IN1, paso[i][0]);
    digitalWrite(IN2, paso[i][1]);
    digitalWrite(IN3, paso[i][2]);
    digitalWrite(IN4, paso[i][3]);
    delay(10);
  }
}
