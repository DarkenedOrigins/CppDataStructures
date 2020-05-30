#ifndef Pet_H
#define Pet_H
#include <string>
#include "animal.h"
using namespace std;
class Pet : public Animal{
	private:
		string name_;
		string owner_name_;
	public:
		Pet();
		Pet(string type, string food, string name, string owner);
		string getName();
		string getOwnerName();
		void setName(string name);
		void setOwnerName(string owner);
		string print();
};
#endif
