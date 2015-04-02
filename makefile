all:

Darwin.log:
	git log > Darwin.log

Doxyfile:
	doxygen -g

RunDarwin: Darwin.h Darwin.c++ RunDarwin.c++
	g++ -pedantic -std=c++11 -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin

RunDarwin.tmp: RunDarwin
	RunDarwin < RunDarwin.in > RunDarwin.tmp
	diff RunDarwin.tmp RunDarwin.out

TestDarwin: Darwin.h Darwin.c++ TestDarwin.c++
	g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lgtest_main -lpthread

TestDarwin.out: TestDarwin
	valgrind ./TestDarwin     >  TestDarwin.out 2>&1
	gcov -b  Darwin.c++     >> TestDarwin.out
	gcov -b  TestDarwin.c++ >> TestDarwin.out

html: Doxyfile Darwin.h Darwin.c++ RunDarwin.c++ TestDarwin.c++
	doxygen Doxyfile

darwin-tests:
	git clone https://github.com/cs371p-spring-2015/darwin-tests.git

check:
	@[ -d html                            ] && echo "html/                           found" || echo "html/                           NOT FOUND"
	@[ -e darwin-tests/EID-RunDarwin.out  ] && echo "darwin-tests/EID-RunDarwin.out  found" || echo "darwin-tests/EID-RunDarwin.out  NOT FOUND"
	@[ -e darwin-tests/EID-TestDarwin.c++ ] && echo "darwin-tests/EID-TestDarwin.c++ found" || echo "darwin-tests/EID-TestDarwin.c++ NOT FOUND"
	@[ -e darwin-tests/EID-TestDarwin.out ] && echo "darwin-tests/EID-TestDarwin.out found" || echo "darwin-tests/EID-TestDarwin.out NOT FOUND"
	@[ -e Darwin.c++                      ] && echo "Darwin.c++                      found" || echo "Darwin.c++                      NOT FOUND"
	@[ -e Darwin.h                        ] && echo "Darwin.h                        found" || echo "Darwin.h                        NOT FOUND"
	@[ -e Doxyfile                        ] && echo "Doxyfile                        found" || echo "Doxyfile                        NOT FOUND"
	@[ -e RunDarwin.c++                   ] && echo "RunDarwin.c++                   found" || echo "RunDarwin.c++                   NOT FOUND"
	@[ -e RunDarwin.out                   ] && echo "RunDarwin.out                   found" || echo "RunDarwin.out                   NOT FOUND"
	@[ -e TestDarwin.c++                  ] && echo "TestDarwin.c++                  found" || echo "TestDarwin.c++                  NOT FOUND"
	@[ -e TestDarwin.out                  ] && echo "TestDarwin.out                  found" || echo "TestDarwin.out                  NOT FOUND"

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunDarwin
	rm -f RunDarwin.tmp
	rm -f TestDarwin
	rm -f TestDarwin.out
