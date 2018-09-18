//
// Created by Khyber on 9/7/2018.
//

#ifndef SET_FIELD_H
#define SET_FIELD_H

/**
 * Sets a \param field with the memory pointed to by a \param ptr
 * using memcpy(), which circumvents const modifiers.
 *
 * @param field the field to set with the memory pointed to by \param ptr
 * @param ptr the pointer to the memory to set the \param field with
 */
#define setFieldMemory(field, ptr) \
    memcpy((void *) &(field), ptr, sizeof(field))

/**
 * Sets a \param field with a \param val using memcpy(),
 * which circumvents const modifiers.
 *
 * @param field the field to set with \param val
 * @param val the value to set the \param field with
 */
#define setField(field, val) \
    do { \
        typeof(val) _val = val; \
        setFieldMemory(field, &_val); \
    } while (false)

#endif // SET_FIELD_H
