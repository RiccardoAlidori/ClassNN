# current version of the script
MAKEFILE_AUTHOR = BarbisanLuca
# current version of the script
MAKEFILE_VERSION = 1.0.3

# configure the input folders
# - name of the output program
BIN := $(subst $(empty) $(empty),_,$(shell basename "$(PWD)"))
# - output folder
BUILD_DIR = ./bin

# - folder containing *.cpp files
SRC_DIR = ./src
# - folder containing *.hpp files
HDR_DIR = $(SRC_DIR)/include
# - output objects files
OBJ_DIR = $(BUILD_DIR)/objects

# find the source files
SRCS != find $(SRC_DIR) -name "*.cpp"
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
#OBJECTS = bin/main.o bin/neuron.o bin/layer.o bin/net.o
#HEADERS = src/include/*.hpp
DEPFILES := $(patsubst %.o, %.d, $(OBJECTS))

CC = g++
CFLAGS  = -g -Wall -lm -std=c++11 -I/usr/include/python2.7 -lpython2.7
CPPFLAGS = $(patsubst %,-I%,$(shell find $(HDR_DIR) -type d))


# link the object files, compile them if not updated
$(BUILD_DIR)/$(BIN) : $(OBJS)
	@mkdir -p $(@D)
	@printf "\n%s" $(CXX)
	@for file in $(OBJS); do \
		printf "\t%s\n" $$file; \
		done;
	$(CC) $(CFLAGS) -o $@ $^
	@printf "\nout\t%s\n" $@

-include $(DEPFILES)

# compile the object files 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p -v $(@D)
	@printf "%s\t%s -> %s\n" $(CXX) $< $@
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

# compute the name of the backup folder
DATE != date +%Y-%m-%d___%H-%M-%S

#bin/run:  $(OBJECTS) $(HEADERS)
#	$(CC) $(CFLAGS) -o $@ $^
#
#-include $(DEPFILES)


#bin/main.o:  src/main.cpp 
#	@mkdir -p bin
#	$(CC) $(CFLAGS) -c src/main.cpp -o $@ 
#
#bin/neuron.o: src/neuron.cpp
#	@mkdir -p bin
#	$(CC) $(CFLAGS) -c $^ -o $@ 
#
#bin/layer.o: src/layer.cpp
#	@mkdir -p bin
#	$(CC) $(CFLAGS) -c $^ -o $@ 
#
#bin/net.o: src/net.cpp
#	@mkdir -p bin
#	$(CC) $(CFLAGS) -c $^ -o $@ 

.PHONY: run
# run the program, compile it if it is not updated
run : $(BUILD_DIR)/$(BIN)
	@$(BUILD_DIR)/$(BIN)


.PHONY: clean
clean: 
	@rm -fvr $(BUILD_DIR)

.PHONY : backup
# Creates a folder with the name in the format "YYYY-MM-DD___hh-mm-ss"
# All the $SRC_DIR, $HDR_DIR and $RES_DIR directories and subdirecories are copied into this folder 
backup :
	@mkdir -p -v BACKUP/$(DATE)
	@cp -p -r -v $(RES_DIR) BACKUP/$(DATE)
	@cp -p -r -v $(SRC_DIR) BACKUP/$(DATE)
	@cp -p -r -v $(HDR_DIR) BACKUP/$(DATE)
	@cp -p -v Makefile BACKUP/$(DATE)

.PHONY : makefile_version
# print the version of this makefile script
makefile_version :
	@printf "version number: %s\n" $(MAKEFILE_VERSION)

.PHONY : makefile_author
# print the version of this makefile script
makefile_author :
	@printf "Author: %s\n" $(MAKEFILE_AUTHOR)
