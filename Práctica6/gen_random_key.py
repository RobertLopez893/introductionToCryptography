# Lab 06. AES-CTR
# By: López Reyes José Roberto. 6CV4.

from Crypto.Random import get_random_bytes
import base64


# Generate a random key
def gen_key(bits):
    key = get_random_bytes(bits // 8)
    encoded_key = base64.b64encode(key)
    print(f"Key: {key.hex()}")

    # Store the key in a file
    try:
        with open("key.txt", "w") as file:
            file.write(encoded_key.decode('utf-8'))
            print("Successfully saved in 'key.txt'.")
    except FileNotFoundError:
        print("Error: The file was not able to be opened.")
    except Exception as e:
        print(f"There was an error writing into the file: {e}")


print("\n128 bits:")
gen_key(128)

print("\n192 bits:")
gen_key(192)

print("\n256 bits:")
gen_key(256)
