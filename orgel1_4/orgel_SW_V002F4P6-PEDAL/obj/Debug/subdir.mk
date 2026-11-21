################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c
	@	@	riscv-none-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\ooizumis\WCH\orgel1_4-NNN\orgel_SW_V002F4P6-PEDAL\Debug" -I"C:\ooizumis\WCH\orgel1_4-NNN\orgel_SW_V002F4P6-PEDAL\Core" -I"C:\ooizumis\WCH\orgel1_4-NNN\orgel_SW_V002F4P6-PEDAL\User" -I"C:\ooizumis\WCH\orgel1_4-NNN\orgel_SW_V002F4P6-PEDAL\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

