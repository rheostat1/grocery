all: stack_test tree

stack_test:
	gcc stack.c stack_test.c -o st

tree:
	gcc queue.c stack.c node.c -o t

.PHONEY: clean

clean:
	@rm -rf *.o st t
