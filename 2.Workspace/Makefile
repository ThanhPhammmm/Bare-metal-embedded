CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T 4.LinkerScript/stm32_linker_script.ld -Wl,-Map=6.MapFinal/final.map

SRC=1.Core/1.Source/main.c
INCLUDE=-I1.Core/2.Include
OBJ=1.Core/3.Build/main.o

SRC1=1.Core/1.Source/syscalls.c
OBJ1=1.Core/3.Build/syscalls.o

STARTUP_SRC=3.StartUp/stm32_startup.c
STARTUP_OBJ=3.StartUp/Build/stm32_startup.o

LINKER_SCRIPT_SRC = 4.LinkerScript/stm32_linker_script.ld

FINAL_ELF = 5.ElfFinal/final.elf

READOBJ = arm-none-eabi-objdump.exe

all: $(OBJ) $(OBJ1) $(STARTUP_OBJ) $(FINAL_ELF)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDE)

$(OBJ1): $(SRC1)
	$(CC) $(CFLAGS) $^ -o $@

$(STARTUP_OBJ): $(STARTUP_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(FINAL_ELF): $(OBJ) $(STARTUP_OBJ) $(OBJ1)
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
	rm -f $(OBJ) $(STARTUP_OBJ) $(FINAL_ELF)