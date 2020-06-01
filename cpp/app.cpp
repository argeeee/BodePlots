#include <iostream>

#include "Bode.h"

int main() {
	using namespace bode;

	Bode bode = Bode("s");
	cout << bode.getSolution() << "\n";

	cin.get(); 
	return 0;
}