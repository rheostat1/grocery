all: stack_test tree

stack_test:
	gcc stack.c stack_test.c -o st

tree:
	gcc node.c stack.c -o t

.PHONEY: clean

clean:
	@rm -rf *.o st t
