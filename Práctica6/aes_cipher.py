# Lab 06. AES-CTR
# By: López Reyes José Roberto. 6CV4.

from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES
import base64


# AES Cipher
def cipher(key, plaintext):
    # Reading key from file
    try:
        with open(key, "r") as file:
            K = base64.b64decode(file.read())
            print(f"Successfully opened {key}.")
    except FileNotFoundError:
        print(f"Error: The file {key} was not found.")
    except Exception as e:
        print(f"An error occurred as trying to read from the file: {e}")

    # Reading plaintext from file
    try:
        with open(plaintext, "rb") as file:
            M = file.read()
            print(f"Successfully opened {plaintext}.")
    except FileNotFoundError:
        print(f"Error: The file {plaintext} was not found.")
    except Exception as e:
        print(f"An error occurred as trying to read from the file: {e}")

    # Generate random IV
    iv = get_random_bytes(8)

    # Create an AES Object
    aes_ciph = AES.new(K, AES.MODE_CTR, nonce=iv)
    C = aes_ciph.encrypt(M)

    # print(f"IV: {base64.b64encode(iv)}")
    # print(f"Ciphertext: {base64.b64encode(C)}")

    print("Encryption process finished.")
    cipher_file = input("Enter the name of the ciphertext file: ")

    # Store it all in a file
    try:
        with open(cipher_file, "wb") as file:
            file.write(base64.b64encode(iv + C))
            print(f"Successfully saved in '{cipher_file}'.")
    except FileNotFoundError:
        print("Error: The file was not able to be opened.")
    except Exception as e:
        print(f"There was an error writing into the file: {e}")

    return C


# Ciphering person
def bob():
    print("--- AES Ciphering ---")

    key = input("Enter the name of your textfile containing the key: ")
    plaintext = input("Enter the name of your textfile containing your plaintext: ")

    cipher(key, plaintext)


bob()
