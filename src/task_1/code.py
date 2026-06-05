c_hex = "ed924527ff3a43600e318248daa62a18307096f78f5ea899598eb5ce7de2adbd6565ce5cfe896dcee24521f615cedb8236ed642a1966592cac7cae40412a717594e75b58d610b9ca2ea8642c336b804357ca1f405f9b713a9f492f1a85b64e9601385fb872a1c9e487af698727359e91221c3e3acacd476ab374469daf586c11bf1a5eb09a957670be8b353c901868d86bf2fe9074361a2a54c73df56ca38d"
c = int(c_hex, 16)
e = 5

def integer_nth_root(x, n):
    if x < 0:
        return None
    if x == 0:
        return 0
    low, high = 1, 1
    while high ** n <= x:
        high *= 2
    while low < high:
        mid = (low + high + 1) // 2
        if mid ** n <= x:
            low = mid
        else:
            high = mid - 1
    return low

m = integer_nth_root(c, e)

# Проверка, что m^5 действительно равно c
if pow(m, e) == c:
    flag = m.to_bytes((m.bit_length() + 7) // 8, 'big').decode('utf-8')
    print("Флаг:", flag)
    with open("RSA_cracked.txt", "w", encoding="utf-8") as f:
        f.write(flag)
else:
    print("Ошибка: атака не сработала")
