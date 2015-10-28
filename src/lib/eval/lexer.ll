%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "eval_context.h"
# include "parser.h"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token.
static isc::eval::location loc;
%}
%option noyywrap nounput batch debug noinput
int   [0-9]+
blank [ \t]

%{
    // Code run each time a pattern is matched.
#define YY_USER_ACTION  loc.columns(yyleng);
%}

%%

%{
    // Code run each time yylex is called.
    loc.step();
%}

{blank}+   loc.step();
[\n]+      loc.lines(yyleng); loc.step();

\"[a-zA-Z_0-9]*\" {
    // This is a string, no need to do any conversions here.
    return isc::eval::EvalParser::make_STRING(yytext, loc);
}

option\[{int}\] {
    long n = strtol(yytext, NULL, 10);
    /// @todo: Sanity check n
    if (n<0 || n>65535) {
        driver.error(loc, "Option code has invalid values. Allowed range: 0..65535");
    }

    return isc::eval::EvalParser::make_OPTION(n, loc);
}

"==" {
    return isc::eval::EvalParser::make_EQUAL(loc);
}

"substring" {
    return isc::eval::EvalParser::make_SUBSTRING(loc);
}

"("      return isc::eval::EvalParser::make_LPAREN(loc);
")"      return isc::eval::EvalParser::make_RPAREN(loc);
","      return isc::eval::EvalParser::make_COMA(loc);

.          driver.error (loc, "invalid character");
<<EOF>>    return isc::eval::EvalParser::make_END(loc);
%%

void
EvalContext::scan_begin()
{
    yy_flex_debug = trace_scanning;
    if (file.empty () || file == "-") {
        yyin = stdin;
    }
    else if (!(yyin = fopen(file.c_str (), "r"))) {
        error ("cannot open " + file + ": " + strerror(errno));
        exit (EXIT_FAILURE);
    }
}

void
EvalContext::scan_end()
{
    fclose (yyin);
}
