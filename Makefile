SRCS := src/entry.cpp
LIBS := -lgmp -lgmpxx -lglu32 -lopengl32 -lglfw3dll
IDIR := -I$(GLFW)\include -I$(GMP)
LDIR := -L$(GLFW)\lib-mingw-w64
NAME := mandelbrot_demo.exe

compile:$(SRCS)
	@echo "compile starting ..."
	@echo external included : $(IDIR)
	g++ -Wall -O2 $(IDIR) -c $(SRCS)
	@echo "compile completed."
link:compile
	@echo "link starting ..."
	@echo external included : $(LDIR)
	ld -o $(NAME) $(LDIR) $(LIBS)
	@echo link completed
test:
	@echo "This is a test"
clean:
	rm *.o
all:
	@echo "Build starting ..."
	@echo external included $(IDIR) , $(LDIR)
	g++ -o $(NAME) -Wall -O2 $(SRCS) $(IDIR) $(LDIR) $(LIBS)
	# make link
	# make test
	@echo "Build completed."