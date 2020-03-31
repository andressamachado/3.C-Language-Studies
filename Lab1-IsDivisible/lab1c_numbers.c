#include <stdio.h>
#include <stdlib.h>

/* PROGRAM: Dividers  
   AUTHOR:  Andressa Machado [040923007]
   DATE:   13.Jan.2019
   PURPOSE: Takes 3 command-line arguments and print if the number [1 through 100 ] is divisible by the arguments.
   LEVEL OF DIFFICULTY: 1
   CHALLENGES: none
   HOURS SPENT: less than one hour          
*/

int main( int argc, char *argv[] ) {
    
	if( argc == 4 ) {
		int n1 = atoi( argv[1] );	// convert 1st command line arg from a string (e.g., "5") to an integer (e.g., 5)
		int n2 = atoi( argv[2] );	// convert 2nd command line arg from a string to an integer
		int n3 = atoi( argv[3] );   // convert 3rd command line arg from a string to an integer
		
		// iterate over the first 100 integers
		for( int i = 1; i <= 100; i++ ){
			
			if( i % n1 == 0 && i % n2 == 0 && i % n3 == 0 )
				printf( " %2d is divisible by ALL of %d AND %d AND %d\n", i, n1, n2, n3 );
			else if( i % n1 == 0 && i % n3 == 0 )
				printf( " %2d is divisible by both %d AND %d\n", i, n1, n3 );
			else if( i % n2 == 0 && i % n3 == 0 )
				printf( " %2d is divisible by both %d AND %d\n", i, n2, n3 );
			else if( i % n1 == 0 && i % n2 == 0 )
				printf( " %2d is divisible by both %d AND %d\n", i, n1, n2 );
			else if( i % n1 == 0 )
				printf( "%3d is divisible by %d\n", i, n1 );
			else if( i % n2 == 0 )
				printf( "%3d is divisible by %d\n", i, n2 );
			else if( i % n3 == 0 ) 
				printf( "%3d is divisible by %d\n", i, n3 );
			else 
				printf( "%3d\n", i );
		}
    }
	//In case the user enter another number of arguments other than three, it will print the user the correct usage 
    else
		printf( "usage: numbers [INT] [INT] [INT]\n" );

	return EXIT_SUCCESS;
}