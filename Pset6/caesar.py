from cs50 import get_string
import sys


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python caesar.py number")
    else:
        # get turns of cipher wheel
        turns = int(sys.argv[1])

    # get word from user
    plaintext = get_string("plaintext: ")

    # print ciphertext
    print("ciphertext: ", end='')

    # loop through chars in string add turns, modulo for asci
    for c in plaintext:
        if c.islower() == True:
            cipher = ((ord(c) + turns - 97) % 26 + 97)
            print(chr(cipher), end='')
        elif c.isupper() == True:
            cipher = ((ord(c) + turns - 65) % 26 + 65)
            print(chr(cipher), end='')
    print()


if __name__ == "__main__":
    main()