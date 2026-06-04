/*
Exemplo de sistema de controle básico.
*/

#include <Robo.h>

Robo robo(1);

void setup() {
  robo.roboSetup();
  randomSeed(analogRead(A0));
}


void loop() {
  float distancia = robo.lerDistancia();

  if (distancia > 30) {
    robo.irParaFrente(VEL_MED);
  }
  else if (distancia > 5 && distancia <= 30) {
    int movimento = random(1, 3);
    if (movimento == 1) {
      robo.girarDireita(VEL_MIN);
    }
    else if (movimento == 2) {
      robo.girarEsquerda(VEL_MIN);
    }    
  }
  else if (distancia <= 5) {
    robo.irParaTras(VEL_MED);
  }
}
