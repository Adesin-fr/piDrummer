################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tools/lutgen/main.cpp 

OBJS += \
./src/tools/lutgen/main.o 

CPP_DEPS += \
./src/tools/lutgen/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/lutgen/%.o: ../src/tools/lutgen/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


