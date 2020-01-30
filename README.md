# ECEN5813-project1
PES Project 1 for ECEN 5813. By Dhruva Koley and Sagar Eligar

# Contents
- ProgramOne.out: output file for program one
- ProgramTwo.out: output file for program two
- ProgramThree.out: output file for program three
- one.c: source code for program one
- two.c: source code for program two
- three.c: source code for program three
- makefile

# Comments
Output formatting for program one is a bit off but should still be readable
For some input values and operands, the printed **absolute** binary is shorter than the operand size. E.g. Value of -7 with operand of 4 would print 0b111 instead of 0b0111. However, no actual information is lost since its a representation of the absolute of the value.
Behaviour for program three is that the binary checker will test for **exactly** 3 'ones' in the last 4 bits.

# Environment
 - Ubuntu 18.04 LTS
 - GCC