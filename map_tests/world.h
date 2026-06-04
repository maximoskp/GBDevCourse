#include "character.h"
#include "map/map_tiles.c"
#include "map/map.c"

Character player;
Key key;
Rabbit rabbit;

void world_init(){
    character_init(&player, 80, 72);
    key_init(&key, 30, 24);
    rabbit_init(&rabbit, 45, 34);
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
    (top_left == 3 || top_right == 3 || bottom_left == 3 || bottom_right == 3)) {
        return 1;
    }
    return 0;
}

uint8_t player_close_to_door(){
    uint8_t top = (player.y-16 + 4 )/8;
    uint8_t bottom = (player.y-16 + 7 + 4 )/8;
    uint8_t left = (player.x-8 + 4 )/8;
    uint8_t right = (player.x-8 + 7 + 4 )/8;

    uint8_t top_left = map[top * 20 + left];
    uint8_t top_right = map[top * 20 + right];
    uint8_t bottom_left = map[bottom * 20 + left];
    uint8_t bottom_right = map[bottom * 20 + right];

    if (top_left == 3 || top_right == 3 || bottom_left == 3 || bottom_right == 3) {
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

uint8_t move_player(uint8_t joypad_key, uint8_t just_pressed){
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
    if (player.has_key){
        key.x = player.x + 7;
        key.y = player.y;
        move_sprite(1, key.x, key.y);
    }
    if (player_close_to_door() && player.has_key){
        return 1;
    }
    return 0;
}

void move_rabbit(){
    uint8_t horizontal_motion = 0;
    uint8_t vertical_motion = 0;

    if (rabbit.x < player.x){
        horizontal_motion = 1;
    } else if (rabbit.x > player.x){
        horizontal_motion = -1;
    }
    if (rabbit.y < player.y){
        vertical_motion = 1;
    } else if (rabbit.y > player.y){
        vertical_motion = -1;
    }

    if (!world_is_solid(rabbit.x + horizontal_motion, rabbit.y + vertical_motion)){
        rabbit.x += horizontal_motion;
        rabbit.y += vertical_motion;
        scroll_sprite(2,horizontal_motion,vertical_motion);
    }
}

uint8_t world_control_character(uint8_t joypad_key, uint8_t just_pressed){
    if(++player.current_motion_frame >= player.frame_to_update_motion){
        uint8_t result = move_player(joypad_key, just_pressed);
        if (result == 1){
            return 1;
        }
        move_rabbit();
        if (rabbit.x < player.x + 8 && rabbit.x + 8 > player.x &&
            rabbit.y < player.y + 8 && rabbit.y + 8 > player.y) {
            return 2;
        }
    }
    if ( (just_pressed & J_A) == J_A ){
        if (player.has_key){
            player.has_key = 0;
        } else if (player_touches_key()){
            player.has_key = 1;
        }
    }
    return 0;
}