CXX=g++
CXXFLAGS += -g -Wall -Wextra -pthread
CPPFLAGS += -isystem src -std=c++11

MKDIR_P = mkdir -p
OBJ_DIR = obj

all: no_lock no_lock_tests submission

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

submission:
	zip -r no-lock-submission.zip src

obj/%.o: src/%.cpp ${OBJ_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

obj/no_lock_tests.o: test/no_lock_tests.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

no_lock_tests : obj/NoLockStack.o obj/no_lock_tests.o /usr/lib/libgtest.a /usr/lib/libgtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

no_lock: obj/main.o obj/NoLockStack.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *~ obj/*.o *.zip
	rm -f -r obj/
	rm -f no_lock no_lock_tests output.txt
