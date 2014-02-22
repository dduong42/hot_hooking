push rdi
push rsi
push rdx

mov rax, 1
mov rdi, 1
lea rsi, [rel string]
mov rdx, end_string - string
syscall

mov rax, 1
pop rdx
pop rsi
pop rdi
syscall

ret

string:
db "Hooked !", 0xa
end_string: