alph = ['A', 'B', 'C']
words = []
from pprint import pprint

def cond(str):
    bs = 0
    for i in range(len(str)):
        if str[i] == 'B':
            bs += 1
        if str[i] == 'C' and i > 0 and str[i - 1] == 'C':
            return False
    return bs >= 2

currword = [0,0,0,0]
for a in range(3):
    currword[0] = alph[a]
    for b in range(3):
        currword[1] = alph[b]
        for c in range(3):
            currword[2] = alph[c]
            for d in range(3):
                currword[3] = alph[d]
                if cond(currword):
                    words.append(''.join(currword))

pprint(words)