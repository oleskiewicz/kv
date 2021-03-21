CC     = cc
CFLAGS = -std=c11 -Wall
PREFIX = /usr/local

example: example.c kv.h

install:
	install kv.h $(DESTDIR)$(PREFIX)/include
	gzip < kv.3 > $(DESTDIR)$(PREFIX)/share/man/man3/kv.3.gz
	gzip < kv.5 > $(DESTDIR)$(PREFIX)/share/man/man5/kv.5.gz

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/include/kv.h \
		$(DESTDIR)$(PREFIX)/share/man/man3/kv.3.gz \
		$(DESTDIR)$(PREFIX)/share/man/man5/kv.5.gz

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
