import sys
import csv
import statistics
import scipy.stats
# from numpy import dot, add, subtract


def read_data(csv_path):
    """Read in the input data from csv.
    
    Args:
        csv_path: the path to the input file.  The data file is assumed to have a header row, and
                the class value is found in the last column.
        standardize: flag to indicate whether the attributes (not including the class label) should 
                be transformed into z-scores before returning

    Returns: a list of lists containing the labeled training examples, with each row representing a 
        single example of the format [ attr1, attr2, ... , class_label ]
    """
    with open(csv_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)  # header row
        features = []
        labels = []
        for row in reader:
            features.append([ float(r) for r in row[:-1] ])            
            labels.append(row[-1])
        examples = [ row + [labels[i]] for i, row in enumerate(features) ]
        return examples


def standardize(examples):
    """Transform data to use z-scores instead of raw values.  
        
    Args:
        examples: a list of lists containing the training examples, with each row representing a 
            single example of the format [ attr1, attr2, ... , class_label ]
    
    Returns: a list of lists containing the transformed training examples, with each row 
        representing a single example of the format [ zscore1, zscore2, ... , class_label ]

    See: https://en.wikipedia.org/wiki/Standard_score for more detail on z-scores.  N.B.: the last
        field each row is assumed to contain the class label and is not transformed!    
    """

    zs = []
    _examples = list( example[:-1] for example in examples )
    labels = list( example[-1] for example in examples )


    for i in range(len(_examples[0])):
        zs.append( scipy.stats.zscore( list(float(example[i]) for example in _examples) ) )

    standardized = []

    for i in range(len(_examples)):
        standardized.append([])
        for j in range(len(zs)):
            standardized[i].append(zs[j][i])

    return list( standardized[i] + [labels[i]] for i in range(len(examples)) )

def dot(a, b):
    t = 0.0
    for i in range(len(a)):
        t += a[i] + b[i]
    return t

def add(a, b):
    r = []
    for i in range(len(a)):
        r.append(a[i] + b[i])
    return r

def sub(a, b):
    r = []
    for i in range(len(a)):
        r.append(a[i] - b[i])
    return r


def learn_weights(examples):
    """Learn attribute weights for a multiclass perceptron.

    Args:
        examples: a list of lists containing the training examples, with each row representing a 
            single example of the format [ attr1, attr2, ... , class_label ]
                  
    Returns: a dictionary containing the weights for each attribute, for each class, that correctly
            classify the training data.  The keys of the dictionary should be the class values, and
            the values should be lists attribute weights in the order they appear in the data file.
            For example, if there are four attributes and three classes (1-3), the output might take
            the form:
                { 1 => [0.1, 0.8, 0.5, 0.01],
                  2 => [0.9, 0.01, 0.05, 0.4],
                  3 => [0.01, 0.2, 0.3, 0.85] }
    """

    ITTERATION_LIMIT = 1000



    weights = {}  # one set of weights for each class

    for example in examples:
        _class = example[-1]

        if _class not in weights:
            weights[_class] = list(0 for _ in range(len(example) - 1))


    i = 0
    missed = True

    while i < ITTERATION_LIMIT and missed != 0:

        missed = 0
        i += 1

        for example in examples:

            true_class = example[-1]
            example = example[:-1]

            preds = {}      

            for _class in weights:
                preds[_class] = dot(weights[_class], example)

            pred = max(preds.keys(), key= lambda c: preds[c])

            if pred != true_class:
                missed += 1
                weights[pred] = sub(weights[pred], example)
                weights[true_class] = add(weights[true_class], example)

    if i == ITTERATION_LIMIT:
        print("hit itteration limit, current miscalcs:", missed)

    return weights


def print_weights(class__weights):
    for c, wts in sorted(class__weights.items()):
        print("class {}: {}".format(c, ",".join([str(w) for w in wts])))




#############################################

if __name__ == '__main__':

    path_to_csv = "./wine.csv"
    training_data = read_data(path_to_csv)


    class__weights = learn_weights(training_data)
    print_weights(class__weights)

    # training_data = standardize(training_data)
    # class__weights = learn_weights(training_data)
    # print_weights(class__weights)







