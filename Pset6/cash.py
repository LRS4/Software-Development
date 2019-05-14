import cs50


def main():
    while True:
        dollars = cs50.get_float("Change owed: ")
        if dollars > 0:
            break

    # convert to cents
    cents = round(dollars * 100)

    # initialise coin count to zero
    count = 0

    # loop for 25c
    while cents >= 25:
        cents = cents - 25
        count += 1

    # loop for 10c
    while cents >= 10:
        cents = cents - 10
        count += 1

    # loop for 5c
    while cents >= 5:
        cents = cents - 5
        count += 1

    # loop for 1c
    while cents >= 1:
        cents = cents - 1
        count += 1

    return(print(f"{count}"))


if __name__ == "__main__":
    main()