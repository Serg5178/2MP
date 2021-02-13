#include<iostream>
#include "map.h"


int main(){
    class map<int,char*> map;
    
    map.insert(10, "privet1");
    map.insert(11, "privet");
    map.insert(9, "privet3");
    map.insert(7, "privet");
    std::cout << map[11] << std::endl;
    std::cout << map[9] << std::endl;
    std::cout << map.search(8) << std::endl;
    class map<int,char*> map1 = map;
    map.clear();
    std::cout << map.isEmpety() << std::endl;   
    return 0; 
}