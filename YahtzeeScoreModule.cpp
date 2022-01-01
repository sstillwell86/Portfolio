//YahtzeeScoreModule.cpp

#include "YahtzeeScoreModule.h"
#include <iostream>
#include <string>
using namespace std;

YahtzeeScoreModule::YahtzeeScoreModule() {
	acesScore = -1, twosScore = -1, threesScore = -1, foursScore = -1, fivesScore = -1, sixesScore = -1, totalScore = -1, threeOfKindScore = -1,
	fourOfKindScore = -1, yahtzeeScore = -1, chanceScore = -1, yahtzeeBonusCount = 0, totalUpper = -1, totalLower = -1, 
	fullHouseScore = -1, smallStraightScore = -1, largeStraightScore = -1;
}
YahtzeeScoreModule::~YahtzeeScoreModule() {
}
int YahtzeeScoreModule::functionCaller(int rolls[5], string category) {
	if (*(rolls) == *(rolls + 1) && *(rolls) == *(rolls + 2) && *(rolls) == *(rolls + 3) && *(rolls) == *(rolls + 4) && yahtzeeScore == 50) {
		yahtzeeBonusCount += 1;
	}
	if (category == "TotalScore") {
		returnScore = totalScore;
	}
	if (category == "BonusUpper") {
		returnScore = bonus;
	}
	if (category == "TotalUpper") {
		returnScore = totalUpper;
	}
	if (category == "YahtzeeBonus") {
		returnScore = yahtzeeBonus;
	}
	if (category == "TotalLower") {
		returnScore = totalLower;
	}
	if (category == "GrandTotal") {
		returnScore = grandTotal;
	}
	if (category == "Aces") {
		returnScore = aces(rolls);
	}
	if (category == "Twos") {
		returnScore = twos(rolls);
	}
	if (category == "Threes") {
		returnScore = threes(rolls);
	}
	if (category == "Fours") {
		returnScore = fours(rolls);
	}
	if (category == "Fives") {
		returnScore = fives(rolls);
	}
	if (category == "Sixes") {
		returnScore = sixes(rolls);
	}
	if (category == "ThreeOfKind") {
		returnScore = threeOfKind(rolls);
	}
	if (category == "FourOfKind") {
		returnScore = fourOfKind(rolls);
	}
	if (category == "Yahtzee") {
		returnScore = yahtzee(rolls);
	}
	if (category == "Chance") {
		returnScore = chance(rolls);
	}
	if (category == "FullHouse") {
		returnScore = fullHouse(rolls);
	}
	if (category == "SmallStraight") {
		returnScore = smallStraight(rolls);
	}
	if (category == "LargeStraight") {
		returnScore = largeStraight(rolls);
	}
	if (returnScore == -1) {
		return returnScore;
	}
	if (acesScore >= 0 && twosScore >= 0 && threesScore >= 0 && foursScore >= 0 && fivesScore >= 0 && sixesScore >= 0 && totalScore == -1) {
		totalScore = acesScore + twosScore + threesScore + foursScore + fivesScore + sixesScore;
		if (totalScore >= 63) {
			bonus = 35;
		}
		else bonus = 0;
		totalUpper = totalScore + bonus;
	}
	if (threeOfKindScore >= 0 && fourOfKindScore >= 0 && fullHouseScore >= 0 && smallStraightScore >= 0 && largeStraightScore >= 0 && yahtzeeScore >= 0 && chanceScore >= 0 && totalUpper >= 0) {
		yahtzeeBonus = yahtzeeBonusCount * 100;
		totalLower = threeOfKindScore + fourOfKindScore + fullHouseScore + smallStraightScore + chanceScore + largeStraightScore + yahtzeeScore + yahtzeeBonus;
		grandTotal = totalUpper + totalLower;
	}
	return returnScore;
}

int YahtzeeScoreModule::aces(int *rolls) {
	if (acesScore >= 0) {
		return -1;
	}
	acesScore = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 1) {
			acesScore += 1;
		}
	}
	return acesScore;
}

int YahtzeeScoreModule::twos(int *rolls) {
	if (twosScore >= 0) {
		return -1;
	}
	twosScore = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 2) {
			twosScore += 2;
		}
	}
	return twosScore;
}

int YahtzeeScoreModule::threes(int *rolls) {
	if (threesScore >= 0) {
		return -1;
	}
	threesScore = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 3) {
			threesScore += 3;
		}
	}
	return threesScore;
}

int YahtzeeScoreModule::fours(int *rolls) {
	if (foursScore >= 0) {
		return -1;
	}
	foursScore = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 4) {
			foursScore += 4;
		}
	}
	return foursScore;
}

int YahtzeeScoreModule::fives(int *rolls) {
	if (fivesScore >= 0) {
		return -1;
	}
	fivesScore = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 5) {
			fivesScore += 5;
		}
	}
	return fivesScore;
}

int YahtzeeScoreModule::sixes(int *rolls) {
	if (sixesScore >= 0) {
		return -1;
	}
	sixesScore = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 6) {
			sixesScore += 6;
		}
	}
	return sixesScore;
}
int YahtzeeScoreModule::threeOfKind(int *rolls) {
	if (threeOfKindScore >= 0) {
		return -1;
	}
	threeOfKindScore = 0;
	int onesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 1) {
			onesCount++;
		}
	}
	int twosCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 2) {
			twosCount++;
		}
	}
	int threesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 3) {
			threesCount++;
		}
	}
	int foursCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 4) {
			foursCount++;
		}
	}
	int fivesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 5) {
			fivesCount++;
		}
	}
	int sixesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 6) {
			sixesCount++;
		}
	}
	if (onesCount < 3 && twosCount < 3 && threesCount < 3 && foursCount < 3 && fivesCount < 3 && sixesCount < 3) {
		return 0;
	}
	for (int i = 0; i < 5; i++) {
		threeOfKindScore += *(rolls + i);
	}
	return threeOfKindScore;
}
int YahtzeeScoreModule::fourOfKind(int *rolls) {
	if (fourOfKindScore >= 0) {
		return -1;
	}
	fourOfKindScore = 0;
	int onesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 1) {
			onesCount++;
		}
	}
	int twosCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 2) {
			twosCount++;
		}
	}
	int threesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 3) {
			threesCount++;
		}
	}
	int foursCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 4) {
			foursCount++;
		}
	}
	int fivesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 5) {
			fivesCount++;
		}
	}
	int sixesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 6) {
			sixesCount++;
		}
	}
	if (onesCount < 4 && twosCount < 4 && threesCount < 4 && foursCount < 4 && fivesCount < 4 && sixesCount < 4) {
		return 0;
	}
	for (int i = 0; i < 5; i++) {
		fourOfKindScore += *(rolls + i);
	}
	return fourOfKindScore;
}
int YahtzeeScoreModule::yahtzee(int *rolls) {
	if (yahtzeeScore >= 0) {
		return -1;
	}
	yahtzeeScore = 0;
	int onesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 1) {
			onesCount++;
		}
	}
	int twosCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 2) {
			twosCount++;
		}
	}
	int threesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 3) {
			threesCount++;
		}
	}
	int foursCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 4) {
			foursCount++;
		}
	}
	int fivesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 5) {
			fivesCount++;
		}
	}
	int sixesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 6) {
			sixesCount++;
		}
	}
	if (onesCount == 5 || twosCount == 5 || threesCount == 5 || foursCount == 5 || fivesCount == 5 || sixesCount == 5) {
		yahtzeeScore = 50;
		return yahtzeeScore;
	}
	else return 0;
}
int YahtzeeScoreModule::chance(int *rolls) {
	if (chanceScore >= 0) {
		return -1;
	}
	chanceScore = 0;
	for (int i = 0; i < 5; i++) {
		chanceScore += *(rolls + i);
	}
	return chanceScore;
}
int YahtzeeScoreModule::fullHouse(int *rolls) {
	if (fullHouseScore >= 0) {
		return -1;
	}
	int onesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 1) {
			onesCount++;
		}
	}
	int twosCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 2) {
			twosCount++;
		}
	}
	int threesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 3) {
			threesCount++;
		}
	}
	int foursCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 4) {
			foursCount++;
		}
	}
	int fivesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 5) {
			fivesCount++;
		}
	}
	int sixesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 6) {
			sixesCount++;
		}
	}
	if (onesCount == 2 || twosCount == 2 || threesCount == 2 || foursCount == 2 || fivesCount == 2 || sixesCount == 2) {
		if (onesCount == 3 || twosCount == 3 || threesCount == 3 || foursCount == 3 || fivesCount == 3 || sixesCount == 3) {
			fullHouseScore = 25;
			return 25;
		}
		else {
			fullHouseScore = 0;
			return 0;
		}
	}
	fullHouseScore = 0;
	return 0;
}
int YahtzeeScoreModule::smallStraight(int *rolls) {
	if (smallStraightScore >= 0) {
		return -1;
	}
	int onesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 1) {
			onesCount++;
		}
	}
	int twosCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 2) {
			twosCount++;
		}
	}
	int threesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 3) {
			threesCount++;
		}
	}
	int foursCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 4) {
			foursCount++;
		}
	}
	int fivesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 5) {
			fivesCount++;
		}
	}
	int sixesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 6) {
			sixesCount++;
		}
	}
	if ((onesCount >= 1 && twosCount >= 1 && threesCount >= 1 && foursCount >= 1) || (twosCount >= 1 && threesCount >= 1 && foursCount >= 1 && fivesCount >= 1) || (threesCount >= 1 && foursCount >= 1 && fivesCount >= 1 && sixesCount >= 1)) {
		smallStraightScore = 30;
		return 30;
	}
	else {
		smallStraightScore = 0;
		return 0;
	}
}
int YahtzeeScoreModule::largeStraight(int *rolls) {
	if (largeStraightScore >= 0) {
		return -1;
	}
	int onesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 1) {
			onesCount++;
		}
	}
	int twosCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 2) {
			twosCount++;
		}
	}
	int threesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 3) {
			threesCount++;
		}
	}
	int foursCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 4) {
			foursCount++;
		}
	}
	int fivesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 5) {
			fivesCount++;
		}
	}
	int sixesCount = 0;
	for (int i = 0; i < 5; i++) {
		if (*(rolls + i) == 6) {
			sixesCount++;
		}
	}
	if ((onesCount == 1 && twosCount == 1 && threesCount == 1 && foursCount == 1 && fivesCount ==1) || (twosCount == 1 && threesCount == 1 && foursCount == 1 && fivesCount == 1 && sixesCount ==1)) {
		largeStraightScore = 40;
		return 40;
	}
	else {
		largeStraightScore = 0;
		return 0;
	}
}