from pwn import *

# This code works (2023.11.17)

context.log_level = "debug"

p = remote("141.164.48.98", "30004")

while True:
    buf = p.recv(1000)
    if buf[:3] == b"HIT":
        break

    expr = re.search(b"[0-9]+[ ]*[-+*/%][ ]*[0-9]+", buf).group().decode("ascii")
    oper = expr.split(" ")

    num1, num2 = int(oper[0]), int(oper[2])
    num0 = 0
    if oper[1] == "-":
        num1 -= num2
    elif oper[1] == "+":
        num1 += num2
    elif oper[1] == "*":
        num1 *= num2
    elif oper[1] == "/":
        num1 //= num2
    else:
        num1 %= num2

    p.sendline(str(num1))
