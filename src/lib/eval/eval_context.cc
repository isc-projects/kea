#include <eval/eval_context.h>
#include <eval/parser.h>
#include <exceptions/exceptions.h>
#include <fstream>

EvalContext::EvalContext()
  : trace_scanning (false), trace_parsing (false)
{
}

EvalContext::~EvalContext()
{
}

int
EvalContext::parseFile(const std::string &filename)
{
    file = filename;
    scan_begin();
    isc::eval::EvalParser parser(*this);
    parser.set_debug_level(trace_parsing);
    int res = parser.parse();
    scan_end();
    return res;
}

int
EvalContext::parseString(const std::string& str)
{
    /// @todo: Is there any way for the parser to read from a stream,
    /// rather than a file? It would be better to use stringstream,
    /// but it seems that the lexer operates on FILE* interface.

    // Put the content into a file and then open that file for reading.
    remove("/tmp/eval");
    std::fstream f("/tmp/eval", std::ios::out);

    if (!f.good()) {
        isc_throw(isc::Unexpected, "Can't write /tmp/eval file");
    }
    f << str;
    f.close();

    return (parseFile("/tmp/eval"));
}

void
EvalContext::error(const isc::eval::location& l, const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void
EvalContext::error (const std::string& m)
{
  std::cerr << m << std::endl;
}
