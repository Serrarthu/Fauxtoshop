# ---------------------------------------
# CHOISIR LE COMPILATEUR ICI
# ---------------------------------------
# Linux            : g++
# Windows (32 bit) : g++-4
# Windows (64 bit) : i686-pc-cygwin-g++-4
CC = g++
# ---------------------------------------
#On choisit les flags pour la compilation ici
CFLAGS = -std=c++11 -pedantic -Wall -Wextra -Weffc++ -fopenmp -Wl,-rpath,.
EXEC_NAME = Fauxtoshop
SRC_DIR = src/*.cpp src/base/*.cpp src/structure/*.cpp src/deblur/*.cpp

all : $(EXEC_NAME)
	@echo "Compiled."

$(EXEC_NAME) : $(SRC_DIR)
	@$(CC) -o $(EXEC_NAME) $(CFLAGS) $(SRC_DIR) libeistipng.so

%.o: %.cpp
	@$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.h
	@$(CC) $(CFLAGS) -o $@ -c $<


clean :
	@rm -rf *.o $(EXEC_NAME)
	@echo "Cleaned."
