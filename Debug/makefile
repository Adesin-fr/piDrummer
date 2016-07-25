################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/filter/subdir.mk
-include src/core/subdir.mk
-include src/c_api/subdir.mk
-include src/backend/xaudio2/subdir.mk
-include src/backend/wasapi/subdir.mk
-include src/backend/null/subdir.mk
-include src/backend/coreaudio/subdir.mk
-include src/backend/alsa/subdir.mk
-include src/audiosource/wav/subdir.mk
-include src/audiosource/vic/subdir.mk
-include src/audiosource/tedsid/subdir.mk
-include src/audiosource/speech/subdir.mk
-include src/audiosource/sfxr/subdir.mk
-include src/audiosource/monotone/subdir.mk
-include src/audiosource/modplug/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: urDrummer

# Tool invocations
urDrummer: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "urDrummer" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) urDrummer
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
