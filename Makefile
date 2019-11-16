Scheduling: main_program.c
	gcc -o Scheduling main_program.c
	ls -l

clean:
	if [ -a Scheduling ] ; \
	then \
		rm Scheduling ; \
	fi;
	ls -l