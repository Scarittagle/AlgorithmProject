NAME := ladder
SRCS := $(wildcard *.cpp)
OBJS := ${SRCS:.cpp=.o}
BOOST_HOME := /home/s/suw/boost_1_65_1/

CXXFLAGS += $(foreach includedir,$(BOOST_HOME),-I$(includedir))
CXXFLAGS += -Wall -std=c++11

.PHONY: all clean

all: ${NAME}

$(NAME): $(OBJS)
	$(LINK.cc) $(OBJS) -o $(NAME)

clean:
	@- rm -rf $(OBJS) $(NAME)