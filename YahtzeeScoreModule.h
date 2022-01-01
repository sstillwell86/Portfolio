//YahtzeeScoreModule.h

#pragma once
#include <string>
using namespace std;
class YahtzeeScoreModule {
private:
public: 
	YahtzeeScoreModule();
	~YahtzeeScoreModule();
	int returnScore, acesScore = -1, twosScore = -1, threesScore = -1, foursScore = -1, fivesScore = -1, sixesScore = -1, totalScore = -1, threeOfKindScore = -1,
	fourOfKindScore = -1, yahtzeeScore = -1, chanceScore = -1, yahtzeeBonusCount = 0, totalUpper = -1, yahtzeeBonus, totalLower = -1, bonus, grandTotal,
	fullHouseScore = -1, smallStraightScore = -1, largeStraightScore = -1;
	int aces(int *rolls);
	int twos(int *rolls);
	int threes(int *rolls);
	int fours(int *rolls);
	int fives(int *rolls);
	int sixes(int *rolls);
	int threeOfKind(int *rolls);
	int fourOfKind(int *rolls);
	int yahtzee(int *rolls);
	int chance(int *rolls);
	int fullHouse(int *rolls);
	int smallStraight(int *rolls);
	int largeStraight(int *rolls);
	int functionCaller(int rolls[5], string category);
};