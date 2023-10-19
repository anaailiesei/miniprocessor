# miniprocessor
Implementation of a bit interpreter similar to a processor. It has the capability to decode and execute simple instructions for addition, subtraction, multiplication, and division

# First Task:
## Interpret the instruction given
In the main:

1. Read the instruction inst.
2. Print N by calling the function get_N(inst):
   Function get_N (returns the value of N):
	2.1. Use a mask to obtain the bits corresponding to N (the first 3 bits).
	2.2. Calculate the value of N by converting the binary number obtained into decimal.
	2.3. Return the obtained number + 1.
3. Iterate through all operations in a loop and print them by calling the function get_Nth_op():
   Function get_Nth_op (returns the N-th operation):
3.1. Use a mask to obtain the two bits corresponding to the N-th operation (divide by 2 raised to the -position of the bit to be found - and find the remainder when divided by 2).
3.2. Use the following encoding to determine the operation:
    00 - '+'
    01 - '-'
    10 - '*'
    11 - '/'
3.3. Return the operation.
4. Print Dim by calling the function get_dim():
   Function get_dim (returns the value of Dim):
4.1. Use a mask to obtain the 4 bits corresponding to the dimension (dim).
These bits immediately follow the bits corresponding to the operations.
4.2. Convert the obtained binary number into decimal.
4.3. Return the obtained number + 1.

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
## Execute instructions when operands have weird dimension (not divisible by 4)

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
7. Pentru fiecare instructiune in parte: 
    Se parcurge instructiunea pe "bucatele" de biti de dimensiune Dim
    (bitii se aflta tot cu ajutorul unei masti = 2 la puterea -pozitia bitului-
    si restul la impartirea cu 2) si se transforma numarul obtinut din decimal
    in binar
    Daca o "bucatica" este prea mare, se afla bitii care incap in instructiunea
    curenta si se transforma numarul din binar in decimal.
    Se trece apoi la urmatoarea instructiune si se afla bitii ramasi. Numarul
    rezultat prin concatenarea bitilor este transformat din baza 2 in baza 10.
8. Se reazlizeaza calculul dintre rezultat (tot ce a fost inainte de operandul
actual) si operandul actual folosind operatia corespunzatoare celor doi 
(operatia cu indexul contor-1)
9. Se printeaza rezultatul

# Fourth Task
## Execute instruction (with operator precedence rule)

1. Se citeste prima instructiune inst
2. Se obtin valorile pentru N si Dim apeland functiile get_N() si get_dim()
3. Intr-un pointer de char-uri (operatii) se retin operatiile apeland functia
get_Nth_op()
4. "prioritate_op"	- vectorul care contine prioritatile operatiilor din 
vectorul "operatii" (0 pentru + sau -, 1 pentru * sau /). El se obtine apeland
functia "prioritate_operatie" care are rolul de a-i atribui fiecarei operatii
o prioritate
	Functia primeste 3 parametrii: 
		- numarul de operatii "N"
		- vectorul "operatii"
		- vectorul "prioritate_op"
	Se parcurge vectorul "operatii" element cu element
	Fiecarui element din "oeratii" i se atribuie un numar (0 pentru + sau -, 
    1 pentru * sau /) care semnifica prioritatea operatiei
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
 
