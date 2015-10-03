from math import *
from operator import *
from nltk import word_tokenize
from nltk.util import ngrams

#Kl divergence 
# Finds KL diveregence for 2 probability 
# distributions
def get_KL(p,q):
	kl = 0 ;
	for i,item in p.iteritems():
		if( i not in q ):
			kl = kl + 0 ; 
		else:
			kl = kl + p[i]*log(p[i]/q[i],2) + q[i]*log(q[i]/p[i],2) ; 
	return kl;

#This is fallback function for finding suitable measure for comparing n-grams
# Here, if we have some positive value for trigram we directly consider it 
# else we consider weighted bigram and if bigram is also zero then we fall 
# back to weighted unigram.
def fallback(uniKL,biKL,triKL):
	w1 = 1;
	w2 = 0.75;
	w3 = 0.5;
	if(triKL != 0):
		return w1*triKL ;
	if(biKL != 0):
		return w2*biKL ;
	else:
		return w3*uniKL ;

#Returns Unigram, Bigram and Trigram Probabilities for given 
#codeFile
def getNgramProbs(file):
	f = open(file,'r');
	unigramList = [] ;
	for line in f.read().split():
		unigramList.append( line );

	bigramList = ngrams(unigramList, 2);
	trigramList = ngrams(unigramList, 3);

	#dictionary of unigrams, bigrams, trigrams
	unigramDict = dict()
	bigramDict = dict()
	trigramDict = dict()

	#Counts for Unigrams
	countUni = 0 ;
	for item in unigramList:
		countUni += 1
		if item not in unigramDict:
			unigramDict[item] = 1
		else:
			unigramDict[item] += 1

	#Counts for Bigram
	for item in bigramList:
		if item not in bigramDict:
			bigramDict[item] = 1
		else:
			bigramDict[item] += 1

	#Counts for Trigrams
	for item in trigramList:
		if item not in trigramDict:
			trigramDict[item] = 1
		else:
			trigramDict[item] += 1

	#Probabilities for Trigrams
	for key,item in trigramDict.iteritems():
		trigramDict[key] /= float(bigramDict[(key[0],key[1])]) ; 

	#Probabilities for Bigrams
	for key,item in bigramDict.iteritems():
		bigramDict[key] /= float(unigramDict[key[0]]) ; 

	#Probabilities for Unigrams
	for key,item in unigramDict.iteritems():
		unigramDict[key] /= float(countUni) ; 

	# print "***** Unigrams";
	# for key,item in unigramDict.iteritems():
	#     print str(key) + ' ' + str(item) ;
	# print "***** Bigrams";
	# for key,item in bigramDict.iteritems():
	#     print str(key) + ' ' + str(item) ;
	# print "***** Trigrams";
	# for key,item in trigramDict.iteritems():
	#     print str(key) + ' ' + str(item) ;
	
	return [unigramDict,bigramDict,trigramDict];

#this is function for parsing and finding probabilities 
#for the generous language model
def getGenModel(file):
	ipFile = open(file);

	unigramDict = dict(); 
	bigramDict = dict();
	trigramDict = dict();

	ipFileLine = ipFile.readline()
	UnigramCount = int(ipFileLine)
	tempCount = 0
	while tempCount < UnigramCount:
		ipFileLine = ipFile.readline()
		words = ipFileLine.split()
		unigramDict[words[0]] = float(words[1]) ;
		tempCount += int(words[1])

	ipFileLine = ipFile.readline()
	BigramCount = int(ipFileLine)
	tempCount = 0
	while tempCount < BigramCount:
		ipFileLine = ipFile.readline()
		words = ipFileLine.split()
		bigramDict[(words[0],words[1])] = float(words[2]);
		tempCount+=int(words[2])

	ipFileLine=ipFile.readline()
	TrigramCount=int(ipFileLine)
	tempCount=0
	while tempCount<TrigramCount:
		ipFileLine=ipFile.readline()
		words=ipFileLine.split()
		trigramDict[(words[0],words[1],words[2])] = float(words[3]);
		tempCount+=int(words[3])

	#Probabilities for Trigrams
	for key,item in trigramDict.iteritems():
		trigramDict[key] /= float(bigramDict[(key[0],key[1])]) ; 

	#Probabilities for Bigrams
	for key,item in bigramDict.iteritems():
		bigramDict[key] /= float(unigramDict[key[0]]) ; 

	#Probabilities for Unigrams
	for key,item in unigramDict.iteritems():
		unigramDict[key] /= float(UnigramCount) ; 

	# print "***** Unigrams";
	# for key,item in unigramDict.iteritems():
	#     print str(key) + ' ' + str(item) ;
	# print "***** Bigrams";
	# for key,item in bigramDict.iteritems():
	#     print str(key) + ' ' + str(item) ;
	# print "***** Trigrams";
	# for key,item in trigramDict.iteritems():
	#     print str(key) + ' ' + str(item) ;

	return [unigramDict,bigramDict,trigramDict] ;

def main():
	
	#the inputs here are the Genral model and keyword listing of two codefiles
	f = open(".confFile", "r")
	[uni1,bi1,tri1] = getNgramProbs(f.readline()[:-1]);
	[uni2,bi2,tri2] = getNgramProbs(f.readline()[:-1]);
	[uni3,bi3,tri3] = getGenModel(f.readline()[:-1]);

	#KL divergence for each feature in file 1 and file 2
	uniKL = get_KL(uni1,uni2) ;
	biKL = get_KL(bi1,bi2) ;
	triKL = get_KL(tri1,tri2) ;

	#KL divergence for each feature in file 2 and Genearal Model
	uniKL0 = get_KL(uni3,uni2) ;
	biKL0 = get_KL(bi3,bi2) ;
	triKL0 = get_KL(tri3,tri2) ;

	print('uniKL '+str(uniKL)+' biKL '+str(biKL)+' triKL '+str(triKL));
	print('uniKL '+str(uniKL0)+' biKL '+str(biKL0)+' triKL '+str(triKL0));
	total =  fallback(uniKL,biKL,triKL);
	total0 =  fallback(uniKL0,biKL0,triKL0);
	print('So, Here we are \nKL Diveregence in file 1 and file 2 : '+str(total)+'\nKL Diveregence in file 2 and general Model : '+str(total0));
	return ;

if __name__ == '__main__':
	main();




