################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tools/codegen/main.cpp 

OBJS += \
./src/tools/codegen/main.o 

CPP_DEPS += \
./src/tools/codegen/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/codegen/%.o: ../src/tools/codegen/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


