#include <gb/gb.h>
#include <stdio.h>
#include "SmilerSprites.c"

void main(void){
    uint8_t currentspriteindex = 1;

    set_sprite_data(0, 2, Smiler);
    set_sprite_tile(0, currentspriteindex);
    move_sprite(0, 8, 16);
    SHOW_SPRITES;

    while(1){
        if(currentspriteindex == 0){
            currentspriteindex = 1;
        }
        else{
            currentspriteindex = 0;
        }
        set_sprite_tile(0, currentspriteindex);
        delay(500);
        scroll_sprite(0,1,1);
    }
}