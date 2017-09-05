from math import log10, floor, sqrt, log

# Arquivos de entrada e saida
infile = "in.dat"
outfile = "out.dat"

# Erro da tensao do osciloscopio, retirado de:
# http://www.ggte.unicamp.br/eam/pluginfile.php/338375/mod_resource/content/1/F%20329%20-%201S%202017%20-%20Aula%209%20-%20Exp%205.pdf
def errTensaoOsc(value, div):
    return 0.03*value + 0.1*div + 1e-3

# Retorna um float apenas com os algarismos significativos
def toSignificant(x):
    return round(x, -int(floor(log10(abs(x)))))

# Abre o arquivo que contem os dados.
with open(infile) as f:
    
    # Abre o arquivo de saida
    with open(outfile, 'w') as o:
        # Escreve o cabeçalho no arquivo de saída
        descStr = "Frequencia (Hz),Vpp1 (V),Vpp2 (V),Tdb (dB)\n"
        print(descStr.replace(',', '\t'))
        o.write(descStr)

        # Le as linhas do aquivo de entrada
        lines = f.readlines()

        # Le e processa cada linha do arquivo de entrada, escrevendo-a no arquivo de saida.
        for line in lines[1:]:
            # Obtem os dados e calcula os erros.
            data = line.split('\t')
            err1 = errTensaoOsc(float(data[2]), float(data[1]))
            err2 = errTensaoOsc(float(data[4]), float(data[3]))

            # Calculo do erro de Tdb(transferencia)
            Tdb = float(data[-1])
            errPart1 = 20/(log(10)*float(data[2]))
            errPart2 = 20/(log(10)*float(data[4]))
            errTdb = sqrt((errPart1*err1)**2 + (errPart2*err2)**2)

            # Formatacao de saida
            sig1 = ".%df" % -int(floor(log10(abs(err1)))) # String pra formatar erro significativo do canal 1
            sig1 = "%" + sig1
            sig2 = ".%df" % -int(floor(log10(abs(err2)))) # String pra formatar erro significativo do canal 2
            sig2 = "%" + sig2
            sigTdb = ".%df" % -int(floor(log10(abs(errTdb)))) # String pra formatar erro significativo do Tdb
            sigTdb = "%" + sigTdb

            # Linha de saida da tabela            
            outLine = ("%f,"+sig1+u"\u00B1"+sig1+","+sig2+u"\u00B1"+sig2+","+sigTdb+u"\u00B1"+sigTdb+"\n") % (float(data[0]),
                                                                                                              float(data[2]),
                                                                                                              toSignificant(err1),
                                                                                                              float(data[4]),
                                                                                                              toSignificant(err2),
                                                                                                              Tdb,
                                                                                                              toSignificant(errTdb))

            # Escreve a linha no arquivo de saida
            print(outLine.replace(',', '\t'))
            o.write(outLine)
