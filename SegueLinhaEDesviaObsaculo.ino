/*
Laboratório de Automação e Robótica Móvel (LARM/UFSC)

Biblioteca do robô para Arduino do projeto Oficina de Robótica

@2026

*/

#define ANALOGICO                   0
#define DIGITAL                     1

/* Se os sensores de infravermelho foram ligados em portas digitais o 
valor da macro deve ser DIGITAL, caso contrário, ANALOGICO.
*/
#define INFRAVERMELHO               DIGITAL

// Tipos de dados
typedef const int pino_t;
typedef const int delta_t;
typedef const int velocidade_t;

/*
--------------------------------------------------------------
Motores
--------------------------------------------------------------
*/

pino_t MOTOR_DIREITA_F            = 9;
pino_t MOTOR_DIREITA_T            = 11;
pino_t MOTOR_ESQUERDA_F           = 5;
pino_t MOTOR_ESQUERDA_T           = 3;

/*
--------------------------------------------------------------
Sensores
--------------------------------------------------------------
*/

pino_t ULTRASSOM_ECHO             = 8;
pino_t ULTRASSOM_TRIGGER          = 7;

pino_t INFRAVERMELHO_E            = 2;    // Infravermelho lado esquerdo
pino_t INFRAVERMELHO_D            = 4;    // Infravermelho lado direito

/*
--------------------------------------------------------------
Deltas (diferenças de rotação entre os motores)
--------------------------------------------------------------
*/

delta_t DELTA_MOTOR_DIREITA       = 0;
delta_t DELTA_MOTOR_ESQUERDA      = 0;

/*
--------------------------------------------------------------
Níveis de velocidade
--------------------------------------------------------------
*/

velocidade_t VEL_MAX             = 220;
velocidade_t VEL_MED             = 160;
velocidade_t VEL_MIN             = 100;



/*
Protótipo das funções
*/
float calcularDistancia();
void configurarRobo();
void mostrarMSG(char *msg);
float lerDistancia();
uint8_t lerInfravermelhoEsquerda();
uint8_t lerInfravermelhoDireita();
void roboSetup();
void irParaFrente(velocidade_t velocidade);
void irParaTras(velocidade_t velocidade);
void virarDireita(velocidade_t velocidade);
void virarEsquerda(velocidade_t velocidade);
void girarDireita(velocidade_t velocidade);
void girarEsquerda(velocidade_t velocidade);
void parar();
void checkHardware(bool modo_verboso = false);



/*
Funções setup() e loop()
*/

void setup() {
  roboSetup();
  Serial.begin(9600);
}

void loop() {
    int infraEsq = lerInfravermelhoEsquerda();
    int infraDir = lerInfravermelhoDireita();

    if (infraEsq == 0 && infraDir == 1) {
        virarDireita(90);
        delay(15);
    }
    if (infraEsq == 1 && infraDir == 0) {
        virarEsquerda(90);
        delay(15);
    }

    float distancia = lerDistancia();

    if (distancia < 7) {
        girarEsquerda(80);
        delay(800);
        parar();
        delay(500);
    } else {
        irParaFrente(80);
    }
    Serial.println(distancia);
}


/*
Implementação das funções
*/
float calcularDistancia()
{
    float tempo = 0;

    digitalWrite(ULTRASSOM_TRIGGER, HIGH);
    delayMicroseconds(200);
    digitalWrite(ULTRASSOM_TRIGGER, LOW);

    // Calcular tempo a partir do diparo do sinal
    tempo = pulseIn(ULTRASSOM_ECHO, HIGH);

    return tempo / 2 / 58;
}

void configurarRobo()
{
    // Configurar pinos motores
    pinMode(MOTOR_DIREITA_F, OUTPUT);
    pinMode(MOTOR_DIREITA_T, OUTPUT);
    pinMode(MOTOR_ESQUERDA_F, OUTPUT);
    pinMode(MOTOR_ESQUERDA_T, OUTPUT);

    // Configurar pinos sensores
    pinMode(ULTRASSOM_ECHO, INPUT);
    pinMode(ULTRASSOM_TRIGGER, OUTPUT);

    pinMode(INFRAVERMELHO_E, INPUT);
    pinMode(INFRAVERMELHO_D, INPUT);

    // Garantir que o trigger esteja em zero
    digitalWrite(ULTRASSOM_TRIGGER, LOW);
}

void mostrarMSG(char *msg)
{
    Serial.println("------------------------------------------------------");
    Serial.println(msg                                                     );
    Serial.println("------------------------------------------------------");
    Serial.println();
}

float lerDistancia()
{
    delay(11);
    return calcularDistancia();
}

uint8_t lerInfravermelhoEsquerda()
{
    #if INFRAVERMELHO == DIGITAL
    return digitalRead(INFRAVERMELHO_E);
    #elif INFRAVERMELHO == ANALOGICO
    return analogRead(INFRAVERMELHO_E);
    #endif
}

uint8_t lerInfravermelhoDireita()
{
    #if INFRAVERMELHO == DIGITAL
    return digitalRead(INFRAVERMELHO_D);
    #elif INFRAVERMELHO == ANALOGICO
    return analogRead(INFRAVERMELHO_D);
    #endif
}


void roboSetup()
{
    configurarRobo();
}

void irParaFrente(velocidade_t velocidade)
{
    analogWrite(MOTOR_DIREITA_F, velocidade + DELTA_MOTOR_DIREITA);
    analogWrite(MOTOR_ESQUERDA_F, velocidade + DELTA_MOTOR_ESQUERDA);
}

void irParaTras(velocidade_t velocidade)
{
    analogWrite(MOTOR_DIREITA_T, velocidade + DELTA_MOTOR_DIREITA);
    analogWrite(MOTOR_ESQUERDA_T, velocidade + DELTA_MOTOR_ESQUERDA);
}

void virarDireita(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_DIREITA_F, 0);
    analogWrite(MOTOR_ESQUERDA_F, velocidade + DELTA_MOTOR_ESQUERDA);
}

void virarEsquerda(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_ESQUERDA_F, 0);
    analogWrite(MOTOR_DIREITA_F, velocidade + DELTA_MOTOR_DIREITA);
}

void girarDireita(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_DIREITA_T, velocidade + DELTA_MOTOR_DIREITA);
    analogWrite(MOTOR_ESQUERDA_F, velocidade + DELTA_MOTOR_ESQUERDA);

}

void girarEsquerda(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_DIREITA_F, velocidade + DELTA_MOTOR_DIREITA);
    analogWrite(MOTOR_ESQUERDA_T, velocidade + DELTA_MOTOR_ESQUERDA);
}

void parar()
{
    analogWrite(MOTOR_DIREITA_F, 0);
    analogWrite(MOTOR_DIREITA_T, 0);
    analogWrite(MOTOR_ESQUERDA_F, 0);
    analogWrite(MOTOR_ESQUERDA_T, 0);
}

void checkHardware(bool modo_verboso = false)
{
    if (modo_verboso) {
        mostrarMSG("Verificação de hardware");
        Serial.println("--> acionando motores para frente                     ");

        irParaFrente(VEL_MED);
        delay(2000);
        parar();

        Serial.println("--> acionando motores para tras                       ");

        irParaTras(VEL_MED);
        delay(2000);
        parar();

        Serial.println("--> acionando motores para virar a direita            ");

        virarDireita(VEL_MED);
        delay(2000);
        parar();

        Serial.println("--> acionando motores para virar a esquerda           ");

        virarEsquerda(VEL_MED);
        delay(2000);
        parar();

        Serial.println("--> acionando motores para girar a direita            ");

        girarDireita(VEL_MED);
        delay(2000);
        parar();

        Serial.println("--> acionando motores para girar a esquerda           ");

        girarEsquerda(VEL_MED);
        delay(2000);
    }
    else {
        irParaFrente(VEL_MED);
        delay(2000);
        parar();

        irParaTras(VEL_MED);
        delay(2000);
        parar();

        virarDireita(VEL_MED);
        delay(2000);
        parar();

        virarEsquerda(VEL_MED);
        delay(2000);
        parar();

        girarDireita(VEL_MED);
        delay(2000);
        parar();

        girarEsquerda(VEL_MED);
        delay(2000);
        parar();
    }
    Serial.println("Check de hardware concluído");
    parar();    
}