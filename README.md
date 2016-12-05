## Juan Razo

## Shell Lab

For this lab I started with fixing my tokenizer lab. I began to test my tokenizer by tokenizing the envp with "=". The test 
was tested in the envDemo.c. I then moved to look for PATH and tokenize by  ":" and was succesful in OS X 64 bit. However when 
I moved the code into the Linux VM I started to get a free error. I realized that this was because the VM was 32 bit and the 
allocation size was different and was only happening at a specific string value of 92. The problem was caused because I was 
calling malloc with the exact size of the token and then adding the EOC '\0' to the size +1. Once the problem was fixed I was
able to move into the shell lab succesfully. My next step was to get familliar with execve for this I read stakoverflow to get
a good understanding. 
http://stackoverflow.com/questions/7656549/understanding-requirements-for-execve-and-setting-environment-vars
After becoming familiar with execve I moved on to understanding fork() and began to implement simple ls. This was achived by
creating a function that was trying to execute the input from the user. I had to implement a concatinate to myToc, this
allowed me to add a '/' and the first parameter from the user. The concatinate added to myToc uses realloc for the size is 
different when adding chars. I then moved to implement pipes, this was done by checking if the input from the user had a '|' .
This was a work around and took me some time to understand how pipes work. I then got help from David Pruitt and suggested to
use recurssion to look for pipes. Eric Camacho was also in the discussion and discussed most of the lab with Camacho. I was
able to get up to the pipes requirements and failed 3 tests in the testShell.sh. The tests that I failed were redirect, 
background, and change dir. I did not have time to add comments or clean up my code for I was working on the lab till the last
 minute. 





In this lab, you will create a user shell in the C programming language that can understand:

- simple commands (e.g. $ /bin/ls or $ ls )
- simple pipes (e.g. $ /bin/ls | /bin/sort -r)
- redirecting input and output (e.g. $ ls > /tmp/files.txt)
- background tasks (e.g. $ find /etc -print & )
-  "cd" ## for "cd" you will need to lookup the library routine "chdir" in the (online) unix manual

optional (except for grad students)
- setting environment variables: "var=value" 
- expanding ~ at the beginning of a parameter
- expanding non-embedded environment variables (e.g. "echo $PATH")

optional for everyone
- command line editing using readline(3)
- expanding embedded environment variables (e.g. "echo ${HOME}/bin"
- expanding ~ within a parameter (e.g. "ls | dd of=~/files.txt")
- Programs that cannot be exec'd or terminate with errors (non-zero exit codes) should be reported.

Your lab must directly use the posix calls:

- pipe()
- fork()
- dup() or dup2()
- execve() (you cannot use execvp)
- wait()
- open() and close()
- chdir()

These system calls are documented in chapter 2 of the unix manual (e.g. $ man 2 fork).

In addition, your program should dynamically allocate memory using the
library calls malloc and free. You may (if you like) use calloc and
strdup which are part of the same library.

## Testing your lab

The OS Grading Team has created a testing harness for your shell lab
located in shell/testShell.sh.  

This may require a couple of very minor changes to your shell lab:

The tests will provide commands to your shells through standard input
(fd #0).  Those command sequences terminate with end-of-file.  Just
like bash, your shell should terminate when they read this
end-of-file. End-of-file is easy to detect as that a request to read()
more than zero bytes will transfer zero bytes.

If there is a PS1 (prompt string #1) environment variable, then your
shell's prompt should be its value.  This is used to suppress your
shell's prompt.  Otherwise, your shell can use any reasonable prompt
string.

To test this, try

  $ export PS1=""

before invoking your shell.

Note that the arch1 virtual machine's default value for PS1 is "[\u@\h
\W]$ " where bash substitutes \u with username, \h with hostname, and
\w with the current working directory.  

Your shell should not write extraneous messages to standard out 
(fd #1).  This is because our tester will be confused by that
information.  
It's fine to print such information to "standard error" (fd #2).

## Useful Snippets

The shellLabDemos contains several demonstration programs that
utilize the system calls and features necessary to implement your shell.

- argDemo: print command line arguments (how argv works)
- envDemo: print the contents of envp (how envp works)
- forkPipeDemo: a short program that uses fork & pipe
- execDemo.c: a short program using exec


## Grading

Our TA will assess:the following aspects of your project:

- documentation/readability/software engineering
- exec properly
- fork properly (shell does not terminate with commands...). Includes checking if program failed (exit code != 0).
- pipe between commands
- background commands
- proper use of PATH environment variable
- proper functioning of environment variables
- proper functioning of change-directory builtin (cd)
