#include "pet.h"
#include <string>
using namespace std;
Pet::Pet():Pet("cat","fish","Fluffy","Cinda"){}
Pet::Pet(string type, string food, string name, string owner){
	setType(type);
	food_=food;
	name_=name;
	owner_name_=owner;
}
string Pet::getName(){
	return name_;
}
string Pet::getOwnerName(){
	return owner_name_;
}
void Pet::setName(string name){
	name_=name;
}
void Pet::setOwnerName(string owner){
	owner_name_=owner;
}
string Pet::print(){
	return "My name is "+name_;
}
