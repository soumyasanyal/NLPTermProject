import itertools
import nltk
from nltk import word_tokenize
from nltk.util import ngrams

#read the code file
with open("codeFile.txt","r") as codeFile:
	codeData = codeFile.readlines()

#read the keywords file
with open("keywords.txt","r") as keyFile:
	keyData = keyFile.readlines()

#create code string from list
codeString = "".join(codeData)

#create key string from list
keyString = "".join(keyData)

#tokenize code Data
codeToken = nltk.word_tokenize(codeString)

#tokenize key data
keyToken = nltk.word_tokenize(keyString)

#new list of code tokens without any punctuations
newCodeToken = []

#get only keywords stream from the codeToken
for word in codeToken:
	if word.isalnum() and word in keyToken:
		newCodeToken.append(word)

#ngrams for code data
codeUnigrams = ngrams(newCodeToken,1)
codeBigrams = ngrams(newCodeToken,2)
codeTrigrams = ngrams(newCodeToken,3)

# #make code data ngram compiled list
# it1 = iter(codeUnigrams)
# it2 = iter(codeBigrams)
# it3 = iter(codeTrigrams)
# codeNgrams = itertools.chain(it1, it2, it3)

#make and populate ngrams dictionary
keyDictUni = {}
keyDictBi = {}
keyDictTri = {}
for key in codeUnigrams:
	if keyDictUni.has_key(key):
		keyDictUni[key] += 1
	else:
		keyDictUni[key] = 1;

for key in codeBigrams:
	if keyDictBi.has_key(key):
		keyDictBi[key] += 1
	else:
		keyDictBi[key] = 1;

for key in codeTrigrams:
	if keyDictTri.has_key(key):
		keyDictTri[key] += 1
	else:
		keyDictTri[key] = 1;

#print all ngrams
for key in keyDictUni:
	print key , "->", keyDictUni[key]

for key in keyDictBi:
	print key , "->", keyDictBi[key]

for key in keyDictTri:
	print key , "->", keyDictTri[key]
