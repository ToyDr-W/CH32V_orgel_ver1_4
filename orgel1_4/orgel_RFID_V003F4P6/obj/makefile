################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
orgel_RFID_V003F4P6.hex \

SECONDARY_LIST += \
orgel_RFID_V003F4P6.lst \

SECONDARY_SIZE += \
orgel_RFID_V003F4P6.siz \


# All Target
all: orgel_RFID_V003F4P6.elf secondary-outputs

# Tool invocations
orgel_RFID_V003F4P6.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\ooizumis\WCH\orgel1_4-NNN\orgel_RFID_V003F4P6\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"orgel_RFID_V003F4P6.map" --specs=nano.specs --specs=nosys.specs -o "orgel_RFID_V003F4P6.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
	@	@
orgel_RFID_V003F4P6.hex: orgel_RFID_V003F4P6.elf
	@	riscv-none-embed-objcopy -O ihex "orgel_RFID_V003F4P6.elf"  "orgel_RFID_V003F4P6.hex"
	@	@
orgel_RFID_V003F4P6.lst: orgel_RFID_V003F4P6.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "orgel_RFID_V003F4P6.elf" > "orgel_RFID_V003F4P6.lst"
	@	@
orgel_RFID_V003F4P6.siz: orgel_RFID_V003F4P6.elf
	@	riscv-none-embed-size --format=berkeley "orgel_RFID_V003F4P6.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) orgel_RFID_V003F4P6.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
