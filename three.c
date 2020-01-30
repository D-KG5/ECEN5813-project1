#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
    Program three by Dhruva Koley and Sagar Eligar
*/

// macros for rotate function
#define RIGHT 1
#define LEFT 0

/* 
   adaptation of dec2bin1s function from program one
   inspired by https://www.geeksforgeeks.org/binary-representation-of-a-given-number/
   Author: Narendra Kangralkar
*/
void hex2bin(uint16_t hex) {
	printf("Binary: ");
    // iterate over 16 bits of hex variable
    for (uint16_t i = 1 << 15; i > 0; i = i / 2){
        (hex & i) ? printf("1") : printf("0"); 
    }
    printf("    ");
}

// function to check if last 4 bits of binary contain 3 ones and print if True or False
void bincheck(uint16_t hex) {
	printf("Result: "); 
	uint8_t cnt = 0; 
    // iterate over last 4 bits and increment cnt if '1' is detected
    for (uint8_t i = 1 << 4; i > 0; i = i / 2){
        if(hex & i){
        	cnt++;
    	} 
    }
    if(cnt == 3){
    	printf("True\n");
    } else{
    	printf("False\n");
    }
} 

/* 
    Function to rotate n by rot bits. Direction is set by dir
    inspired by https://www.geeksforgeeks.org/rotate-bits-of-an-integer/
    Author: SoumikMondal 
*/
uint16_t rotate(uint16_t num, uint8_t rot, uint8_t dir) { 
	uint16_t res = 0;
	switch(dir){
		case(LEFT):
			/* 
                Left shift num by rot 
                Bitwise OR of that with right shift num by (16 bits - rot)
                to put first rot bits of num at lsb 
            */
			res = (num << rot) | (num >> (16 - rot));
			break;
		case(RIGHT):
            /* 
                Right shift num by rot 
                Bitwise OR of that with left shift num by (16 bits - rot)
                to put first rot bits of num at lsb 
            */
			res = (num >> rot) | (num << (16 - rot)); ;
			break;
		default:
			printf("Error rotating\n");
			res = -1;
	}
   return res; 
}

int main(){
    uint16_t input = 0xFACE;

    printf("Original: 0x%X\n", input);

    // split input into bytes to get each individual hex per array index
    uint16_t ogarr[3];
    ogarr[3] = (input >> 12) & 0xF;	// F
    ogarr[2] = (input >> 8) & 0xF;	// A
    ogarr[1] = (input >> 4) & 0xF;	// C
    ogarr[0] = input & 0xF;	// E

    // print binary and check last 4 bits for exactly 3 'ones'
    hex2bin(input);
    bincheck(ogarr[0]);

    // concatenate original input array backwards to get input hex in reverse
    uint16_t rev = ((ogarr[0] << 12) | (ogarr[1] << 8) | (ogarr[2] << 4) | (ogarr[3]));
    
    printf("Reversed: 0x%X\n", rev);
    // assign original input array to reverse array but in reverse
    uint16_t revarr[3];
    revarr[3] = ogarr[0];	// E
    revarr[2] = ogarr[1];	// C
    revarr[1] = ogarr[2];	// A
    revarr[0] = ogarr[3];	// F

    // print binary and check last 4 bits for exactly 3 'ones'
    hex2bin(rev);
    bincheck(revarr[0]);

    // rotate input hex left by 6
    uint16_t rot_left = rotate(input, 6, LEFT);
    printf("Rotated left by 6: 0x%X\n", rot_left);

    hex2bin(rot_left);
    uint16_t rot_left_bits = rot_left & 0xF;
    bincheck(rot_left_bits);

    // rotate input hex right by 6
    uint16_t rot_right = rotate(input, 6, RIGHT);
    printf("Rotated right by 6: 0x%X\n", rot_right);

    hex2bin(rot_right);
    uint16_t rot_right_bits = rot_right & 0xF;
    bincheck(rot_right_bits);

    return 0;
}
