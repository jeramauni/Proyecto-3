#include "Component.h"

std::vector<std::string> Component::GetWords(std::string& s)
{
	std::vector<std::string> words;
	std::string word;
	for (auto x : s)
	{
		if (x == '/')
		{
			words.push_back(word);
			word = "";
		}
		else
		{
			word = word + x;
		}
	}
	words.push_back(word);
	return words;
}
