//
// Created by 甘尧 on 2019-09-25.
//

#pragma once

#include "base/marcos.h"

namespace CPU::A64 {


    union HalfFloat {
        u16 bits;
        s16 bits_signed; // TODO: is this guaranteed to be two's complement?
        struct {
            u16 mantissa : 10;
            u16 exponent : 5;
            u16 sign : 1;
        };

        struct {
            u16 : 9;
            u16 is_quiet : 1;
            u16 : 6;
        };

        static const u64 max_exp = 0x1F;
    };

    union SingleFloat {
        u32 bits;
        s32 bits_signed; // TODO: is this guaranteed to be two's complement?
        float val;
        struct {
            u32 mantissa : 23;
            u32 exponent : 8;
            u32 sign : 1;
        };

        struct {
            u32 : 22;
            u32 is_quiet : 1;
            u32 : 9;
        };

        static const u64 max_exp = 0xFF;
    };

    union Double {
        u64 bits;
        s64 bits_signed; // TODO: is this guaranteed to be two's complement?
        double val;
        struct {
            u64 mantissa : 52;
            u64 exponent : 11;
            u64 sign : 1;
        };

        struct {
            u64 : 51;
            u64 is_quiet : 1;
            u64 : 12;
        };


        static const u64 maxExp = 0x7FF;
    };

    typedef union {
        u64 Q;
        u64 D[2];
        u32 S[4];
        u16 H[8];
        u8 B[16];

        HalfFloat float_h;
        SingleFloat float_s;
        Double float_d;
    } Vec;

    typedef union {
        u64 X;
        struct {
            u64 W : 32;
            u64 R : 32;
        };
    } Reg;

    struct PSTATE {
        bool N; // Negative
        bool Z; // Zero
        bool C; // Carry
        bool V; // Overflow
        int SS;
        int IL;
        int nRW;
        int EL;
        int SP;
        int D;
        int A, I, F;
    };

    struct VirtualTLB {
        VAddr vaddr;
        VAddr target;
    };

    struct CPUContext {
        Reg cpu_registers[29];
        Reg fp; // x29
        Reg lr; // x30
        u64 sp;
        u64 pc;
        PSTATE pstate;
        Vec vector_registers[32];
        u32 fpcr;
        u32 fpsr;
        u64 tpidr;
        u64 tpidrro;
        // memory
        VAddr host_sp;
        VAddr tlb;
        VAddr page_table;
        // dispatcher
        VAddr dispatcher_table;
        // flags
        VAddr suspend_flag;
        // help fields
        u64 forward;
        u64 forward_ext;
        u64 tmp_lr;
        u64 tmp_pc;
    };
}

extern "C" const VAddr OFFSET_CTX_A64_CPU_REG;
extern "C" const VAddr OFFSET_CTX_A64_SP;
extern "C" const VAddr OFFSET_CTX_A64_PC;
extern "C" const VAddr OFFSET_CTX_A64_PSTATE;
extern "C" const VAddr OFFSET_CTX_A64_VEC_REG;
extern "C" const VAddr OFFSET_CTX_A64_FPCR;
extern "C" const VAddr OFFSET_CTX_A64_FPSR;
extern "C" const VAddr OFFSET_CTX_A64_TPIDR;
extern "C" const VAddr OFFSET_CTX_A64_TPIDRRO;
extern "C" const VAddr OFFSET_CTX_A64_FORWARD;
extern "C" const VAddr OFFSET_CTX_A64_FORWARD_EXT;
extern "C" const VAddr OFFSET_CTX_A64_QUERY_PAGE;
extern "C" const VAddr OFFSET_CTX_A64_TLB;
extern "C" const VAddr OFFSET_CTX_A64_PAGE_TABLE;
extern "C" const VAddr OFFSET_CTX_A64_SUSPEND_ADDR;
extern "C" const VAddr OFFSET_CTX_A64_DISPATCHER_TABLE;
extern "C" const VAddr OFFSET_CTX_A64_TMP_LR;
extern "C" const VAddr OFFSET_CTX_A64_SVC_NUM;
extern "C" const VAddr OFFSET_CTX_A64_HOST_SP;
extern "C" const VAddr OFFSET_CTX_A64_TMP_PC;

