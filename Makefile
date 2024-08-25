#all : pandoc
pandoc : nodoc.c
	$(CC) -g $(CFLAGS) $(LDFLAGS) -o $@ $<
