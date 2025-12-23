# Lab 07. RSA
# By: López Reyes José Roberto. 6CV4.

from Crypto.Util.number import getPrime, GCD, inverse
import random


# Prime Generation
def generar_primos():
    print("\n--- Generación de números primos aleatorios ---\n")

    tamanos = [32, 64, 128, 512, 2048]

    for bits in tamanos:
        primo = getPrime(bits)
        print(f"Primo de {bits} bits:")
        print(primo)
        print("-" * 60)


# RSA Key Generation
def generar_llaves_rsa(bits):
    print("\n--- Generación de llaves RSA ---\n")

    # Tamaños posibles
    tamanos = [64, 128, 256, 512, 1024]

    if bits not in tamanos:
        print("\nTamaño de llave inválido.")
        return

    # Generar p y q
    p = getPrime(bits)
    q = getPrime(bits)

    while p == q:
        q = getPrime(bits)

    print(f"\np = {p}")
    print(f"q = {q}")

    # Calcular n y φ(n)
    n = p * q
    phi = (p - 1) * (q - 1)

    print(f"\nn = p * q = {n}")
    print(f"φ(n) = {phi}")

    # Elegir e aleatorio válido
    while True:
        e = random.randrange(2, phi)
        if GCD(e, phi) == 1 and e != 3 and e != 65537 and e % 2 != 0:
            break

    print(f"\ne = {e}")

    # Calcular d (inverso modular de e)
    d = inverse(e, phi)

    print(f"d = {d}")

    # Mostrar llaves
    print("\n=== LLAVES RSA GENERADAS ===\n")
    print(f"Llave pública (e, n):")
    print(f"e = {e}")
    print(f"n = {n}")
    print(f"({e}, {n})\n")

    print("Llave privada (d):")
    print(f"d = {d}")
    print("\n---------------------------------------------\n")


def main():
    print("\n--- RSA Key Generation ---\n")

    bits = int(input("Ingrese tamaño de los primos (64, 128, 256, 512 o 1024 bits): "))

    generar_primos()
    generar_llaves_rsa(bits)


if __name__ == "__main__":
    main()
