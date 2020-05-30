#include "bar.h"
#include "foo.h"
#include <string>

using namespace potd;
using namespace std;

bar::bar(string name){
	f_ = new foo(name);
}
bar::bar(const bar &obj){
	f_=new foo(obj.get_name());
}
bar::~bar(){
	delete f_;
}
void bar::operator=(const bar &obj){
	delete this->f_;
	this->f_=new foo(obj.get_name());
}
string bar::get_name()const{
	return f_->get_name();
}
