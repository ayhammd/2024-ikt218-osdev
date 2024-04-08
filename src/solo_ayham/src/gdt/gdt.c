/* code from cource lecture
 * https://perara.notion.site/Session-6-Global-Descriptor-Tables-b43f3c4ca20741b7ac46018c0ad6f26e
 */

#include <gdt.h>

struct gdt_entry gdt_entries[5];
struct gdt_ptr gdt_ptr;

void init_gdt()
{
   // Set the GDT limit
   gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
   gdt_ptr.base = (uint32_t)&gdt_entries;

   // num, base, limit, access, granularity
   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   // Flush GDT pointer
   gdt_flush((uint32_t)&gdt_ptr);
}

void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_low = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access = access;
}
