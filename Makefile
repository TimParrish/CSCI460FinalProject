Scheduling: main_program.c
	gcc main_program.c -lgsl -lgslcblas -lm -o Scheduling
	ls -l

clean:
	if [ -a Scheduling ] ; \
	then \
		rm Scheduling ; \
	fi;
	ls -l