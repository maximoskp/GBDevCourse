#include <gb/gb.h>
#include <stdio.h>
#include "character.h"
#include "map/map_tiles.c"
#include "map/map.c"

#define WORLD_TILE_FREE    0x00
#define WORLD_TILE_SOLID_1 0x01
#define WORLD_TILE_SOLID_2 0x02

#define SPRITE_X_OFFSET 8
#define SPRITE_Y_OFFSET 16

void show_world(){
    set_bkg_data(0, 3, map_tiles);
    set_bkg_tiles(0, 0, 20, 18, map);
}

uint8_t is_solid_tile(uint8_t x, uint8_t y){
    uint8_t left   = (x - SPRITE_X_OFFSET) >> 3; // >> 3 is the same as /8, but faster
    uint8_t right  = (x + 7 - SPRITE_X_OFFSET) >> 3;
    uint8_t top    = (y - SPRITE_Y_OFFSET) >> 3;
    uint8_t bottom = (y + 7 - SPRITE_Y_OFFSET) >> 3;

    // check all 4 corners of the sprite, if any of them is a solid tile, then the whole tile is solid
    uint8_t top_left = map[top * 20 + left];
    uint8_t top_right = map[top * 20 + right];
    uint8_t bottom_left = map[bottom * 20 + left];
    uint8_t bottom_right = map[bottom * 20 + right];
    return (top_left == WORLD_TILE_SOLID_1) || (top_left == WORLD_TILE_SOLID_2) ||
           (top_right == WORLD_TILE_SOLID_1) || (top_right == WORLD_TILE_SOLID_2) ||
           (bottom_left == WORLD_TILE_SOLID_1) || (bottom_left == WORLD_TILE_SOLID_2) ||
           (bottom_right == WORLD_TILE_SOLID_1) || (bottom_right == WORLD_TILE_SOLID_2);
}

void world_control_character(Character* c, uint8_t joypad_key){
    if(++c->current_motion_frame >= c->frame_to_update_motion){
        c->current_motion_frame = 0;
        c->horizontal_motion = -1*( (J_LEFT & joypad_key)>>1 ) + (J_RIGHT & joypad_key);
        c->vertical_motion = -1*( (J_UP & joypad_key)>>2 ) + ( (J_DOWN & joypad_key)>>3 );
        
        if ( c->horizontal_motion || c->vertical_motion ){
            if( ++c->current_animation_subframe >= c->subframe_to_update_animation ){
                c->current_animation_subframe = 0;
                c->current_sprite_index = (c->current_sprite_index + 1) % 2;
            }
            set_sprite_tile(0, c->current_sprite_index+1);
        }
        if (!c->horizontal_motion && !c->vertical_motion){
            // current_animation_subframe = 0;
            c->current_sprite_index = 0;
            set_sprite_tile(0, c->current_sprite_index);
        }
        if (is_solid_tile(c->x + c->horizontal_motion, c->y + c->vertical_motion)){
            c->horizontal_motion = 0;
            c->vertical_motion = 0;
        }
        c->x += c->horizontal_motion;
        c->y += c->vertical_motion;
        scroll_sprite(0,c->horizontal_motion,c->vertical_motion);
    }
}