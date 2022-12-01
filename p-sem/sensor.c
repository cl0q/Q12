
#include <stdio.h>
#include "ev3.h"
#include "brick.h"
#include "ev3.h"
#include "coroutine.h"
#include <unistd.h>

#define _S_COLOR IN1

int main() {
  brick_init();
  color_set_mode_col_color(_S_COLOR);
  printf("%d\n", sensor_get_mode(_S_COLOR));
  int buffer;
  for(int i=0; i<8; i++){
    if(i=0){
        printf("%d\n", i);
        sensor_get_value0(_S_COLOR, buffer);
        printf("%d\n", buffer);
      }
    if(i=1){
        printf("%d\n", i);
        sensor_get_value1(_S_COLOR, buffer);
        printf("%d\n", buffer);
      }
    if(i=2){
        printf("%d\n", i);
        sensor_get_value2(_S_COLOR, buffer);
        printf("%d\n", buffer);
      }
    if(i=3){
        printf("%d\n", i);
        sensor_get_value3(_S_COLOR, buffer);
        printf("%d\n", buffer);
      }
    if(i=4){
        printf("%d\n", i);
        sensor_get_value4(_S_COLOR, buffer);
        printf("%d\n", buffer);
      }
    if(i=5){
        printf("%d\n", i);
        sensor_get_value5(_S_COLOR, buffer);
        printf("%d\n", buffer);
      }
    if(i=6){
        printf("%d\n", i);
        sensor_get_value6(_S_COLOR, buffer);
        printf("%d\n", buffer);
      }
    if(i=7){
        printf("%d\n", i);
        sensor_get_value7(_S_COLOR, buffer);
        printf("%d\n", buffer);
      }
  }
  return 0;
}
