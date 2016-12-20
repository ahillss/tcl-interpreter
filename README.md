####Minimal TCL Interpreter
A minimal C/C++ embeddable TCL interpreter based off [picol](http://oldblog.antirez.com/post/picol.html). The upvar, uplevel and expr commands have been implemented and eval has been replaced.

Goal is to be very small with no depedencies.

A subset of TCL, though the expr command uses polish notation instead of the infix expressions.

[Ragel](https://www.colm.net/open-source/ragel) is used to generate the parsers for eval and expr.

[Online example](http://andrewhills.github.io/tcl_interpreter/em/example.html) built with emscripten.

#####Command line:
* REPL : no args
* eval file : filename as arg

#####Builtin commands:
* upvar : otherVar myVar
* uplevel : body
* expr : expression
* incr : val
* decr : val
* for : start test next body
* while : test body
* if : test body1 else body2

#####TODO
* "elseif" for "if" command
* implement error stack
* record file, proc and position of errors
* make sure errors propagate through eval and expr calls
* varargs for procs
* backslash escaping spaces, tabs, quotes, brackets etc
* test parsers for certain conditions
* in eval parser, check first word of statement is a command?
* add callback for when undefined commands are called?
* make syntax shortcuts optional (e.g. for $a and ${a})?
* expr: '&&', '||', '?' with short-circuit evaluation
* expr: '~', '!', '%', '&', '^', '|', '**', '<<', '>>', '//', 'eq', 'ne', 'in', 'ni', 'neg', 'abs', 'acos', 'asin', 'atan', 'atan2', 'ceil', 'cos', 'exp', 'floor', 'fmod', 'int', 'log', 'log10', 'max', 'min', 'pow', 'rand', 'round', 'sin', 'sqrt', 'srand', 'tan'
