################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/benchmark.c \
../src/dwt_timer.c \
../src/hal_entry.c \
../src/hal_warmstart.c \
../src/micro_helium_math.c \
../src/scalar_math_baseline.c \
../src/usermain.c 

C_DEPS += \
./src/benchmark.d \
./src/dwt_timer.d \
./src/hal_entry.d \
./src/hal_warmstart.d \
./src/micro_helium_math.d \
./src/scalar_math_baseline.d \
./src/usermain.d 

OBJS += \
./src/benchmark.o \
./src/dwt_timer.o \
./src/hal_entry.o \
./src/hal_warmstart.o \
./src/micro_helium_math.o \
./src/scalar_math_baseline.o \
./src/usermain.o 

SREC += \
Micro_T_Helium_Accel.srec 

MAP += \
Micro_T_Helium_Accel.map 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	$(file > $@.in,-mthumb -mfloat-abi=hard -mcpu=cortex-m85+nopacbti -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RAFSP_EK_RA8P1_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra_cfg/fsp_cfg/bsp" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/inc" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2/include" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2/config" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2" -I"." -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra_gen" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra_cfg/fsp_cfg" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/src" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/fsp/inc" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/fsp/inc/api" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/fsp/inc/instances" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -Wno-stringop-overflow -Wno-format-truncation -flax-vector-conversions --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

