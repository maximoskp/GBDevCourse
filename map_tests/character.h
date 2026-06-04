#include <gb/gb.h>
#include <stdio.h>
#include "sprites/walker3.c"
#include "sprites/key_sprite.c"
#include "sprites/killer_rabbit_sprite.c"

typedef struct {
    uint8_t x;
    uint8_t y;

    uint8_t current_sprite_index;
    uint16_t current_motion_frame;
    uint16_t frame_to_update_motion;
    uint16_t current_animation_subframe;
    uint16_t subframe_to_update_animation;

    uint8_t horizontal_motion;
    uint8_t vertical_motion;

    uint8_t has_key;
} Character;

typedef struct {
    uint8_t x;
    uint8_t y;
} Key;

typedef struct {
    uint8_t x;
    uint8_t y;
} Rabbit;

void character_init(Character* c , uint8_t x, uint8_t y){
    c->x = x;
    c->y = y;

    c->current_sprite_index = 0;
    c->current_motion_frame = 0;
    c->frame_to_update_motion = 100;
    c->current_animation_subframe = 0;
    c->subframe_to_update_animation = 5;

    c->horizontal_motion = 0;
    c->vertical_motion = 0;

    c->has_key = 0;

    set_sprite_data(0, 3, walker);
    set_sprite_tile(0, c->current_sprite_index);
    move_sprite(0, c->x, c->y);
}

void key_init(Key* k, uint8_t x, uint8_t y){
    k->x = x;
    k->y = y;

    set_sprite_data(3, 0, key_sprite);
    set_sprite_tile(1, 3);
    move_sprite(1, k->x, k->y);
}

void rabbit_init(Rabbit* r, uint8_t x, uint8_t y){
    r->x = x;
    r->y = y;

    set_sprite_data(4, 0, killer_rabbit_sprite);
    set_sprite_tile(2, 4);
    move_sprite(2, r->x, r->y);
}

void control_character(Character* c, uint8_t joypad_key){
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
        scroll_sprite(0,c->horizontal_motion,c->vertical_motion);
    }
}