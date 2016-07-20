################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/backend/openal/soloud_openal.cpp 

C_SRCS += \
../src/backend/openal/soloud_openal_dll.c 

OBJS += \
./src/backend/openal/soloud_openal.o \
./src/backend/openal/soloud_openal_dll.o 

CPP_DEPS += \
./src/backend/openal/soloud_openal.d 

C_DEPS += \
./src/backend/openal/soloud_openal_dll.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/openal/%.o: ../src/backend/openal/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/backend/openal/%.o: ../src/backend/openal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


