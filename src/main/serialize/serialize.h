//
// Created by Khyber on 10/14/2018.
//

#ifndef SERIALIZE_H
#define SERIALIZE_H

/**
 * Defines a serializer function for the given \param Type.
 * It requires that these functions already be defined:
 *      size_t Type##_serializedLength(Type type);
 *      void Type##_serializeInto(Type type, Buffer *buffer);
 *
 * @param Type the type of value for which the serializer should be defined.
 */
#define defineSerialize(Type) \
Buffer Type##_serialize(Type *const type) { \
    const size_t size = Type##_serializedLength(type); \
    Buffer buffer = { \
            .index = 0, \
            .length = size, \
            .data = malloc(size), \
    }; \
    if (!buffer.data) { \
        perror("malloc(size)"); \
        return INVALID_BUFFER; \
    } \
    Type##_serializeInto(type, &buffer); \
    return buffer; \
}

#endif // SERIALIZE_H
