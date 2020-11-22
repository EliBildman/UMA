
import re
import csv
import time
import json
import random
from pandas import DataFrame
from sklearn.naive_bayes import MultinomialNB
from sklearn.feature_extraction.text import CountVectorizer
from nltk.tokenize import TweetTokenizer
from pprint import pprint

gender = {
    0: 'Female',
    1: 'Male'
}

tweet_tokenizer = TweetTokenizer()
cVect, classifier = CountVectorizer(lowercase=True, tokenizer=tweet_tokenizer.tokenize), MultinomialNB()


def helper(dataset, gender):
    newDataSet = []
    reg = [
        ('\\n', ' ',),
        ('\\t', ' ',),
        ('\s+', ' ',)
    ]
    for i in range(len(dataset)):
        if dataset[i]:
            str = dataset[i]
            str = str.lower()
            for regex, rep in reg:
                str = re.sub(regex, rep, str)
            row = [gender, str]
            newDataSet.append(row)

    return newDataSet


def main():
    testSet = []
    filename1 = 'male_bios.json'
    filename2 = 'female_bios.json'
    f = open(filename2)
    m = open(filename1)
    dataSetM = json.load(m)
    dataSetF = json.load(f)
    f1 = helper(dataSetF, 0)
    f2 = helper(dataSetM, 1)
    dataSet = f1+f2
    random.shuffle(dataSet)
    #for i in range(trainTestRatio):
    #    testSet.append(random.choice(dataSet))
    train_dataSet, test_dataSet = split(dataSet)
    #test_dataSet = dataSet[trainTestRatio:]
    train(train_dataSet)
    # printOut = predict(test_dataSet)
    # outputWrite(printOut[0],printOut[1],printOut[2])

def split(arr):
    trainTestRatio = int(len(arr) * 0.80)
    return arr[:trainTestRatio], arr[trainTestRatio:]

def train(trainSet):
    line, index = [], []
    for i in range(len(trainSet)):
        line.append({'gender': trainSet[i][0], 'bio': trainSet[i][1]})
        index.append(i)
    dataFrame = DataFrame(line, index=index)
    bio = dataFrame['bio'].values
    bow = cVect.fit_transform(bio)
    targets = dataFrame['gender'].values
    classifier.fit(bow, targets)


def predict(testSet):
    texts, actual = [], []
    for testData in testSet:
        actual.append(testData[0])
        texts.append(testData[1])
    return classifier.predict_proba(cVect.transform(texts)), texts, actual


def outputWrite(probability, textArr, actual):
    successes = 0
    result = "\n"
    for i in range(len(textArr)):
        realGender = actual[i]
        if probability[i][0] < probability[i][1]:
            predicted = 1
        else:
            predicted = 0
        if predicted == realGender:
            successes += 1
        res = [gender[predicted], probability[i][predicted]
               * 100, gender[actual[i]]]
        result = result + "\n{0}:{1:.2f}%, ({2}): {3}".format(
            res[0], res[1], res[2], textArr[i])

    accuracy = float(successes)/(len(textArr))* 100.00
    result = "\nTotal Predictions:\t\t{0}\nAccurate predictions:\t{1}\nAccuracy:\t\t\t\t{2}%".format(len(textArr), successes, round(accuracy, 1)) + result
    fileOutput = open("results.txt", "w")
    fileOutput.write(result)
    fileOutput.close()

#i think the __name__ thing is lame
main()

word_list = cVect.get_feature_names()
coefs = classifier
words_with_coefs = []

for i in range(len(word_list)):
    words_with_coefs.append( (word_list[i], coefs[i]) )

words_with_coefs.sort(key = lambda x: x[1])


pprint(words_with_coefs[-10:])
