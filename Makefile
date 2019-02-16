
BIN_DIR = bin

TEST_OUT_DIR = test_output

BINS =  \
  $(BIN_DIR)/test_hypot \
  $(BIN_DIR)/test_hypot_old \
  $(BIN_DIR)/test_hypot_old \
  $(BIN_DIR)/test_hypot_new

all: $(BINS)

$(BIN_DIR)/test_hypot: test_hypot.cpp
	g++ -std=c++17 -g -Wall -Wextra -Wno-psabi -I../tr29124_test/include -I../tr29124_test/polynomial/include -o $(BIN_DIR)/test_hypot test_hypot.cpp

$(BIN_DIR)/test_hypot_new: test_hypot_new.cpp
	g++ -std=c++17 -g -Wall -Wextra -Wno-psabi -o $(BIN_DIR)/test_hypot_new test_hypot_new.cpp

$(BIN_DIR)/test_hypot_old: test_hypot_new.cpp
	g++ -std=c++17 -g -Wall -Wextra -Wno-psabi -DOLDWAY=1 -o $(BIN_DIR)/test_hypot_old test_hypot_new.cpp

$(BIN_DIR)/test_hypot_old2: test_hypot_new.cpp
	g++ -std=c++17 -g -Wall -Wextra -Wno-psabi -DOLDOLDWAY=1 -o $(BIN_DIR)/test_hypot_old2 test_hypot_new.cpp

test: $(BINS)
	$(BIN_DIR)/test_hypot > $(TEST_OUT_DIR)/test_hypot.txt
	$(BIN_DIR)/test_hypot_old2 > $(TEST_OUT_DIR)/test_hypot_old2.txt
	$(BIN_DIR)/test_hypot_old > $(TEST_OUT_DIR)/test_hypot_old.txt
	$(BIN_DIR)/test_hypot_new > $(TEST_OUT_DIR)/test_hypot_new.txt

diff:
	kdiff3 $(TEST_OUT_DIR)/test_hypot_old2.txt $(TEST_OUT_DIR)/test_hypot_old.txt $(TEST_OUT_DIR)/test_hypot_new.txt

clean:$(BINS)
	rm -rf $(BINS)


$(TEST_OUT_DIR): $(TEST_OUT_DIR)
	if test ! -d $(TEST_OUT_DIR); then \
	  mkdir $(TEST_OUT_DIR); \
	fi


$(BIN_DIR):
	if test ! -d $(BIN_DIR); then \
	  mkdir $(BIN_DIR); \
	fi
