/*
Exemplo para testar o sensor de ultrassom.
*/

#include <Robo.h>

Robo robo(1);

void setup() {
  robo.roboSetup();
  Serial.begin(9600);
}

void loop() {
  Serial.print("Distância medida (cm)...: ");
  Serial.println(robo.lerDistancia());
}
