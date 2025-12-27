#include "strategy.h"
#include "pid.h"
#include "robot_hal.h"

static PIDConfig pid_motor_esq;
static PIDConfig pid_motor_dir;
static uint8_t initialized = 0;

void strategy_init(void) {
  // Configura os ganhos do PID (calibrar na prática!)
  pid_motor_esq.kp = 1.5f;
  pid_motor_esq.ki = 0.1f;
  pid_motor_esq.kd = 0.0f;
  pid_reset(&pid_motor_esq);

  pid_motor_dir.kp = 1.5f;
  pid_motor_dir.ki = 0.1f;
  pid_motor_dir.kd = 0.0f;
  pid_reset(&pid_motor_dir);

  initialized = 1;
}

void run_strategy(void) {
  float controle_esq, controle_dir;

  if (!initialized)
    strategy_init();

  // Estratégia provisória para teste: andar para frente
  controle_esq = pid_calculate(&pid_motor_esq, 50.0f, 0.0f);
  controle_dir = pid_calculate(&pid_motor_dir, 50.0f, 0.0f);

  hal_motor_set(0, (int8_t)controle_esq); // Motor ID 0
  hal_motor_set(1, (int8_t)controle_dir); // Motor ID 1
}
