################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Channel.cpp \
../src/UsbDriver.cpp \
../src/main.cpp 

OBJS += \
./src/Channel.o \
./src/UsbDriver.o \
./src/main.o 

CPP_DEPS += \
./src/Channel.d \
./src/UsbDriver.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/shai/Desktop/workspace/ophiropt.drivers.usb.linux/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


