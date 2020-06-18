# Generic items -------------------------------------------------------------

CXX = arm-elf-g++
CC = arm-elf-gcc
AS = arm-elf-as
LD = arm-elf-ld

CPPFLAGS = -DforARM -D__arm -D__cplusplus -DforDebug \
        -I$(NT_ROOT)/include/ \
        -I$(NT_ROOT)/include/Frames/ \
        -I$(NT_ROOT)/include/CLibrary/ \
        -I$(NT_ROOT)/include/CommAPI/ \
        -I$(NT_ROOT)/include/Communications/ \
        -I$(NT_ROOT)/include/HAL/ \
        -I$(NT_ROOT)/include/OS600/ \
        -I$(NT_ROOT)/include/PCMCIA/ \
        -I$(NT_ROOT)/include/Power/ \
        -I$(NT_ROOT)/include/Toolbox/ \
        -I$(NT_ROOT)/include/Utilities/ \
        -I$(NT_ROOT)/include/UtilityClasses/
CXXFLAGS = -fno-builtin -fomit-frame-pointer -mbig-endian -Os -fno-rtti \
        -mno-apcs-frame -fvtable-thunks
CFLAGS = -fno-builtin -fomit-frame-pointer -mbig-endian -Os -mno-apcs-frame
LDFLAGS = -e 0 -q -EB -nostartfiles -nodefaultlibs -nostdlib --no-demangle \
        --gc-sections -T $(NT_ROOT)/lib/ldscripts/armelf.x
ASFLAGS = -EB

LIBS = $(NT_ROOT)/lib/$(TARGET).a

%.o: %.cp
	$(CXX) -c $< $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS)

%.s: %.cp
	$(CXX) -S $< $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS)

$(PACKAGE).ntkc: $(PACKAGE)
	export LUA_PATH="$(NT_ROOT)/bin/?;$(LUA_PATH)"; \
    $(NT_ROOT)/bin/elf2nsof.lua $< $@ $(PACKAGE) "$(ENTRYPOINTS)"

$(PACKAGE): $(OBJS) $(LIBS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	$(RM) $(OBJS) $(PACKAGE) $(PACKAGE).ntkc
