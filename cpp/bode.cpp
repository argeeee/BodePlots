#include <emscripten.h>
#include <emscripten/bind.h>
#include <string>
#include <memory>

#include "Bode.h"

using namespace emscripten;


void GenetatePlots(std::string text, std::string mR, std::string mA, std::string pR) {
	using namespace std;

	stringstream ss;
	ss << "GenerateCalculatedPlotListeners(";
	ss << mR << ","
	// << mA << ","
		 << pR << ")";

	string newText = string("document.querySelector('#f-text').innerText = \"") + text + string("\"");

	emscripten_run_script(ss.str().c_str());
	emscripten_run_script(newText.c_str());
	emscripten_run_script("revealCalculated()");
}

void PrintJsError(std::string vecS) {
	std::stringstream ss;
	ss << "printErrors(";
	ss << vecS;
	ss << ")";
	emscripten_run_script(ss.str().c_str());
}

EMSCRIPTEN_BINDINGS(bode_) {
  function("CalculatePlot", &CalculatePlot);
}