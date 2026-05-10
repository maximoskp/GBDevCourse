#include <gb/gb.h>
#include <stdio.h>
#include "SmilerSprites.c"

// optimised to skip delay and read motion based on a counter

void main(void){
    uint8_t currentspriteindex = 0;
    // time management
    uint16_t time_to_update_motion = 10;
    // motion management
    uint8_t vertical_motion = 0;
    uint8_t horizontal_motion = 0;

    set_sprite_data(0, 2, Smiler);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    while(1){
        delay(time_to_update_motion);
        uint8_t joypad_value = joypad();
        // printf("Joypad value: %d\n", joypad_value);
        if (joypad_value == J_LEFT){
            horizontal_motion = -1;
            // horizontal_motion = 255; // same thing but unsigned, -1 is 255 in unsigned 8 bit
        } else if (joypad_value == J_RIGHT){
            horizontal_motion = 1;
        } else {
            horizontal_motion = 0;
        }
        if (joypad_value == J_UP){
            vertical_motion = -1;
            // vertical_motion = 255; // same thing but unsigned, -1 is 255 in unsigned 8 bit
        } else if (joypad_value == J_DOWN){
            vertical_motion = 1;
        } else {
            vertical_motion = 0;
        }
        scroll_sprite(0,horizontal_motion,vertical_motion);
    }
}

// Problem: We cannot have diagonal motion. In this setup we would need to
// check for each combination of directions and then move the sprite accordingly,
// which is a lot of checks and code.