#ifndef EVAL_CONTEXT_H
#define EVAL_CONTEXT_H
# include <string>
# include <map>
# include "parser.h"

// Tell Flex the lexer's prototype ...
# define YY_DECL \
    isc::eval::EvalParser::symbol_type yylex (EvalContext& driver)

// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of Calc++.
class EvalContext
{
public:
  EvalContext ();
  virtual ~EvalContext ();

  isc::dhcp::Expression expression;

  int result;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;

  // Run the parser on file F.
  // Return 0 on success.
  int parseFile(const std::string& filename);

  int parseString(const std::string& str);

  // The name of the file being parsed.
  // Used later to pass the file name to the location tracker.

  std::string file;
  // Whether parser traces should be generated.
  bool trace_parsing;

  // Error handling.
  void error (const isc::eval::location& l, const std::string& m);
  void error (const std::string& m);
};
#endif // ! EVALCONTEXT_HH
