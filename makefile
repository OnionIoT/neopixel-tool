
# find the os
UNAME_S := $(shell uname -s)

# main compiler
CXX := g++
# CXX := clang --analyze # and comment out the linker last line for sanity

# define the directories
SRCDIR := src
INCDIR := include
BUILDDIR := build
BINDIR := bin
LIBDIR := lib

# define common variables
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -maxdepth 1 -type f \( -iname "*.$(SRCEXT)" ! -iname "*main*.$(SRCEXT)" \) )
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CXXFLAGS := -g # -Wall

INC := $(shell find $(INCDIR) -maxdepth 1 -type d -exec echo -I {}  \;)
LIB := $(LIB) -L$(LIBDIR) -loniondebug -lonioni2c

ifeq ($(UNAME_S),Darwin)
	# only add this when compiling on OS X
	INC += -I $(LIBDIR)
endif

# define specific binaries to create
LIB0 := libonionneopixel
LIB0_TARGET := $(LIBDIR)/$(LIB0).so

APP0 := neopixel-tool
APP0_SOURCES := src/main.cpp
APP0_OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(APP0_SOURCES:.$(SRCEXT)=.o))
APP0_TARGET := $(BINDIR)/$(APP0)
APP0_LIB := $(LIB) -lonionneopixel


all: info $(LIB0_TARGET) $(APP0_TARGET)

$(LIB0_TARGET): $(OBJECTS)
	@echo " Compiling $@"
	@mkdir -p $(LIBDIR)
	$(CXX) -shared -o $@  $^ $(LIB)
	@$(LIB) += -libonionneopixel

$(APP0_TARGET): $(APP0_OBJECTS) 
	@mkdir -p $(BINDIR)
	@echo " Linking..."
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $(APP0_TARGET) $(APP0_LIB)

# generic: build any object file required
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo "building $@"
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(BINDIR) $(LIB0_TARGET)

info:
	@echo "CXX: $(CXX)"
	@echo "CXXFLAGS: $(CXXFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "LIB: $(LIB)"
	@echo "INC: $(INC)"
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"


# Tests
tester:
	$(CXX) $(CXXFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
#ticket:
#  $(CXX) $(CXXFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
