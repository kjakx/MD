CXX = g++
CFLAGS    = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers -std=c++17
INCLUDE   = -I./src/include
TARGET    = ./bin/MD
SRCDIR    = ./src
SOURCES   = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR    = ./obj
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS   = $(OBJECTS:.o=.d)

.cpp.o: $(SOURCES)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
