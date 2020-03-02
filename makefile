pa1:
	gcc -o MWST ./src/main.c
clean:
	rm MWST && rm output_file
test:
	./MWST input_file output_file
