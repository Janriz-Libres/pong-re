CXX := g++
RM := rm -f
CPPFLAGS := -g
LDFLAGS := -g
LDLIBS := -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SRCS))
EXEC := pong

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^ >> ./.depend;

clean:
	$(RM) $(OBJS)

distclean:
	$(RM) $(EXEC)

