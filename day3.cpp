#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>

//Return if symbol, we assume anything that's not a number nor a dot
//is a sumbol
//returns 1 if symbol, 0 if not
int symbol(char c){
    if (isdigit(c) || c == '.'){
        return 0;
    }
    return 1;
}

int gear(char c){
    if (c == '*'){
        return 2;
    }
    return 0;
}

int main(){
    int padding = 1, sumOfEngineParts = 0;
    int inputSize = 10 + (padding * 2);
    char m[inputSize][inputSize] = {};
    std::vector<std::vector<std::pair<char, int>>> adjMatrix;
    std::vector<std::vector<std::pair<char, int>>> gearMatrix;
    std::vector<std::string> lines;
    lines = fileLinesToStringVector(std::string("inputs/test_day3"));

    std::string line;

    //create original matrix from input
    for (int i = 0; i < inputSize; i++){
        line = lines[i];
        for (int j = 0; j < inputSize; j++){
            m[i][j] = line[j];
            std::cout << m[i][j];
        }
        std::cout << std::endl;
    }

    for (int i = 0 + padding; i < inputSize - padding; i++){
        line = lines[i];
        std::vector<std::pair<char, int>> row;
        for (int j = 0 + padding; j < inputSize - padding; j++){
            char c = line[j];
            if(symbol(m[i-1][j-1]) || symbol(m[i-1][j]) || symbol(m[i-1][j+1]) || symbol(m[i][j-1])
             || symbol(m[i][j+1]) || symbol(m[i+1][j-1]) || symbol(m[i+1][j]) || symbol(m[i+1][j+1])){
                row.push_back(std::make_pair(c, 1));
            } else {
                row.push_back(std::make_pair(c, 0));
            }
        }
        adjMatrix.push_back(row);
    }

    //go through matrix to find part numbers
    for (int i = 0 + padding; i < inputSize - padding; i++){
        std::string number = "";
        int numStart = 0;
        std::pair<int, std::pair<int, int>> lastGear;
        bool numLastTime = false;
        for (int j = 0 + padding; j < inputSize; j++){
            //find what number it is, how many chars long, check all for adjency
            //std::cout << "running adj on char " << m[i][j] << std::endl;
            if(isdigit(m[i][j])){
                if(numLastTime){
                    number += m[i][j];
                } else {
                    numStart = j;
                    number += m[i][j];
                    numLastTime = true;
                }
            } else {
                if (numLastTime){
                    //check for adjecy
                    bool enginePart = false;
                    bool posGear = false;
                    for(int n = numStart - padding; n < numStart - padding + number.length(); n++){
                        if (adjMatrix[i - padding][n].second == 1){
                            enginePart = true;
                            break;
                        }
                    }

                    if(enginePart){
                        sumOfEngineParts += stoi(number);
                    }
                    numLastTime = false;
                    number = "";
                }
            }
        }
    }

    for (int i = 0 + padding; i < inputSize - padding; i++){
        line = lines[i];
        std::vector<std::pair<char, int>> row;
        for (int j = 0 + padding; j < inputSize - padding; j++){
            char c = line[j];
            if(gear(m[i-1][j-1]) || gear(m[i-1][j]) || gear(m[i-1][j+1]) || gear(m[i][j-1])
             || gear(m[i][j+1]) || gear(m[i+1][j-1]) || gear(m[i+1][j]) || gear(m[i+1][j+1])){
                row.push_back(std::make_pair(c, 2));
            } else {
                row.push_back(std::make_pair(c, 0));
            }
        }
        gearMatrix.push_back(row);
    }

    //Had an idea two solve part two in a similar way to part 1, however..
    //it gets messy real quick.. 
    for (int i = 0 + padding; i < inputSize - padding; i++){
        std::string number = "";
        int numStart = 0;
        bool numLastTime = false;
        for (int j = 0 + padding; j < inputSize; j++){
            if((m[i][j]) == '*'){
                std::cout << "Found star at " << i << " " << j << std::endl;
            }
        }
    }

    //print for testing
    // for (int i = 0; i < inputSize-2; i++){
    //     for (int j = 0; j < inputSize-2; j++){
    //         std::cout << gearMatrix[i][j].first << "," << gearMatrix[i][j].second << " "; 
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "Sum of engine parts: " << sumOfEngineParts << std::endl;
    return 0;
}