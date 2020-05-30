#include <iostream>
#include <string>
using namespace std;
string getFortune(const string &s){
	int x = s.length();
	x = x%5;
	switch(x){
		case 0:
			return"I'm sure you'll do great!";
			break;
		case 1:
			return"Your wish is my command";
			break;
		case 2:
			return"Ask me later";
			break;
		case 3:
			return "now is not the time";
			break;
		case 4:
			return"It's your lucky day";
			break;
	}
	return "What?";
}
