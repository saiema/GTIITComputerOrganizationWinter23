# IPC (Inter-Process Communications)

In this topic we explore only two ways for processes to communicate with each other:
 * pipe: a buffer-like file with an input component and an output component.
 * signals: can be considered as very simple messages that can be sent to a process, each signal can have an
   associated handler, which is a function that will be executed to handle that signal.

## Unnamed and named pipes

### Unnamed pipes

These are created when using the `|` operator in *Bash* as in `cmd_1 | cmd_2`, this will create an *unnamed* pipe, redirect the standard output of `cmd_1` to the input component of the pipe, and redirect the output component of the pipe to the standard input of `cmd_2`.

### Named pipes

These are created by calling `mkfifo <pipe name>`, i.e.: `mkfifo my_pipe`, and will create a named pipe as a special file. One can then redirect the standard output to the input component of this named pipe like `cmd_1 > my_pipe`; and redirect the ouput component of the ouput component of the named pipe to the standard input of another command like `cmd_2 < my_pipe`.

One can also use this named pipe as a file if one has a program that takes a file as input, for example `cat my_pipe`.

### Examples on this topic

The `toUpperCase.c` program will transform any string into upper case. The different options to call this program are:

 * `./toUpperCase` which will start reading from the standard input.
 * `./toUpperCase <arg1> <arg2> ... <argN>` which according to the type of each argument will do the following:
   * If the argument is not a file, it will read it as a string and output that string in upper case.
   * If the argument is a file, it will read from the file and output the contents in upper case.

The `lameChatGPT.c` program will read from a file and output it's result to another file. The different options to call this program are:

 * `./lameChatGPT` it will read from standard input and write to standard output.
 * `./lameChatGPT <filename>` it will read from a file called `filename` and write to standard output.
 * `./lameChatGPT <filename_I> <filename_O>` it will read from a file called `filename_I` and write to a file named `filename_O`.

 The behavior of `lameChatGPT` depends on the input it read:
  * `I'm <string>` will write `Hello <string, nice to meet you!`.
  * `Time` will write the current time.
  * `Goodbye` will write `Goodbye, shutting down...` and exit.

  ## Signals

  Signals are a very simple IPC mechanism, in general the only data transmited with a signal is the signal itself. Another limitation is that same signals can't be acumulated, i.e.: if a process recieves a signal *S* and before it can handle that signal, another signal *S* arrives, the second one will be lost.

  ### Examples on this topic

  The `spareMe.c` program declared custom handlers for both `SIGINT` (Interruption from keyboard, i.e.: Ctrl + C), and `SIGTERM`, the signal sent by default when calling `kill <pid>`. When a handler is called (because a signal handled by that handler arrived) the handler needs to be reattached for that signal.

  You can compile (`gcc -o spareMe spareMe.c`) and run this program `./spareMe` to see how it reacts to interruptions from keyboard (Ctrl + C), and signals from kill (`kill <pid>`).

  As a bonus, modify this program so it prints its *PID* in every line it prints.