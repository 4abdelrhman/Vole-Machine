#include <iostream>
#include "Memory.h"
using namespace std ;

long Memory:: read(long address){
    if (address >= 0 && address < 256) {
        return data[address];
    } else {
        cerr << "Memory read error: Invalid address " << address << endl;
        return 0;
    }
}
void Memory :: write (long address, long value) {
    if (address >= 0 && address < 256) {
        data[address] = value;
    } else {
        cerr << "Memory write error: Invalid address " << address << endl;
    }
}
