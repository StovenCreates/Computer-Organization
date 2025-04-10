// CSE30 assignment template
// 
// id: 
//
////////////////////////////////////////
#include "Version.h"

#ifndef MYHASH_S
    .section .note.GNU-stack,"",%progbits
    .end
#else

    // version 1.0 08/22/2024
    .arch   armv6
    .arm
    .fpu    vfp
    .syntax unified

    
    .text

    .type   hashfn, %function
    .global hashfn
    // determine how many registers to save and set FP_OFF
    .equ    FP_OFF, 28          // (# of preserved regs - 1) * 4

    // preserved register use table fill this in to help you
    //
    // r4
    // r5
    // r6
    // r7
    // r8
    // r9

hashfn:
	push    {r4-r9, fp, lr}     // use r4-r9 protected regs
    add     fp, sp, FP_OFF      // locate our frame pointer
    // DO NOT EDIT PROLOGUE ABOVE
    // You can use temporary r0-r3 and preserved r4-r9
    // Store return value (results) in r0
    ///////////////////////////////////////////////////////
    
    // YOUR CODE GOES HERE
    
    ///////////////////////////////////////////////////////
    // DO NOT EDIT EPILOGUE BELOW
    sub     sp, fp, FP_OFF      // restore sp
    pop     {r4-r9, fp, lr}     // restore saved registers
    bx      lr                  // function return
    .size   hashfn, (. - hashfn)
    .section .note.GNU-stack,"",%progbits
.end
#endif
