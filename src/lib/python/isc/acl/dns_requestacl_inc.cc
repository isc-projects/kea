namespace {
const char* const RequestACL_doc = "\
The ACL itself.\n\
\n\
It holds bunch of ordered entries, each one consisting of a check ( of\n\
any kind, it might be even compound) and an action that is returned\n\
whenever the action matches. They are tested in the order and first\n\
match counts.\n\
\n\
This is non-copyable. It seems that there's no need to copy them (even\n\
when it would be technically possible), so we forbid it just to\n\
prevent copying it by accident. If there really is legitimate use,\n\
this restriction can be removed.\n\
\n\
The class is template. It is possible to specify on which context the\n\
checks match and which actions it returns. The actions must be\n\
copyable for this to work and it is expected to be something small,\n\
usually an enum (but other objects are also possible).\n\
\n\
There are protected functions. In fact, you should consider them\n\
private, they are protected so tests can get inside. This class is not\n\
expected to be subclassed in real applications.\n\
\n\
ACL(default_action)\n\
\n\
    Constructor.\n\
\n\
    Parameters:\n\
      default_action It is the action that is returned when the\n\
                 checked things \"falls off\" the end of the list\n\
                 (when no rule matched).\n\
\n\
";

const char* const RequestACL_execute_doc = "\
execute(context) ->  Action \n\
\n\
The actual main function that decides.\n\
\n\
This is the function that takes the entries one by one, checks the\n\
context against conditions and if it matches, returns the action that\n\
belongs to the first matched entry or default action if nothing\n\
matches.\n\
\n\
Parameters:\n\
  context    The thing that should be checked. It is directly passed\n\
             to the checks.\n\
\n\
Return Value(s): The action for the ACL entry that first matches the\n\
context.\n\
";
} // unnamed namespace
