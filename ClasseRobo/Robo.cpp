#include "Robo.h"

float Robo::calcularDistancia()
{
    float tempo = 0;

    digitalWrite(ULTRASSOM_TRIGGER, HIGH);
    delayMicroseconds(200);
    digitalWrite(ULTRASSOM_TRIGGER, LOW);

    // Calcular tempo a partir do diparo do sinal
    tempo = pulseIn(ULTRASSOM_ECHO, HIGH);

    return tempo / 2 / 58;
}

void Robo::configurarRobo()
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

Robo::Robo(uint8_t id)
{
    roboId = id;
}

void Robo::mostrarMSG(char *msg)
{
    Serial.println("------------------------------------------------------");
    Serial.println(msg                                                     );
    Serial.print  ("Robô ID:                                              ");
    Serial.println(getRoboID()                                             );
    Serial.println("------------------------------------------------------");
    Serial.println();
}

float Robo::lerDistancia()
{
    delay(500);
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


uint8_t Robo::getRoboID()
{
    return roboId;
}

void Robo::roboSetup()
{
    configurarRobo();
}

void Robo::irParaFrente(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_DIREITA_F, velocidade + DELTA_MOTOR_DIREITA);
    analogWrite(MOTOR_ESQUERDA_F, velocidade + DELTA_MOTOR_ESQUERDA);
}

void Robo::irParaTras(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_DIREITA_T, velocidade + DELTA_MOTOR_DIREITA);
    analogWrite(MOTOR_ESQUERDA_T, velocidade + DELTA_MOTOR_ESQUERDA);
}

void Robo::virarDireita(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_DIREITA_F, 0);
    analogWrite(MOTOR_ESQUERDA_F, velocidade + DELTA_MOTOR_ESQUERDA);
}

void Robo::virarEsquerda(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_DIREITA_F, velocidade + DELTA_MOTOR_DIREITA);
    analogWrite(MOTOR_ESQUERDA_F, 0);
}

void Robo::girarDireita(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_DIREITA_T, velocidade + DELTA_MOTOR_DIREITA);
    analogWrite(MOTOR_ESQUERDA_F, velocidade + DELTA_MOTOR_ESQUERDA);

}

void Robo::girarEsquerda(velocidade_t velocidade)
{
    parar();
    analogWrite(MOTOR_DIREITA_F, velocidade + DELTA_MOTOR_DIREITA);
    analogWrite(MOTOR_ESQUERDA_T, velocidade + DELTA_MOTOR_ESQUERDA);
}

void Robo::parar()
{
    analogWrite(MOTOR_DIREITA_F, 0);
    analogWrite(MOTOR_DIREITA_T, 0);
    analogWrite(MOTOR_ESQUERDA_F, 0);
    analogWrite(MOTOR_ESQUERDA_T, 0);
}

void Robo::checkHardware(bool modo_verboso = false)
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