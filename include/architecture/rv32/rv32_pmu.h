// Hardware Performance Monitor (HPM)

#ifndef __rv32_pmu_h
#define __rv32_pmu_h

#include <architecture/cpu.h>
#include <architecture/pmu.h>

__BEGIN_SYS

class RV32_PMU: public PMU_Common
{

private:
    typedef CPU::Reg32 Reg32;
    static const unsigned int CHANNELS = 3;
    static const unsigned int FIXED = 0;
    static const unsigned int EVENTS = 10; // 54 if A53

public:

    RV32_PMU() {};

    // Machine Hardware Performance Monitor Event Register

    // Instruction Commit Events, mhpeventX[7:0] = 0
    enum {
        Exception_taken                                 = 8,
        Integer_load_instruction_retired                = 9,
        Integer_store_instruction_retired               = 10,
        Atomic_memory_operation_retired                 = 11,
        System_instruction_retired                      = 12,
        Integer_arithmetic_instruction_retired          = 13,
        Conditional_branch_retired                      = 14,
        JAL_instruction_retired                         = 15,
        JALR_instruction_retired                        = 16,
        Integer_multiplication_instruction_retired      = 17,
        Integer_division_instruction_retired            = 18,
        Floating_point_load_instruction_retired         = 19,
        Floating_point_store_instruction_retired        = 20,
        Floating_point_addition_retired                 = 21,
        Floating_point_multiplication_retired           = 22,
        Floating_point_fused_multiply_add_retired       = 23,
        Floating_point_division_or_square_root_retired  = 24,
        Other_floating_point_instruction_retired        = 25
    };

    // Microarchitectural Events , mhpeventX[7:0] = 1
    enum {
        Load_use_interlock                  = 8,
        Long_latency_interlock              = 9,
        CSR_read_interlock                  = 10,
        Instruction_cache_ITIM_busy         = 11,
        Data_cache_DTIM_busy                = 12,
        Branch_direction_misprediction      = 13,
        Branch_jump_target_misprediction    = 14,
        Pipeline_flush_from_CSR_write       = 15,
        Pipeline_flush_from_other_event     = 16,
        Integer_multiplication_interlock    = 17,
        Floating_point_interlock            = 18
    };

    // Memory System Events, mhpeventX[7:0] = 2
    enum {
        Instruction_cache_miss                      = 8,
        Data_cache_miss_or_memory_mapped_IO_access  = 9,
        Data_cache_writeback                        = 10,
        Instruction_TLB_miss                        = 11,
        Data_TLB_miss                               = 12
    };
    
    static void config(Channel channel, Event event, Flags flags = NONE) {
        db<PMU>(TRC) << "PMU::config(c=" << channel << ",e=" << event << ",f=" << flags << ")" << endl;

        /*
           Instruction Commit Events = 0
           Microarchitectural Events = 1
           Memory System Events      = 2
        */

        _event = event;
    }
    
    static void start(Channel channel) {}

    static void stop(Channel channel) {}

    static Count read(Channel channel) { 
        db<PMU>(TRC) << "PMU::read(c=" << channel << ")" << endl;

        Reg32 reg;
        
        if (check()) {
            asm volatile (R"(
                csrr    %0, mhpmcounter3
            )": "=r"(reg));

            return 1;
        }

        return 1;
    }
    
    static void write(Channel channel, Count count) {
        db<PMU>(TRC) << "PMU::write(ch=" << channel << ",ct=" << count << ")" << endl;

        Reg32 reg;
        
        if (check()) {
            asm volatile (R"(
                csrw    mhpmcounter3, %0
            )": : "r"(reg));
        }
    }

    static void reset(Channel channel) {
        db<PMU>(TRC) << "PMU::reset(c=" << channel << ")" << endl;
        write(channel, 0);
    }

    static unsigned int minstret() {
        Reg32 reg;
        
        asm volatile (R"(
            csrr    %0, minstret
        )": "=r"(reg));

        return reg;
    }

    static unsigned int minstreth() {
        Reg32 reg;
        
        asm volatile (R"(
            csrr    %0, minstreth
        )": "=r"(reg));

        return reg;
    }

    static unsigned int mcycle() {
        Reg32 reg;
        
        asm volatile (R"(
            csrr    %0, mcycle
        )": "=r"(reg));

        return reg;
    }
    
    static unsigned int mcycleh() {
        Reg32 reg;
        
        asm volatile (R"(
            csrr    %0, mcycleh
        )": "=r"(reg));

        return reg;
    }

private:

    static bool check(Channel channel) {
        Reg32 reg;
        
        asm volatile (R"(
            csrr    %0, mhpevent3
        )": "=r"(reg));

        return ((reg & 0xFF) == _event && ((reg >> channel) & 0b1));
    }

private:
    unsigned int _event;

};

class PMU: private RV32_PMU
{
    friend class CPU;

private:
    typedef RV32_PMU Engine;

public:
    using Engine::CHANNELS;
    using Engine::FIXED;
    using Engine::EVENTS;

    using Engine::Event;
    using Engine::Count;
    using Engine::Channel;

public:
    PMU() {}

    using Engine::config;
    using Engine::read;
    using Engine::write;
    using Engine::start;
    using Engine::stop;
    using Engine::reset;
    using Engine::mcycle;

private:
    static void init() { Engine::init(); }
};


__END_SYS

#endif

