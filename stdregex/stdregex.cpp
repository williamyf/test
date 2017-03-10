// stdregex.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <regex>

int main()
{
	//std::string s("this subject has a submarine as a subsequence");
	std::string s("abcdef.1.2.1page.zmesh");
	std::smatch m;
	//std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"
	std::regex e("(\\.\\dpage\\.)");   // matches words beginning by "sub"

	std::cout << "Target sequence: " << s << std::endl;
	std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
	std::cout << "The following matches and submatches were found:" << std::endl;

	while (std::regex_search(s, m, e)) {
		for (auto x : m) std::cout << x << " ";
		std::cout << std::endl;
		s = m.suffix().str();
	}
	if (std::regex_match(s,e))
	{
		std::cout << "matches" << std::endl;
	}
	return 0;
}

