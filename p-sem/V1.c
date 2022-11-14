#include <stdio.h>
#include "ev3.h"
#include "brick.h"
#include "ev3.h"
#include "coroutine.h"
#include <unistd.h>

#define _M_RIGHT	OUTD
#define _M_LEFT		OUTA

int rightLeft=0;

void mTest(int rightLeft) {

	if ( tacho_is_plugged( _M_LEFT, TACHO_TYPE__NONE_ )) {
		printf("FOUND _M_LEFT ON PORT_A\n");
	}else{printf("%s", "CONNECT _M_LEFT TO PORT_A!\n");}

	if ( tacho_is_plugged( _M_RIGHT, TACHO_TYPE__NONE_ )) {
		printf("FOUND _M_RIGHT ON PORT_D\n");
	}else{printf("%s", "CONNECT _M_RIGHT TO PORT_D!\n");}
					
	switch(rightLeft) {
		case 1:
			tacho_set_speed_sp(_M_RIGHT, 100);
			tacho_run_forever(_M_RIGHT);
			sleep_ms(5000);
			tacho_stop(_M_RIGHT);
		case 2:
			tacho_set_speed_sp(_M_LEFT, 100);
			tacho_run_forever(_M_LEFT);
			sleep_ms(5000);
			tacho_stop(_M_LEFT);
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
				mTest(2);
				break;
			case EV3_KEY_RIGHT:
				printf("%s", "right\n");
				mTest(1);
				break;
		}
		CORO_YIELD();
	}
CORO_END();
}



int main() {
	brick_init();
	while(true){
		CORO_CALL( handle_brick_control );
	}
	return 0;
}
