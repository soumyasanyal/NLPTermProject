import sys
import re
import os
import clang.cindex
from clang.cindex import Index
from clang.cindex import TokenKind
from clang.cindex import CursorKind
from optparse import OptionParser, OptionGroup
from nltk import word_tokenize
from nltk.util import ngrams
import sys, getopt
from os import listdir
from os.path import isfile, join

class STagger():

	def __init__(self, fileName):
		self.filename = fileName
		self.tagged = []
		self.unigrams = []
		self.tu = None
		self.tagger(fileName)
	
	#function to get the height of a subtree rooted at node
	#This function can be used to print the height of a FUNCTION_DECL node which helps to
	#distinguish between function declarations and function definitions
	#Mostly, by default the function declaration is of height 2
	def getHeight(self, node):
		if node.get_children() == None:		#leaf node
			depth  = 0
		else:
			depth = -1
			for c in node.get_children():
				depth = max(depth, getHeight(c))
		return depth + 1

	#function to print the token kinds found in the given input c code
	#the removeIdentifiers is a boolean flag to be set by the user
	def find_typerefs(self, removeIdentifiers):
		node = self.tu.cursor 	#root node
		for myCursor in node.get_children():
			for tok in myCursor.get_tokens():
				if tok.kind == TokenKind.KEYWORD:
					self.tagged.append([tok.spelling, tok.cursor.kind, tok.kind])
				if tok.kind == TokenKind.IDENTIFIER and not removeIdentifiers:
					self.tagged.append([tok.spelling, tok.cursor.kind, tok.kind])

	#function to print the bigrams tokens found in the given input c code
	#the removeIdentifiers is a boolean flag to be set by the user
	def find_unigrams(self, removeIdentifiers, toDump = False):
		node = self.tu.cursor 	#root node
		for myCursor in node.get_children():
			for tok in myCursor.get_tokens():
				if tok.kind == TokenKind.KEYWORD:
					self.unigrams.append(tok.spelling)
				if tok.kind == TokenKind.IDENTIFIER and not removeIdentifiers:
					self.unigrams.append("identifier")
		if toDump:
			pattern = re.compile("^[(/\w)*]*/")
			m = pattern.match(self.filename)
			folderName = m.group()
			if not os.path.exists(folderName + "dump/"):
				os.mkdir(folderName + "dump/")
			fileName = folderName + "dump/" + self.filename[m.end() : len(self.filename)] + ".dump"
			f = open(fileName, "w")
			for x in self.unigrams:
				f.write(x + "\n")
			f.close()


	#set removeIdentifiers true -> dont keep identifiers
	def tagger(self, fileName):
		#create a index
		index = Index.create()
		#get translation unit for traversal of AST
		self.tu = index.parse(fileName)

#fetches the files from the given directory
class FetchNExecute():

	def __init__(self):
		self.onlyfiles = []

	def parseArgsNExecute(self):
		try:
			opts, args = getopt.getopt(sys.argv[1:], "f:i:t:",["folder=", "file=", "testFolder="])
		except getopt.GetoptError:
			print 'Error'
			sys.exit(2)

		inputfile = ""
		inputfolder = ""
		for opt, arg in opts:
			if opt in ("-f" , "--folder"):
				inputfolder = arg
		 		tempLlist = [ f for f in listdir(inputfolder) if isfile(join(inputfolder,f))]
		 		for t in tempLlist:
		 			t = inputfolder + "/" + t
		 			self.onlyfiles.append(t)
		 		model = LangModel()
				model.trainModel(self.onlyfiles)
		 	elif opt in ("-t" , "--testFolder"):
				inputfolder = arg
		 		tempLlist = [ f for f in listdir(inputfolder) if isfile(join(inputfolder,f))]
		 		f = open(".confFile", "w")
		 		for t in tempLlist:
		 			t = inputfolder + "/" + t
		 			self.onlyfiles.append(t)
		 			stag = STagger(t)
		 			stag.find_unigrams(True, True)
		 			f.write(t + "\n")
		 		f.write("corpus.txt\n")
		 		f.close()

			# elif opt in ("-i" , "--file"):
			# 	inputfile = arg;
		 # 		self.onlyfiles.append(inputfile)
		return self.onlyfiles

#trains a language model from the code files
class LangModel():

	def __init__(self):
		pass

	def trainModel(self, listOfFilenames):
		#dictionary of unigrams, bigrams, trigrams
		unigramDict = dict()
		bigramDict = dict()
		trigramDict = dict()

		#total count of unigrams, bigrams, trigrams
		countUni = 0
		countBi = 0
		countTri = 0

		i = 1
		#iterate over list of files
		for fileName in listOfFilenames:
			print "Reading", i
			i += 1
			stag = STagger(fileName)
			stag.find_unigrams(True, False)
			for item in stag.unigrams:
				countUni += 1
				if item not in unigramDict:
					unigramDict[item] = 1
				else:
					unigramDict[item] += 1
			codeBigrams = ngrams(stag.unigrams, 2)
			codeTrigrams = ngrams(stag.unigrams, 3)
			for item in codeBigrams:
				countBi += 1
				if item not in bigramDict:
					bigramDict[item] = 1
				else:
					bigramDict[item] += 1
			for item in codeTrigrams:
				countTri += 1
				if item not in trigramDict:
					trigramDict[item] = 1
				else:
					trigramDict[item] += 1

		
		#write the ngrams to the file
		outputFile = open('corpus.txt', 'w')
		outputFile.write(str(countUni) + "\n")
		for key, x in unigramDict.iteritems():
			outputFile.write(str(key) + " " + str(x) + "\n")

		outputFile.write(str(countBi) + "\n")
		for key, x in bigramDict.iteritems():
			outputFile.write(str(key[0]) + " "  + str(key[1]) + " " + str(x) + "\n")

		outputFile.write(str(countTri) + "\n")
		for key, x in trigramDict.iteritems():
			outputFile.write(str(key[0]) + " " + str(key[1]) + " " + str(key[2]) + " " + str(x) + "\n")

		outputFile.close()

#kind of main function
def main():
	tempClass = FetchNExecute()
	tempClass.parseArgsNExecute()

if __name__ == '__main__':
	main()