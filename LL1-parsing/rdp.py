import sys
import traceback

class TokenHolder():
    def __init__(self, tokens):
        '''Create a holder for the tokens - basically,
        a list with nice method names. Reverse the list
        to make the processing efficient.
        '''
        tokens = tokens.copy()
        tokens.reverse()
        self.tokens = tokens
    
    def nextToken(self):
        ''' 
        Get the next token if one exists
        '''
        if len(self.tokens) > 0:
            self.tokens.pop()
        else:
            raise Exception("More tokens required but none available")

    def getToken(self):
        return self.tokens[-1]

    def isEmpty(self):
        return len(self.tokens) == 0
        #return len(self.remainingTokens) == 0 and self.token == None

    def displayTokens(self):
        print(self.tokens)


def tokenize(lexemes):
    '''
    Get the types for the lexemes: either quote, parenthesis
    (left or right), or atom for anything else.
    Returns a TokenHolder for parsing.
    '''
    # Make a copy of lexemes
    tokens = list(lexemes)
    nonAtoms = ['(', ')', '\'', None]
    for i in range(len(tokens)):
        if tokens[i] not in nonAtoms:
            tokens[i] = 'atom'
    return TokenHolder(tokens)


def match(expected, tokenHolder):
    '''
    Match the current token against the expected value.
    If successful, change to next token.
    '''
    if tokenHolder.getToken() == expected:
        tokenHolder.nextToken()
    else:
        raise Exception('Parse error: '+ tokenHolder['token'] + " but expected " + expected)

def P(tokenHolder):
    if tokenHolder.getToken() in ['atom','\'', '(']:
        E(tokenHolder)
    else:
        raise Exception('Parse error in P')

def E(tokenHolder): 
    if tokenHolder.getToken() == 'atom':
        match('atom', tokenHolder)
    elif tokenHolder.getToken() == '\'':
        match('\'', tokenHolder)
        E(tokenHolder)
    elif tokenHolder.getToken() == '(':
        match('(', tokenHolder)
        E(tokenHolder)
        Es(tokenHolder)
        match(')', tokenHolder)
    else:
        raise Exception('Parse error in E')

def Es(tokenHolder):
    if tokenHolder.getToken() in ['atom','\'', '(']:
        E(tokenHolder)
        Es(tokenHolder)
    elif tokenHolder.getToken() == ')':
        pass
    else:
        raise Exception('Parse error in Es')

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 rdp.py fileWithStringsToParse.txt")
        print("Parses each line of fileWithStringsToParse.txt separately.")
        sys.exit()

        
    with open(sys.argv[1],'r') as f:
        for line in f:
            # Assumes we can get lexemes based on spaces
            # (this is a hack!)
            lexemes = line.split()
            tokenHolder = tokenize(lexemes)
            try:
                #tokenHolder.nextToken()
                P(tokenHolder)
                if tokenHolder.isEmpty():
                    print("Successfully parsed line: ", line)
                else:
                    raise Exception("Leftover tokens at end of parse")
            except Exception as e:
                print(e)
                print("Error parsing line: ", line)
                print("Current token at error:", tokenHolder.getToken())
                print("All tokens remaining to process at error:")
                tokenHolder.displayTokens()

            


if __name__ =='__main__':
    main()