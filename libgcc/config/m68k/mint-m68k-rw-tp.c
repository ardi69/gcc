extern char __main_tls[];
extern void abort(void);

static void * ___m68k_read_tp(void) {
	return __main_tls;
}
//weak_alias (___m68k_read_tp, __m68k_read_tp)
void *__m68k_read_tp(void) __attribute__ ((weak, alias ("___m68k_read_tp")));

 //__dl_deallocate_tls
static void ___m68k_write_tp(void * tp __attribute__((unused))) {
	abort();
}
//weak_alias (___m68k_write_tp, __m68k_write_tp)
void __m68k_write_tp(void *) __attribute__ ((weak, alias ("___m68k_write_tp")));

