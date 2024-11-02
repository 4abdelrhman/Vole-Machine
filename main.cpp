#include <bits/stdc++.h>
#include "Memory.h"
#include "Machine.h"
#include "Register.h"
using namespace std;

int main(){
    cout << "Welcome to our Machine Simulator Program\n";
    cout << "Enter the file name :\n";
    string name;
    cin >> name;
    Machine x;
    x.open(name);
}
