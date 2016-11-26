"""
Esse arquivo tinha como objetivo desenvolver um algoritmo de sort
A partir de uma inteligência artificial

Infelizmente o objetivo do lab é encontrar o tempo de um algoritmo que funcione sempre
Enquanto a AI só funciona em x% dos casos
"""

import numpy as np
import neurolab as nl
import numpy.random as rand

def main():
    my_input = np.array([[]])
    my_target = np.array([sorted(x) for x in my_input])

    net = nl.net.newc(nl.tool.minmax(my_input), 25)

    error = net.train(my_input, my_target, epochs=1000, show=1)

    import pylab as pl
    pl.title('Classification Problem')
    pl.plot(error)
    pl.xlabel('Epoch number')
    pl.ylabel('error (default MAE)')
    pl.show()

if __name__ == '__main__':
    main()