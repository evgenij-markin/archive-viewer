#ifndef ARCH_INFO_H
#define ARCH_INFO_H

#include <stdint.h>
#include <QString>

struct Archive_info
{
    QString  filename;                  /* filename utf8 null-terminated string */
    int64_t  compressed_size;           /* compressed size */
    int64_t  uncompressed_size;         /* uncompressed size */
};

#endif // ARCH_INFO_H
