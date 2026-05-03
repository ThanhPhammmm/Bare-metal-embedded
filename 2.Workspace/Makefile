CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0
LDFLAGS= -nostdlib -T 4.LinkerScript/stm32_linker_script.ld

SRC=1.Core/1.Source/main.c
INCLUDE=-I1.Core/2.Include
OBJ=1.Core/3.Build/main.o

STARTUP_SRC=3.StartUp/stm32_startup.c
STARTUP_OBJ=3.StartUp/Build/stm32_startup.o

LINKER_SCRIPT_SRC = 4.LinkerScript/stm32_linker_script.ld

FINAL_ELF = 5.ElfFinal/final.elf

READOBJ = arm-none-eabi-objdump.exe

all: $(OBJ) $(STARTUP_OBJ) $(FINAL_ELF)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDE)

$(STARTUP_OBJ): $(STARTUP_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(FINAL_ELF): $(OBJ) $(STARTUP_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

readObj: $(OBJ)
	$(READOBJ) $(OBJ) -d > 2.Log/main.log

readObj1: $(OBJ)
	$(READOBJ) $(OBJ) -D > 2.Log/main1.log

readObj2: $(STARTUP_OBJ)
	$(READOBJ) $(STARTUP_OBJ) -D > 2.Log/statup.log

display: $(OBJ)
	$(READOBJ) -h $(OBJ)

display1: $(STARTUP_OBJ)
	$(READOBJ) -h $(STARTUP_OBJ)

display2:$(FINAL_ELF)
	$(READOBJ) -h $(FINAL_ELF)

clean:
	rm -f $(OBJ) $(STARTUP_OBJ)