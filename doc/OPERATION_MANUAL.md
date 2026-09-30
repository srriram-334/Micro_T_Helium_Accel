# Micro T-Helium-Accel — Operation & Evaluation Manual

## 1. System Specifications & Environment
To compile, flash, and evaluate the **demo Project** (and verify the middleware on the reference hardware platform), ensure your host environment matches the following toolchain and hardware configuration:

| Component | Specification |
| :--- | :--- |
| **Evaluation Board** | Renesas EK-RA8P1 Evaluation Kit |
| **Target Microcontroller** | Renesas RA8P1 (`R7KA8P1KFLCAC` — Cortex-M85) |
| **Integrated Development Environment** | Renesas e2 studio |
| **Flexible Software Package (FSP)** | Version `6.5.0` |
| **Toolchain** | GCC ARM Embedded `13.2.1.arm-13-7` |
| **Arm CMSIS Package** | Arm CMSIS Version 6 - Core (M) `v6.1.0+fsp.6.5.0` |
| **Target OS** | μT-Kernel 3.0 (BSP2 / Flat Multi-Core CPU0) |

---

## 2. Directory Structure

    .
    ├── demo_project/       # Ready-to-import e2 studio project (Debug Mode)
    ├── doc/                # Detailed evaluation and operation manuals
    │   └── OPERATION_MANUAL.md
    ├── inc/                # Middleware header files
    │   ├── micro_helium_math.h
    │   └── dwt_timer.h
    ├── src/                # Middleware source code & test suites
    │   ├── micro_helium_math.c
    │   ├── benchmark.c
    │   └── usermain.c
    ├── benchmark.png       # Terminal output benchmark results screenshot
    └── LICENSE             # MIT Open Source License

---

## 3. Part 1: Quick Evaluation via demo Project

This section provides step-by-step instructions for evaluation judges to rapidly build, flash, and execute the pre-configured project in Renesas e2 studio.

### Step 1: Import Project into e2 studio
1. Launch **Renesas e2 studio**.
2. Select your workspace location.
3. Select **File → Import...** from the main menu.
4. Expand **General**, choose **Existing Projects into Workspace**, and click **Next**.
5. Select **Select root directory**, click **Browse...**, and navigate to the `demo_project` folder inside this repository.
6. Ensure `demo_project` is checked in the *Projects* panel and click **Finish**.

### Step 2: Build the Project (Debug Mode)
1. In the **Project Explorer**, right-click `demo_project`.
2. Click **Build Project** (or press `Ctrl + B`).
3. Verify in the e2 studio Console tab that compilation completes with **0 Errors**.

*Note: The project is specifically configured and verified under **Debug Mode**, allowing full register and cycle counter inspection.*
*Note: If you encounter semantic errors in e² studio but the build completes successfully, you can safely ignore them and continue.


### Step 3: Flash and Launch Debugger
1. Connect the **Renesas EK-RA8P1** board to your host PC using a micro-USB cable on the J-Link Debug Port (`J10`).
2. In e2 studio, click **Run → Debug Configurations...**.
3. Under **Renesas GDB Hardware Debugging**, select `demo_project`.
4. Verify target settings: J-Link ARM interface connected to target device `R7KA8P1KFLCAC`.
5. Click **Debug** to flash the microcontroller and initialize the GDB debug perspective.

### Step 4: Configure Serial Terminal & Verify Output
1. Open a serial terminal (e2 studio Terminal View, Tera Term, or PuTTY).
2. Configure COM port settings:
   - **Baud Rate:** `115200` bps
   - **Data Bits:** 8 | **Parity:** None | **Stop Bits:** 1 | **Flow Control:** None
3. Click **Resume (F8)** in e2 studio to execute the firmware.

### Operational Verification Criteria
- **Preemption Safety Test:** Upon boot, `usermain.c` schedules `main_task` (Priority 10) and `preempt_task` (Priority 5). The high-priority task preempts vector calculations mid-execution. Confirm safety via log:

      [Preempt Task] High priority preemption triggered!
      [Preempt Task] Helium vector operation successfully completed.

- **Benchmark Suite:** The console displays execution cycle comparisons measured via Cortex-M85 DWT registers for 1024-element vectors and 32x32 matrices (Scalar C vs. ARM Helium MVE speedup).

---

## 4. Part 2: Integrating Middleware into Custom Projects

Developers can integrate the **Micro T-Helium-Accel** middleware into any existing μT-Kernel 3.0 project running on Cortex-M85 hardware.

### Step 1: File Transfer
- Copy all header files from `inc/` (`micro_helium_math.h`, `dwt_timer.h`) into your project's include path.
- Copy `src/micro_helium_math.c` and `src/dwt_timer.c` into your project's source directory.

### Step 2: Include Middleware Header
Include the main middleware header in your RTOS task source files:

    #include "micro_helium_math.h"

### Step 3: API Function Reference

| Function Name | Description | Target Workload |
| :--- | :--- | :--- |
| **`helium_vec_add_f32`** | Accelerated element-wise float vector addition | Vector Arithmetic |
| **`helium_vec_mult_f32`** | Accelerated element-wise float vector multiplication | Vector Arithmetic |
| **`helium_vec_offset_f32`** | Vector scalar offset addition | Vector Arithmetic |
| **`helium_vec_max_f32`** | Finds maximum scalar value in vector array | Reduction / Stats |
| **`helium_vec_variance_f32`** | Computes statistical variance across vector array | Reduction / Stats |
| **`helium_vec_dot_prod_f32`** | Computes vector inner dot product | Linear Algebra |
| **`helium_vec_rms_f32`** | Root Mean Square calculation | Signal Processing |
| **`helium_mat_vec_mult_f32`** | Matrix-vector multiplication ($M \times N$) | Linear Algebra / Edge AI |
| **`helium_mat_mult_f32`** | Full matrix-matrix multiplication ($M \times N \times P$) | Matrix Operations / DSP |
| **`helium_nn_relu_f32`** | Vectorized Rectified Linear Unit ($\max(0, x)$) | Neural Network Layer |
| **`helium_nn_softmax_f32`** | Vectorized Softmax probability distribution | Neural Network Layer |

---

## 5. Technical Notes & Evaluation Constraints
- **Hardware Cycle Counting:** Cycle counts are measured directly using the Cortex-M85 Data Watchpoint and Trace (DWT) cycle counter (`DWT->CYCCNT`).
- **Context Switch Integrity:** During RTOS preemption, 128-bit vector registers (`Q0–Q7`) and MVE control registers are preserved across task context switches under μT-Kernel 3.0 scheduling.
