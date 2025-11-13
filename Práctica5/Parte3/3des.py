# Lab 05. Bit Permutation
# By: López Reyes José Roberto. 6CV4.

from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
import base64


# Generate a random key
def gen_key():
    key = get_random_bytes(24)
    encoded_key = base64.b64encode(key)

    # Store the key in a file
    try:
        with open("3des_key.txt", "w") as file:
            file.write(encoded_key.decode('utf-8'))
            print("Successfully saved in '3des_key.txt'.")
    except FileNotFoundError:
        print("Error: The file was not able to be opened.")
    except Exception as e:
        print(f"There was an error writing into the file: {e}")


# 3DES Ciphering
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

    # IV Vector
    IV = get_random_bytes(8)

    # Creating Cipher Object
    encipher = DES3.new(K, DES3.MODE_CBC, IV)

    # Padding Data
    M = pad(M, DES3.block_size)

    # Encrypting
    C = encipher.encrypt(M)

    # Saving the IV Vector and the ciphertext
    final_output = IV + C
    b64_o = base64.b64encode(final_output)

    # Store it all in a file
    try:
        with open("ciphertext_3des.txt", "w") as file:
            file.write(b64_o.decode('utf-8'))
            print("Successfully saved in 'ciphertext_3des.txt'.")
    except FileNotFoundError:
        print("Error: The file was not able to be opened.")
    except Exception as e:
        print(f"There was an error writing into the file: {e}")


# 3DES Deciphering
def decipher(key, ciphertext):
    # Reading key from file
    try:
        with open(key, "r") as file:
            K = base64.b64decode(file.read())
            print(f"Successfully opened {key}.")
    except FileNotFoundError:
        print(f"Error: The file {key} was not found.")
    except Exception as e:
        print(f"An error occurred as trying to read from the file: {e}")

    # Reading ciphertext from file
    try:
        with open(ciphertext, "r") as file:
            coded_input = file.read()
            print(f"Successfully opened {ciphertext}.")
    except FileNotFoundError:
        print(f"Error: The file {ciphertext} was not found.")
    except Exception as e:
        print(f"An error occurred as trying to read from the file: {e}")

    # Decoding and extracting the information
    data_bytes = base64.b64decode(coded_input)
    IV = data_bytes[:8]
    C = data_bytes[8:]

    # Creating Cipher Object
    deciph = DES3.new(K, DES3.MODE_CBC, IV)

    # Decrypt the data
    M = deciph.decrypt(C)

    # Unpadding the result
    final_output = unpad(M, DES3.block_size)

    # Store it all in a file
    try:
        with open("recovered_3des.txt", "wb") as file:
            file.write(final_output)
            print("Successfully saved in 'recovered_3des.txt'.")
    except FileNotFoundError:
        print("Error: The file was not able to be opened.")
    except Exception as e:
        print(f"There was an error writing into the file: {e}")


# Ciphering person
def bob():
    key = input("Enter the name of your textfile containing the key: ")
    plaintext = input("Enter the name of your textfile containing your plaintext: ")

    cipher(key, plaintext)


# Deciphering person
def alice():
    key = input("Enter the name of your textfile containing the key: ")
    ciphertext = input("Enter the name of your textfile containing your ciphertext: ")

    decipher(key, ciphertext)


gen_key()
bob()
# alice()
