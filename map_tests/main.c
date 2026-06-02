#include <gb/gb.h>
#include <stdio.h>
#include "world.h"

void main(void){
    world_init();
    SPRITES_8x8;
    SHOW_SPRITES;
    SHOW_BKG;

    uint16_t current_joypad_frame = 0;
    uint16_t frame_to_update_joypad = 10;

    uint8_t joypad_value = 0;

    while(1){
        if(++current_joypad_frame >= frame_to_update_joypad){
            current_joypad_frame = 0;
            joypad_value = joypad();
        }
        world_control_character(joypad_value);
    }
}