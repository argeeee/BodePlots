#include <emscripten.h>
#include <emscripten/bind.h>
#include <string>
#include <memory>

#include "Bode.h"

using namespace emscripten;

void CalculatePlot(std::string text) {
  using namespace bode;
  using namespace std;

  Parser parser(text);
  auto syntaxTree = parser.Parse();

  const auto& diagnostics = parser._reporter->Diagnistics;

  if (!diagnostics->size())
  {
    Evaluator evaluator;
    const auto& root = syntaxTree->Root;

    vector<double> module;
    for (int i = 0; i < 10; i++) {
      module.push_back(
        log10(abs(evaluator.Evaluate(root, pow_(10, i))))
      );
    }
    stringstream ss;
    ss << "GenerateCalculatedPlotListeners([";
    for (int i = 0; i < module.size(); i++) {
      ss << module.at(i);
      if (i != module.size() - 1)
        ss << ',';
      else 
        ss << "],[";
    }

    vector<double> phase;
    for (int i = 0; i < 10; i++) {
      const auto& c = evaluator.Evaluate(root, pow_(10, i)); 
      phase.push_back(
        -atan(c.imag() / c.real())
      );
    }
    for (int i = 0; i < phase.size(); i++) {
      ss << phase.at(i);
      if (i != phase.size() - 1)
        ss << ',';
      else 
        ss << ']';
    }
    ss << ")";

    string newText = string("document.querySelector('#f-text').innerText = \"") + text + string("\"");

    emscripten_run_script(ss.str().c_str());
    emscripten_run_script(newText.c_str());
    emscripten_run_script("revealCalculated()");

  }
  else
  { 
    stringstream ss;
    ss << "printErrors([";
    for (int i = 0; i < diagnostics->size(); i++) {
      ss << '"' << diagnostics->at(i) << '"';
      if (i != diagnostics->size() - 1)
        ss << ',';
      else 
        ss << ']';
    }
    ss << ")";
    emscripten_run_script(ss.str().c_str());
  }

} 

EMSCRIPTEN_BINDINGS(bode_) {
  function("CalculatePlot", &CalculatePlot);
}