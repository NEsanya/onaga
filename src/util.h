#ifndef UTIL_H
#define UTIL_H

typedef enum ong_result
{
    ONG_SUCCESS = 0,
    ONG_OUT_OF_MEMORY = -1,
    ONG_UNSUPPORTED_DEVICE = -2,
    ONG_INITIALIZATION_ERROR = -3
} ong_result_t;

#define ONG_RETURN_IFN_SUCCESS(result)\
    if (result != ONG_SUCCESS)\
        return result

#define ONG_MALLOC_CHECK(pointer)\
    if (pointer == NULL)\
        {\
            printf ("[%s] onaga out of memory.", __FILE__);\
            return ONG_OUT_OF_MEMORY;\
        }\

typedef struct
{
    unsigned char major;
    unsigned char minor;
} ong_version_t;

typedef struct
{
    ong_version_t version;
    unsigned int width;
    unsigned int height;
    const char *title;
} ong_create_data_t;

#endif
