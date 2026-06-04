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
    uint8_t previously_pressed = 0;

    uint8_t winning_condition = 0;

    uint8_t game_paused = 0;

    while(winning_condition == 0){
        if(++current_joypad_frame >= frame_to_update_joypad){
            current_joypad_frame = 0;
            joypad_value = joypad();
            uint8_t just_pressed = joypad_value & ~previously_pressed;
            // printf("just: %d\n", just_pressed);
            // printf("prev: %d\n\n\n", previously_pressed);
            if (game_paused == 0){
                winning_condition = world_control_character(joypad_value, just_pressed);
            }
            previously_pressed = joypad_value;
            if ((just_pressed & J_START) == J_START){
                game_paused = !game_paused;
            }
            if ((just_pressed & J_SELECT) == J_SELECT){
                world_init();
                SPRITES_8x8;
                SHOW_SPRITES;
                SHOW_BKG;
                winning_condition = 0;
            }
        }
    }
    if (winning_condition == 1){
        printf("\n\n\n\n\n     you win!\n");
        HIDE_SPRITES;
    }
    if (winning_condition == 2){
        printf("\n\n\n\n\n     you lose!\n");
        HIDE_SPRITES;
    }
}