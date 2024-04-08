#include <libc/stdint.h>
#include <libc/stddef.h>
#include <libc/stdbool.h>
#include <multiboot2.h>
#include <gdt.h>
#include <libc/stdio.h>

int main(uint32_t magic, struct multiboot_info *mb_info_addr)
{

    init_gdt();

    printf(10, "Hello World!");
    return kernel_main();
}
