#include <libc/stdio.h>
#include <libc/stdint.h>

void printf(int color, const char *string)
{

    volatile char *video_memory = (volatile char *)0xB8000;
    while (*string != 0)
    {
        *video_memory++ = *string++;
        *video_memory++ = color;
    }
}