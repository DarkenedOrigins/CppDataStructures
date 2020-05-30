#ifndef BAR_H
#define BAR_H
#include "foo.h"
#include <string>

namespace potd{
	class bar{
		public:
			bar(std::string);
			bar(const bar &obj) ;
			~bar();
			void operator=(const bar &obj);
			std::string get_name() const;
		private:
			potd::foo *f_;
	};
}
#endif
