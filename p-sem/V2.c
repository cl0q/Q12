// © 2022 Timo Katzenberger <katzenbergertimo@gmail.com> &&
// © 2022 Oliver Ilczuk <oliver@ilczuk.com>

// MIT Lincense


// importing necessary libraries
#include <string.h>
#include <stdio.h>
#include "ev3.h"
#include "brick.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "coroutine.h"
#include <unistd.h>

// defining used ports and function
#define _M_RIGHT	OUTD
#define _M_LEFT		OUTA
#define _M_BELT   OUTB
#define _M_MONEY  OUTC
#define COLOR_COUNT ((int)(sizeof(color) / sizeof(color[0])))

// defining global variables
int rightLeft=0;	 /*         0      1        2       3        4        5       6         7  */
const char const *color[] = {"?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN"};
int val, credits;

// Initializes program, pulls back pushers to reset position, test runs _M_BELT and _M_MONEY
int init() {
	printf("\n\n<<<---------BEGIN INIT-------->>>\n\n");
		if( tacho_is_plugged ( _M_LEFT, TACHO_TYPE__NONE_ )) {
			printf("FOUND _M_LEFT ON PORT_A\n");
		}else {
			printf("%s", "CONNECT _M_LEFT TO PORT_A!\n");
			brick_uninit();
			return 1;
	}

	if ( tacho_is_plugged ( _M_RIGHT, TACHO_TYPE__NONE_ )) {
		printf("FOUND _M_RIGHT ON PORT_D\n");
	}else {
		printf("%s", "CONNECT _M_RIGHT TO PORT_D!\n");
		brick_uninit();
		return 1;
	}

	if ( tacho_is_plugged ( _M_BELT, TACHO_TYPE__NONE_ )) {
		printf("FOUND _M_BELT ON PORT_B\n");
	}else {
		printf("%s", "CONNECT _M_BELT TO PORT_B!\n");
		brick_uninit();
		return 1;
	}

	if ( tacho_is_plugged ( _M_MONEY, TACHO_TYPE__NONE_ )) {
		printf("FOUND _M_MONEY ON PORT_C\n");
	}else {
		printf("%s", "CONNECT _M_MONEY TO PORT_C!\n");
		brick_uninit();
		return 1;
	}

	tacho_set_speed_sp( _M_RIGHT, -100 );
	tacho_run_forever( _M_RIGHT );
	sleep_ms( 500 );
	tacho_stop( _M_RIGHT );

	tacho_set_speed_sp( _M_LEFT, -100 );
	tacho_run_forever( _M_LEFT );
	sleep_ms( 500 );
	tacho_stop( _M_LEFT );

	tacho_set_speed_sp( _M_BELT, 200 );
	tacho_run_forever( _M_BELT );
	sleep_ms( 1000 );
	tacho_stop( _M_BELT );

	tacho_set_speed_sp( _M_MONEY, 100 );
	tacho_run_forever( _M_MONEY );
	sleep_ms( 100 );
	tacho_set_speed_sp( _M_MONEY, -100 );
	tacho_run_forever( _M_MONEY );
	sleep_ms( 100 );
	tacho_stop( _M_MONEY );

	printf("\n>>>----------END INIT---------<<<\n\n");

	return 0;
}

// cleaner way to print current credits
void getCredits() {
	if( credits != 0){
		printf( "\033[0;32m[CREDIT]\033[0m     %i\n", credits);
	}else if( credits == 0){
		printf( "\033[0;31m[CREDIT]\033[0m     %i\n", credits);
	}
}

// method to select candy being pushed out, case 1 == right, case 2 == left
void selection( int rightLeft ) {
	switch( rightLeft ) {
		case 1:
      //_M_RIGHT
			tacho_set_speed_sp( _M_RIGHT, 1000 );
			tacho_run_forever( _M_RIGHT );
			sleep_ms( 2000 );
			tacho_stop( _M_RIGHT );
			sleep_ms( 500 );
			tacho_set_speed_sp( _M_RIGHT, -100 );
			tacho_run_forever( _M_RIGHT );
      // _M_BELT
			tacho_set_speed_sp( _M_BELT, 200 );
			tacho_run_forever( _M_BELT );
			sleep_ms( 2000 );
			tacho_stop( _M_BELT );

			tacho_stop( _M_RIGHT );
			break;

		case 2:
			// _M_LEFT
			tacho_set_speed_sp( _M_LEFT, 200 );
			tacho_run_forever( _M_LEFT );
			sleep_ms( 2000 );
			tacho_stop( _M_LEFT );
			sleep_ms( 500 );
			tacho_set_speed_sp( _M_LEFT, -100 );
			tacho_run_forever( _M_LEFT );
			sleep_ms( 500 );
			tacho_stop( _M_LEFT );

			break;
	}
}

// finds connected sensor and reads color infront of color sensor
void getColor() {
	uint8_t sn_colors;
	if( ev3_search_sensor ( LEGO_EV3_COLOR, &sn_colors, 0 ) == true) {
		set_sensor_mode( sn_colors, "COL-COLOR" );
		if( !get_sensor_value ( 0, sn_colors, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
			val = 0;
		}
	}
}

// runs _M_MONEY to retrieve given change
void motorMoney() {
	tacho_set_speed_sp( _M_MONEY, -175 );
	tacho_run_forever( _M_MONEY );
	sleep_ms( 1000 );
	tacho_stop( _M_MONEY );
	sleep_ms( 500 );
	tacho_set_speed_sp( _M_MONEY, 175 );
	tacho_run_forever( _M_MONEY );
	sleep_ms( 500 );
	tacho_stop( _M_MONEY );
}

// sets credits according to given change
void setCredits() {
	//1 Euro, red, brown
	if( val == 5 || val == 7 ) {
		credits++;
		printf("\033[0;36m[STATS ]\033[0m     Change: 1 Euro  ||  Color: %s\n", color[val]);
    getCredits();
    motorMoney();
	//2 Euro, yellow, blue
	} else if( val == 4 || val == 2 ){
    credits = credits + 2;
    printf("\033[0;36m[STATS ]\033[0m     Change: 2 Euro  ||  Color: %s\n", color[val]);
    getCredits();
    motorMoney();
	} else{
    printf("\033[0;31m[  !!  ]\033[0m     Could NOT determine change!\n");
    getCredits();
	}
}

// coroutine to always check for key inputs
CORO_CONTEXT( handle_brick_control );
CORO_DEFINE( handle_brick_control ) {
	CORO_LOCAL uint8_t keys, pressed = EV3_KEY__NONE_;

	CORO_BEGIN();
	for( ; ; ) {
		CORO_WAIT(( keys = brick_keys()) != pressed );
		pressed = keys;
		// if enough credits, push out candy, else throw error
		switch( pressed ) {
			case EV3_KEY_LEFT:
				if( credits >= 1 ){
					printf( "%s", "\033[0;33m[ACTION]\033[0m     left\n" );
					selection( 2 );
					credits--;
					getCredits();
				} else{
					printf( "%s", "\033[0;31m[ERROR ]\033[0m     NOT ENOUGH CREDITS\n");
					getCredits();
        }
				break;
			case EV3_KEY_RIGHT:
        if( credits >= 2){
					printf( "%s", "\033[0;33m[ACTION]\033[0m     right\n" );
					selection( 1 );
					credits = credits - 2;
					getCredits();
        } else{
					printf( "%s", "\033[0;31m[ERROR ]\033[0m     NOT ENOUGH CREDITS\n");
					getCredits();
        }
        break;
			case EV3_KEY_CENTER:
				printf( "\033[0;35m[ GIVE ]\033[0m\n" );
				getColor();
				setCredits();
				break;
		}
		CORO_YIELD();
	}
CORO_END();
}

int main() {
	brick_init();
	init();
	getColor();
	for( ; ; ){
		CORO_CALL( handle_brick_control );
	}
	return 0;
}
