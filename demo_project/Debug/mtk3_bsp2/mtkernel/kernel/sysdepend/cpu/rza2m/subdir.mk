################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/sf_boot.S 

C_SRCS += \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/ttb_ini.c 

C_DEPS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/ttb_ini.d 

OBJS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/sf_boot.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/ttb_ini.o 

SREC += \
Micro_T_Helium_Accel.srec 

S_UPPER_DEPS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/sf_boot.d 

MAP += \
Micro_T_Helium_Accel.map 


# Each subdirectory must supply rules for building sources it contributes
mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/%.o: ../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/%.S
	$(file > $@.in,-mthumb -mfloat-abi=hard -mcpu=cortex-m85+nopacbti -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -x assembler-with-cpp -D_RENESAS_RA_ -D_RAFSP_EK_RA8P1_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra_cfg/fsp_cfg/bsp" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/inc" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2/include" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2/config" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2" -I"." -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra_gen" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra_cfg/fsp_cfg" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/src" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/fsp/inc" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/fsp/inc/api" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/fsp/inc/instances" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/arm/CMSIS_6/CMSIS/Core/Include" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"
mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/%.o: ../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rza2m/%.c
	$(file > $@.in,-mthumb -mfloat-abi=hard -mcpu=cortex-m85+nopacbti -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RAFSP_EK_RA8P1_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra_cfg/fsp_cfg/bsp" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/inc" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2/include" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2/config" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/mtk3_bsp2" -I"." -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra_gen" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra_cfg/fsp_cfg" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/src" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/fsp/inc" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/fsp/inc/api" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/fsp/inc/instances" -I"C:/Users/skull/e2_studio/workspace/Micro_T_Helium_Accel/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -Wno-stringop-overflow -Wno-format-truncation -flax-vector-conversions --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

