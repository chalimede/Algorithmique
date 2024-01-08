""" Convert infix expression to postfix expression """

################################################################
## Copyright(C) 2024, Charles Theetten, <chalimede@proton.me> ##
################################################################

import re
import sys


def infix_postfix(expression):
    """ infix_postfix function """
    res         = 0
    stack       = []

    for elem in expression:
        if re.match("[0-9]", elem):
            res += elem
        elif re.match("[-+\\/*]", elem):
            res += ' '
            stack.append(elem)
        elif elem == ')':
            res += ' '
            res += stack.pop()
    while stack:
        res += ' '
        res += stack.pop()

    return res

def main():
    """main function"""
    expression = sys.argv[1]
    print(infix_postfix(expression))


if __name__ == '__main__':
    main()
