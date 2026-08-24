processflow:
	gcc -Wall -Wextra -Wpedantic -std=c11 -g main.c -o processflow

run:
	./processflow

clean:
	rm -f processflow

.PHONY: processflow run clean