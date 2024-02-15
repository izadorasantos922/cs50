import re

text = input("Writte a text ");

Lettersregex = r'[a-zA-Zá-úÁ-Ú]+'
lettersArray = re.findall(Lettersregex, text)
result = ''.join(lettersArray);
length = len(result);

sentences_regex = r'[.,;!?]'
text_with_hashtags = re.sub(sentences_regex, '#', text)
qtdy_sentences = text_with_hashtags.count('#')
spaceRegex = r'\b\w+\b'
wordsArray = re.findall(spaceRegex, text)
numberWords = len(wordsArray)
L = length / numberWords) * 100
S = qtdy_sentences/numberWords) * 100
indice = round((0.0588 * L) - (0.296 * S) - 15.8)

print("Grade ", indice, "!")

