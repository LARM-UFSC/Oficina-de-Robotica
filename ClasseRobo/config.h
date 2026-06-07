#ifndef CONFIG_H
#define CONFIG_H

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

pino_t MOTOR_DIREITA_F            = 11;
pino_t MOTOR_DIREITA_T            = 9;
pino_t MOTOR_ESQUERDA_F           = 5;
pino_t MOTOR_ESQUERDA_T           = 3;

/*
--------------------------------------------------------------
Sensores
--------------------------------------------------------------
*/

pino_t ULTRASSOM_ECHO             = 8;
pino_t ULTRASSOM_TRIGGER          = 7;

pino_t INFRAVERMELHO_E            = 0;    // Infravermelho lado esquerdo
pino_t INFRAVERMELHO_D            = 0;    // Infravermelho lado direito

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

#endif