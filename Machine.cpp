#include <bits/stdc++.h>
#include "Machine.h"
#include "Register.h"
#include "Memory.h"
using namespace std;

Machine :: Machine() {
    counter = 0;
}
void Machine::open(string file_name) {
    ifstream f(file_name);
    if (!f.is_open()) {
        cout << "Error opening file: " << file_name << endl;
        return;
    }
    string line;
    while (getline(f, line)) {
        if (line.length() != 4) {
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
            cout << "Invalid instruction format: " << line << endl;
            continue;
        }
        // Parse the instruction
        string opcode_str = line.substr(0, 1);
        string reg_str = line.substr(1, 1);
        string address_str = line.substr(2, 2);
        // Convert the parts from hex strings to integers
        int opcode = stoi(opcode_str, nullptr, 16);
        int reg = stoi(reg_str, nullptr, 16);
        int address = stoi(address_str, nullptr, 16);
        // Store the instruction in memory (e.g., encode in 4 hex digits for simulation)
        M.write(counter++, (opcode << 8) | (reg << 4) | address);
    }
    f.close();
    work();
}

void Machine::work() {
    cout << "Starting execution with " << counter + 1 << " instructions." << endl;

    for (step = 0; step <= counter; step++) {
        long instruction = M.read(step);
        int opcode = (instruction >> 8) & 0xF;
        int reg = (instruction >> 4) & 0xF;
        int address = instruction & 0xFF;

        // Output the instruction in the specified format before executing
        cout << "Instruction " << (step + 1) << ": ";

        switch (opcode) {
            case 1: // LOAD R, M[XY]
                cout << "Load R" << reg << " with " << hex << setw(2) << setfill('0') << address << endl;
                break;
            case 2:
                cout << "Load R" << reg << " with " << hex << setw(2) << setfill('0') << address << endl;
                break;
            case 3: // STORE R, M[XY]
                cout << "Store R" << reg << " to M" << hex << setw(2) << setfill('0') << address << endl;
                break;
            case 4: // MOVE 0RS - Move value from R to S
                cout << "Move R" << reg << " to R" << address << endl;
                break;
            case 5: // ADD R, S, T
                cout << "Add R" << reg << " with R" << ((address >> 4) & 0xF) 
                    << " into R" << ((address >> 4) & 0xF) << endl;
                break;
            case 0xB: // JUMP R, XY if R == R0
                cout << "Comp R" << reg << " with R0" << endl;
                break;
            case 0xC: // HALT
                cout << "HALT" << endl;
                cout << "Program halted." << endl;
                exit(0);
            default:
                cout << "Unknown opcode: " << opcode << endl;
                break;
        }
        operations(opcode, reg, address);
    }
}


long Machine :: convert(string s) {
    return stol(s, nullptr, 16);
}
long Machine:: get_counter(){
    return counter;
}
void Machine::Load(long address_of_R, long address_of_XY) {
    if (address_of_XY >= 0 && address_of_XY < 256) {
        long val = M.read(address_of_XY); 
        R.Set_Value(address_of_R, val);    
    } else {
        cerr << "Load error: Invalid memory address " << address_of_XY << endl;
    }
}

void  Machine :: Move(long address_of_R , long address_of_S){
    long val = R.Get_Value(address_of_R) ;
    R.Set_Value(address_of_S , val) ;
 //   Reg.Remove_Register(address_of_R) ;
}

void Machine::JUMP(long reg, long xy) {
    if (R.Get_Value(reg) == R.Get_Value(0)) { 
        step = xy - 1; 
    }
}

long Machine :: Screen() {
    return M.read(0);
}
void Machine::operations(int opcode, int reg, int xy) {
    // Ensure `reg` is within valid register bounds
    if (reg < 0 || reg >= R.Get_Register_Size()) {
        cout << "Register write error: Invalid address " << reg << endl;
        return;
    }

    switch (opcode) {
        case 1: // LOAD R, M[XY]
            if (xy >= 0 && xy < 256) { // Check memory bounds for `xy`
                Load(reg, xy);
            } else {
                cout << "Memory read error: Invalid address " << xy << endl;
            }
            break;
            
        case 2: // LOAD R, immediate XY
            R.Set_Value(reg, xy);
            break;
            
        case 3: // STORE R, M[XY] (or output to screen if XY == 0x00)
            if (xy == 0x01) { // Specific memory location for "screen" output
                cout << R.Get_Value(reg) << " ";
            }
            M.write(xy, R.Get_Value(reg));
            break;
        case 4: // MOVE R to S
            if (xy >= 0 && xy < R.Get_Register_Size()) { // Check register bounds for `xy`
                Move(reg, xy);
            } else {
                cout << "Register write error: Invalid address " << xy << endl;
            }
            break;
            
        case 5: // ADD R, S, T - Integer addition
        {
            long S = (xy >> 4) & 0xF;  // S
            long T = xy & 0xF;         // T
            if (S >= 0 && S < R.Get_Register_Size() &&
                T >= 0 && T < R.Get_Register_Size()) {
                R.Set_Value(reg, R.Get_Value(S) + R.Get_Value(T));
            } else {
                cout << "Register read error: Invalid address " << S << " or " << T << endl;
            }
            break;
        }
            
        case 6: // Floating-point ADD (similar to ADD but as float)
        {
            long S = (xy >> 4) & 0xF;  // S
            long T = xy & 0xF;         // T
            if (S >= 0 && S < R.Get_Register_Size() &&
                T >= 0 && T < R.Get_Register_Size()) {
                float num1 = static_cast<float>(R.Get_Value(S));
                float num2 = static_cast<float>(R.Get_Value(T));
                R.Set_Value(reg, static_cast<long>(num1 + num2));
            } else {
                cout << "Register read error: Invalid address " << S << " or " << T << endl;
            }
            break;
        }
            
        case 0xB: // JUMP R, XY if R == R0
            if (xy >= 0 && xy < 256) { // Check memory bounds for `xy`
                JUMP(reg, xy);
            } else {
                cout << "Memory jump error: Invalid address " << xy << endl;
            }
            break;
            
        case 0xC: // HALT
            cout << "Program halted." << endl;
            exit(0);
            
        default:
            cout << "Unknown opcode: " << opcode << endl;
            break;
    }
}
