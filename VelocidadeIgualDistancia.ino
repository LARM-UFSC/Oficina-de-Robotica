#define TRAS_ESQUERDA 3
#define FRENTE_ESQUERDA 5
#define FRENTE_DIREITA 9
#define TRAS_DIREITA 11

#define TRIGGER 7
#define ECHO 8

#define INFRA_DIR_A A1
#define INFRA_ESQ_A A2
#define INFRA_DIR_D 2
#define INFRA_ESQ_D 4

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(INFRA_ESQ_A, INPUT);
  pinMode(INFRA_DIR_A, INPUT);
  pinMode(INFRA_ESQ_D, INPUT);
  pinMode(INFRA_DIR_D, INPUT);

  pinMode(FRENTE_ESQUERDA, OUTPUT);
  pinMode(FRENTE_DIREITA, OUTPUT);
  pinMode(TRAS_ESQUERDA, OUTPUT);
  pinMode(TRAS_DIREITA, OUTPUT);

  void andar_frente(int velD, int velE);
  void andar_tras(int velD, int velE);
  void virar_direita();
  void virar_esquerda();
  void meia_volta_dir();
  void meia_volta_esq();
  void parar();
}

void loop() {
  digitalWrite(TRIGGER,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER,LOW);

  
  long duracao = pulseIn(ECHO, HIGH);
  float distancia = duracao * 0.034/2;

  float infra_dir_a = analogRead(INFRA_DIR_A);
  float infra_esq_a = analogRead(INFRA_ESQ_A);
  bool infra_dir_d = digitalRead(INFRA_DIR_D);
  bool infra_esq_d = digitalRead(INFRA_ESQ_D);
  
  Serial.println(distancia);

  if(distancia>20){
    if(distancia>255){
      distancia = 200;
    }
    int velocidade=(int)distancia;
    if(velocidade<50){
        velocidade=50;
    }
    andar_frente(velocidade+10, velocidade+10);
  }
  if(distancia<20 && distancia>10){
    meia_volta_dir();
  }
 
}

void andar_frente(int velD, int velE){
  analogWrite(TRAS_ESQUERDA, 0);
  analogWrite(TRAS_DIREITA, 0);
  analogWrite(FRENTE_ESQUERDA, velE);
  analogWrite(FRENTE_DIREITA, velD);
}

void andar_tras(int velD, int velE){
  analogWrite(FRENTE_ESQUERDA, 0);
  analogWrite(FRENTE_DIREITA, 0);
  analogWrite(TRAS_ESQUERDA, velE);
  analogWrite(TRAS_DIREITA, velD);
}


void virar_direita(){
  analogWrite(FRENTE_ESQUERDA, 100);
  analogWrite(FRENTE_DIREITA, 0);
  analogWrite(TRAS_ESQUERDA, 0);
  analogWrite(TRAS_DIREITA, 0);
  delay(600);
}

void virar_esquerda(){
  analogWrite(FRENTE_ESQUERDA, 0);
  analogWrite(FRENTE_DIREITA, 100);
  analogWrite(TRAS_ESQUERDA, 0);
  analogWrite(TRAS_DIREITA, 0);
  delay(600);
}

void meia_volta_dir(){
  analogWrite(FRENTE_ESQUERDA, 100);
  analogWrite(FRENTE_DIREITA, 0);
  analogWrite(TRAS_ESQUERDA, 0);
  analogWrite(TRAS_DIREITA, 100);
  delay(800);
}

void meia_volta_esq(){
  analogWrite(FRENTE_ESQUERDA, 0);
  analogWrite(FRENTE_DIREITA, 100);
  analogWrite(TRAS_ESQUERDA, 100);
  analogWrite(TRAS_DIREITA, 0);
  delay(800);
}

void parar(){
  analogWrite(FRENTE_ESQUERDA, 0);
  analogWrite(FRENTE_DIREITA, 0);
  analogWrite(TRAS_ESQUERDA, 0);
  analogWrite(TRAS_DIREITA, 0);
}
