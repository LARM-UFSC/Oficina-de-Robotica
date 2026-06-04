/*
Exemplo para testar os motores do robô.

Movimentos:
  -> frente
  -> trás
  -> direita (virar e girar)
  -> esquerda (virar e girar)
*/

#include <Robo.h>

Robo robo(1);

void setup() {
  robo.roboSetup();  
  Serial.begin(9600);
  robo.checkHardware(true);
}

void loop() {

}
