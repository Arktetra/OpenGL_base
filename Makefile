# This uses Bash shell...

CC = g++

LDFLAGS = src/lib/libglfw3.dll.a -lglfw3
DEPFLAGS = -MP -MD

INCDIRS = src/includes		# can be a list
INCGLAD = src/includes/GLAD/glad.c
OPT = -O1

CFLAGS = -std=c++11 -Wall -Wextra -g $(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

APPNAME = app 
EXT = .cpp
SRCDIR = src
BUILDDIR = build
DEPDIR = dep

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.obj, $(SRCFILES))
DEPFILES = $(patsubst $(SRCDIR)/%.cpp, $(DEPDIR)/%.d, $(SRCFILES))

all: $(APPNAME)

$(APPNAME): $(OBJECTS)
	$(CC) $(INCGLAD) -o $@ $^ $(LDFLAGS)

-include $(DEPFILES)

$(BUILDDIR)/%.obj: $(SRCDIR)/%.cpp Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

debug:
	$(warning SRCFILES = $(SRCFILES))
	$(warning OBJECTS = $(OBJECTS))

clean:
	rm $(BUILDDIR)/*.obj
	rm $(DEPDIR)/*.d
