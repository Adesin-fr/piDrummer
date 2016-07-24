################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/c_api/soloud_c.cpp 

OBJS += \
./src/c_api/soloud_c.o 

CPP_DEPS += \
./src/c_api/soloud_c.d 


# Each subdirectory must supply rules for building sources it contributes
src/c_api/%.o: ../src/c_api/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


