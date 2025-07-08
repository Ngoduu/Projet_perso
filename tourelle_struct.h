#include <stdio.h>

typedef struct{
  uint16_t msg_id;
  uint16_t msg_counter;
  uint16_t msg_publisher;
  //int8_t current_mode;
  //int8_t exec_report;
  //int8_t state;
} TLA_OUT_heartbeat;

/*typedef enum {
  TLA_OUT_heartbeat_NOT_USED = 0;
  TLA_OUT_heartbeat_ON_USE = 1;
  TLA_OUT_heartbeat_OFF_USE = 2;
  TLA_OUT_heartbeat_DIAGNOSTIC = 3;
}*/

typedef struct {
  uint16_t msg_id;
  uint16_t msg_counter;
  uint16_t msg_publisher;
  //int8_t cmd;
}TLA_IN_mode;

typedef struct {
  uint16_t msg_id;
  uint16_t msg_counter;
  uint16_t msg_publisher;
  int16_t pan;
  int16_t tilt;
}TLA_IN_cmd_pos; 

typedef struct {
  uint16_t msg_id;
  uint16_t msg_counter;
  uint16_t msg_publisher;
  int16_t pan;
  int16_t tilt;
}TLA_OUT_pos;

typedef struct{
  uint16_t msg_id;
  uint16_t msg_counter;
  uint16_t msg_publisher;
  //int8_t mode;
  int16_t pan;
  int16_t tilt;
}TLA_IN_cmd_spd;

typedef struct{
  uint16_t msg_id;
  uint16_t msg_counter;
  uint16_t msg_publisher;
  uint8_t laser_time;
  //uint8_t laser_mode;
}TLA_IN_laser;

typedef struct{
  uint16_t msg_id;
  uint16_t msg_counter;
  uint16_t msg_publisher;
  //int8_t power_mask;
}TLA_OUT_laser_state;



