#ifndef PID_H
#define PID_H

typedef struct {
  float kp;
  float ki;
  float kd;
  float integral;
  float prev_error;
} PIDConfig;

float pid_calculate(PIDConfig *pid, float setpoint, float measured);
void pid_reset(PIDConfig *pid);

#endif
