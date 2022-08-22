TARGET_NAME = sparrow
CC = g++
CFLAGS = -fno-exceptions -fno-rtti

CPP_FILES = $(wildcard ./src/*.cpp)
CPP_OBJ_FILES = $(patsubst %.cpp, %.cpp.o, $(CPP_FILES))
DEPENDENCY_FILES = $(patsubst %.cpp, %.cpp.d, $(CPP_FILES))

$(TARGET_NAME).elf: $(CPP_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.cpp.o: %.cpp
	@$(CC) -MM -MT $@ -MF $<.d $<
	$(CC) $(CFLAGS) -c -o $@ $<

## this `-include` should be after compile rules
-include $(DEPENDENCY_FILES)

.PHONY: clean lss

lss:
	@objdump -S -D $(TARGET_NAME) > $(TARGET_NAME).lss

clean:
	@rm -f $(TARGET_NAME).elf $(CPP_OBJ_FILES) $(DEPENDENCY_FILES) \
		$(TARGET_NAME).lss

