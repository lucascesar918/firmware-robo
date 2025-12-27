#include "hal_mock.hpp"
#include "../hal/robot_hal.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include "grSim_Commands.pb.h"
#include "grSim_Packet.pb.h"
#include "grSim_Replacement.pb.h"

static int sock_fd = -1;
static struct sockaddr_in grsim_addr;
static bool is_initialized = false;

static std::string grsim_ip = "127.0.0.1";
int grsim_port = 20011;
const bool IS_YELLOW_TEAM = false;

MockRobot::MockRobot(std::string ip, int port) {
  grsim_ip = ip.c_str();
  grsim_port = port;
  std::cout << "[MockRobot] Inicializado em " << ip << ":" << port << std::endl;

  hal_init();
}

extern "C" {

void hal_init() { std::cout << "[HAL_MOCK] hal_init chamado." << std::endl; }

void hal_hardware_init() {
  if (is_initialized)
    return;

  if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    std::cerr << "[ERRO] Falha ao criar socket UDP!" << std::endl;
    return;
  }

  memset(&grsim_addr, 0, sizeof(grsim_addr));
  grsim_addr.sin_family = AF_INET;
  grsim_addr.sin_port = htons(grsim_port);

  if (inet_pton(AF_INET, grsim_ip.c_str(), &grsim_addr.sin_addr) <= 0) {
    std::cerr << "[ERRO] Endereço IP inválido!" << std::endl;
    return;
  }

  is_initialized = true;
  std::cout << "[MOCK] Conectado ao grSim em " << grsim_ip << ":" << grsim_port
            << std::endl;
}

void hal_motor_set(uint8_t id, int8_t speed) {
  if (!is_initialized)
    hal_hardware_init();

  float wheel_speed = (float)speed * 0.3f;

  grSim_Packet packet;

  packet.mutable_commands()->set_timestamp(0.0);
  packet.mutable_commands()->set_isteamyellow(IS_YELLOW_TEAM);

  grSim_Robot_Command *cmd = packet.mutable_commands()->add_robot_commands();
  cmd->set_id(id);

  cmd->set_wheelsspeed(true);
  cmd->set_wheel1(wheel_speed);
  cmd->set_wheel2(wheel_speed);
  cmd->set_wheel3(0);
  cmd->set_wheel4(0);

  cmd->set_kickspeedx(0);
  cmd->set_kickspeedz(0);
  cmd->set_veltangent(0);
  cmd->set_velnormal(0);
  cmd->set_velangular(0);
  cmd->set_spinner(false);

  std::string buffer;
  packet.SerializeToString(&buffer);

  sendto(sock_fd, buffer.c_str(), buffer.size(), 0,
         (const struct sockaddr *)&grsim_addr, sizeof(grsim_addr));
}

void hal_kick(float power) {
  if (!is_initialized)
    return;

  std::cout << "[MOCK] Chute! Força: " << power << std::endl;
}

float hal_get_battery() { return 12.6f; }
}
