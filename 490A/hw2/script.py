import json
from collections import Counter
from pprint import pprint
from nltk.tokenize import RegexpTokenizer
from sklearn.metrics import plot_confusion_matrix
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.feature_extraction import DictVectorizer





tokenizer = RegexpTokenizer('(?=\S*[\'-])*([a-zA-Z\'-]+)')
vectorizer = DictVectorizer(sparse=False)
log_reg = LogisticRegression()

#returns { p_arr, label, sentence }
def read_annotation(anno):
    toks = tokenizer.tokenize(anno['sentence'].lower())
    return { 'bag': Counter(toks), 'label': anno['label'], 'sentence': anno['sentence'] }


def read_all_annotations(filename):
    annotations = []
    with open(filename, 'r', encoding='utf8') as f:
        data = json.load(f)
        for datum in data:
            annotations.append(read_annotation(datum))
    return annotations

# def presence_array(ts):
#     p_array = []
#     for word in feature_words:
#         p_array.append( 1 if word in ts else 0 )
#     return p_array

def dict_vector_data(annos):
    x = vectorizer.fit_transform(list( anno['bag'] for anno in annos ))
    y = list( anno['label'] for anno in annos )
    return (x, y)

def display_confusion_matrix(x_test, y_test):
    disp = plot_confusion_matrix(log_reg, x_test, y_test, display_labels=['1st Person', '2nd Person', '3rd Person', 'Unclear'], cmap=plt.cm.Greens)
    disp.ax_.set_title('Log Reg Model')
    print(disp.confusion_matrix)
    plt.show()

def train_test_model(filename, display_confusion=False):
    annos = read_all_annotations(filename)
    x, y = dict_vector_data(annos)
    x_train, x_test, y_train, y_test = train_test_split( x, y, test_size= 0.25 )
    log_reg.fit(x_train, y_train)
    print('accuracy:', log_reg.score(x_test, y_test) )
    if display_confusion:
        display_confusion_matrix(x_test, y_test)

def find_word(i):
    for word in vectorizer.vocabulary_:
        if vectorizer.vocabulary_[word] == i:
            return word
    return -1

def coefs_for(class_):
    class_i = list(log_reg.classes_).index(class_)
    coefs = []
    for i in range(len(vectorizer.vocabulary_)):
        word = find_word(i)
        weight = log_reg.coef_[class_i][i]
        coefs.append( (word, weight) )
    return coefs

def print_top(n):
    for class_ in [1, 2, 3, 4]:
        print("CLASS:", class_)
        coefs = coefs_for(class_)
        coefs.sort(key= lambda x: x[1], reverse=True)
        pprint(coefs[:n])
        print()

if __name__ == '__main__':
    train_test_model('annotations.json')

