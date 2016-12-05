EFILES= shell
all: $(EFILES) mytoc.o

argDemo: argDemo.o
envDemo: envDemo.o mytoc.o
exec: exec.o
forkPipeDemo: forkPipeDemo.o
rwDemo: rwDemo.o
saferFork: saferFork.o
sigIgn: sigIgn.o
sigPrint: sigPrint.o
mytoc.o: mytoc.c
	gcc -c mytoc.c
shell:shell.o mytoc.o
	cc -o shell shell.o mytoc.o
clean:
	rm -f *.o $(EFILES)
