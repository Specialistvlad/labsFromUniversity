build:
	cd computer-algorithms; make;
	cd subject-data-structures; make;

clean:
	cd computer-algorithms; make clean;
	cd subject-data-structures; make clean;

.PHONY: build
