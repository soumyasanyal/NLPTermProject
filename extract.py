import sys
import clang.cindex
from clang.cindex import Index
from clang.cindex import TokenKind
from clang.cindex import CursorKind
from optparse import OptionParser, OptionGroup

CGRN = "\x1B[32m"	#green color output
CNRM = "\x1B[0m"	#normal output

#function to get the height of a subtree rooted at node
def getHeight(node):
	if node.get_children() == None:		#leaf node
		depth  = 0
	else:
		depth = -1	#we need max of the heights of subtrees
		for c in node.get_children():
			depth = max(depth, getHeight(c))
	return depth + 1

#function to print the token kinds found in the given input c code
#This fumction also prints the height of a FUNCTION_DECL node which helps to
#distinguish between function declaarations and function definitions
#Mostly, by default the function declaration is of height 2
def find_typerefs(node):
	for myCursor in node.get_children():
		if myCursor.kind == CursorKind.FUNCTION_DECL:
			print "*************************************"
			print "function height:", getHeight(myCursor)
			print "*************************************"
		for tok in myCursor.get_tokens():
			if tok.kind != TokenKind.COMMENT:
				print tok.spelling, tok.cursor.kind, tok.kind
			#uncheck the below to get notified about comments too
			# else:
			# 	print "************ITS A COMMENT:IGNORE************"

#kind of main function
def main():

	#user interface: gives directions of usage
	parser = OptionParser("usage: %prog [options] {filename} [clang-args*]")
	parser.disable_interspersed_args()
	(opts, args) = parser.parse_args()

	if len(args) == 0:
		parser.error('invalid number arguments')

	#create a index
	index = Index.create()
	#get translation unit for traversal of AST
	tu = index.parse(sys.argv[1])
	print 'Translation unit:', tu.spelling
	find_typerefs(tu.cursor)	#passing root node


if __name__ == '__main__':
	main()
