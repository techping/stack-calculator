OUTPUT = stack_calculator
SRC = stack.c

${OUTPUT} : ${OUTPUT}.c ${SRC}
	gcc -o $@ $^ -lm

.PHONY: clean
clean:
	rm ${OUTPUT}
