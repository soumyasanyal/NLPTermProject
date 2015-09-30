import sys
import clang.cindex
import numpy
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
	def find_unigrams(self, removeIdentifiers):
		node = self.tu.cursor 	#root node
		for myCursor in node.get_children():
			for tok in myCursor.get_tokens():
				if tok.kind == TokenKind.KEYWORD:
					self.unigrams.append(tok.spelling)
				if tok.kind == TokenKind.IDENTIFIER and not removeIdentifiers:
					self.unigrams.append("identifier")

	#set removeIdentifiers true -> dont keep identifiers
	def tagger(self, fileName):
		#create a index
		index = Index.create()
		#get translation unit for traversal of AST
		self.tu = index.parse(fileName)

def getFileList():
	# print 'Usage: python prog.py -f folder1 -f folder2 -i file1.c'
	# print 'Number of arguments:', len(sys.argv), 'arguments.'
	# print 'Argument List:', str(sys.argv)

	try:
		opts, args = getopt.getopt(sys.argv[1:], "f:i:",["folder=", "file="])
		# print opts
		# print sys.argv[1:]
	except getopt.GetoptError:
		print 'Error'
		sys.exit(2)

	inputfile = ""
	inputfolder = ""
	onlyfiles = []
	for opt, arg in opts:
		if opt in ("-f" , "--folder"):
			inputfolder = arg
	 		tempLlist = [ f for f in listdir(inputfolder) if isfile(join(inputfolder,f))]
	 		for t in tempLlist:
	 			t = inputfolder + "/" + t
	 			onlyfiles.append(t)
		elif opt in ("-i" , "--file"):
			inputfile = arg;
	 		onlyfiles.append(inputfile)
	# print "Folder: ",inputfolder
	# print "File: ",inputfile
	# print str(onlyfiles)
	return onlyfiles
		
#kind of main function
def main():
	#global dictionary to contain id of newfound Keywords
	DictOfKeywords = dict()
	#used to index the newfound keywords
	indexCount = 0

	#dictionary of unigrams
	unigramDict = dict()

	# listOfFilenames = getFileList()
	listOfFilenames = ['code.c', 'code2.c']

	#total count of tokens
	countTokens = 0

	#iterate over list of files
	for fileName in listOfFilenames:
		stag = STagger(fileName)
		stag.find_unigrams(True)
		for item in stag.unigrams:
			countTokens += 1
			if item not in DictOfKeywords:
				unigramDict[item] = 1
				DictOfKeywords[item] = indexCount
				indexCount += 1
			else:
				unigramDict[item] += 1
		#upper for needs to run completely once to get proper id of each word

	# print countTokens
	for key, x in unigramDict.iteritems():
		print key, x
	
	# length = len(DictOfKeywords)
	# bigramArr = numpy.zeros((length, length))
	# trigramArr = numpy.zeros((length, length, length))
	# codeBigrams = ngrams(stag.unigrams, 2)
	# codeTrigrams = ngrams(stag.unigrams, 3)
	# for word in codeBigrams:
	# 	first = word[0]
	# 	second = word[1]
	# 	id1 = DictOfKeywords[first]
	# 	id2 = DictOfKeywords[second]
	# 	bigramArr[id1][id2] += 1


	# s = ""
	# s = str(DictOfKeywords.keys())
	# s = s[1:len(s) - 1] + "\n"
	# for x in range(length):
	# 	for y in range(length):
	# 		s += "%d," % (bigramArr.item((x, y)))
	# 	s = s[:len(s) - 3] + "\n"
	# print s



if __name__ == '__main__':
	main()