################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/audiosource/monotone/soloud_monotone.cpp 

OBJS += \
./src/audiosource/monotone/soloud_monotone.o 

CPP_DEPS += \
./src/audiosource/monotone/soloud_monotone.d 


# Each subdirectory must supply rules for building sources it contributes
src/audiosource/monotone/%.o: ../src/audiosource/monotone/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


