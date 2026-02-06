# 🔐 Introduction to Cryptography

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Institution](https://img.shields.io/badge/Institution-ESCOM%20%7C%20IPN-800000?style=for-the-badge&logo=school&logoColor=white)
![Semester](https://img.shields.io/badge/Semester-26%2F1-purple?style=for-the-badge)

This repository centralizes the coding exercises and laboratory sessions for the **Introduction to Cryptography** course taught by **Dr. Sandra Díaz Santiago** at the **Escuela Superior de Cómputo (ESCOM)**. The project covers classical cryptosystems, modular arithmetic algorithms, and modern symmetric/asymmetric implementations.

---

## 🚀 Course Projects

The coursework is divided into sequential laboratories, exploring fundamental and advanced concepts of cryptography:

### 1️⃣ Classical Ciphers & Modular Arithmetic
* **Lab 01: Modular Arithmetic & Shift Cipher**
  * Implementation of multiplication tables for $\mathbb{Z}_{n}-\{0\}$.
  * Analysis of multiplicative inverses in finite fields.
  * **Shift Cipher:** Full implementation of encryption/decryption using modular addition/subtraction in $\mathbb{Z}_{n}$.

* **Lab 02: Affine Cipher**
  * Generation of valid keys $K=(a,b)$ for the Affine Cipher checking $gcd(a,n)=1$.
  * **Cryptanalysis:** Algorithms to recover plaintext given a ciphertext and key.
  * Implementation of modular arithmetic over ASCII printable characters.

* **Lab 03: Extended Euclidean Algorithm (EEA)**
  * Implementation of the EEA to compute the greatest common divisor (GCD).
  * Calculation of **Multiplicative Inverses** for Affine keys ($a^{-1} \pmod n$).

* **Lab 04: Permutation Cipher**
  * **Algorithm Design:** Pseudocode for random permutation generation and inverse permutations ($\pi^{-1}$).
  * **File Processing:** Enciphering and deciphering text files (>10kb) using permutation blocks.

### 2️⃣ Block Ciphers & Modern Cryptography
* **Lab 05: Bitwise Ops & SPN Construction (Parts I-V)**
  * **Bitwise Primitives:** Low-level manipulation (getting/setting $n$-th bit, shifts, masks) and XOR encryption.
  * **SPN Components:** Design and implementation of random **Substitution Boxes (S-Boxes)** and **Permutation Boxes (P-Boxes)**.
  * **Toy Block Cipher:** Full implementation of a custom SPN cipher including Key Mixing, Substitution, and Permutation layers.
  * **Finite Fields:** Implementation of polynomial multiplication in **$GF(2^8)$** modulo $x^8+x^5+x^3+x+1$.
  * **Modes of Operation:** Implementation of **CTR (Counter Mode)** for the Toy Cipher and usage of **3DES-CBC** via libraries.

* **Lab 06: AES - Counter Mode (CTR)**
  * **Key Generation:** Random generation of 128, 192, and 256-bit AES keys.
  * **AES-CTR:** Implementation of encryption and decryption using a unique **nonce/IV**.
  * Integration with **Base64** encoding for ciphertext storage.

* **Lab 07: RSA Implementation**
  * **Large Primes:** Generation of primes (up to 2048 bits).
  * **Key Generation:** Computation of public $(e, n)$ and private $(d)$ keys verifying $gcd(e, \phi(n))=1$.
  * **Core Logic:** Implementation of $c = m^e \pmod n$ and $m = c^d \pmod n$ for secure integer exchange.

---

## 🗂️ Repository Structure

Each directory contains the source code and specific documentation for the lab session.

```text
/
├── Practica1/       # Modular Arith. & Shift Cipher
├── Practica2/       # Affine Cipher & Modular Inverse
├── Practica3/       # Extended Euclidean Algorithm
├── Practica4/       # Permutation Cipher (Files)
├── Practica5/       # Bitwise Ops & SPN Construction
├── Practica6/       # AES-CTR & Base64
└── Practica7/       # RSA KeyGen & Crypto
```

## 🛠️ Technologies & Concepts
* **Languages:** C++ (Core), Python (Prototyping).
* **Libraries:** Standard I/O, Math libraries for modular arithmetic.
* **Key Concepts:**
  * Finite Fields ($\mathbb{Z}_n$).
  * Symmetric Key Cryptography (AES, Affine, Shift).
  * Public Key Cryptography (RSA).
  * Block Ciphers & Modes of Operation (CTR).

---

## ⚠️ Academic Integrity Note
This repository was created for educational purposes and personal reference.

**Goal:** To serve as a study archive and portfolio of the implemented cryptographic algorithms.

**Disclaimer:** It is strongly recommended not to copy or plagiarize the code presented here for academic submissions. Real learning comes from the self-implementation of these mathematical models.

---

## 👤 Author

- **[RobertLopez893](https://github.com/RobertLopez893)**

---

_Introduction to Cryptography - Semester 26/1 - ESCOM IPN_
