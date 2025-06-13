#include <iostream>
#include <list>

#include "Containers/UnorderedMap.h"
#include "DataStructures/HashTable.h"
using namespace std;

int main() {

    sdf::UnorderedMap<int, int> map;
    map.insert(1,2);
    map.insert(2,3);
    map.remove(1);
    cout << map.find(1);



    return 0;
}