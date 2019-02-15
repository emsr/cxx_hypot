
all: test_hypot test_hypot_new test_hypot_old test_hypot_old2

test_hypot: test_hypot.cpp
	g++ -std=c++17 -g -Wall -Wextra -Wno-psabi -I../tr29124_test/include -I../tr29124_test/polynomial/include -o test_hypot test_hypot.cpp

test_hypot_new: test_hypot_new.cpp
	g++ -std=c++17 -g -Wall -Wextra -Wno-psabi -o test_hypot_new test_hypot_new.cpp

test_hypot_old: test_hypot_new.cpp
	g++ -std=c++17 -g -Wall -Wextra -Wno-psabi -DOLDWAY=1 -o test_hypot_old test_hypot_new.cpp

test_hypot_old2: test_hypot_new.cpp
	g++ -std=c++17 -g -Wall -Wextra -Wno-psabi -DOLDOLDWAY=1 -o test_hypot_old2 test_hypot_new.cpp

test: test_hypot test_hypot_new test_hypot_old test_hypot_old2
	./test_hypot > test_hypot.txt
	./test_hypot_old2 > test_hypot_old2.txt
	./test_hypot_old > test_hypot_old.txt
	./test_hypot_new > test_hypot_new.txt

diff: test_hypot_new test_hypot_old test_hypot_old2
	kdiff3 test_hypot_old2.txt test_hypot_old.txt test_hypot_new.txt

clean: test_hypot test_hypot_new test_hypot_old test_hypot_old2
	rm -rf test_hypot test_hypot_new test_hypot_old test_hypot_old2
