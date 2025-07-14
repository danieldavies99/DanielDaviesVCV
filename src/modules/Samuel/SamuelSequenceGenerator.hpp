#pragma once
#include <vector>
#include <string>
#include <algorithm>

struct SequenceGenerator
{
	int dotLength = 1;
	int dashLength = 3;
	int newLetterLength = 3;
	int newWordLength = 7;
	std::vector<bool> sequence;
	void pushDot();
	void pushDash();
	void pushNewPartInLetter();
	void pushNewLetter();
	void pushNewWord();
	void generateSequence(std::string message);
};
