#include "eval_context.h"
#include "parser.h"

#include <fstream>

EvalContext::EvalContext ()
  : trace_scanning (false), trace_parsing (false)
{
  variables["one"] = 1;
  variables["two"] = 2;
}

EvalContext::~EvalContext ()
{
}

int
EvalContext::parseFile(const std::string &filename)
{
    file = filename;
    scan_begin();
    yy::EvalParser parser (*this);
    parser.set_debug_level(trace_parsing);
    int res = parser.parse();
    scan_end();
    return res;
}

int
EvalContext::parseString(const std::string& str)
{
    remove("/tmp/eval");
    std::fstream f("/tmp/eval", std::ios::trunc);

    f << str;
    f.close();

    return (parseFile("/tmp/eval"));
}

void
EvalContext::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void
EvalContext::error (const std::string& m)
{
  std::cerr << m << std::endl;
}
