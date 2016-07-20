################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/backend/opensles/soloud_opensles.cpp 

OBJS += \
./src/backend/opensles/soloud_opensles.o 

CPP_DEPS += \
./src/backend/opensles/soloud_opensles.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/opensles/%.o: ../src/backend/opensles/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


