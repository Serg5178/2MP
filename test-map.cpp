#include <iostream>
#include "map.h"
#include <ctime>
int main(){
    srand(time(NULL));
    class map<int,std::string> map;
    for(int j = 0; j < 50; j++){
        for(int i = 0; i < 10000; i++){
            map.insert(rand()%1000, "a1");
            
        }
        map.test();
        map.clear();
    }
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
    class map<int,std::string> map1 = map;
    map.clear();
    std::cout << map1.isEmpety() << " " << map.isEmpety()<< "\n";
    map1.insert(14,"a11");
    map1.print();
    return 0; 
}