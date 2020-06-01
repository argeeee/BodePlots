#ifndef BODE_H_
#define BODE_H_

#include <string>
#include <sstream>

namespace bode {

	using namespace std;

	class Bode {
	 public:
		Bode(const string& text)
			: _text(text)
		{
		}

		string getSolution() {
			stringstream ss;
			return ss.str();
		}

	 private:
	 	void parse() { }

	 private:
		string _text;
	};

};

#endif