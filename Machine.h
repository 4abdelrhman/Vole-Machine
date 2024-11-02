#ifndef MACHINE_H
#define MACHINE_H
using namespace std;
#include "Register.h"
#include "Memory.h"

class Machine {
private:
    long counter;
    long op;
    long r;
    long m;
    long step;
public:
    Register R;
    Memory M;
    Machine();
    void open(string);
    void work();
    long convert(string);
    void operations(int, int, int );
    long get_counter();
    void Load(long address_of_R , long address_of_XY ) ;
    void Move(long address_of_R , long address_of_S) ;
    void JUMP(long address_of_R , long address_of_XY ) ;
    long Screen ();
};

#endif //MACHINE_H
