from puzz import EightPuzzleBoard
from random import choice
from solver import run_algo, print_sol
from datetime import datetime
from sys import argv
import statistics
from matplotlib import pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages 

opposites = {'left': 'right', 'up': 'down', 'right': 'left', 'down': 'up'}

def create_test_case(steps):
    state = EightPuzzleBoard('012345678')
    last = None
    for _ in range(steps):
        succs = state.successors()
        if last != None and opposites[last] in succs:
            del succs[opposites[last]]
        _next = choice(list(succs.keys()))
        state = succs[_next]
        last = _next
    return state

def test_algos(algos, scramble, tests, weight_flag, print_sols=False, pdf_name="plots.pdf"):

    global no_weight
    no_weight = weight_flag

    solves = {}
    for algo in algos:
        solves[algo] = []
    
    for i in range(tests):
        test_state = create_test_case(scramble)
        for algo in algos:
            start = datetime.now()
            sol = run_algo(algo, test_state, weight_flag)
            end = datetime.now()
            if print_sols:
                print_sol(sol)
            if algo == algos[0]:
                print('test ', i, ':', test_state)

            solves[algo].append(sol)
                
            time_elapsed = (end - start).total_seconds()
            sol_len = len(sol[0]) - 1

            print('\t', 'algo:' , algo, '\t',  "time (s):", time_elapsed, '\t',  'weight:', sol_len if no_weight else sol[0][sol_len][0].cost )
    
    gen_pdf(solves, pdf_name)

def gen_pdf(solves, pdf_name):
    pp = PdfPages(pdf_name)
    algos = list(solves.keys())
    for i, title in enumerate(['Average Path Cost', 'Average Additions to Frontier', 'Average Expanded Nodes']):
        avgs = []
        for algo in solves:
            data = list(solve[i + 1] for solve in solves[algo])
            avgs.append(statistics.mean(data))

        plt.figure(figsize = (10, 5))
        plt.bar(algos, avgs, color ='green',  width = 0.8) 
        plt.xlabel("Algorithm") 
        plt.ylabel(title) 
        plt.title(title + " by Algorithm") 
        pp.savefig()

    pp.close()

        

print('-- RUNNING WEIGHTED --')
test_algos(['bfs', 'ucost', 'greedy', 'astar'], int(argv[1]), int(argv[2]), False, pdf_name='plots.pdf')

print('-- RUNNING UNWEIGHTED --')
test_algos(['bfs', 'ucost', 'greedy', 'astar'], int(argv[1]), int(argv[2]), True, pdf_name='plots_unweighted.pdf')
