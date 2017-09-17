#include <iostream>
#include <cstdlib>                      // access: rand, srand
using namespace std;
#include <unistd.h>                     // access: getpid

int times = 1000;                       // default value
int status = 0;                         // global status flag

int rtn1( int i ) {
    for ( int j = 0; j < times; j += 1 ) {
        if ( rand() % 10000 == 42 ) {
            status = 1;
            return j;
        }
    }
    return -1;
}
int rtn2( int i ) {
    for ( int j = times; j >= 0; j -= 1 ) {
        if ( rand() % 10000 == 42 ) {
            status = 1;
            return j;
        }
    }
    return -1;
}
int g( int i ) {
    int val;
    for ( int j = 0; j < times; j += 1 ) {
        if ( rand() % 2 == 0 ) val = rtn1( i );
        else val = rtn2( i );
        if(status == 1) return val;
    }
    if ( i % 2 ) {
        val = rtn2( i );
        if(status == 1) return val;
    }
    return rtn1( i );
}
int f( int i ) {
    int val;
    for ( int j = 0; j < times; j += 1 ) {
        val = g( i );
        if(status == 1) return val;
    }
    if ( i % 2 ) {
        val = g( i );
        if(status == 1) return val;
    }
    return g( i );
}
int main( int argc, char *argv[] ) {
    int seed = getpid();                // default value
    try {       // process command-line arguments
        switch ( argc ) {
          case 3: times = stoi( argv[2] ); if ( times <= 0 ) throw 1;
          case 2: seed = stoi( argv[1] ); if ( seed <= 0 ) throw 1;
          case 1: break;                // use defaults
          default: throw 1;
        } // switch
    } catch( ... ) {
        cout << "Usage: " << argv[0] << " [ seed (> 0) [ times (> 0) ] ]" << endl;
        exit( 1 );
    } // try
    srand( seed );      // set random-number seed

    int rc = f( 3 );
    if(status == 0)
        cout << "seed:" << seed << " times:" << times << " complete" << endl;
    else
        cout << "seed:" << seed << " times:" << times << " rc:" << rc << endl;
}