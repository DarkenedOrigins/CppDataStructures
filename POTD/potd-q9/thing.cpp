#include "thing.h"
#include <string>
using namespace potd;
using namespace std;
Thing::Thing(int max){
	props_max_ = max;
	props_ct_ = 0;
	properties_ = new string[max];
	values_=new string[max];
}
Thing::Thing(Thing &obj) const{
	props_max_ = obj.props_max_;
	props_ct_ = obj.props_ct_;
	properties_ = obj.properties_;
	values_ = obj.values_;
