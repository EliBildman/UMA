name: Eli Bildman

best meal: Dominos while drunk

weights change path costs:

It seems like asigning the arbitrary weights (and using the modified huristic) makes the A* algorithm sub-optimal. It tend to return paths shorter than greedy, but longer than bfs and ucost. I put 
Example case: 
test  5 : 158342670
    algo: bfs       time (s): 1.501744      weight: 55
    algo: ucost     time (s): 3.027024      weight: 55
    algo: greedy    time (s): 1.142165      weight: 225
    algo: astar     time (s): 0.065021      weight: 103

notes:
it should all be working. The tester fails right now if the solver halts or cant find a solution for any case, because it would ruin the data. The tester is run 'python3 tester.py [complexity] [num tests]'
