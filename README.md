# miniprocessor
Implementation of a bit interpreter similar to a processor. It has the capability to decode and execute simple instructions for addition, subtraction, multiplication, and division

# First Task:
## Interpret the instruction given
In the main:

1. Read the instruction inst.
2. Print N by calling the function get_N(inst):\
   Function get_N (returns the value of N):
- Use a mask to obtain the bits corresponding to N (the first 3 bits).
- Calculate the value of N by converting the binary number obtained into decimal.
- Return the obtained number + 1.
3. Iterate through all operations in a loop and print them by calling the function get_Nth_op():
   Function get_Nth_op (returns the N-th operation):
  - Use a mask to obtain the two bits corresponding to the N-th operation (divide by 2 raised to the -position of the bit to be found - and find the remainder when divided by 2).
  -  Use the following encoding to determine the operation:
     - 0 - '+'
     - 01 - '\-'
     - 10 - '*'
     - 11 - '/'
- Return the operation.
4. Print Dim by calling the function get_dim():\
   Function get_dim (returns the value of Dim):
  - Use a mask to obtain the 4 bits corresponding to the dimension (dim).
These bits immediately follow the bits corresponding to the operations.
- Convert the obtained binary number into decimal.
-  Return the obtained number + 1.

# Second Task:
## Execute instruction (without operator precedence rule)

1. Read the first instruction, inst.
2. Obtain the values for N and Dim by calling the functions get_N() and get_dim().
3. Store the operations in a char pointer (operations) by calling the function get_Nth_op().
4. Find out how many instructions are being read for operands (nr_citiri) using the formula provided in the statement.
5. Initialize the result to 0.
6. Read the instructions for operands (instr).
7. Use a mask to determine the bits corresponding to each operand (iterate through instr in sections of size Dim).
8. Convert the binary number obtained into decimal.
9. Perform the calculation between the result (everything before the current operand) and the current operand using the operation corresponding to the two (the operation with the index contor-1).
10. Print the result.
    
# Third task:
## Execute instructions when operands have weird dimensions (not divisible by 4)

In the main:

1. Read the first instruction, inst.
2. Obtain the values for N and Dim by calling the functions get_N() and get_dim().
3. Store the operations in a char pointer (operations) by calling the function get_Nth_op().
4. "contor" - a counter used to keep track of how many operands have been processed.
5. Initialize the result to 0.
6. Read the instructions for operands (instr).
7. For each individual instruction:\
- Break down the instruction into "chunks" of bits, each of size Dim.
- Find the bits using a mask (bit position is determined by 2 raised to the power of the bit's position, and the remainder when divided by 2), and convert the obtained number from decimal to binary.
- If a "chunk" is too large, find the bits that fit within the current instruction and convert the number from binary to decimal.
- Then, move on to the next instruction and find the remaining bits. Concatenate the bits, and convert the resulting number from base 2 to base 10.
8. Perform the calculation between the result (everything before the current operand) and the current operand using the operation corresponding to the two (the operation with index contor-1).
9. Print the result.

# Fourth Task
## Execute instruction (with operator precedence rule)

1. Read the first instruction, inst.
2. Obtain the values for N and Dim by calling the functions get_N() and get_dim().
3. Store the operations in a char pointer (operations) by calling the function get_Nth_op().
4. prioritate_op - a vector that contains the priorities of operations from the "operations" vector (0 for + or -, 1 for * or /). It is obtained by calling the function "prioritate_operatie," which assigns a priority to each operation.\
	The function takes three parameters:
	- the number of operations, "N"
	- the "operations" vector
	- the "prioritate_op" vector\
	Iterate through the "operations" vector element by element.\
	Each element of "operations" is assigned a number (0 for + or -, 1 for * or /) that signifies the operation's priority.
5. operanzi - a vector that contains the operands (in base 10).\
The vector is obtained by calling the function get_operanzi, which is an extension of the functionality from task 3. Instead of calculating a result, each time an operand is obtained, it is stored in the "operanzi" vector.
6. Calculate the result using the function "calculator":\
The function takes four parameters:
- N = the number of operations
- the "operanzi" vector
- the "operations" vector
- the "prioritate_op" vector\
Iterate through all operands, starting from the second one (index 1), in a "for" loop from 0 to N.\
Distinguish the following cases:\
i. The first operation in the sequence has a priority of 1:\
Perform all successive operations with a priority of 1 until you encounter an operation with a priority of 0 or reach the end of the operation sequence.\
Store the result in a variable, "rezultat."\
Jump from the current index to the index of the last term used and continue the algorithm.
ii. The first operation in the sequence has a priority of 0, but a priority-1 operation follows it:\
Perform all successive operations with a priority of 1 that follow until you encounter an operation with a priority of 0 or reach the end of the operation sequence.\
Store the result in an intermediate result variable, "rezultat intermediar."\
Perform the first operation between the intermediate result and the first operand.\
Store the result in a variable, "rezultat."\
Jump from the current index to the index of the last term used and continue the algorithm.\
iii. The operations before and after the current operand have a priority of 0:\
Perform the calculation between the result and the current operand.\
Store the result in the "rezultat" variable.\
iv. Move on to a new iteration.\
Return the value of the "rezultat" variable.\
7. Display the result.
