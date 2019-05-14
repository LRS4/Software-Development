from cs50 import get_string
import sys

# a program to read in a list of banned words and apply them to user input 
# this will turn banned words into stars i.e. darn into ****

def main():

    # if less than two arguments exit
    if len(sys.argv) != 2:
        sys.exit("Usage: python bleep.py dictionary")

    # get banned words file
    banned_words = sys.argv[1]

    # open file
    file = open(banned_words, "r")

    # create set for storage
    words = set()

    # store file contents in the set 'words' (unordered and static)
    for line in file:
        words.add(line.rstrip("\n"))

    # get a message
    message = get_string("What would you like to censor?\n")

    # split message into words
    message = message.split()

    # iterate over each word in message
    for i in message:

        # set a counter on loop
        count = 0

        # iterate over words in set
        for j in words:

            # if the word in the message is in the banned list set count to 1
            # and take the length of the word
            if i in j:
                count += 1
                n = len(j)

        # if the count equals 1 replace that word with * the length of the word and a space
        if count == 1:
            print(j.replace(j, "*" * n), end=" ")

        # else print the word and a space
        else:
            print(i, end=" ")

    # print return to finish
    print("")


if __name__ == "__main__":
    main()
