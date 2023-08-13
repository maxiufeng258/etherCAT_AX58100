################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SSC/SSC-Device.c \
../SSC/coeappl.c \
../SSC/ecatappl.c \
../SSC/ecatcoe.c \
../SSC/ecateoe.c \
../SSC/ecatfoe.c \
../SSC/ecatslv.c \
../SSC/el9800hw.c \
../SSC/eoeappl.c \
../SSC/foeappl.c \
../SSC/mailbox.c \
../SSC/objdef.c \
../SSC/sdoserv.c 

OBJS += \
./SSC/SSC-Device.o \
./SSC/coeappl.o \
./SSC/ecatappl.o \
./SSC/ecatcoe.o \
./SSC/ecateoe.o \
./SSC/ecatfoe.o \
./SSC/ecatslv.o \
./SSC/el9800hw.o \
./SSC/eoeappl.o \
./SSC/foeappl.o \
./SSC/mailbox.o \
./SSC/objdef.o \
./SSC/sdoserv.o 

C_DEPS += \
./SSC/SSC-Device.d \
./SSC/coeappl.d \
./SSC/ecatappl.d \
./SSC/ecatcoe.d \
./SSC/ecateoe.d \
./SSC/ecatfoe.d \
./SSC/ecatslv.d \
./SSC/el9800hw.d \
./SSC/eoeappl.d \
./SSC/foeappl.d \
./SSC/mailbox.d \
./SSC/objdef.d \
./SSC/sdoserv.d 


# Each subdirectory must supply rules for building sources it contributes
SSC/%.o SSC/%.su SSC/%.cyclo: ../SSC/%.c SSC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -IC:/Users/maxiu/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/maxiu/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/maxiu/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/maxiu/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -I"C:/Users/maxiu/Documents/STM32WorkSpace/etherCAT_AX58100/ECAT_AX58100/SSC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SSC

clean-SSC:
	-$(RM) ./SSC/SSC-Device.cyclo ./SSC/SSC-Device.d ./SSC/SSC-Device.o ./SSC/SSC-Device.su ./SSC/coeappl.cyclo ./SSC/coeappl.d ./SSC/coeappl.o ./SSC/coeappl.su ./SSC/ecatappl.cyclo ./SSC/ecatappl.d ./SSC/ecatappl.o ./SSC/ecatappl.su ./SSC/ecatcoe.cyclo ./SSC/ecatcoe.d ./SSC/ecatcoe.o ./SSC/ecatcoe.su ./SSC/ecateoe.cyclo ./SSC/ecateoe.d ./SSC/ecateoe.o ./SSC/ecateoe.su ./SSC/ecatfoe.cyclo ./SSC/ecatfoe.d ./SSC/ecatfoe.o ./SSC/ecatfoe.su ./SSC/ecatslv.cyclo ./SSC/ecatslv.d ./SSC/ecatslv.o ./SSC/ecatslv.su ./SSC/el9800hw.cyclo ./SSC/el9800hw.d ./SSC/el9800hw.o ./SSC/el9800hw.su ./SSC/eoeappl.cyclo ./SSC/eoeappl.d ./SSC/eoeappl.o ./SSC/eoeappl.su ./SSC/foeappl.cyclo ./SSC/foeappl.d ./SSC/foeappl.o ./SSC/foeappl.su ./SSC/mailbox.cyclo ./SSC/mailbox.d ./SSC/mailbox.o ./SSC/mailbox.su ./SSC/objdef.cyclo ./SSC/objdef.d ./SSC/objdef.o ./SSC/objdef.su ./SSC/sdoserv.cyclo ./SSC/sdoserv.d ./SSC/sdoserv.o ./SSC/sdoserv.su

.PHONY: clean-SSC

