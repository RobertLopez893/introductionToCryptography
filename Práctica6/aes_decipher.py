# Lab 06. AES-CTR
# By: López Reyes José Roberto. 6CV4.

from Crypto.Cipher import AES
import base64


# AES Cipher
def decipher(key, ciphertext):
    # Reading key from file
    try:
        with open(key, "r") as file:
            K = base64.b64decode(file.read())
            print(f"Successfully opened {key}.")
            print(f"\nKey: {K}")
    except FileNotFoundError:
        print(f"Error: The file {key} was not found.")
    except Exception as e:
        print(f"An error occurred as trying to read from the file: {e}")

    # Reading ciphertext from file
    try:
        with open(ciphertext, "r") as file:
            coded_input = file.read()
            print(f"Successfully opened {ciphertext}.")
            print(f"\nCiphertext: {coded_input}")
    except FileNotFoundError:
        print(f"Error: The file {ciphertext} was not found.")
    except Exception as e:
        print(f"An error occurred as trying to read from the file: {e}")

    # Decoding and extracting the information
    data_bytes = base64.b64decode(coded_input)
    IV = data_bytes[:8]
    C = data_bytes[8:]

    print(f"\nIV: {base64.b64encode(IV)}")
    print(f"Ciphertext: {base64.b64encode(C)}")

    # Creating Cipher Object
    deciph = AES.new(K, AES.MODE_CTR, nonce=IV)

    # Decrypt the data
    M = deciph.decrypt(C)
    print(f"\nRecovered Plaintext: {M}\n")

    print("Decryption process finished.")
    decipher_file = input("Enter the name of the recovered text file: ")

    # Store it all in a file
    try:
        with open(decipher_file, "wb") as file:
            file.write(M)
            print(f"Successfully saved in '{decipher_file}'.")
    except FileNotFoundError:
        print("Error: The file was not able to be opened.")
    except Exception as e:
        print(f"There was an error writing into the file: {e}")

    return M


# Ciphering person
def alice():
    print("--- AES Deciphering ---")

    key = input("Enter the name of your textfile containing the key: ")
    ciphertext = input("Enter the name of your textfile containing your ciphertext: ")

    decipher(key, ciphertext)


alice()
