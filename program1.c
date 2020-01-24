#include <stdio.h>
#include <stdlib.h>


int input[11][3] = {{-7, 10, 4}, { -7, 9, 4}, {-7, 10, 5}, {-10, 10, 4}, {236, 10, 8}, {0354, 8, 8}, {0xEB, 16, 8}, {-125, 10, 8}, {65400, 10, 8}, {65400, 10, 16}, {-32701, 10, 16}};

void dec2bin(int dec){
	int absdec = abs(dec);
	if(absdec > 1)
		dec2bin(absdec/2);

	printf("%d", absdec % 2);
	return;
}

void dec2binmag(int dec){
	if(dec < 1){
		printf("1");
		dec2bin(dec);
	}
	else{
		printf("0");
		dec2bin(dec);
	}
	return;
}

void dec2bin1s(int dec, int operand) 
{ 
    int i; 
    for (i = 1 << operand; i > 0; i = i / 2) 
        (~(abs(dec)) & i)? printf("1"): printf("0"); 
} 

void dec2bin2s(int dec, int operand) 
{ 
    int i; 
    for (i = 1 << operand; i > 0; i = i / 2) 
        (dec & i)? printf("1"): printf("0"); 
} 

int main(void) {

	for(int i=0; i < 11; i++){
		if(((input[i][1] == 8) || (input[i][1] == 10) || (input[i][1] == 16)) && ((input[i][2] == 4) || (input[i][2] == 8) || (input[i][2] == 16))){
			printf("input: {%d, %d, %d}\n", input[i][0], input[i][1], input[i][2]);

			printf("Binary (abs): 0b");
			dec2bin(input[i][0]);
			printf("\n");

			printf("Octal (abs): %o\n", abs(input[i][0]));

			printf("Decimal (abs): %d\n", abs(input[i][0]));

			printf("Hex (abs): 0x%x\n", abs(input[i][0]));

			// for(int j=0; j < input[i][2]; j++){

			// }
			printf("Binary (1's): 0b");
			dec2bin1s(input[i][0], input[i][2]);
			printf("\n");

			printf("Binary (2's): 0b");
			dec2bin2s(input[i][0], input[i][2]);
			printf("\n");

			printf("Binary (sign mag): 0b");
			dec2binmag(input[i][0]);
			printf("\n");


		}
		else{
			printf("Error\n");
		}
	}

  // printf("input[0][0]: %d, %d, %d\n", input[0][0], input[0][1], input[0][2]);
  // printf("input[0][0]: %d, %d, %d\n", input[6][0], input[6][1], input[6][2]);

  return 0;
}
