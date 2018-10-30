################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/l3gd20/l3gd20.c 

OBJS += \
./Utilities/Components/l3gd20/l3gd20.o 

C_DEPS += \
./Utilities/Components/l3gd20/l3gd20.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/l3gd20/%.o: ../Utilities/Components/l3gd20/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32F30 -DSTM32F3DISCOVERY -DSTM32F3 -DSTM32F303VCTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -DUSE_RTOS_SYSTICK -I"/home/nop/hole/workspace_eclipse/3_Discovery/inc" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/Components/l3gd20" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/Components/Common" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/Components/lsm303dlhc" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Utilities/STM32F3-Discovery" -I"/home/nop/hole/workspace_eclipse/3_Discovery/CMSIS/device" -I"/home/nop/hole/workspace_eclipse/3_Discovery/CMSIS/core" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/nop/hole/workspace_eclipse/3_Discovery/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"/home/nop/hole/workspace_eclipse/3_Discovery/HAL_Driver/Inc" -I"/home/nop/hole/workspace_eclipse/3_Discovery/HAL_Driver/Inc/Legacy" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


