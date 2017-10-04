#
# Rodrigo Seiji Piubeli Hirao
# RA: 186837
#
import argparse
import numpy as np
from prettytable import PrettyTable

def main():
    """ Main function to execute simplex function
    """
    np.seterr(divide='ignore')

    parser = argparse.ArgumentParser(description='simplex - a simpelx solver.')

    parser.add_argument('-i', '--input', 
                        action='store', 
                        help='input test file')
    
    args = parser.parse_args()

    if args.input:
        with open(args.input, 'r') as f:
            objective = list(int(x) for x in
                    f.readline()[:-1].split(';'))

            restrictions = []
            for r in f:
                try:
                    restrictions += [[
                            list(int(x) for x in 
                                r[:-1].split(';')[:len(objective)]),
                            int(r[:-1].split(';')[-1])
                            ]]
                except:
                    pass

            result = simplex(objective, restrictions)
            print(result)

        return 0
    else:
        print('I need an input file. For help type:')
        print('$ python simplex.py --help')
        return 1

def simplex(objective, restrictions):
    """ Calculates simplex

    Args: 
        objetive ([int]): vector containing objective function
        restrictions ([[[int], int]]): matrix containing restrictions equations

    Returns:
        result (int): maximum value of objective function
    """
    return _simplex(_createStandardTable(objective, restrictions))

def _simplex(A):
    """ Calculate simplex from std table

    Args:
        A ([[int]]): std table to work with simplex

    Returns:
        result (int): maximum value of objective function
    """
    h, w = A.shape
    
    col = A.argmin(axis=1)[0]
    row = A[:,w-1]/A[:,col]
    row = np.where(row == np.min(row[row > 0]))[0][0]
    A[row,:] /= A[row,col]
    for i in range(h):
        if i == row:
            continue
        A[i,:] -= A[row,:]*A[i,col]
    if A[0][A[0] < 0].any():
        return _simplex(A)
    else:
        return A[0,w-1]

def _createStandardTable(objective, restrictions):
    """ Creates the std table for simplex operations

    Args: 
        objetive ([int]): vector containing objective function
        restrictions ([[[int], int]]): matrix containing restrictions equations

    Returns:
        A ([[int]]): std table to work with simplex
    """
    objective = [-obj for obj in objective]
    num_variables = len(objective)
    for i in range(len(restrictions)):
        objective += [0]
        restrictions[i][0] += [0 for r in restrictions]
        restrictions[i][0][num_variables + i] = 1
    objective += [0]
    table = np.array([objective] + [r[0] + [r[1]] for r in restrictions])
    
    return table.astype('float')


if __name__ == '__main__':
    main()
