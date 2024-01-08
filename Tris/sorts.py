""" compute sorting algorithms """

################################################################
## Copyright(C) 2024, Charles Theetten, <chalimede@proton.me> ##
################################################################

import random
import sys
from timeit import timeit

SETUP = """
from functools import reduce
from __main__ import bubble_sort
from __main__ import quick_sort
from __main__ import ma
from __main__ import mb
from __main__ import nb
"""


def bubble_sort(elements):
    """ bubble sort algorithm """
    i = len(elements) - 1
    j = 0

    while i > 0:
        while j < i:
            if elements[j] > elements[j + 1]:
                elements[j], elements[j + 1] = elements[j + 1], elements[j]
            j += 1
        j = 0
        i -= 1

def partition(elements, left, right):
    """ partition function """
    i = left - 1
    j = right
    k = elements[right]

    while i < j:
        i += 1
        while elements[i] < k:
            i += 1
        j -= 1
        while j > 0 and elements[j] > k:
            j -= 1
        if i < j:
            elements[i], elements[j] = elements[j], elements[i]
    elements[i], elements[right] = elements[right], elements[i]
    return i

def quick_sort(elements, left, right):
    """ quick sort algorithm """
    pivot = 0

    if left < right:
        pivot = partition(elements, left, right)
        quick_sort(elements, left, pivot - 1)
        quick_sort(elements, pivot + 1, right)

def main():
    """ main function """
    inf_bound   = int(sys.argv[1])
    upp_bound   = int(sys.argv[2])
    list_size   = int(sys.argv[3])
    nb          = int(sys.argv[4])

    ma = random.sample(range(inf_bound, upp_bound), list_size)
    mb = ma[:]
    print(f"Before:  {ma}")
    print(f"Bubble sort: {timeit('bubble_sort(ma)', setup=SETUP, number=nb):.3f}")
    print(f"After:   {ma}\n\n")
    print(f"Before:  {mb}")
    print(f"Quick sort: {timeit('quick_sort(mb, 0, len(mb) - 1)', setup=SETUP, number=nb):.3f}")
    print(f"After:   {mb}")


if __name__ == '__main__':
    main()
