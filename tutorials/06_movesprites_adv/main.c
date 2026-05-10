#include <gb/gb.h>
#include <stdio.h>
#include "SmilerSprites.c"

// optimised to skip delay and read motion based on a counter

void main(void){
    uint8_t currentspriteindex = 0;
    // time management
    uint16_t current_frame = 0;
    uint16_t frame_to_update_motion = 1000;
    // motion management
    uint8_t vertical_motion = 0;
    uint8_t horizontal_motion = 0;

    set_sprite_data(0, 2, Smiler);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    while(1){
        if(++current_frame >= frame_to_update_motion){
            uint8_t joypad_value = joypad();
            current_frame = 0;
            horizontal_motion = -1*( (J_LEFT & joypad_value)>>1 ) + (J_RIGHT & joypad_value);
            vertical_motion = -1*( (J_UP & joypad_value)>>2 ) + ( (J_DOWN & joypad_value)>>3 );
            // printf("h: %d - v: %d\n", horizontal_motion, vertical_motion);
            scroll_sprite(0,horizontal_motion,vertical_motion);
        }
    }
}