#ifndef MEMORY_H
#define MEMORY_H
#include<iostream>
#include<array>
using namespace std;
class Memory{
private:
    array<long,256> data;

public:
    Memory(){
        data.fill(0);
    }
    long read(long address);
    void write(long address, long value);
};
#endif
