#all : pandoc
pandoc : nodoc.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
