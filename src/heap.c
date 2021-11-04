#include "system.h"

struct memory_segment_header* first_free_memory_segment;

void heap_init(unsigned long long heap_addr, unsigned long long heap_len)
{
    first_free_memory_segment = (struct memory_segment_header*)heap_addr;
    first_free_memory_segment->memory_lenght = heap_len;
    first_free_memory_segment->next_segment = 0;
    first_free_memory_segment->previous_segment = 0;
    first_free_memory_segment->next_free_segment = 0;
    first_free_memory_segment->previous_free_segment = 0;
    first_free_memory_segment->free = 1;
}

void* malloc(unsigned long long size)
{
    unsigned long long rem = size % 8;
    size -= rem;
    if(rem != 0) size += 8;

    struct memory_segment_header* current_memory_segment = first_free_memory_segment;

    while(1)
    {
        if(current_memory_segment->memory_lenght >= size)
        {
            if(current_memory_segment->memory_lenght > size + sizeof(struct memory_segment_header))
            {
                struct memory_segment_header* new_segment_header = (struct memory_segment_header*)((unsigned long long)current_memory_segment + sizeof(struct memory_segment_header) + size);

                new_segment_header->free = 1;
                new_segment_header->memory_lenght = ((unsigned long long)current_memory_segment->memory_lenght) - (sizeof(struct memory_segment_header) + size);
                new_segment_header->next_free_segment = current_memory_segment->next_free_segment;
                new_segment_header->next_segment = current_memory_segment->next_segment;
                new_segment_header->previous_segment = current_memory_segment;
                new_segment_header->previous_free_segment = current_memory_segment->previous_free_segment;

                current_memory_segment->next_free_segment = new_segment_header;
                current_memory_segment->next_segment = new_segment_header;
                current_memory_segment->memory_lenght = size;
            }
            if(current_memory_segment == first_free_memory_segment)
            {
                first_free_memory_segment = current_memory_segment->next_free_segment;
            }
            current_memory_segment->free = 0;
            if(current_memory_segment->previous_free_segment != 0) current_memory_segment->previous_free_segment->next_free_segment = current_memory_segment->next_free_segment;
            if(current_memory_segment->next_free_segment != 0) current_memory_segment->next_free_segment->previous_free_segment = current_memory_segment->previous_free_segment;
            if(current_memory_segment->previous_free_segment != 0) current_memory_segment->previous_free_segment->next_free_segment = current_memory_segment->next_free_segment;
            if(current_memory_segment->next_free_segment != 0) current_memory_segment->next_free_segment->previous_free_segment = current_memory_segment->previous_free_segment;

            if(current_memory_segment->previous_segment != 0) current_memory_segment->previous_segment->next_free_segment = current_memory_segment->next_free_segment;
            if(current_memory_segment->next_segment != 0) current_memory_segment->next_segment->previous_free_segment = current_memory_segment->previous_free_segment;

            return current_memory_segment + sizeof(struct memory_segment_header);
        }
        if(current_memory_segment->next_free_segment == 0)
        {
            return 0;
        }
        current_memory_segment = current_memory_segment->next_free_segment;
    }
}