#include <gb/gb.h>
#include <stdio.h>
#include "character.h"
#include "map/map_tiles.c"
#include "map/map.c"

// optimised to skip delay and read motion based on a counter

Character player;

void main(void){
    SPRITES_8x8;
    character_init(&player, 80, 72);
    SHOW_SPRITES;

    set_bkg_data(0, 3, map_tiles);
    set_bkg_tiles(0, 0, 20, 18, map);
    SHOW_BKG;

    uint16_t current_joypad_frame = 0;
    uint16_t frame_to_update_joypad = 10;

    uint8_t joypad_value = 0;

    while(1){
        if(++current_joypad_frame >= frame_to_update_joypad){
            current_joypad_frame = 0;
            joypad_value = joypad();
        }
        control_character(&player, joypad_value);
    }
}