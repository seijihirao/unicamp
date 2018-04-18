#!/usr/bin/env python
# -*- coding: utf-8 -*-

from sys import stdin

code = stdin.readline().replace(' ', '')

translation = {
    'A': 'SW(3)',
    'B': 'SW(2)',
    'C': 'SW(1)',
    'D': 'SW(0)'
}

result = '('

for i in range(len(code)):
    if(code[i] in translation):
        if(i > 0 and (code[i-1] in translation or code[i-1] == '\'')):
            result += ' AND '
        if(i > 0 and code[i-1] == '+'):
            result += ') OR ('
        if(i < len(code) and code[i+1] == '\''):
            result += 'NOT '
        result += translation[code[i]]

print(result)
