// CSE30 assignment template
// 
// id: 
//
////////////////////////////////////////
#include "Version.h"

#ifndef MYINSTNODE_S
    .section .note.GNU-stack,"",%progbits
    .end
#else

    // version 1.0 08/22/2024
    .arch   armv6
    .arm
    .fpu    vfp
    .syntax unified

    #include "node.h"    
    
    .extern malloc
    .extern free
    .extern strcpy
    .extern strncpy
    .extern strlen
    .text

    .type   insert_node, %function
    .global insert_node
    // determine how many registers to save and set FP_OFF
    //.equ    FP_OFF, ??

    // preserved register use table fill this in to help you
    //
    // r4
    // r5
    // r6
    // r7
    // r8
    // r9

insert_node:
    // set up stack frame
    
    // implement the function

    // remove stack frame
    bx      lr                  // function return
    .size   insert_node, (. - insert_node)
    .section .note.GNU-stack,"",%progbits
.end
#endif
