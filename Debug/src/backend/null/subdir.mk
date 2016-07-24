################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/backend/null/soloud_null.cpp 

OBJS += \
./src/backend/null/soloud_null.o 

CPP_DEPS += \
./src/backend/null/soloud_null.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/null/%.o: ../src/backend/null/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


