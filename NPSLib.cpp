#include <iostream>
#include "NPSLib.h"

void say_hello(){
    std::cout << "Hello, from learn-c!\n";
}

class NPSLib : public NPS_Pack
{
private:
    /* data */
public:
    NPSLib();
    ~NPSLib();
};

NPSLib::NPSLib(/* args */)
{
}

NPSLib::~NPSLib()
{
}

inline int NPS_Pack::pack(unsigned char *buf, int len, char *packcode, void* p4, void* p5, ...)
{
    unsigned char *index = buf;
    void **local_8 = &p4;
    char *nextCode = packcode;

    // Helper lambda to check remaining buffer size
    auto remaining_size = [&](unsigned char *current) {
        return len - (current - buf);
    };

    // Helper lambda to write a 4-byte big-endian integer
    auto write_big_endian_4 = [&](unsigned char *current, uint value) {
        current[0] = (value >> 24) & 0xFF;
        current[1] = (value >> 16) & 0xFF;
        current[2] = (value >> 8) & 0xFF;
        current[3] = value & 0xFF;
    };

    while (*nextCode != '\0') {
        switch (*nextCode) {
            case 'b': { // Block of bytes
                void *src_ptr = *local_8;
                size_t block_size = (size_t)local_8[1];

                if (!src_ptr || remaining_size(index) < (int)block_size) return -1;

                memcpy(index, src_ptr, block_size);
                index += block_size;
                local_8 += 2;
                break;
            }
            case 'c': { // Single byte
                if (!*local_8 || remaining_size(index) < 1) return -1;

                *index = *(unsigned char *)*local_8;
                index += 1;
                local_8 += 1;
                break;
            }
            case 'l': { // 4-byte big-endian integer
                if (!*local_8 || remaining_size(index) < 4) return -1;

                uint value = *(uint *)*local_8;
                write_big_endian_4(index, value);
                index += 4;
                local_8 += 1;
                break;
            }
            case 'p': { // Block of data with size specified in buffer
                void *src_ptr = *local_8;
                size_t block_size = (size_t)local_8[1];

                if (!src_ptr || remaining_size(index) < 4 + (int)block_size) return -1;

                write_big_endian_4(index, (uint)block_size);
                index += 4;

                memcpy(index, src_ptr, block_size);
                index += block_size;
                local_8 += 2;
                break;
            }
            case 's': { // 2-byte big-endian integer
                if (!*local_8 || remaining_size(index) < 2) return -1;

                ushort value = *(ushort *)*local_8;
                index[0] = (value >> 8) & 0xFF;
                index[1] = value & 0xFF;
                index += 2;
                local_8 += 1;
                break;
            }
            default:
                return -1; // Unsupported format code
        }

        nextCode++;
    }

    return index - buf;
}

inline int NPS_Pack::unpack(NPS_Pack *param_1, unsigned char *data, int len, char *packcode, _NPS_CommData *dest, ...)
{
    unsigned char *index = data;
    _NPS_CommData **local_8 = &dest;
    char *nextCode = packcode;

    // Helper lambda to check remaining buffer size
    auto remaining_size = [&](unsigned char *current) {
        return len - (current - data);
    };

    // Helper lambda to read a 4-byte big-endian integer
    auto read_big_endian_4 = [&](unsigned char *current) {
        return (uint)current[0] << 24 | (uint)current[1] << 16 | (uint)current[2] << 8 | (uint)current[3];
    };

    while (*nextCode != '\0') {
        switch (*nextCode) {
            case 'b': { // Block of bytes
                void *dest_ptr = *local_8;
                size_t block_size = (size_t)local_8[1];
                size_t available_size = remaining_size(index);

                if (!dest_ptr || block_size > available_size) return -1;

                memcpy(dest_ptr, index, block_size);
                index += block_size;
                local_8 += 2;
                break;
            }
            case 'c': { // Single byte
                if (!*local_8 || remaining_size(index) < 1) return -1;

                *(unsigned char *)*local_8 = *index;
                index += 1;
                local_8 += 1;
                break;
            }
            case 'l': { // 4-byte big-endian integer
                if (!*local_8 || remaining_size(index) < 4) return -1;

                uint *dest_ptr = (uint *)*local_8;
                *dest_ptr = read_big_endian_4(index);
                index += 4;
                local_8 += 1;
                break;
            }
            case 'p': { // Block of data with size specified in buffer
                void *dest_ptr = *local_8;
                size_t max_size = (size_t)local_8[1];

                if (!dest_ptr || remaining_size(index) < 4) return -1;

                size_t block_size = read_big_endian_4(index);
                index += 4;

                if (block_size > max_size || remaining_size(index) < (int)block_size) return -1;

                memcpy(dest_ptr, index, block_size);
                ((unsigned char *)dest_ptr)[block_size] = '\0';
                index += block_size;
                local_8 += 2;
                break;
            }
            case 's': { // 2-byte big-endian integer
                if (!*local_8 || remaining_size(index) < 2) return -1;

                ushort *dest_ptr = (ushort *)*local_8;
                *dest_ptr = (ushort)index[0] << 8 | (ushort)index[1];
                index += 2;
                local_8 += 1;
                break;
            }
            default:
                return -1; // Unsupported format code
        }

        nextCode++;
    }

    return index - data;
}

