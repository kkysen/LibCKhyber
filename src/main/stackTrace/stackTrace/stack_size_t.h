//
// Created by Khyber on 9/23/2018.
//

#ifndef STACK_SIZE_T_H
#define STACK_SIZE_T_H

#include <stdint.h>

#include <signal.h>

typedef u16 stack_size_t; // SIGSTKSZ	= 8192

#define STACK_SIZE_MAX ((stack_size_t) SIGSTKSZ)

#endif // STACK_SIZE_T_H
