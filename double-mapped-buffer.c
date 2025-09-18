#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

#define defer_error(string) do { perror(string); goto defer; } while (0)

extern int memfd_create(const char *, unsigned int flags);

int main()
{
    int pagesize = getpagesize();

    void *page_aligned_ptr = mmap(NULL, 2 * pagesize, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (page_aligned_ptr == MAP_FAILED) defer_error("mmap");
    munmap(page_aligned_ptr, pagesize);

    int fd = memfd_create("black magic fuckery", 0);
    ftruncate(fd, pagesize);

    uint32_t *arr = mmap(page_aligned_ptr, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
    if (arr == MAP_FAILED) defer_error("allocation");

    uint32_t *ret = mmap(page_aligned_ptr+pagesize, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
    if (ret == MAP_FAILED) defer_error("allocation 2");

    arr[0] = 0xaabbccdd;
    printf("arr[0] = %x\narr[%d] = %x\n", arr[0], pagesize/4, arr[pagesize/4]);

defer:
    return 0;
}
