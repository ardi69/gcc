extern void *malloc(__SIZE_TYPE__);
extern void *memcpy(void *, void *, __SIZE_TYPE__);
extern void *memset(void *dst, int, __SIZE_TYPE__);
extern void mfree(void*);
extern void abort(void);
extern char __TLS_DATA__[];
extern char __TLS_DATA_SIZE__[];
extern char __TLS_SIZE__[];

#define data_size ((__SIZE_TYPE__)__TLS_DATA_SIZE__)
#define size ((__SIZE_TYPE__)__TLS_SIZE__)

void *__m68k_allocate_tls(void);
void *__m68k_allocate_tls(void) {
	char *tls_data = (char*)malloc(size);
	if (__builtin_expect(tls_data == (char*)0, 0)) abort();
	memcpy(tls_data, __TLS_DATA__, data_size);
	memset(tls_data + data_size, 0, size - data_size);
	return tls_data;
}
void __m68k_deallocate_tls(void *);
void __m68k_deallocate_tls(void *tls) {
	mfree(tls);
}

