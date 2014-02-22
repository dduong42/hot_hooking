all: target hook

target: target.c
	$(CC) $(CFLAGS) $< -o $@

libinject/libinject.a:
	make -C libinject

hook: hook.c libinject/libinject.a
	$(CC) $(CFLAGS) $^ -o $@
		
clean:
	$(RM) target hook
	
re: clean all