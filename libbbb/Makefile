include ../config.mk

RUN_ARGS := -i -

$(EXECUTABLE): $(OBJECTS)
		$(MAKE_LIB) $@ $^

$(OBJROOT)/%.o : $(SRCROOT)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: install_headers $(EXECUTABLE)

install:
	mkdir -p $(DSTROOT)/usr/local/lib
	install -m 755 $(EXECUTABLE) $(DSTROOT)/usr/local/lib

run: clean all
	$(EXECUTABLE) $(RUN_ARGS)

clean:
	rm -rf $(BLDROOT)

install_headers:
	mkdir -p $(HDRROOT)$(HDR_INSTALL)
	install $(HEADERS) $(HDRROOT)$(HDR_INSTALL)
