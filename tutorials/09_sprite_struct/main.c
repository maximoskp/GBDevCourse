#include <gb/gb.h>
#include <stdio.h>
#include "sprites/walker3.c"

// optimised to skip delay and read motion based on a counter

void main(void){
    uint8_t currentspriteindex = 0;
    // time management
    uint16_t current_motion_frame = 0;
    uint16_t frame_to_update_motion = 1000;
    uint16_t current_animation_subframe = 0;
    uint16_t subframe_to_update_animation = 5;
    // motion management
    uint8_t vertical_motion = 0;
    uint8_t horizontal_motion = 0;

    set_sprite_data(0, 3, walker);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    while(1){
        if(++current_motion_frame >= frame_to_update_motion){
            uint8_t joypad_value = joypad();
            current_motion_frame = 0;
            horizontal_motion = -1*( (J_LEFT & joypad_value)>>1 ) + (J_RIGHT & joypad_value);
            vertical_motion = -1*( (J_UP & joypad_value)>>2 ) + ( (J_DOWN & joypad_value)>>3 );
            
            if ( horizontal_motion || vertical_motion ){
                if( ++current_animation_subframe >= subframe_to_update_animation ){
                    current_animation_subframe = 0;
                    currentspriteindex = (currentspriteindex + 1) % 2;
                }
                set_sprite_tile(0, currentspriteindex+1);
            }
            if (!horizontal_motion && !vertical_motion){
                // current_animation_subframe = 0;
                currentspriteindex = 0;
                set_sprite_tile(0, currentspriteindex);
            }
            scroll_sprite(0,horizontal_motion,vertical_motion);
        }
    }
}