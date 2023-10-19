# miniprocessor
Implementation of a bit interpreter similar to a processor. It has the capability to decode and execute simple instructions for addition, subtraction, multiplication, and division

# First Task:
## Interpret the instruction given
In the main:

1. Read the instruction inst.
2. Print N by calling the function get_N(inst):
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
4. Print Dim by calling the function get_dim():
   Function get_dim (returns the value of Dim):
  - Use a mask to obtain the 4 bits corresponding to the dimension (dim).
These bits immediately follow the bits corresponding to the operations.
- Convert the obtained binary number into decimal.
-  Return the obtained number + 1.

# Second Task:
## Execute instruction (without operator precedence rule)

In main:
1. Se citeste prima instructiune inst
2. Se obtin valorile pentru N si Dim apeland functiile get_N() si get_dim()
3. Intr-un pointer de char-uri (operatii) se retin operatiile apeland functia
get_Nth_op()
5. Se afla cate instructiuni se citesc apoi pentru operanzi (nr_citiri) 
folosind formula
din enunt 
4. contor = contor folosit pentru a sti cati operanzi s-au parcurs
5. Se initializeaza rezultatul cu 0
6. Se citesc instructiunile pentru operanzi (instr)
7. Folosind o masca se afla bitii corespunzatori pentru fiecare operand
(instr se parcurge instr in sectiuni de dimensiunea Dim)
8. Se transforma numarul astfel aflat din binar in zecimal
9. Se reazlizeaza calculul dintre rezultat (tot ce a fost inainte de operandul
actual) si operandul actual folosind operatia corespunzatoare celor doi 
(operatia cu indexul contor-1)
10. Se printeaza rezultatul

# Third task:
## Execute instructions when operands have weird dimensions (not divisible by 4)

In the main:

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

# Fourth Task
## Execute instruction (with operator precedence rule)

1. Read the first instruction, inst.
2. Obtain the values for N and Dim by calling the functions get_N() and get_dim().
3. Store the operations in a char pointer (operations) by calling the function get_Nth_op().
4. prioritate_op - a vector that contains the priorities of operations from the "operations" vector (0 for + or -, 1 for * or /). It is obtained by calling the function "prioritate_operatie," which assigns a priority to each operation.
	The function takes three parameters:
	- the number of operations, "N"
	- the "operations" vector
	- the "prioritate_op" vector
	Iterate through the "operations" vector element by element.
	Each element of "operations" is assigned a number (0 for + or -, 1 for * or /) that signifies the operation's priority.
5. "operanzi" - vectorul care contine operanzii (in baza 10)
Vectorul se obtine apeland functia get_operanzi care este o extindere a
functionalitatii task-ului 3. In loc sa se calculeze un rezultat, de fiecare
data cand se obtine un operand acesta se "retine" in vectorul operanzi
6. Rezultatul se calculeaza folosind functia "calculator":
Functia primeste 4 parametrii:
		- N = numarul de operatii
		- vectorul "operanzi" 
		- vectorul "operatii"
		- vectorul "prioritate_op"
Se parcurg toti operanzii, incepand de la cel de-al doilea (index 1), intr-un
"for" de la 0 la N
Se disting urmatoarele cazuri:
	i. Prima operatie din sir este de prioritate 1: 
	- se efectueaza toate operatiile de prioritate 1 succesive, pana se ajunge 
	la o operatie de prioritate 0 sau pana cand se ajunge la finalul sirului
    de operatii
	- se retine rezultatul intr-o variabila rezultat
	- se sare de la indexul actual la indexul ultimului termen utilizat si se
    continua algoritmul

	ii. Prima operatie din sir este de prioritate 0, dar dupa ea urmeaza o
	operatie de prioritate 1 
	- se efectueaza toate operatiile de prioritate 1 care urmeaza, pana se
    ajunge
	la o operatie de prioritate 0 sau pana cand se ajunge la finalul sirului
    de operatii
	- rezultatul se retine intr-o variabila intermediara de rezultat
    intermediar
	- se efectueaza si prima operatie, dintre rezultatul intermediar si primul
    operand
    - rezultatul se retine intr-o variabila rezultat
	- se sare de la indexul actual la indexul ultimului termen utilizat si se
    continua algoritmul

	iii. Operatiile de dinainte si de dupa operandul curent sunt de
    prioritate 0
	- se efectueaza calculul dintre rezultat si operandul curent 
	- rezultatul se retine in variabila rezultat

	*iv. se trece la o noua iteratie

	Se returneaza valoarea variabilei rezultat

7. Se afiseaza rezultatul 
 
