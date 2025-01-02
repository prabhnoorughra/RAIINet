CXX = g++ -std=c++20
CXXFLAGS = -Wall -g -O -MMD -Werror=vla -I/usr/X11R6/include -L/usr/X11R6/lib -lX11  # use -MMD to generate dependencies
SOURCES = $(wildcard *.cc)   # Pick up all implementation files
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC = raiinet				# Enter the executable name

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -lX11 -o $(EXEC)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)


