CXX=g++
CXXFLAGS += -g -Wall -Wextra -pthread
CPPFLAGS += -isystem src -std=c++11

MKDIR_P = mkdir -p
OBJ_DIR = obj

all: fstream

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

obj/%.o: %.cpp ${OBJ_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

one: obj/fstream.o
	$(CXX) -o $@ $^

clean:
	rm -f *~ obj/*.o *.zip
	rm -f fstream
