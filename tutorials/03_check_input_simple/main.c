#include <gb/gb.h>
#include <stdio.h>

void main(void){
    uint8_t currentspriteindex = 0;

    // printf("J_RIGHT: %d\n", J_RIGHT);
    // printf("J_LEFT: %d\n", J_LEFT);
    // printf("J_UP: %d\n", J_UP);
    // printf("J_DOWN: %d\n", J_DOWN);
    // printf("J_A: %d\n", J_A);
    // printf("J_B: %d\n", J_B);
    // printf("J_SELECT: %d\n", J_SELECT);
    // printf("J_START: %d\n", J_START);

    while(1){
        delay(100); // delay to prevent spamming the console with values
        uint8_t joypad_value = joypad();
        // printf("Joypad value: %d\n", joypad_value);
        if(joypad_value == J_A){
            printf("A pressed\n");
        }
        if(joypad_value == J_B){
            printf("B pressed\n");
        }
    }
}