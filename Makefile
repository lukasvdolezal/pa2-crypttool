PROGRAM=dolezl11
CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -Wextra -g -Wno-long-long -O0 -ggdb

all: compile doc

run: compile
	./$(PROGRAM)

compile: $(PROGRAM)

doc: src/main.cpp src/*.hpp
	doxygen Doxyfile

$(PROGRAM): objs/main.o objs/CData.o objs/CMD5.o objs/CList.o objs/CCaesar.o objs/MyLibrary.o objs/CCipher.o objs/CVigener.o objs/CSha1.o objs/CBase64.o objs/CDesCBC.o objs/CDes.o objs/CDesECB.o
	$(CC) $(CFLAGS) $^ -o $@ -lcrypto

objs/main.o: src/main.cpp src/CData.hpp src/CList.hpp src/CCipher.hpp src/MyLibrary.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CList.o: src/CList.cpp src/CList.hpp src/CCipher.hpp src/CMD5.cpp src/CCaesar.hpp src/CVigener.hpp src/CSha1.hpp src/CBase64.hpp src/CDesCBC.hpp src/CDesECB.hpp src/MyLibrary.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CData.o: src/CData.cpp src/CData.hpp src/CMD5.hpp src/CCaesar.hpp src/CCipher.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CMD5.o: src/CMD5.cpp src/CMD5.hpp src/CCipher.hpp src/CData.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CCaesar.o: src/CCaesar.cpp src/CCaesar.hpp src/CCipher.hpp src/MyLibrary.hpp src/CData.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/MyLibrary.o: src/MyLibrary.cpp src/MyLibrary.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CCipher.o: src/CCipher.cpp src/CCipher.hpp src/CData.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CVigener.o: src/CVigener.cpp src/CVigener.hpp src/CData.hpp src/CCipher.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CSha1.o: src/CSha1.cpp src/CSha1.hpp src/CData.hpp src/CCipher.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CBase64.o: src/CBase64.cpp src/CBase64.hpp src/CData.hpp src/CCipher.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CDesCBC.o: src/CDesCBC.cpp src/CDesCBC.hpp src/CData.hpp src/CDes.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CDes.o: src/CDes.cpp src/CDes.hpp src/CCipher.hpp src/CData.hpp src/MyLibrary.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs/CDesECB.o: src/CDesECB.cpp src/CDesECB.hpp src/CData.hpp src/CDes.hpp | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lcrypto

objs:
	mkdir objs

clean:
	rm -rf $(PROGRAM) objs/ doc/ 2>/dev/null