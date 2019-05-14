from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # TODO
    a_lines = set(a.split("\n"))
    b_lines = set(b.split("\n"))

    return a_lines & b_lines


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    a_sentences = set(sent_tokenize(a))
    b_sentences = set(sent_tokenize(b))

    return a_sentences & b_sentences


def find_substrings(str, n):
    substrings = []

    for i in range(len(str) - n + 1):
        substrings.append(str[i:i + n])

    return substrings


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO
    a_substrings = set(find_substrings(a, n))
    b_substrings = set(find_substrings(b, n))

    return a_substrings & b_substrings
