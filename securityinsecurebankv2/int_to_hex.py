array_IV = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
array_KEY = [84, 104, 105, 115, 32, 105, 115, 32, 116, 104, 101, 32, 115, 117, 112, 101, 114, 32, 115, 101, 99, 114, 101, 116, 32, 107, 101, 121, 32, 49, 50, 51]
array_before = [74, 97, 99, 107, 64, 49, 50, 51, 36]
array_after = [-65, -5, 9, -90, 40, 67, 10, -115, -100, -112, 57, -117, 91, -107, 48, -117]
arrs = [array_IV, array_KEY, array_before, array_after]

for i in range(len(array_after)):
    if array_after[i] < 0:
        array_after[i] = 256 + array_after[i]
print(len(array_IV))
print(len(array_KEY))
print(len(array_before))
print(len(array_after))
print(''.join('{:02x}'.format(x) for x in array_IV))
print(''.join('{:02x}'.format(x) for x in array_KEY))
print(''.join('{:02x}'.format(x) for x in array_before))
print(''.join('{:02x}'.format(x) for x in array_after))

for a in arrs:
    st = []
    for x in a:
        st.append(chr(x))
    print('[' + ''.join(st) + ']')