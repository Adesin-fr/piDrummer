################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/backend/alsa/soloud_alsa.cpp 

OBJS += \
./src/backend/alsa/soloud_alsa.o 

CPP_DEPS += \
./src/backend/alsa/soloud_alsa.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/alsa/%.o: ../src/backend/alsa/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


