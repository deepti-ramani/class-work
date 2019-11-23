/********************
Ohms.c
by: Ryan Scheppler and finished by Deepti Ramani
last edited: 11/6/2018
brief: This program is meant to use funcitons to figure out different missing pieces of circuit data.
gcc -Wall -Wextra -ansi -pedantic -O -o ohm Ohms.c
*******************/
/*NULL*/
#include <stddef.h>
/* printf */
#include <stdio.h>

#define RESNUM 10

/* calculate the total resistance and current of a circuit with given voltage, parallel resistor values, and sequential resistor values */
void testCircuit(double V, double ParallelResistors[], int NumPar, double SequentialResistors[], int NumSeq);

/*Function takes 3 pointers one of which is NULL, solves for the missing values and returns what it should be. Returns -1 if something was wrong.*/
double findMissingOhmValue(double* V, double* I, double* R);

/*takes an array of resistances for parallel resistors and a given size of the array and stores the total reistance into the double pointed at by Rtotal, 
can be used with as many resistances as needed in a row.*/
void findTotalResistanceParallel(double* Rtotal, double Resistor[], int size);

int main(void)
{
	/*5 volts, 2 amps*/
	double V = 5, I = 2, R;
	
	double Resistor[RESNUM];
	
	/* for the test circuit at the bottom */
	double SequentialResistors[] = { 25.0 };
	double ParallelResistors[] = { 50.0, 100.0 };
	
	double* pV = &V;
	double* pI = &I;
	double* pR = NULL;
	
	int i;
	
	R = findMissingOhmValue(pV, pI, pR);
	
	printf("Given a voltage of %.5f Volts, and a current of %.5f Amps, the total resistance would be %.5f Ohms\n", V, I, R);
	
	V = 12;
	R = 100;
	
	pV = &V;
	pI = NULL;
	pR = &R;
	
	I = findMissingOhmValue(pV, pI, pR);
	
	printf("Given a voltage of %.5f Volts, and a total resistance of %.5f Ohms, the current would be %.5f Amps\n", V, R, I);
	
	I = 0.5;
	R = 14;
	
	pV = NULL;
	pI = &I;
	pR = &R;
	
	V = findMissingOhmValue(pV, pI, pR);
	
	printf("Given a current of %.5f Amps, and a total resistance of %.5f Ohms, the voltage would be %.5f Volts\n", I, R, V);
	
	Resistor[0] = 300;
	Resistor[1] = 300;
	
	findTotalResistanceParallel(pR, Resistor, 2);
	
	printf("Total resistance is %f when R1, %f, and R2, %f, are hooked in parallel.\n", *pR, Resistor[0], Resistor[1]);
	
	for(i = 0; i < RESNUM; i++)
	{
		Resistor[i] = (i+1)*10;
	}
	/* run setup with first 2 then run through other parallel resistors */
	Resistor[0] = 10;
	Resistor[1] = 20;
	findTotalResistanceParallel(pR, Resistor, 2);
	printf("Total resistance is %f with resistor values 10, 20.\n", *pR);
	findTotalResistanceParallel(pR ,Resistor, RESNUM);
	
	printf("Total resistance is %f with resistor values 10, 20, 30, 40, 50, 60, 70, 80, 90, and 100.\n", *pR);
	
	/* calculate total resistance and current for the test circuit shown below:
	                    |----R2---|
	5V ------R1----------         --------Ground
	                    |---R3----|
	R1 = 25 Ohms, R2 = 50 Ohms, R3 = 100 Ohms
	*/
	V = 5.0;
	testCircuit(V, ParallelResistors, 2, SequentialResistors, 1);
	
	return 0;
}

/* calculate the total resistance and current of a circuit with given voltage, parallel resistor values, and sequential resistor values */
void testCircuit(double V, double ParallelResistors[], int NumPar, double SequentialResistors[], int NumSeq)
{
	/* iterator */
	int i;
	
	/* need to calculate these */
	double I = 0.0;
	double Rparallel = 0.0;
	double Rsequential = 0.0;
	double Rtotal = 0.0;
	
	printf("With parallel resistor(s) ");
	
	/* find Rparallel */
	for(i = 0; i < NumPar; i++)
	{
		printf("%.1f, ", ParallelResistors[i]);
		Rparallel += 1.0 / ParallelResistors[i];
	}
	Rparallel = 1.0 / Rparallel;
	
	printf("and sequential resistor(s) ");
	
	/* find Rsequential */
	for(i = 0; i < NumSeq; i++)
	{
		printf("%.1f, ", ParallelResistors[i]);
		Rsequential += SequentialResistors[i];
	}
	
	/* find Rtotal */
	Rtotal = Rsequential + Rparallel;
	printf("the total resistance is %f\n", Rtotal);
	
	/* find current */
	I = V / Rtotal;
	printf("Given a voltage of %f and total resistance of %f, the current is %f\n", V, Rtotal, I);
}


/* Fill in this function! */
/*takes an array of resistances for parallel resistors and a given size of the array and stores the total resistance into the double pointed at by Rtotal, 
can be used with as many resistances as needed in a row.*/
void findTotalResistanceParallel(double* Rtotal, double Resistors[], int size)
{
	int i;
	/* start from 0 */
	*Rtotal = 0.0;
	for(i = 0; i < size; i++)
	{
		*Rtotal += 1.0 / Resistors[i];
	}
	*Rtotal = 1.0 / *Rtotal;
}

/* Fill in this function! */
/*Function takes 3 pointers one of which is NULL, solves for the missing values and returns what it should be. Returns -1 if something was wrong.*/
double findMissingOhmValue(double* V, double* I, double* R)
{
	/* find voltage */
	if (V == NULL)
	{
		return *I * *R;
	}
	/* find current */
	else if (I == NULL)
	{
		return *V / *R;
	}
	/* find resistance */
	else if (R == NULL)
	{
		return *V / *I;
	}
	/* if it gets here, something went wrong */
	return -1;
}