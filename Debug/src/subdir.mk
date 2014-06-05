################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Leds.c 

OBJS += \
./src/Leds.o 

C_DEPS += \
./src/Leds.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gcc -I/root/android/source_code/linux-3.0.8/include -I/root/android/source_code/linux-3.0.8/arch/arm/include -I/root/android/source_code/linux-3.0.8/arch/arm/mach-s5pv210 -I/root/android/source_code/linux-3.0.8/arch/arm/plat-samsung -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


