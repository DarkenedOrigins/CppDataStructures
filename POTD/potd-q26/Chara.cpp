#include "Chara.h"
#include <iostream>
#include <string>
#include <queue>
string Chara::getStatus() const{
	int x = CharaQueue.size();
	if(x==0){return "Empty";}
	if(x<=3){return "Light";}
	if(x>=4 && x<=6){return "Moderate";}else{return "Heavy";}
}
void Chara::addToQueue(string name){
	CharaQueue.push(name);
}
string Chara::popFromQueue(){
	string x = CharaQueue.front();
	CharaQueue.pop();
	return x;
}
