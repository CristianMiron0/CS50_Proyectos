while True:
    try:
        userInput = int(input("Height: "))
        if userInput >= 1 and userInput <= 8:
            break

    except ValueError:
        pass

for i in range(1, userInput + 1):
    for j in range(userInput - i):
        print(" ", end="")

    for z in range(0, i):
        print("#", end="")

    print("  ", end="")

    for x in range(0, i):
        print("#", end="")

    print()
