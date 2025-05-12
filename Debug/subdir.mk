################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Menu.cpp \
../MenuAdmin.cpp \
../MenuUsuario.cpp \
../SocketCliente.cpp \
../main.cpp 

CPP_DEPS += \
./Menu.d \
./MenuAdmin.d \
./MenuUsuario.d \
./SocketCliente.d \
./main.d 

OBJS += \
./Menu.o \
./MenuAdmin.o \
./MenuUsuario.o \
./SocketCliente.o \
./main.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./Menu.d ./Menu.o ./MenuAdmin.d ./MenuAdmin.o ./MenuUsuario.d ./MenuUsuario.o ./SocketCliente.d ./SocketCliente.o ./main.d ./main.o

.PHONY: clean--2e-

