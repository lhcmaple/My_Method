a.out:test.out
	g++ test.out -g -o a.out -std=c++11
test.out:test.cpp linear_list.h
	g++ -c test.cpp -g -o test.out -std=c++11 -I ./