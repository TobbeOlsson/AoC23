#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>

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
    int padding = 1, sumOfEngineParts = 0, sumRatio = 0;
    int inputSize = 140 + (padding * 2);
    char m[inputSize][inputSize] = {};
    std::map<int, std::vector<int>> gearMap;
    std::vector<std::vector<std::pair<char, int>>> adjMatrix;
    std::vector<std::vector<std::pair<char, int>>> gearMatrix;
    std::vector<std::string> lines;
    lines = fileLinesToStringVector(std::string("inputs/input_day3.in"));
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

    //create adjacentMatrix
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
                    for(size_t n = numStart - padding; n < numStart - padding + number.length(); n++){
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


    //Create "empty" gearMatrix
    for (int i = 0 + padding; i < inputSize - padding; i++){
        line = lines[i];
        std::vector<std::pair<char, int>> row;
        for (int j = 0 + padding; j < inputSize - padding; j++){
            char c = line[j];
            row.push_back(std::make_pair(c, 0));
        }
        gearMatrix.push_back(row);
    }

    //find star, add starId to all indices adjacent in gearMatrix
    int starNumber = 1;
    for (int i = 0 + padding; i < inputSize - padding; i++){
        std::string number = "";
        for (int j = 0 + padding; j < inputSize; j++){
            if((m[i][j]) == '*'){
                //std::cout << "Found star at " << i << " " << j << std::endl;
                gearMatrix[i-1-padding][j-1-padding].second = starNumber;
                gearMatrix[i-1-padding][j-padding].second = starNumber;
                gearMatrix[i-1-padding][j+1-padding].second = starNumber;
                gearMatrix[i-padding][j-1-padding].second = starNumber;
                gearMatrix[i-padding][j+1-padding].second = starNumber;
                gearMatrix[i+1-padding][j-1-padding].second = starNumber;
                gearMatrix[i+1-padding][j-padding].second = starNumber;
                gearMatrix[i+1-padding][j+1-padding].second = starNumber;
                gearMap[starNumber];
                starNumber++;
            }
        }
    }

    //go through matrix to find gearing, add possible gears to gearMap
    for (int i = 0 + padding; i < inputSize - padding; i++){
        std::string number = "";
        int numStart = 0;
        std::pair<int, std::pair<int, int>> lastGear;
        bool numLastTime = false;
        for (int j = 0 + padding; j < inputSize; j++){
            //find what number it is, how many chars long, check all for gearing
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
                    //check for gearing
                    bool posGear = false;
                    int starId;
                    for(size_t n = numStart - padding; n < numStart - padding + number.length(); n++){
                        if (gearMatrix[i - padding][n].second){
                            posGear = true;
                            starId = gearMatrix[i - padding][n].second;
                            break;
                        }
                    }

                    if(posGear){
                        gearMap[starId].push_back(stoi(number));
                        //std::cout << "Possible gear part: " << number << std::endl;
                    }
                    numLastTime = false;
                    number = "";
                }
            }
        }
    }

    //go thru gearMap to check which gears has two numbers connected, then add to sumRatio
    for(auto it = gearMap.cbegin(); it != gearMap.cend(); ++it){
        int ratio = 0;
        if(it->second.size() == 2){
            ratio = it->second[0] * it->second[1];
            sumRatio += ratio;
        }
        std::cout << it->first << " " << it->second[0] << "\n";
    }

    //print for testing
    // for (int i = 0; i < inputSize-2; i++){
    //     for (int j = 0; j < inputSize-2; j++){
    //         std::cout << gearMatrix[i][j].first << "," << gearMatrix[i][j].second << " "; 
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "Sum of engine parts: " << sumOfEngineParts << std::endl;
    std::cout << "Sum of all gear ratios: " << sumRatio << std::endl;
    return 0;
}