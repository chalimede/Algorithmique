""" Perform some base conversions """

################################################################
## Copyright(C) 2024, Charles Theetten, <chalimede@proton.me> ##
################################################################

import sys


def base_binary(n):
    """ base_binary function """
    res = "0" if n == 0 else ""

    while n > 0:
        res += str(n % 2)
        n //= 2

    return res[::-1]

def base_n(n, base):
    """ base_binary function """
    res = ""
    ind = len(base)

    while n > 0:
        res += base[n % ind]
        n //= ind

    return res[::-1]

def main():
    """main function"""
    if len(sys.argv) == 2:
        n = int(sys.argv[1])
        print(f"\nConversion de {n} en base 2 : {base_binary(n)}.\n")
    else:
        n    = int(sys.argv[1])
        base = sys.argv[2]
        print(f"\nConversion de {n} en base {len(base)} : {base_n(n, base)}.\n")


if __name__ == '__main__':
    main()
