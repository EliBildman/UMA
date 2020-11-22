# import torch
from transformers import BertTokenizer, BertModel
from sklearn.feature_extraction import DictVectorizer
from collections import Counter
import json
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression


tokenizer = BertTokenizer.from_pretrained('bert-base-uncased')
vectorizer = DictVectorizer(sparse=False)
log_reg = LogisticRegression()

def read_annotation(anno):
    toks = tokenizer.tokenize( anno['sentence'].lower() )
    # print(toks)
    return { 'bag': Counter(toks), 'label': anno['label'], 'sentence': anno['sentence'] }


def read_all_annotations(filename):
    annotations = []
    with open(filename, 'r', encoding='utf8') as f:
        data = json.load(f)
        for datum in data:
            annotations.append(read_annotation(datum))
    return annotations


def dict_vector_data(annos):
    x = vectorizer.fit_transform(list( anno['bag'] for anno in annos ))
    y = list( anno['label'] for anno in annos )
    return (x, y)


text = "This is preposterous!"
marked_text = "[CLS] " + text + " [SEP]"

# Tokenize our sentence with the BERT tokenizer.
# tokenized_text = tokenizer.tokenize(marked_text)

def train_test_model(filename):
    annos = read_all_annotations(filename)
    x, y = dict_vector_data(annos)
    x_train, x_test, y_train, y_test = train_test_split( x, y, test_size= 0.25 )
    log_reg.fit(x_train, y_train)
    print('accuracy:', log_reg.score(x_test, y_test) )



train_test_model('annotations.json')