# python has no do while loop


def main():
    # invoke a infinite loop and break when condition is met
    while True:
        height = int(input("Height: "))
        if height >= 1 and height <= 8:
            break

    for i in range(height):

        # loop for spaces
        spaces = height - 1
        for j in range(spaces - i):
            print(" ", end="")

        # loop for first set of hashes
        for m in range(i + 1):
            print("#", end='')

        print("  ", end='')

        # loop for second set of hashes
        for k in range(i + 1):
            print("#", end="")
        print()


if __name__ == "__main__":
    main()
