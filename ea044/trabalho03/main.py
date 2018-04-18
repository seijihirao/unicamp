#
# Rodrigo Seiji P. Hirao
# RA.: 186837
#
import numpy as np
import random
from math import sin

def travellingSalesman():
    """ Execute travelling salesman problem
        with meta-heuristic solution
    """
    W, X, Y, Z = 6, 8, 3, 7
    graph = np.matrix([[0 for j in range(18)] for i in range(18)])
    graph[0,1]  = graph[1,0]  = 30+Y
    graph[0,7]  = graph[7,0]  = 29
    graph[0,11] = graph[11,0] = 30+Z
    graph[0,12] = graph[12,0] = 37
    graph[1,2]  = graph[2,1]  = 10+W
    graph[1,7]  = graph[7,1]  = 28
    graph[1,11] = graph[11,1] = 39
    graph[2,3]  = graph[3,2]  = 20+X
    graph[2,7]  = graph[7,2]  = 30
    graph[2,12] = graph[12,2] = 54
    graph[3,4]  = graph[4,3]  = 39
    graph[3,5]  = graph[5,3]  = 32
    graph[3,6]  = graph[6,3]  = 20+Y
    graph[3,8]  = graph[8,3]  = 20+Z
    graph[3,9]  = graph[9,3]  = 33
    graph[3,13] = graph[13,3] = 56
    graph[4,5]  = graph[5,4]  = 12
    graph[4,6]  = graph[6,4]  = 26
    graph[4,9]  = graph[9,4]  = 19
    graph[5,6]  = graph[6,5]  = 17
    graph[5,10] = graph[10,5] = 30
    graph[6,10] = graph[10,6] = 30+Z
    graph[7,11] = graph[11,7] = 25
    graph[7,12] = graph[12,7] = 20+W
    graph[8,9]  = graph[9,8]  = 26
    graph[8,12] = graph[12,8] = 34
    graph[8,13] = graph[13,8] = 20+Y
    graph[8,15] = graph[15,8] = 43
    graph[9,10] = graph[10,9] = 24
    graph[9,13] = graph[13,9] = 30
    graph[9,14] = graph[14,9] = 19
    graph[10,14]= graph[14,10]= 20+W
    graph[10,17]= graph[17,10]= 36
    graph[11,12]= graph[12,11]= 27
    graph[11,15]= graph[15,11]= 20+X
    graph[12,13]= graph[13,12]= 24
    graph[12,15]= graph[15,12]= 19
    graph[13,14]= graph[14,13]= 20
    graph[13,15]= graph[15,13]= 20+Y
    graph[13,16]= graph[16,13]= 17
    graph[14,16]= graph[16,14]= 18
    graph[14,17]= graph[17,14]= 20+X
    graph[15,16]= graph[16,15]= 26
    graph[16,17]= graph[17,16]= 10+W
    
    paths = [[] for i in range(18)]
    for i in range(18):
        paths.append([])
        for j in range(18):
            if graph[i, j] != 0:
                paths[i].append(j)
    
    objective = {
        'path': [0, 11, 15, 16, 17],
        'weight': 30+Z + 20+X + 26 + 10+W
    }

    for i in range(10000):
        cur_path = [0]
        cur_weight = 0
        cur_city = 0
        while cur_city != 17:
            next_city = random.choice(paths[cur_city])
            cur_path.append(next_city)
            cur_weight += graph[cur_city, next_city]
            cur_city = next_city
            if cur_weight > objective['weight']:
                break
        if cur_weight < objective['weight']:
            objective['path'] = cur_path
            objective['weight'] = cur_weight
    
    return objective

def optimization():
    objective = {
        'x': 10,
        'y': 10,
        'z': 10,
        'result': 50 + 100 + 100 + 5*sin(300)
    }

    for i in range(10000):
        x = random.uniform(-10, 10)
        y = random.uniform(-10, 10)
        z = random.randint(-10, 10+1)

        result = 0.5 * x**2 + y**2 + z**2 + 5*sin(x+y+z)
        if result < objective['result']:
            objective['x'] = x
            objective['y'] = y
            objective['z'] = z
            objective['result'] = result

    return objective

def main():
    """ Main function to execute functions
    """
    print("Problema do caixeiro viajante")
    print()
    objective = travellingSalesman()
    print("O caminho mais curto é:\n{path}\nDe tamanho {weight}".format(**objective))
    
    print()
    print()
    
    print("Problema de otimização")
    print()
    objective = optimization()
    print("A solução ótima é:\nx = {x:.2f}\ny = {y:.2f}\nz = {z:.2f}\nDe resultado {result:.2f}".format(**objective))


if __name__ == '__main__':
    main()
