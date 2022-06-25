// EPOS RISC-V 32 Program Starter

        .file "rv64_crt0.S"

        .section .text
        .align  8
        .global _start
        .type   _start, function
_start:

       // Only hart (core) 0 cleans cache
        mv      t0, tp
        bnez    t0, 2f
1:
        sw      zero, (a0)
        addi    a0, a0, 8
        bltu    a0, a1, 1b
2:
        // Temporary stack(s) for INIT were created and configure by SETUP
        // BSS was cleared by SETUP
        call      _init
        // call _pre_main

        .align  8
        .globl  __epos_app_entry
        .type   __epos_app_entry, function
__epos_app_entry:
        // mv      t0, tp
        // bnez    t0, _pre_main

        // Main's stack was allocated by Thread::init()
        call    main
        lw      a0, 0(sp)
        ; addi    sp, sp, -8
        ; sw      a0, 0(sp)   // save main's return value to be used by exit()
        call    _fini
        call    _exit
