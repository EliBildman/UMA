import re
import csv
import time
import json
import random
from nltk.tokenize import TweetTokenizer
from pprint import pprint

tt = TweetTokenizer()

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


def replace_token_list(anno):
    return (anno[0], tt.tokenize(anno[1]))




filename1 = 'male_bios.json'
filename2 = 'female_bios.json'
f = open(filename2)
m = open(filename1)
dataSetM = json.load(m)
dataSetF = json.load(f)
f1 = helper(dataSetF, 0)
f2 = helper(dataSetM, 1)
dataSet = f1+f2
t_dataset = list(replace_token_list(anno) for anno in dataSet)

tot = 0
for data in t_dataset:
    for word in data[1]:
        if word in '!.?':
            tot += 1
    tot += 1



pprint(tot)