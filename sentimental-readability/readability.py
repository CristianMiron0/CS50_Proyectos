from cs50 import get_string

def main():
    text = get_string("Text: ")

    letters = numberLetters(text)
    words = numberWords(text)
    sentences = numberSentences(text)

    L = (float(letters) / float(words)) * 100
    S = (float(sentences) / float(words)) * 100

    result = 0.0588 * L - 0.296 * S - 15.8
    result = round(result)

    if result <= 1:
        print("Before Grade 1")
    elif result >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {result}")


def numberLetters(sentence):
    total = 0

    for char in sentence:
        if char.isalpha():
            total += 1
        else:
            continue

    return total



def numberWords(sentence):
    total = 0

    for char in sentence:
        if char == " ":
            total += 1
        else:
            continue

    return total + 1



def numberSentences(sentence):
    total = 0

    for char in sentence:
        if char in ".?!":
            total += 1
        else:
            continue

    return total



main()
