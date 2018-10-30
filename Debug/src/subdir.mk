################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MY_fault_injector.c \
../src/MY_hardware_config.c \
../src/MY_os_threads.c \
../src/MY_useful_functions.c \
../src/main.c \
../src/stm32f3xx_it.c \
../src/syscalls.c \
../src/system_stm32f3xx.c 

OBJS += \
./src/MY_fault_injector.o \
./src/MY_hardware_config.o \
./src/MY_os_threads.o \
./src/MY_useful_functions.o \
./src/main.o \
./src/stm32f3xx_it.o \
./src/syscalls.o \
./src/system_stm32f3xx.o 

C_DEPS += \
./src/MY_fault_injector.d \
./src/MY_hardware_config.d \
./src/MY_os_threads.d \
./src/MY_useful_functions.d \
./src/main.d \
./src/stm32f3xx_it.d \
./src/syscalls.d \
./src/system_stm32f3xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32F30 -DSTM32F3DISCOVERY -DSTM32F3 -DSTM32F303VCTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -DUSE_RTOS_SYSTICK -I"/home/nop/hole/workspace_eclipse/3_Discovery/inc" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/Components/l3gd20" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/Components/Common" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/Components/lsm303dlhc" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/STM32F3-Discovery" -I"/home/nop/hole/workspace_eclipse/3_Discovery/CMSIS/device" -I"/home/nop/hole/workspace_eclipse/3_Discovery/CMSIS/core" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"/home/nop/hole/workspace_eclipse/3_Discovery/HAL_Driver/Inc" -I"/home/nop/hole/workspace_eclipse/3_Discovery/HAL_Driver/Inc/Legacy" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


