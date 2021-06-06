import sys
import ply
import ply.lex as lex

def setup():
    '''
    Sets lexer up with number tokens

    :returns lexer
    '''
    tokens = (
        'NUMBER',
        'PLUS',
        'MINUS',
        'MULT',
        'DIV',
        'INV',
        'CLR'
        )

    # Tokens
    t_PLUS  = r'\+'
    t_MINUS  = r'\-'
    t_MULT  = r'\*'
    t_DIV  = r'\/'
    t_INV = r'S'
    t_CLR = r'C'
    
    def t_NUMBER(t):
        r'[-]?[0-9]+(\.[0-9]+)?'
        t.value = float(t.value)
        return(t)
        
    # Error handling rule
    def t_error(t):
        t.lexer.skip(1)

    # Analisador lexico
    return lex.lex()

def main(lexer):
    '''
    Runs the lex with python input
    '''

    # pilha
    stack = []

    while True:
        lexer.input(input(''))
        tok = lexer.token()
        if tok == None:     # no more data
            continue
        elif tok.type == 'NUMBER':
            stack.append(tok.value)
        elif tok.type == 'CLR':
            stack = []
        else:
            o1 = stack.pop()
            o2 = stack.pop()
            result = 0
            if tok.type == 'PLUS':
                result = o1 + o2
            elif tok.type == 'MINUS':
                result = o1 - o2
            elif tok.type == 'MULT':
                result = o1 * o2
            elif tok.type == 'DIV':
                result = o1 / o2
            elif tok.type == 'INV':
                result = -o1
                stack.append(o2)
            stack.append(result)
            print(result)

if __name__ == "__main__":
    lexer = setup()
    main(lexer)
