################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AudioEngine.cpp \
../ControllerLayer.cpp \
../Draw.cpp \
../DrumKit.cpp \
../DrumKitComponent.cpp \
../Instrument.cpp \
../Layer.cpp \
../ScreenDrawing.cpp \
../SerialHandle.cpp \
../Settings.cpp \
../SignalCurve.cpp \
../Trigger.cpp \
../urDrummer.cpp 

OBJS += \
./AudioEngine.o \
./ControllerLayer.o \
./Draw.o \
./DrumKit.o \
./DrumKitComponent.o \
./Instrument.o \
./Layer.o \
./ScreenDrawing.o \
./SerialHandle.o \
./Settings.o \
./SignalCurve.o \
./Trigger.o \
./urDrummer.o 

CPP_DEPS += \
./AudioEngine.d \
./ControllerLayer.d \
./Draw.d \
./DrumKit.d \
./DrumKitComponent.d \
./Instrument.d \
./Layer.d \
./ScreenDrawing.d \
./SerialHandle.d \
./Settings.d \
./SignalCurve.d \
./Trigger.d \
./urDrummer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


