################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tools/resamplerlab/main.cpp 

C_SRCS += \
../src/tools/resamplerlab/stb_image_write.c 

OBJS += \
./src/tools/resamplerlab/main.o \
./src/tools/resamplerlab/stb_image_write.o 

CPP_DEPS += \
./src/tools/resamplerlab/main.d 

C_DEPS += \
./src/tools/resamplerlab/stb_image_write.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/resamplerlab/%.o: ../src/tools/resamplerlab/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/tools/resamplerlab/%.o: ../src/tools/resamplerlab/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


