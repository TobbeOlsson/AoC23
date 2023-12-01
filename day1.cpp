#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>

int combineIntegers(int a, int b){
    int times = 1;
    while (times <= b){
        times *= 10;
    }
    return a*times + b;
}

int isNumberInText(std::string s){
    if (s.substr(0,3) == "one"){
        return 1;
    } else if (s.substr(0,3) == "two"){
        return 2;
    } else if (s.substr(0,5) == "three"){
        return 3;
    } else if (s.substr(0,4) == "four"){
        return 4;
    } else if (s.substr(0,4) == "five"){
        return 5;
    } else if (s.substr(0,3) == "six"){
        return 6;
    } else if (s.substr(0,5) == "seven"){
        return 7;
    } else if (s.substr(0,5) == "eight"){
        return 8;
    } else if (s.substr(0,4) == "nine"){
        return 9;
    }
    return 0;
}

int main(){
    int fDigit, lDigit, calibVal = 0, sum = 0, textNumber;
    std::vector<std::string> lines;
    lines = fileLinesToStringVector(std::string("inputs/input_day1"));
    for (auto line : lines){
        line = line + "   ";
        fDigit = -1;
        lDigit = -1;
        for (size_t i = 0; i < line.size(); i++){
            textNumber = isNumberInText(line.substr(i, 5));
            if (isdigit(line[i])){
                if (fDigit == -1){
                    fDigit = line[i] - '0';
                    lDigit = line[i] - '0';
                } else {
                    lDigit = line[i] - '0';
                }
            } else if (textNumber){
                if (fDigit == -1){
                    fDigit = textNumber;
                    lDigit = textNumber;
                } else {
                    lDigit = textNumber;
                }
            }
        }
        calibVal = combineIntegers(fDigit, lDigit);
        sum += calibVal;
    }
    std::cout << "Sum of calibration values: " << sum << std::endl;
    return 0;
}