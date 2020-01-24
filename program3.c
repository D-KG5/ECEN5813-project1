#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define RIGHT 1
#define LEFT 0

void hex2bin(int hex) {
	printf("Binary: ");  
    for (int i = 1 << 15; i > 0; i = i / 2){
        (hex & i)? printf("1"): printf("0"); 
    }
    printf("    ");
}

void bincheck(int hex) {
	printf("Result: "); 
	int cnt = 0; 
    for (int i = 1 << 3; i > 0; i = i / 2){
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

/*Function to rotate n by rot bits. Direction is set by dir*/
int rotate(int n, int rot, int dir) { 
	int res = 0;
	switch(dir){
		case(LEFT):
			/* In n<<d, last d bits are 0. To put first 3 bits of n at  
			last, do bitwise or of n<<d with n >>(INT_BITS - d) */
			res = (n << rot)|(n >> (16 - rot));
			break;
		case(RIGHT):
			/* In n>>d, first d bits are 0. To put last 3 bits of at  
			first, do bitwise or of n>>d with n <<(INT_BITS - d) */
			res = (n >> rot)|(n << (16 - rot)); ;
			break;
		default:
			printf("Error rotating\n");
			res = -1;
	}
   return res; 
}

int main(){
    int input = 0xFACE;

    printf("Original: 0x%X\n", input);

    int ogarr[3];

    ogarr[3] = (input >> 12) & 0xF;	// F
    ogarr[2] = (input >> 8) & 0xF;	// A
    ogarr[1] = (input >> 4) & 0xF;	// C
    ogarr[0] = input & 0xF;	// E

    // for (int i = 3; i > -1; i--) {
    //     printf("%X", ogarr[i]);
    // }
    // printf("\n");

    hex2bin(input);
    bincheck(ogarr[0]);

    int rev = ((ogarr[0] << 12) | (ogarr[1] << 8) | (ogarr[2] << 4) | (ogarr[3]));
    
    printf("Reversed: 0x%X\n", rev);

    int revarr[3];
    revarr[3] = ogarr[0];	// E
    revarr[2] = ogarr[1];	// C
    revarr[1] = ogarr[2];	// A
    revarr[0] = ogarr[3] & 0xF;	// F

    // printf("%X\n", revarr[3]);
    // printf("%X\n", revarr[2]);
    // printf("%X\n", revarr[1]);
    // printf("%X\n", revarr[0]);

    // for (int j = 3; j > -1; j--) {
    //     printf("%X", revarr[j]);
    // }
    // printf("\n");

    hex2bin(rev);
    bincheck(revarr[0]);


    int rot_left = rotate(input, 6, LEFT);
    printf("Rotated left: 0x%X\n", rot_left);
    hex2bin(rot_left);
    printf("\n");

    int rot_right = rotate(input, 6, RIGHT);
    printf("Rotated right: 0x%X\n", rot_right);
    hex2bin(rot_right);
    printf("\n");

    return 0;
}
