#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// input 2D array
int32_t input[11][3] = {{-7, 10, 4}, { -7, 9, 4}, {-7, 10, 5}, {-10, 10, 4}, {236, 10, 8}, {0354, 8, 8}, {0xEB, 16, 8}, {-125, 10, 8}, {65400, 10, 8}, {65400, 10, 16}, {-32701, 10, 16}};

static FILE *fptr;	// declare file pointer for output file

/*
	recursive function to print binary of an absolute decimal
	inspired by https://www.geeksforgeeks.org/binary-representation-of-a-given-number/
*/
void dec2bin(int32_t dec){
	uint32_t absdec = abs(dec);
	if(absdec > 1){
		dec2bin(absdec / 2);
	}

	fprintf(fptr, "%d", absdec % 2);
	return;
}

// wrapper function to print sign magnitude binary from a decimal
void dec2binmag(int32_t dec, uint16_t operand){
	// check if value fits inside operand limited integer value size
if((((dec >= -8)  && (dec <= 7)) && (operand == 3)) || 
	(((dec >= -128)  && (dec <= 127)) && (operand == 7)) || 
	(((dec >= -32768)  && (dec <= 32767)) && (operand == 15))){
		// if decimal is positive then print 1 and invoke dec2bin, else print 0 and invoke dec2bin
		if(dec < 0){
			fprintf(fptr, "1");
			dec2bin(dec);
		}
		else{
			fprintf(fptr, "0");
			dec2bin(dec);
		}
	} else{
		fprintf(fptr, "Error	");
	}
	return;
}

/*
	function to print 1's complement binary. 
	inspired by https://www.geeksforgeeks.org/binary-representation-of-a-given-number/
*/
void dec2bin1s(int32_t dec, uint16_t operand){
	// check if value fits inside operand limited integer value size
	if((((dec >= -8)  && (dec <= 7)) && (operand == 3)) || 
		(((dec >= -128)  && (dec <= 127)) && (operand == 7)) || 
		(((dec >= -32768)  && (dec <= 32767)) && (operand == 15))){
	    int32_t i; 
	    // iterate over decimal of bit size (operand) and print 1 or 0 based on its negated absolute value
	    for (i = 1 << operand; i > 0; i = i / 2){
	        (~(abs(dec)) & i) ? fprintf(fptr, "1") : fprintf(fptr, "0"); 
	    }
	} else{
		fprintf(fptr, "Error	");
	}
} 

// function to print 2's complement binary. Adapted from dec2bin1s
void dec2bin2s(int32_t dec, uint16_t operand){
		// check if value fits inside operand limited integer value size
	if((((dec >= -8)  && (dec <= 7)) && (operand == 3)) || 
		(((dec >= -128)  && (dec <= 127)) && (operand == 7)) || 
		(((dec >= -32768)  && (dec <= 32767)) && (operand == 15))){
	    int32_t i; 
	    // iterate over decimal of bit size (operand)
	    for (i = 1 << operand; i > 0; i = i / 2){
	        (dec & i) ? fprintf(fptr, "1") : fprintf(fptr, "0"); 
	    }
    } else{
		fprintf(fptr, "Error	");
	}
} 

int main(void){
	// open output file for writing
	fptr = fopen("ProgramOne.out", "w");
	if(fptr == NULL){
		printf("Couldn't open file\n");
		return -1;
	}

	// iterate over 2D array (input[i][0] = value, input[i][1] = radix, input [i][2] = operand)
	for(int i = 0; i < 11; i++){
		// print headers for each input variable to file
		fprintf(fptr, "\nInput:				Value %d    Radix %d		Operand %d\n", input[i][0], input[i][1], input[i][2]);
		// check if radix and operands are valid, else print Error to file. Formatting is wonky though
		if(((input[i][1] == 8) || (input[i][1] == 10) || (input[i][1] == 16)) && ((input[i][2] == 4) || (input[i][2] == 8) || (input[i][2] == 16))){
			// print headers for each input variable to file
			fprintf(fptr, "Output:				Value		Maximum		Minimum\n");

			// print absolute binary of input variable to file
			fprintf(fptr, "Binary (abs):			0b");
			dec2bin(input[i][0]);

			// print maximum of absolute binary to file
			fprintf(fptr, "	0b");
			double max_size = pow((double)2, (double)input[i][2]);
			max_size -= 1;
			dec2bin((uint32_t)max_size);

			// print minimum of absolute binary to file
			fprintf(fptr, "	0b");
			dec2bin2s(0, (input[i][2] - 1));

			// print val, max, min for absolute octal, decimal, hex to file
			fprintf(fptr, "\nOctal (abs):		           0%o       	0%o			0\n", abs(input[i][0]), (uint32_t)max_size);

			fprintf(fptr, "Decimal (abs): 		         %d        	%d			0\n", abs(input[i][0]), (uint32_t)max_size);

			fprintf(fptr, "Hex (abs):    		        0x%X       	0x%X			0x0\n", abs(input[i][0]), (uint32_t)max_size);

			// print 1's complement binary to file
			fprintf(fptr, "Binary (1's):			0b");
			dec2bin1s(input[i][0], (input[i][2] - 1));

			// print max 1's complement binary to file
			double max_size1 = pow((double)2, ((double)input[i][2]));
			max_size1 -= 1;
			fprintf(fptr, "	0b");
			dec2bin((uint32_t)max_size1);

			// print min 1's complement binary to file
			double min_size1 = pow((double)2, ((double)input[i][2] - 1));
			fprintf(fptr, "	0b");
			dec2bin((uint32_t)min_size1);
			fprintf(fptr, "\n");

			// print 2's complement binary to file
			fprintf(fptr, "Binary (2's):			0b");
			dec2bin2s(input[i][0], (input[i][2] - 1));

			// print max 2's complement binary to file
			double max_size2 = pow((double)2, ((double)input[i][2]));
			max_size2 -= 1;
			fprintf(fptr, "	0b");
			dec2bin((uint32_t)max_size2);

			// print min 2's complement binary to file
			double min_size2 = pow((double)2, ((double)input[i][2] - 1));
			min_size2 += 1;
			fprintf(fptr, "	0b");
			dec2bin((uint32_t)min_size2);

			fprintf(fptr, "\n");

			// print sign magnitude binary to file
			fprintf(fptr, "Binary (sign mag):		0b");
			dec2binmag(input[i][0], (input[i][2] - 1));

			// print max sign magnitude binary to file
			double max_sizem = pow((double)2, ((double)input[i][2] - 1));
			max_sizem -= 1;
			fprintf(fptr, "	0b");
			dec2binmag((uint32_t)max_sizem, (input[i][2] - 1));

			// print min sign magnitude binary to file
			fprintf(fptr, "	0b");
			dec2binmag(-((uint32_t)max_sizem), (input[i][2] - 1));
			fprintf(fptr, "\n");
		} else{
			fprintf(fptr, "Error: not a valid operand or radix\n");
		}
	}
	fclose(fptr);
	return 0;
}
