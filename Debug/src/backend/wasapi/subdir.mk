################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/backend/wasapi/soloud_wasapi.cpp 

OBJS += \
./src/backend/wasapi/soloud_wasapi.o 

CPP_DEPS += \
./src/backend/wasapi/soloud_wasapi.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/wasapi/%.o: ../src/backend/wasapi/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


