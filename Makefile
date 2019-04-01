all:
	g++-7 myvector.hpp console_test.cpp -Weffc++ -o build/console_test.out
test:
	cxxtestgen --error-printer -o build/test.cpp vector_test.h
	g++-7 -o build/test.out build/test.cpp -fprofile-arcs -ftest-coverage
