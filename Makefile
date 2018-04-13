CC=gcc
LIBS=-l
SDIR=src
ODIR=obj
AT=@
INC=-Iinclude
CFLAGS=-Wall -Werror

SRCS:=$(wildcard $(SDIR)/*.c)
OBJS=$(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRCS))
	
$(ODIR)/%.o: $(SDIR)/%.c
	$(AT)mkdir -p $(ODIR)
	$(AT)$(CC) $(CFLAGS) $(INC) -c $< -o $@ $(LIBS)crypto

all: $(OBJS)
	$(AT)$(CC) $(INC) -o ministrace $^

clean:
	$(AT)rm -f $(ODIR)/*.o
	$(AT)rm -rf $(ODIR)
	$(AT)rm -rf ministrace
