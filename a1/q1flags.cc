#include <iostream>
#include <cstdlib>                      // access: rand, srand
using namespace std;
#include <unistd.h>                     // access: getpid

int times = 1000;                       // default value

int rtn1( int i ) {
    int flag = -1;
    for ( int j = 0; j < times && flag == -1; j += 1 ) {
        if ( rand() % 10000 == 42 ) flag = j;
    }
    return flag;
}
int rtn2( int i ) {
    int flag = -1;
    for ( int j = times; j >= 0 && flag == -1; j -= 1 ) {
        if ( rand() % 10000 == 42 ) flag = j;
    }
    return flag;
}
int g( int i ) {
    int flag = -1;
    for ( int j = 0; j < times && flag == -1; j += 1 ) {
        if ( rand() % 2 == 0 ) flag = rtn1( i );
        else flag = rtn2( i );
    }
    if(flag == -1) {
        if ( i % 2 ) flag = rtn2( i );
        if(flag == -1)
            flag = rtn1( i );
    }
    return flag;
}
int f( int i ) {
    int flag = -1;
    for ( int j = 0; j < times && flag == -1; j += 1 ) {
        flag = g( i );
    }
    if(flag == -1) {
        if ( i % 2 ) flag = g( i );
        if(flag == -1)
            flag = g( i );
    }
    return flag;
}
int main( int argc, char *argv[] ) {
    int seed = getpid();                // default value
    int arg_flag = 0;

    switch ( argc ) {
        case 3: times = stoi( argv[2] ); if ( times <= 0 ) arg_flag = 1;
        case 2: seed = stoi( argv[1] ); if ( seed <= 0 ) arg_flag = 1;
        case 1: break;                // use defaults
        default: arg_flag = 1;
    } // switch

    if(arg_flag == 1) {
        cout << "Usage: " << argv[0] << " [ seed (> 0) [ times (> 0) ] ]" << endl;
        exit( 1 );
    }

    srand( seed );      // set random-number seed
    // begin program
    int code = f( 3 );
    if(code == -1)
        cout << "seed:" << seed << " times:" << times << " complete" << endl;
    else
        cout << "seed:" << seed << " times:" << times << " rc:" << code << endl;
}