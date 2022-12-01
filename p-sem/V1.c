#include <stdio.h>
#include "ev3.h"
#include "brick.h"
#include "ev3.h"
#include "coroutine.h"
#include <unistd.h>

#define _M_RIGHT	OUTD
#define _M_LEFT		OUTA
#define _M_BELT   OUTB
#define _S_COLOR  IN1

int rightLeft=0;

void init() {
  // checks for motors
	if ( tacho_is_plugged( _M_LEFT, TACHO_TYPE__NONE_ )) {
		printf("FOUND _M_LEFT ON PORT_A\n");
	}else{printf("%s", "CONNECT _M_LEFT TO PORT_A!\n");}

	if ( tacho_is_plugged( _M_RIGHT, TACHO_TYPE__NONE_ )) {
		printf("FOUND _M_RIGHT ON PORT_D\n");
	}else{printf("%s", "CONNECT _M_RIGHT TO PORT_D!\n");}

  if ( tacho_is_plugged( _M_BELT, TACHO_TYPE__NONE_ )) {
    printf("FOUND _M_BELT ON PORT_B\n");
  }else{printf("%s", "CONNECT _M_BELT TO PORT_B!\n");}


  if ( sensor_is_plugged( _S_COLOR, SENSOR_TYPE__NONE_  )) {
    printf("FOUND _S_COLOR ON PORT_1\n");
    color_set_mode_col_reflect(_S_COLOR);
    printf("%d\n", sensor_get_mode(_S_COLOR));
  }else{printf("%s", "CONNECT _S_COLOR TO PORT_1!\n");}

	tacho_set_speed_sp(_M_RIGHT, -100);
	tacho_run_forever(_M_RIGHT);
	sleep_ms(500);
	tacho_stop(_M_RIGHT);

	tacho_set_speed_sp(_M_LEFT, -100);
	tacho_run_forever(_M_LEFT);
	sleep_ms(500);
	tacho_stop(_M_LEFT);

  tacho_set_speed_sp(_M_BELT, 200);
  tacho_run_forever(_M_BELT);
  sleep_ms(1000);
  tacho_stop(_M_BELT);
}

void selection(int rightLeft) {
		switch(rightLeft) {
		case 1:
			tacho_set_speed_sp(_M_RIGHT, 200);
			tacho_run_forever(_M_RIGHT);
			sleep_ms(2000);
			tacho_stop(_M_RIGHT);
      sleep_ms(500);
      tacho_set_speed_sp(_M_RIGHT, -100);
      tacho_run_forever(_M_RIGHT);
  
      tacho_set_speed_sp(_M_BELT, 200);
      tacho_run_forever(_M_BELT);
      sleep_ms(1000);
      tacho_stop(_M_BELT);

      break;
		case 2:
			tacho_set_speed_sp(_M_LEFT, 200);
			tacho_run_forever(_M_LEFT);
			sleep_ms(2000);
			tacho_stop(_M_LEFT);
      sleep_ms(500);
      tacho_set_speed_sp(_M_LEFT, -100);
      tacho_run_forever(_M_LEFT);
      
      break;
	}
}

void sensorTest(int value) {
  color_set_mode_col_reflect(_S_COLOR);
  float value0=0, value1=0, value2=0, value3=0, value4=0, value5=0, value6=0, value7=0; 

  while(true) {
    if(value == 0){
    sensor_get_value0(_S_COLOR, value0);
    printf("%f", "value0:   ", value0, "\n");
    }
  else if(value == 1){
    sensor_get_value1(_S_COLOR, value1);
    printf("%f", "value1:   ", value1, "\n");
    }
  else if(value == 2){
    sensor_get_value2(_S_COLOR, value2);
    printf("%f", "value2:   ", value2, "\n");
  }
  else if(value == 3){
    sensor_get_value3(_S_COLOR, value3);
    printf("%f", "value3:   ", value3, "\n");
    }
  else if(value == 4){
    sensor_get_value4(_S_COLOR, value4);
    printf("%f", "value4:   ", value4, "\n");
    }
  else if(value == 5){
    sensor_get_value5(_S_COLOR, value5);
    printf("%f", "value5:   ", value5, "\n");
    }
  else if(value == 6){
    sensor_get_value6(_S_COLOR, value6);
    printf("%f", "value6:   ", value6, "\n");
    }
  else if(value == 7){
    sensor_get_value7(_S_COLOR, value7);
    printf("%f", "value7:   ", value7, "\n");
    }
  }
}



CORO_CONTEXT( handle_brick_control );

CORO_DEFINE( handle_brick_control ) {
	CORO_LOCAL uint8_t keys, pressed = EV3_KEY__NONE_;

	CORO_BEGIN();
	for( ; ; ) {
		CORO_WAIT(( keys = brick_keys()) != pressed );
		pressed = keys;

		switch( pressed ) {
			case EV3_KEY_LEFT:
				printf("%s", "left\n");
				selection(2);
				break;
			case EV3_KEY_RIGHT:
				printf("%s", "right\n");
				selection(1);
				break;
		}
		CORO_YIELD();
	}
CORO_END();
}



int main() {
	brick_init();
  init();
  sensorTest(2);
	while(true){
		CORO_CALL( handle_brick_control );
	}
	return 0;
}
