#include <iostream>
using namespace std ;
#include "Register.h"
Register :: Register() {
    Register_Container.fill(0) ;
}

void Register::Set_Value(long address, long value) {
    if (address >= 0 && address < Register_Container.size()) {
        Register_Container[address] = value;
    } else {
        std::cerr << "Register write error: Invalid address " << address << std::endl;
    }
}
long Register::Get_Value(long address) {
    if (address >= 0 && address < Register_Container.size()) {
        return Register_Container[address];
    } else {
        std::cerr << "Register read error: Invalid address " << address << std::endl;
        return 0;
    }
}