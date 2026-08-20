processflow:
	gcc main.c -o processflow

run:
	./processflow

clean:
	rm -f processflow

.PHONY: processflow run clean