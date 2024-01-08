""" Compute cesar cipher on text """

################################################################
## Copyright(C) 2024, Charles Theetten, <chalimede@proton.me> ##
################################################################

import sys


def cipher_cesar(text, key, n):
    """ cipher_cesar function """
    res = ""

    for letter in text:
        res += key[(key.index(letter) + n) % len(key)]

    return res

def main():
    """main function"""
    text    = sys.argv[1]
    key     = sys.argv[2]
    n       = int(sys.argv[3])

    print(f"\nClear text  : {text}.")
    print(f"\nCipher text : {cipher_cesar(text, key, n)}.\n")


if __name__ == '__main__':
    main()
