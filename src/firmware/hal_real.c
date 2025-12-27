#include "../hal/robot_hal.h"
#include <pic16f873.h>
#include <stdint.h>

void hal_hardware_init(void) {
  TRISA = 0xFF; // Porta A como entrada (ADC para leitura de bateria)
  TRISB = 0x00; // Porta B como saída (Direção, motor, chute)
  TRISC = 0x00; // Porta C como saída (PWMs)

  PR2 = 0xFF;
  T2CON = 0x04;

  CCP1CON = 0x0C;
  CCP2CON = 0x0C;

  ADCON0 = 0x81;
  ADCON1 = 0x0E;
}

void hal_motor_set(uint8_t id, int8_t speed) {
  // Speed de -100 a 100

  uint8_t duty_cycle;
  uint8_t direction = 0; // 0 = Frente, 1 = Trás

  if (speed < 0) {
    direction = 1;
    speed = -speed;
  }

  if (speed > 100)
    speed = 100;

  duty_cycle = (speed << 1) + (speed >> 1);

  if (id == 0) {
    // Motor esquerdo (CCP1 + RB1)
    CCPR1L = duty_cycle;
    if (direction)
      RB1 = 1;
    else
      RB1 = 0;
  } else if (id == 1) {
    // Motor direito (CCP2 + RB2)
    CCPR2L = duty_cycle;
    if (direction)
      RB2 = 1;
    else
      RB2 = 0;
  }
}

void hal_kick(float power) {
  if (power > 0) {
    RB0 = 1;
    uint16_t i;
    for (i = 0; i < 5000; i++)
      ;
    RB0 = 0;
  }
}

void hal_get_battery() {
  ADGO = 1;

  while (ADGO)
    ;

  uint8_t raw_value = ADRESH;

  return (float)raw_value * 0.058f;
}
