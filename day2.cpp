#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

int main(){
    int blue = 0, red = 0, green = 0, sumOfIds = 0;
    std::vector<std::string> lines;
    lines = fileLinesToStringVector(std::string("inputs/test_day2"));
    for (std::string line : lines){
        std::stringstream ss(line);
        std::string s = "";
        while(ss.good()){
            std:string substr;
            getline(ss, substr, ',');

        }

        //std::cout << line << std::endl;
    }

}