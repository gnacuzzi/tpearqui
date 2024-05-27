#include <stdint.h>
#include <lib.h>
void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}



uint64_t reg_snap[REGS] = {0};      /* Vector de valores de registros */
static char * regs[] = {"RAX", "RBX", "RCX", "RDX", "RBP", "RDI", "RSI", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};

uint64_t * get_snapshot() {
    return reg_snap;
}

void copy_registers(uint64_t * rsp) {
    uint64_t * p = rsp + 23; 
    uint64_t * rspEnd = rsp+7; 
    int i = 0;

    reg_snap[0] = *p;
    reg_snap[1] = (uint64_t) p + 0x30;
    p--;
    while (p != rspEnd) {
        reg_snap[i+2] = *p;
        p--;
        i++;
    }
}

//hasta aca lo agregado
void print_regs(uint64_t rip, uint64_t rsp, uint64_t * newRsp) {
	printf("RIP: 0x%x\nRSP: 0x%x\n", rip, rsp);
    for (int i = 0; i < sizeof(regs)/sizeof(char *); i++)
        printf("%s: 0x%x ", regs[i], *(newRsp - i));
}