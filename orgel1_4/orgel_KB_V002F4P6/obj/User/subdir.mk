################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../User/song_idx.s 

C_SRCS += \
../User/main.c 

OBJS += \
./User/main.o \
./User/song_idx.o 

S_DEPS += \
./User/song_idx.d 

C_DEPS += \
./User/main.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\ooizumis\WCH\orgel1_4-NNN\orgel_KB_V002F4P6\Debug" -I"C:\ooizumis\WCH\orgel1_4-NNN\orgel_KB_V002F4P6\Core" -I"C:\ooizumis\WCH\orgel1_4-NNN\orgel_KB_V002F4P6\User" -I"C:\ooizumis\WCH\orgel1_4-NNN\orgel_KB_V002F4P6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
User/%.o: ../User/%.s
	@	@	riscv-none-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"C:\ooizumis\WCH\orgel1_4-NNN\orgel_KB_V002F4P6\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

