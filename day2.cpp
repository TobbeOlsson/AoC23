#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

int main(){
    int sumOfIds = 0, sumOfGamePowers = 0;
    std::vector<std::string> lines;
    lines = fileLinesToStringVector(std::string("inputs/input_day2"));
    for (std::string line : lines){
        int blue = 0, red = 0, green = 0;
        int gameId, gamePower;
        std::stringstream ss(line);
        std::string s = "";
        std::vector<std::string> lineVect;
        while(getline(ss, s, ':')){
            lineVect.push_back(s);
        }
        gameId = stoi(lineVect[0].substr(5, lineVect[0].length()-1));
        std::cout << gameId << std::endl;

        ss.clear();
        ss.str(lineVect[1]);
        lineVect.clear();
        while(getline(ss, s, ';')){
            lineVect.push_back(s);
        }

        for(std::string game : lineVect){
            ss.clear();
            ss.str(game);
            std::vector<std::string> gameVect;
            while(getline(ss, s, ',')){
                gameVect.push_back(s);
            }

            for(std::string color : gameVect){
                std::stringstream ss2(color);
                int prevnum, count = 0;
                while(getline(ss2, s, ' ')){
                    if(count == 0){
                        count++;
                        continue;
                    } else if (count == 1){
                        prevnum = stoi(s);
                        count++;
                    } else if (count == 2){
                        if(s[0] == 'g'){
                            if(prevnum > green){
                                green = prevnum;
                            }
                        }
                        if(s[0] == 'b'){
                            if(prevnum > blue){
                                blue = prevnum;
                            }
                        }
                        if(s[0] == 'r'){
                            if(prevnum > red){
                                red = prevnum;
                            }
                        }
                        count = 0;
                    }
                }
            }
        }
        gamePower = (green * red * blue);
        sumOfGamePowers += gamePower;
        std::cout << "green: " << green << " red: " << red << " blue: " << blue << std::endl;
        std::cout << "Game power: " << gamePower << std::endl;
        if (red <= 12 && green <= 13 && blue <= 14){
            std::cout << "Game possible!" << std::endl;
            sumOfIds += gameId;
        }
    }
    std::cout << "Sum of possible game IDs: " << sumOfIds << std::endl;
    std::cout << "Sum of all game powers: " << sumOfGamePowers << std::endl;
}