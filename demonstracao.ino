#define DELTA_MD 0
#define DELTA_ME 0

const int trigger   = 7;
const int echo      = 8;

const int motor_esquerda_f = 5;
const int motor_esquerda_t = 3;
const int motor_direita_f  = 9;
const int motor_direita_t  = 11; 

// Funções de direção
void parar()
{
  analogWrite(motor_esquerda_t, 0);
  analogWrite(motor_esquerda_f, 0);
  analogWrite(motor_direita_t, 0);
  analogWrite(motor_direita_f, 0);
}

void ir_para_frente(int velocidade)
{
  parar();
  analogWrite(motor_direita_f, velocidade+DELTA_MD);
  analogWrite(motor_esquerda_f, velocidade+DELTA_ME);
}

void ir_para_tras(int velocidade)
{
  parar();
  analogWrite(motor_direita_t, velocidade+DELTA_MD);
  analogWrite(motor_esquerda_t, velocidade+DELTA_ME);
}

void ir_para_direita(int velocidade)
{
  parar();
  analogWrite(motor_direita_f, 0);
  analogWrite(motor_esquerda_f, velocidade);
}

void ir_para_esquerda(int velocidade)
{
  parar();
  analogWrite(motor_direita_f, velocidade);
  analogWrite(motor_esquerda_f, 0);
}

void girar_para_direita(int velocidade)
{
  parar();
  analogWrite(motor_direita_t, velocidade);
  analogWrite(motor_esquerda_f, velocidade);
}

void girar_para_esquerda(int velocidade)
{
  parar();
  analogWrite(motor_direita_f, velocidade);
  analogWrite(motor_esquerda_t, velocidade);
}

void teste() {
  int acao = random(1, 7);

  if (acao == 1) {
    ir_para_frente(180);    
  }
  else if (acao == 2) {
    ir_para_tras(180);
  }
  else if (acao == 3) {
    ir_para_direita(180);
  }
  else if (acao == 4) {
    ir_para_esquerda(180);
  }
  else if (acao == 5) {
    girar_para_direita(180);
  }
  else if (acao == 6) {
    girar_para_esquerda(180);
  }
  delay(1000);
}


void setup() {
  pinMode(motor_esquerda_f, OUTPUT);
  pinMode(motor_esquerda_t, OUTPUT);
  pinMode(motor_direita_f, OUTPUT);
  pinMode(motor_direita_t, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  randomSeed(analogRead(A0));
  digitalWrite(trigger, LOW);
  Serial.begin(9600);
}

void loop()
{
  float distancia;
  float tempo;

  digitalWrite(trigger, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigger, LOW);

  tempo = pulseIn(echo, HIGH);

  distancia = tempo / 2 / 29;
  Serial.println(distancia);

  if(distancia>20){
    ir_para_frente(100);
  }
  if(distancia>14 && distancia<20){
    ir_para_frente(70);
  }
  if(distancia<15){
    int acao = random(1, 4);
    parar();
    ir_para_tras(100);
    delay(300);
    parar();
    delay(100);
    if(acao==1){
      delay(400);
      ir_para_direita(100);
      delay(500);
    }
    else if(acao==2){
      delay(400);
      ir_para_esquerda(100);
      delay(500);
    }
    else if(acao==3){
      delay(400);
      girar_para_direita(100);
      delay(600);
    }
    else if(acao==4){
      delay(400);
      girar_para_esquerda(100);
      delay(600);
    }
  }
}