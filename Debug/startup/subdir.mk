################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f303xc.s 

OBJS += \
./startup/startup_stm32f303xc.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -I"/home/nop/hole/workspace_eclipse/3_Discovery/inc" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/Components/l3gd20" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/Components/Common" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/Components/lsm303dlhc" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/STM32F3-Discovery" -I"/home/nop/hole/workspace_eclipse/3_Discovery/CMSIS/device" -I"/home/nop/hole/workspace_eclipse/3_Discovery/CMSIS/core" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"/home/nop/hole/workspace_eclipse/3_Discovery/HAL_Driver/Inc" -I"/home/nop/hole/workspace_eclipse/3_Discovery/HAL_Driver/Inc/Legacy" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


