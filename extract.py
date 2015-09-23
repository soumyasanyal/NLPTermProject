import sys
import clang.cindex
from clang.cindex import Index
from clang.cindex import TokenKind
from clang.cindex import CursorKind
from optparse import OptionParser, OptionGroup

def get_info(node):
	if node.get_children() == None:
		depth  = 0
	else:
		depth = -1
		for c in node.get_children():
			depth = max(depth, get_info(c))
	return depth + 1

def find_typerefs(node):
	for myCursor in node.get_children():
		if myCursor.kind == CursorKind.FUNCTION_DECL:
			print "*************************************"
			print "function height:", get_info(myCursor)
			print "*************************************"
		for tok in myCursor.get_tokens():
			if tok.kind != TokenKind.COMMENT:
				print tok.spelling, tok.cursor.kind, tok.kind
			else:
				print "************ITS A COMMENT:IGNORE************"

def main():

	global opts

	parser = OptionParser("usage: %prog [options] {filename} [clang-args*]")
	parser.disable_interspersed_args()
	(opts, args) = parser.parse_args()

	if len(args) == 0:
		parser.error('invalid number arguments')

	index = Index.create()
	tu = index.parse(sys.argv[1])
	print 'Translation unit:', tu.spelling
	# for a in CursorKind.get_all_kinds():
	# 	print a
	find_typerefs(tu.cursor)


if __name__ == '__main__':
	main()
