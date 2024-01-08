""" Compute postfix expressions """

################################################################
## Copyright(C) 2024, Charles Theetten, <chalimede@proton.me> ##
################################################################

import re
import sys


def calculate(operator, op_x, op_y):
    """ calculate function """
    cases = {
        "+": lambda a, b: a + b,
        "-": lambda a, b: a - b,
        "*": lambda a, b: a * b,
        "/": lambda a, b: a / b,
    }

    return cases[operator](op_x, op_y)

def postfix(expression):
    """ postfix function """
    res         = 0
    stack       = []
    elements    = re.split(r"\s+", expression)

    for elem in elements:
        if re.match("^[-+\\/*()]$", elem):
            op1 = stack.pop()
            op2 = stack.pop()
            res = calculate(elem, int(op2), int(op1))
            stack.append(res)
        else:
            stack.append(elem)

    return res

def main():
    """main function"""
    expression = sys.argv[1]
    print(postfix(expression))


if __name__ == '__main__':
    main()
