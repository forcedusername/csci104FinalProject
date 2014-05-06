#ifndef _comparators
#define _comparators
#include <string>

using namespace std;

class int_compare {
	public: 
		bool operator () (int const &lhs, int const &rhs){
      bool ret = false;
      if (lhs > rhs)
        ret = true;
      return ret;
		}
};

class string_compare {
	public:
		bool operator () (string const &lhs, string const &rhs){
      bool ret = false;
      if (lhs > rhs)
        ret = true;
      return ret;
		}
};

#endif
