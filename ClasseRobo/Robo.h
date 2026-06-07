#ifndef ROBOT_H
#define ROBOT_H

#include "config.h"
#include <stdint.h>
#include <Arduino.h>

class Robo {

    private:
        uint8_t roboId;
        velocidade_t vel_atual_motor_d;
        velocidade_t vel_atual_motor_e;

        float calcularDistancia();
        void configurarRobo();
        void mostrarMSG(char *msg);

    public:
        Robo(uint8_t id);
        float lerDistancia();
        uint8_t lerInfravermelhoEsquerda();
        uint8_t lerInfravermelhoDireita();
        uint8_t getRoboID();
        void roboSetup();
        void irParaFrente(velocidade_t velocidade);
        void irParaTras(velocidade_t velocidade);
        void virarDireita(velocidade_t velocidade);
        void virarEsquerda(velocidade_t velocidade);
        void girarDireita(velocidade_t velocidade);
        void girarEsquerda(velocidade_t velocidade);
        void parar();
        void checkHardware(bool modo_verboso = false);
};
#endif