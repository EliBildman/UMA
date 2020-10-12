CXX=g++
CXXFLAGS += -g -Wall -Wextra -pthread
CPPFLAGS += -isystem src -std=c++11

MKDIR_P = mkdir -p
OBJ_DIR = obj

all: inverter inverter_tests submission

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

submission:
	zip -r inverter-submission.zip src

obj/%.o: src/%.cpp ${OBJ_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

obj/inverter_tests.o: test/inverter_tests.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

inverter: obj/inverter.o obj/main.o
	$(CXX) -o $@ $^

inverter_tests : obj/inverter.o obj/inverter_tests.o /usr/lib/libgtest.a /usr/lib/libgtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

clean:
	rm -f *~ obj/*.o *.zip
	rm -f inverter inverter_tests
