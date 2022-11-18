import sys
import traceback 

class Tree:
    '''
    (You'll use this if you add in the parse tree creation.)
    '''
    def __init__(self, item):
        self.item = item
        self.children = []

    def addFirstChild(self, child):
        self.children.insert(0, child)

    def __repr__(self):
        s = self.item
        if len(self.children) > 0:
            s += ' '
            s += repr(self.children)
        return s


def tokenize(lexemes):
    '''
    Get the types for the lexemes: either quote, parenthesis
    (left or right), or atom for anything else.
    Returns a list of these types, which we'll use for the
    actual parsing.
    '''
    # Make a copy of lexemes
    tokens = list(lexemes)
    nonAtoms = ['(', ')', '\'', None]
    for i in range(len(tokens)):
        if tokens[i] not in nonAtoms:
            tokens[i] = 'atom'
    return tokens

def parse(parseStack, tokens, table):
    tokens = tokens.copy() # Avoid destroying the original list
    tree = Tree(parseStack[-1])
    treeStack = [tree] # Track what subtree we'll be adding to
    while len(parseStack) > 0:
        if len(tokens) == 0:
            raise Exception("No tokens remaining but parse stack is not empty.")
        elif parseStack[-1] in table:
            # Current thing is a non-terminal: predict
            nonTerminal = parseStack.pop()
            if tokens[-1] not in table[nonTerminal]:
                raise Exception("Parse error: predicting for " + nonTerminal + " with terminal " + tokens[-1] + " but no rules.")
            rule = table[nonTerminal.strip()][tokens[-1].strip()]
            
            # Prediction step adds to the tree
            subtreeToAddTo = treeStack.pop()
            for i in range(len(rule)-1, -1, -1):
                parseStack.append(rule[i])
                newSubtree = Tree(rule[i]) 
                subtreeToAddTo.addFirstChild(newSubtree) 
                if rule[i] in table:
                    # non-terminal: add to the tree stack as something 
                    # we'll need to add children to
                    treeStack.append(newSubtree)
        else:
            # Current thing is a terminal: match
            if parseStack[-1] != tokens[-1]:
                raise Exception("Parse error: matching " + parseStack[-1] + " but next token is " + tokens[-1])
            parseStack.pop()
            tokens.pop()
    if len(tokens) > 0:
        raise Exception("Finished parse stack but still have tokens: " + str(tokens))
    return tree


def readTable(tableFile):
    '''
    Return the start symbol and a dictionary representing the
    grammar table in table file.
    '''
    table = {}
    startSymbol = None
    with open(tableFile) as f:
        for line in f:
            if len(line.strip()) > 0 and not line.startswith("#"):
                splitLine = line.split()

                if line.startswith("start"):
                    # gives the start symbol
                    startSymbol = splitLine[1]
                else:
                    # Table line: 1st is non-terminal, 2nd terminal, remaining are the rule
                    if splitLine[0] not in table:
                        table[splitLine[0]] = {}
                    table[splitLine[0]][splitLine[1]] = splitLine[2:]
    return startSymbol, table


def main():
    if len(sys.argv) < 3:
        print("Usage: python3 tableParser.py table.txt fileWithStringsToParse.txt")
        print("Parses each line of fileWithStringsToParse.txt separately.")
        sys.exit()

    startSymbol, table = readTable(sys.argv[1])

    with open(sys.argv[2],'r') as f:
        for line in f:
            # Assumes we can get lexemes based on spaces
            # (this is a hack!)
            lexemes = line.split()
            tokens = tokenize(lexemes)
            tokens.append("$")#end of string
            tokens.reverse() # popping from the end is faster so we reverse
            parseStack = []
            parseStack.append("$")
            parseStack.append(startSymbol)
            try:
                #Exception will be raised by parse if there was an error
                tree = parse(parseStack, tokens, table)
                print("Successfully parsed line: ", line.strip())
                print(tree,"\n")
            except Exception as e:
                print(e)
                print("Error parsing line: ", line)

            


if __name__ =='__main__':
    main()

