CC ?= clang
output_file ?= server
LIBS ?= -luv
CFLAGS ?= -Wall -O2 $(LIBS)

default:
	@echo "[ OK ] Compiling server code..."
	@sleep 3
	@$(CC) server.c -o $(output_file) $(CFLAGS)
	@echo "[ OK ] Done. Generated file [ $(output_file) ]"

clean:
	@echo "[ OK ] Cleaning..."
	@sleep 3
	@rm -f *.o $(output_file) 
	@echo "[ OK ] Done..."
