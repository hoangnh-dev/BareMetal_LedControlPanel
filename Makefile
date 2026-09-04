# ==== Project ====
NAME_MODULE = BareMetal_LedControlPanel
BUILD_DIR   = build

# ==== Toolchain ====
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# ==== MCU ====
MCU_FLAGS = -mcpu=cortex-m3 -mthumb

# ==== Source ====
SRCS = main.c startup.c
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# ==== Linker Script ====
LD_SCRIPT = STM32F103C8TX.ld

# ==== Output ====
ELF = $(BUILD_DIR)/$(NAME_MODULE).elf
BIN = $(BUILD_DIR)/$(NAME_MODULE).bin

# ==== Compile Flags ====
CFLAGS = $(MCU_FLAGS) \
         -O0 \
         -g \
         -Wall \
         -ffreestanding \
         -ffunction-sections \
         -fdata-sections

# ==== Link Flags ====
LDFLAGS = $(MCU_FLAGS) \
          -T$(LD_SCRIPT) \
          -nostdlib \
          -Wl,--gc-sections


# =========================================================
# Build
# =========================================================

all: $(BIN)


# Create build directory
$(BUILD_DIR):
	mkdir $(BUILD_DIR)


# Compile .c -> .o
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# Link .o -> .elf
$(ELF): $(OBJS) $(LD_SCRIPT)
	$(CC) $(LDFLAGS) $(OBJS) -o $@
	$(SIZE) $@


# Convert .elf -> .bin
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@


# =========================================================
# Clean
# =========================================================

clean:
	rmdir /s /q $(BUILD_DIR)


.PHONY: all clean


flash:
	st-flash --connect-under-reset write build/BareMetal_LedControlPanel.bin 0x08000000