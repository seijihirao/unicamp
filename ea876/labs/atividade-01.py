import ply.lex as lex

def setup():
    '''
    Sets lexer up with number tokens

    :returns lexer
    '''
    tokens = (
        'EXP',
        'FLOAT',
        'HEX',
        'INT'
    )

    def t_EXP(t):
        r'-?\d\.\d+[eE]-?\d+'
        t.value = float(t.value)
        return t

    def t_FLOAT(t):
        r'-?\d+\.\d+'
        t.value = float(t.value)
        return t

    def t_HEX(t):
        r'-?0[xX][0-9a-fA-F]+'
        t.value = int(t.value, 16)
        return t

    def t_INT(t):
        r'-?\d+'
        t.value = int(t.value)
        return t

    # Error handling rule
    def t_error(t):
        t.lexer.skip(1)

    return lex.lex()


def main(lexer, data):
    '''
    Runs the lex with data as input

    :param data - input data to tokenize
    '''
    lexer.input(data)

    # Tokenize
    while True:
        tok = lexer.token()
        if not tok:
            break
        
        print('%s encontrado, com valor dobrado = %s' % (tok.type, tok.value*2))

#
# Running the progam
#

data = '''
números inteiros positivos e negativos (10, -85, ...);
números em hexadecimal (0xFF, 0X123, ...);
números reais positivos e negativos com ponto decimal (2.765, -3.543, ...);
números com expoentes decimais inteiros (1.56E2, -1.56e-2, ...).
'''

lexer = setup()
main(lexer, data)
