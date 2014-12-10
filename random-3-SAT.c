/********************************************************************
 * Generates a random 3-SAT instance and attempts (up to LIMIT times)
 * to find a satisfying assignment using the random walk algorithm.
 * 
 * Andrew Wong-Rolle 
 * CS 125 Problem Set 10
 * 
 * In this case, clause density was 3*n and initial LIMIT was 1000.
 *
 *******************************************************************/
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<stdio.h>

#define LIMIT 1000
#define n 1000
#define three_n 3000
#define nine_n 9000
#define random_bool ((rand() % 2) == 1)

// Each literal struct has its index, and a boolean indicating negation or not.
typedef struct
{
	bool negated;
	int index;
} literal;

// A clause is just an array of three literals
typedef struct 
{
	literal vars[3]; 
} clause;


int main(void)
{
	srand(time(NULL));

	// i, j, try for loop iterators. a, b, c for random variables.
	int i,j,try,a,b,c = 0; 
	
	// Generates random 3-SAT instance
	clause phi[three_n] = {0};	
	for (i = 0; i < three_n; ++i)
	{
		// Generate random negations
		phi[i].vars[0].negated = random_bool;
		phi[i].vars[1].negated = random_bool;
		phi[i].vars[2].negated = random_bool;
		
		// Generate random indices
		a = rand() % n;
		do
		{
			b = rand() % n;
		}
		while (b == a);	// b must be distinct from a	
		do
		{
			c = rand() % n;
		} while (c == a || c == b); // c distinct from a and b

		phi[i].vars[0].index = a;
		phi[i].vars[1].index = b;
		phi[i].vars[2].index = c;		
	}
	// initially we haven't found any satisfying assignment, indicate this with -1
	int sat_found = -1;
	// Generate a random assignment, which is stored as an n-length array of booleans	
	bool assignment[n];	

	// step (i) of the pseudocode given
	for (try=0; try < LIMIT; ++try)
	{

	// generate random truth assignment
	for (i = 0; i < n; ++i)
	{
		assignment[i] = random_bool;
		/* 
		printf("x%d = ",i);
		fputs(phi[i].vars[j].negated ? "true" : "false", stdout);
		printf("\n"); */
	}

	// performs step (ii) of the pseudocode given
	for (i = 0; i < nine_n; ++i)
	{
		// in this case the arbitrary clause is the first unsatisfied one that appears in the assignment
		int unsatisfied_clause = -1;
		int literal_to_change = -1;
		// evaluates each clause in phi looking for an unsatisfied one
		for (j = 0; j < three_n; ++j)
		{
			// this if statement tells us if clause j is satisfied or not
			// (x == y) is equivalent to XOR, which is equivalent to a bit flip iff bit 1 = false
			if (  !( (assignment[phi[j].vars[0].index] == phi[j].vars[0].negated) || 
				(assignment[phi[j].vars[1].index] == phi[j].vars[1].negated) ||  
				(assignment[phi[j].vars[2].index] == phi[j].vars[2].negated) ) )
			{
				// note where we found the unsatisfied clause
				unsatisfied_clause = j;
				break;
			}
		}
		// if there are no unsatisfied clauses (phi is satisfied), done
		if (unsatisfied_clause < 0)
		{
			sat_found = try+1;		
			break;
		}
		// switches a random literal in unsatisfied clause
		literal_to_change = phi[unsatisfied_clause].vars[(rand() % 3)].index;
		// printf("Changing literal %d\n",literal_to_change);
		assignment[literal_to_change] = !(assignment[literal_to_change]);
			
	}
		// we have a satisfying assignment, so we are good to break out of the try loop		
		if (sat_found > 0)
		{	
			break;	
		}
	}

	if (sat_found < 0)
	{
		printf("No satisfying assignment found.\n");
	}
	else
	{
		printf("Satisfying assignment found on try %d\n", sat_found );
	}

}
