line = input('Enter your sentence : ')
word_list = line.split(' ')
dictionary = dict()

for word in word_list:
  if word in dictionary.keys():
    dictionary[word] = dictionary[word]+1
  else:
    dictionary[word] = 1

print(dictionary)