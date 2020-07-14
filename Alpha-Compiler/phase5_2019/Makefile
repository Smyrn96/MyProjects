all:
	flex --outfile=al.c al.l
	bison -v --yacc --defines --output=parser.c parser.y
	gcc -g -o calc.out al.c parser.c SymTable.h
	gcc -g -o avm.out avm_start.c avm.h -lm 
	
clean:
	rm -rf *.out


	