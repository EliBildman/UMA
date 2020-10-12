from nltk.tokenize import RegexpTokenizer
import json
from collections import Counter
from pprint import pprint




t = RegexpTokenizer('(?=\S*[\'-])*([a-zA-Z\'-]+)')
print(t.tokenize('eli-bildman -elibildman....'))

#returns { bag, label }
def read_annotation(anno):
    toks = t.tokenize(anno['sentence'].lower())
    bag = Counter(toks)
    return { 'bag': bag, 'label': anno['label'] }


def read_all_annotations(filename):
    annotations = []
    with open(filename, 'r') as f:
        data = json.load(f)
        for datum in data:
            annotations.append(read_annotation(datum))
    return annotations

def total_counts(bags):
    c = Counter()
    for bag in bags:
        for word in bag:
            if word in c:
                c[word] += bag[word]
            else:
                c[word] = bag[word]
    return c

annos = read_all_annotations('annotations.json')
totals = total_counts(list(anno['bag'] for anno in annos))

print(totals['vod'])

