PREFIX		 = arm-cortex_a8-linux-gnueabi
LDFLAGS		:= -static

TARGET=hbootuser

CC		 = $(PREFIX)-gcc
AS		 = $(PREFIX)-gcc
LD 		 = $(PREFIX)-gcc

OBJS		:= hbootuser.o

all:		$(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)

$(TARGET):	$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)


.SECONDEXPANSION:
$(C_OBJS):	$$(patsubst %.o,%.c,$$@)
	$(CC) $(CFLAGS) -c $^

