#include "readInput.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <utility>

int main(){
    int totalPoints = 0;
    std::vector<std::string> cards;
    std::vector<int> winningList;
    std::queue<int> wonCards;
    std::vector<int> numsVect, winnersVect;
    cards = fileLinesToStringVector(std::string("inputs/input_day4.in"));
    int cardsWon = cards.size();

    for (auto card : cards){
        int cardNum;
        std::string nums, winners, cardNumString = "", startOfCard;
        std::string token = "|", token2 =":";

        startOfCard = card.substr(0, 8);
        nums = card.substr(10, card.find(token) - 10);
        winners = card.substr(card.find(token) + 2);

        for(size_t i = 4; i < startOfCard.size(); i++){
            if(isdigit(startOfCard[i])){
                cardNumString += startOfCard[i];
            }
        }
        cardNum = stoi(cardNumString);
        
        std::stringstream ss(nums);
        int number;
        while (ss >> number){
            numsVect.push_back(number);
        }
        ss.clear();
        ss.str(winners);
         while (ss >> number){
            winnersVect.push_back(number);
        }
        
        std::sort(numsVect.begin(), numsVect.end());
        std::sort(winnersVect.begin(), winnersVect.end());

        std::vector<int> intersectionVect;
        std::set_intersection(numsVect.begin(), numsVect.end(),
            winnersVect.begin(), winnersVect.end(), std::back_inserter(intersectionVect));

        if(intersectionVect.size() > 0){
            totalPoints += pow(2, intersectionVect.size()-1);
        }

        //add to winningList
        winningList.push_back(intersectionVect.size());

        for(size_t i = 1; i <= intersectionVect.size(); i++){
            wonCards.push(i+cardNum);
            cardsWon++;
        }
        numsVect.clear();
        winnersVect.clear(); 
    }

    //loop thru copies of cards
    while(!wonCards.empty()){
        int cardNum = wonCards.front();
        int thisCardWins = winningList[cardNum-1];

        for(int i = 1; i <= thisCardWins; i++){
            wonCards.push(i+cardNum);
            cardsWon++;
        }
        numsVect.clear();
        winnersVect.clear(); 
        wonCards.pop();
    }

    std::cout << "Total points: " << totalPoints << std::endl;
    std::cout << "Total amount of cards: " << cardsWon << std::endl;
    return 0;
}