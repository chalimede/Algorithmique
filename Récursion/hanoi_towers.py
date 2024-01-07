""" compute hanoi Towers algorithm """

################################################################
## Copyright(C) 2024, Charles Theetten, <chalimede@proton.me> ##
################################################################

import sys


def hanoi_iterative(towers):
    """ hanoi_iterative function """
    stack = []
    steps = 0
    stack.append(towers)

    while stack:
        action          = stack.pop()
        disks           = action["disks"]
        start           = action["s"]
        end             = action["e"]
        tmp             = action["i"]
        if disks == 1:
            print(f"{disks}   {start} -> {end}   {tmp}")
            steps += 1
        else:
            stack.append({ "disks" : disks - 1, "s" : tmp, "e" : end, "i" : start })
            stack.append({ "disks" : 1, "s" : start, "e" : end, "i" : tmp })
            stack.append({ "disks" : disks - 1, "s" : start, "e" : tmp, "i" : end })

    return steps

def hanoi_recursive(disks, start, end, tmp):
    """ hanoi_recursive function """
    if disks > 0:
        hanoi_recursive.steps += 1
        hanoi_recursive(disks - 1, start, tmp, end)
        print(f"{disks}   {start} -> {end}   {tmp}")
        hanoi_recursive(disks - 1, tmp, end, start)

    return hanoi_recursive.steps

def main():
    """ main function """
    nb_disks                 = int(sys.argv[1])
    hanoi_recursive.steps = 0

    print("\nAlgorithme récursif des tours de Hanoi :\n\n")
    res = hanoi_recursive(nb_disks, 1, 3, 2)
    print(f"\nNombre de déplacements : {res}.")
    print("\n--------------------\n")
    print("\nAlgorithme itératif des tours de Hanoi :\n\n")
    res = hanoi_iterative({ "disks" : nb_disks, "s" : 1, "e" : 3, "i" : 2 })
    print(f"\nNombre de déplacements : {res}.")


if __name__ == "__main__":
    main()
