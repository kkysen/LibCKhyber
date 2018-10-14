//
// Created by Khyber on 10/14/2018.
//

#ifndef CLAMP_H
#define CLAMP_H

#define clamp(val, min, max) \
    (val) = fmaxf(val, min); \
    (val) = fminf(val, max)

#endif // CLAMP_H
