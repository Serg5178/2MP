#include <iostream>
#include "map.h"
#include <random>
#include <ctime>
int main(){
    srand(time(0));
    class map<int,char*> map;
    map.insert(13, "a1");
    map.insert(8, "a2");
    map.insert(17, "a3");
    map.insert(15, "a4");
    map.insert(25, "a5");
    map.insert(22, "a6");
    map.insert(27, "a7");
    map.insert(1, "a8");
    map.insert(11, "a9");
    map.insert(6, "a10");
    map.print();
    std::cout << map[22] << std::endl;
    class map<int,char*> map1 = map;
    map.clear();
    std::cout << map1.isEmpety() << " " << map.isEmpety()<< "\n";
    return 0; 
}