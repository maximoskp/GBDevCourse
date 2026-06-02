#include "character.h"
#include "map/map_tiles.c"
#include "map/map.c"

Character player;

void world_init(){
    character_init(&player, 80, 72);
    set_bkg_data(0, 3, map_tiles);
    set_bkg_tiles(0, 0, 20, 18, map);
}

uint8_t world_is_solid(uint8_t x, uint8_t y){
    uint8_t top = (y-16)/8;
    uint8_t bottom = (y-16 + 7)/8;
    uint8_t left = (x-8)/8;
    uint8_t right = (x-8 + 7)/8;

    uint8_t top_left = map[top * 20 + left];
    uint8_t top_right = map[top * 20 + right];
    uint8_t bottom_left = map[bottom * 20 + left];
    uint8_t bottom_right = map[bottom * 20 + right];

    if ((top_left == 1 || top_right == 1 || bottom_left == 1 || bottom_right == 1) ||
    (top_left == 2 || top_right == 2 || bottom_left == 2 || bottom_right == 2)) {
        return 1;
    }
    return 0;
}

void world_control_character(uint8_t joypad_key){
    if(++player.current_motion_frame >= player.frame_to_update_motion){
        player.current_motion_frame = 0;
        player.horizontal_motion = -1*( (J_LEFT & joypad_key)>>1 ) + (J_RIGHT & joypad_key);
        player.vertical_motion = -1*( (J_UP & joypad_key)>>2 ) + ( (J_DOWN & joypad_key)>>3 );
        
        if ( player.horizontal_motion || player.vertical_motion ){
            if( ++player.current_animation_subframe >= player.subframe_to_update_animation ){
                player.current_animation_subframe = 0;
                player.current_sprite_index = (player.current_sprite_index + 1) % 2;
            }
            set_sprite_tile(0, player.current_sprite_index+1);
        }
        if (!player.horizontal_motion && !player.vertical_motion){
            // current_animation_subframe = 0;
            player.current_sprite_index = 0;
            set_sprite_tile(0, player.current_sprite_index);
        }
        if (world_is_solid(player.x + player.horizontal_motion, player.y + player.vertical_motion)){
            player.horizontal_motion = 0;
            player.vertical_motion = 0;
        }
        player.x += player.horizontal_motion;
        player.y += player.vertical_motion;
        scroll_sprite(0,player.horizontal_motion,player.vertical_motion);
    }
}