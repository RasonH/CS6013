section .text  ; this says that we're about to write code (as opposed to data)

global sayHello ; this says that "sayHello" is a symbol that the linker needs to know about
extern puts
extern myPuts


sayHello:           ;and here we go...
  push rbp
  mov rbp, rsp 
  mov rdi, helloString
  call puts
  pop rbp
  ret               ; just return


myPuts:
  mov rdx, rsi      ;store len to rdx
  mov rsi, rdi      ;store string s address to rsi
  mov rdi, 1        ;syscall 
  mov rax, 1
  syscall
  ret


section .rodata
helloString: db "hello",0