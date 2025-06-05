#include <iostream>
#include <string>
#include "Containers/String.h"
using namespace std;

int main() {
    sdf::String str = "      ";
    str.trim();
    cout << str.size() << endl;


    return 0;
}