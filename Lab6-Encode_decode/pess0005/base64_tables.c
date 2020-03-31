#include	<stdio.h>

static unsigned char	INT_TO_CHAR[64];
static unsigned int	CHAR_TO_INT[128] = { 65 };

/**
 * Record a single entry in the both lookup tables
 */
static void recordMapping( unsigned char c, unsigned int i )
{
    INT_TO_CHAR[i] = c;
    CHAR_TO_INT[(unsigned int) c] = i;
}

/**
 * Build the lookup tables (both forward and reverse), as per the Base64 specification
 */
void initializeLookupTables()
{
    int i = 0;

    for ( int c = 'A'; c <= 'Z'; c++ )
	recordMapping( c, i++ );

    for ( int c = 'a'; c <= 'z'; c++ )
	recordMapping( c, i++ );

    for ( int c = '0'; c <= '9'; c++ )
	recordMapping( c, i++ );

    recordMapping( '+', i++ );
    recordMapping( '/', i++ );
}

/**
 * Convert a binary value (0-63) into a printable character, e.g., 3 -> 'D', 62 -> '+'
 *
 * Need to have called initializeLookupTables (once only) before using this function.
 */
unsigned char lookupChar( unsigned int i )
{
    if ( i >= 64 )
	fprintf( stderr, "illegal int passed in '%d'\n", i );
    return INT_TO_CHAR[i];
}

/**
 * Convert a printable character into a binary value (0-63), e.g., 'D' -> 3, '+' -> 63
 *
 * Need to have called initializeLookupTables (once only) before using this function.
 */
unsigned int lookupInt( char c )
{
    unsigned int i = CHAR_TO_INT[(unsigned int) c];
    if ( i == 65 )
	fprintf( stderr, "illegal char passed in '%c'\n", c );

    return i;
}
