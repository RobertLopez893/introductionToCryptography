# Lab 06. AES-CTR
# By: López Reyes José Roberto. 6CV4.

from Crypto.Random import get_random_bytes
import base64


# Generate a random key
def gen_key(bits, filename):
    # Validating a valid AES Key
    if bits not in [128, 192, 256]:
        print(f"Error: {bits} is not a valid AES key size. Please use 128, 192, or 256.")
        return

    # Generate the random key
    key = get_random_bytes(bits // 8)
    encoded_key = base64.b64encode(key)
    # print(f"Key: {key.hex()}")

    # Store the key in a file
    try:
        with open(filename, "wb") as file:
            file.write(encoded_key)
            print(f"Successfully saved in '{filename}'.")
    except FileNotFoundError:
        print("Error: The file was not able to be opened.")
    except Exception as e:
        print(f"There was an error writing into the file: {e}")


# Main Program
def main():
    print("--- Key Generation ---")
    try:
        key_size = input("Enter your key size (in bits): ")
        key_name = input("Enter your filename: ")
        gen_key(int(key_size), key_name)
    except ValueError:
        print(f"There was an error while generating the key.")


main()
