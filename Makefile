CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# EmergencyOperationsDesk.cpp is excluded on purpose - it's explicitly marked in
# Once the facade + adapter are written, delete
# this exclusion and rewrite EmergencyOperationsDesk.cpp against real classes.
SRCS = $(filter-out EmergencyOperationsDesk.cpp, $(wildcard *.cpp))
OBJS = $(SRCS:.cpp=.o)
TARGET = campusguard

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
