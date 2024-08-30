from cs50 import get_int
import re

def main():
    while True:
        digits = get_int("Card Number: ")

        if len(str(digits)) != 13 and len(str(digits)) != 15 and len(str(digits)) != 16:
            print("INVALID")
            return
        else:
            break

    result = formulaLuhn(digits)
    startCard = 0

    while digits > 100:
        digits = digits // 10
        startCard = digits

    if startCard // 10 == 5 and (0 < startCard % 10 < 6) and result:
        print("MASTERCARD")
    elif startCard // 10 == 3 and (startCard % 10 == 4 or startCard % 10 == 7) and result:
        print("AMEX")
    elif startCard // 10 == 4 and result:
        print("VISA")
    else:
        print("INVALID")



def formulaLuhn(digits):
    sum1 = 0
    sum2 = 0
    total = 0
    x = digits

    while x > 0:
        # Remove last digit and add to sum1
        v1 = x % 10
        x = x // 10
        sum1 += v1

        # Remove second to last and add to sum2
        v2 = x % 10
        x = x // 10

        # Multiply and add the digits
        v2 = v2 * 2
        a1 = v2 % 10
        v2 = v2 // 10
        a2 = v2 % 10
        sum2 = sum2 + a1 + a2

    total = sum1 + sum2

    if total % 10 == 0:
        return True

    return False


main()
