""" Compute chess legend """

################################################################
## Copyright(C) 2024, Charles Theetten, <chalimede@proton.me> ##
################################################################

import sys

def nb_grains_chess(nb_grains):
    """ nb_grains_chess function """
    tmp     = 0
    total   = 0

    for i in range(nb_grains):
        tmp     = 2 ** i
        total   += tmp
        print(f"Case\t {i:2} {tmp:26}")

    return total

def main():
    """main function"""
    nb_cases = int(sys.argv[1])
    print(f"\nNumber of grains on the chessboard: {nb_grains_chess(nb_cases)}.")


if __name__ == '__main__':
    main()
