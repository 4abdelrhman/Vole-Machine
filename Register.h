#include <iostream>
#include <array>
using namespace std ;
#ifndef VOLEMACHINELANGUAGESIMULATOR_REGISTER_H
#define VOLEMACHINELANGUAGESIMULATOR_REGISTER_H
    class Register {
    private:
        array < long , 16 > Register_Container ;
    public:
        Register() ;
        void Set_Value (long address , long value) ;
        long Get_Value(long address) ;
        long Get_Register_Size() const {
            return Register_Container.size();
        };
    };


#endif //VOLEMACHINELANGUAGESIMULATOR_REGISTER_H
