#include "character.h"
#include "map/map_tiles.c"
#include "map/map.c"

Character player;
Key key;
Bandit bandit;

uint8_t win_condition = 0;

void world_init(){
    character_init(&player, 80, 72);
    key_init(&key, 30, 24);
    bandit_init(&bandit, 150, 72);
    set_bkg_data(0, 4, map_tiles);
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
            (top_left == 2 || top_right == 2 || bottom_left == 2 || bottom_right == 2) || 
            (top_left == 3 || top_right == 3 || bottom_left == 3 || bottom_right == 3)){
        return 1;
    }
    return 0;
}

uint8_t player_touches_key(){
    if (player.x < key.x + 8 && player.x + 8 > key.x &&
        player.y < key.y + 8 && player.y + 8 > key.y) {
            return 1;
    }
    return 0;
}

uint8_t player_touches_door(){
    uint8_t top = (player.y-16 + 4)/8;
    uint8_t bottom = (player.y-16 + 7 + 4)/8;
    uint8_t left = (player.x-8 + 4)/8;
    uint8_t right = (player.x-8 + 7 + 4)/8;

    uint8_t top_left = map[top * 20 + left];
    uint8_t top_right = map[top * 20 + right];
    uint8_t bottom_left = map[bottom * 20 + left];
    uint8_t bottom_right = map[bottom * 20 + right];
    if (top_left == 3 || top_right == 3 || bottom_left == 3 || bottom_right == 3){
        return 1;
    }
    return 0;
}

void move_bandit(){
    uint8_t horizontal_motion = 0;
    uint8_t vertical_motion = 0;
    if (bandit.x < player.x){
        horizontal_motion = 1;
    } else if (bandit.x > player.x){
        horizontal_motion = -1;
    }
    if (bandit.y < player.y){
        vertical_motion = 1;
    } else if (bandit.y > player.y){
        vertical_motion = -1;
    }
    if (!world_is_solid(bandit.x + horizontal_motion, bandit.y + vertical_motion)){
        bandit.x += horizontal_motion;
        bandit.y += vertical_motion;
        scroll_sprite(2,horizontal_motion,vertical_motion);
    }
     if (player.x < bandit.x + 8 && player.x + 8 > bandit.x &&
        player.y < bandit.y + 8 && player.y + 8 > bandit.y) {
            win_condition = -1;
    }
}

uint8_t world_control_character(uint8_t joypad_key, uint8_t just_pressed_joypad_key){
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
        if (player.is_holding_key){
            key.x = player.x+7;
            key.y = player.y;
            move_sprite(1, key.x, key.y);
        }
        if (player.is_holding_key && player_touches_door()){
            win_condition = 1;
        }else{
            move_bandit();
        }
    }
    if ( (just_pressed_joypad_key & J_A) == J_A ){
        if (player.is_holding_key){
            player.is_holding_key = 0;
        } else if (player_touches_key()){
            player.is_holding_key = 1;
            key.x = player.x+7;
            key.y = player.y;
            move_sprite(1, key.x, key.y);
        }
    }
    return win_condition;
}