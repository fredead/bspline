CC      = gcc  -ggdb
PROF    = -ggdb
C_FLAGS =  -Wall -w $(PROF) -L/usr/local/include -DDEBUG
I_FLAGS = -I/usr/X11R6/include
L_FLAGS =  $(PROF) -L/usr/X11R6/lib -L/usr/local/lib
L_POSTFLAGS =  -lgtk -lgdk -lglib -lXext -lX11 -lm
PROGNAME = bspline

O_FILES = menus.o gfx_window.o main.o mpoints.o tvectors.o bspline.o gfx_label.o gfx_io.o

$(PROGNAME): $(O_FILES)
	rm -f $(PROGNAME)
	$(CC) $(C_FLAGS) $(I_FLAGS) $(L_FLAGS) -o $(PROGNAME) $(O_FILES) $(L_POSTFLAGS)


clean:
	rm -f core *.o $(PROGNAME)
distclean: clean
	rm -f *~

