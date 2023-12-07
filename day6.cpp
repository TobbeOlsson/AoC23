#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

int main(){
    int records = 1;
    std::vector<std::string> lines;
    lines = fileLinesToStringVector(std::string("inputs/input_day6"));
    std::vector<long> timeVect, distanceVect;
    for(int i = 0; i < 2; i++){
        std::string num, secondStar = "";
        std::cout << lines[0] << std::endl;
        std::stringstream ss(lines[i].substr(10,lines[0].length()-10));
        if(i == 0){
            while(ss >> num){
                secondStar += num;
            }
            timeVect.push_back(stol(secondStar));
        } else if (i == 1){
            while(ss >> num){
                secondStar += num;
            }
            distanceVect.push_back(stol(secondStar));
        }        
    }

    for(int scenario = 0; scenario < timeVect.size(); scenario++){
        int wins = 0;
        for(int hold = 0; hold < timeVect[scenario]; hold++){
            long traveled = hold * (timeVect[scenario] - hold);
            if(traveled > distanceVect[scenario]){
                wins++;
            }
        }
        records *= wins;
    }

    std::cout << "answer: " << records << std::endl;
    return 0;
}