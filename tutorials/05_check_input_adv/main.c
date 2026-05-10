#include <gb/gb.h>
#include <stdio.h>

void main(void){
    uint8_t currentspriteindex = 0;

    // binary "and": if both bits are 1, the result is 1, otherwise it's 0
    // the result displays only the truth value of the last bit, 
    // so if the last bit is 0, the result is 0, and if the last bit is 1, the result is 1
    printf("3 & 9: %d\n",3 & 9);
    printf("2 & 8: %d\n",2 & 8);
    printf("3 & 8: %d\n",3 & 8);

    // binary shift right: shifts the bits to the right, filling in with 0s on the left
    printf("2: %d\n",2);
    printf("2 >> 1: %d\n",2 >> 1);
    printf("4: %d\n",4);
    printf("4 >> 1: %d\n",4 >> 1);
    printf("8: %d\n",8);
    printf("8 >> 1: %d\n",8 >> 1);

    printf(" === === === \n");

    // printf("J_RIGHT: %d\n",J_RIGHT); // 1
    // printf("J_LEFT: %d\n",J_LEFT); // 2
    // printf("J_UP: %d\n",J_UP); // 4
    // printf("J_DOWN: %d\n",J_DOWN); // 8
    // printf("J_A: %d\n",J_A); // 16
    // printf("J_B: %d\n",J_B); // 32
    // printf("J_SELECT: %d\n",J_SELECT); // 64
    // printf("J_START: %d\n",J_START); // 128

    // checking button combinations
    // left is 2 (00000010) and down is 8 (00001000), 
    // so if both are pressed, the output of the joypad will 
    // include both (00001010), so it will be 10

    // left and down is 10, so we consider that the joypad output is 10
    printf("(10 & J_LEFT) >> 1: %d\n",(10 & J_LEFT) >> 1);
    printf("(10 & J_DOWN) >> 3: %d\n",(10 & J_DOWN) >> 3);
    // (10 & J_LEFT): checks if J_LEFT is pressed in the joypad output, 
    // and if it is, it will return 2 (00000010), otherwise it will return 0 (00000000)
    //
    // (10 & J_DOWN): checks if J_DOWN is pressed in the joypad output, 
    // and if it is, it will return 8 (00001000), otherwise it will return 0 (00000000)
    //
    // the right shift operator (>>): shifts the bits to the right, filling in with 0s on the left, 
    // - If the result of the binary "and" is 2 (00000010), it will be shifted 1 place to the right
    // and produce 1 (00000001). 
    // - If the result of the binary "and" is 8 (00001000), it will be shifted 3 places to the right
    // and produce 1 (00000001).

    // while(1){
    //     delay(100); // delay to prevent spamming the console with values
    //     uint8_t joypad_value = joypad();
    //     printf("Joypad value: %d\n", joypad_value);

    // }
}