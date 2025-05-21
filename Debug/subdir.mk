################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MenuAdmin.cpp \
../MenuPrincipal.cpp \
../MenuUsuario.cpp \
../SocketCliente.cpp 

CPP_DEPS += \
./MenuAdmin.d \
./MenuPrincipal.d \
./MenuUsuario.d \
./SocketCliente.d 

OBJS += \
./MenuAdmin.o \
./MenuPrincipal.o \
./MenuUsuario.o \
./SocketCliente.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./MenuAdmin.d ./MenuAdmin.o ./MenuPrincipal.d ./MenuPrincipal.o ./MenuUsuario.d ./MenuUsuario.o ./SocketCliente.d ./SocketCliente.o

.PHONY: clean--2e-

