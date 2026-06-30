import math

# Своя функция вместо Crypto.Util.number.long_to_bytes
def long_to_bytes(n):
    return n.to_bytes((n.bit_length() + 7) // 8, 'big')

e = 65537
n = 55089599753625499150129246679078411260946554356961748980861372828434789664694269460953507615455541204658984798121874916511031276020889949113155608279765385693784204971246654484161179832345357692487854383961212865469152326807704510472371156179457167612793412416133943976901478047318514990960333355366785001217

ciphertext_hex = "152772c5d14dedfa4bec8b6aa52702d177ac73b7b65df25e7e60c6b5ba3f101d70cc4768fbdda0789e43b10307d8f9f1493d27e7c56f1eefbb18722a47f10477967fc8c0e48b017e5ba6d63181ea0ce7e45e81e90b6be37baccdf5de046718408cb85dc3a961f1f398c6c0aedba5d30dbeaba0eea8a72648adac9afae4b4ad72"
ciphertext_int = int(ciphertext_hex,16)

print("[*] Факторизация методом Ферма...")

def fermat_factorization(n):
    a = math.isqrt(n)
    if a * a < n:
        a += 1
    
    while True:
        b2 = a*a - n
        b = math.isqrt(b2)
        if b*b == b2:
            return a - b, a + b
        a += 1
        if a % 100000 == 0:
            print(f"[*] Перебираем a = {a}...")

p, q = fermat_factorization(n)
print(f"[+] p = {p}")
print(f"[+] q = {q}")

phi = (p - 1) * (q - 1)
d = pow(e, -1, phi)
print("[+] d вычислен")

m_int = pow(ciphertext_int, d, n)
flag = long_to_bytes(m_int).decode()
print(f"\n✅ ФЛАГ: {flag}\n")

with open("solution.txt", "w") as f:
    f.write(flag)
print("[+] Результат сохранен в solution.txt")
