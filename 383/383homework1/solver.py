from sys import argv
from puzz import EightPuzzleBoard
from pdqpq import PriorityQueue

no_weight = False

#handler: (successor, frontier, explored, no_weight) => n: number of elements added to the frontier
def search(initial, huristic, halt_value=100000):
    frontier_added = 0
    expanded = 0
    explored = []
    frontier = PriorityQueue()
    frontier.add(initial, 0)
    initial.cost = 0

    while not frontier.empty() and expanded < halt_value:

        node = frontier.pop()

        if node.is_goal():
            return create_solution(node, initial, frontier_added, expanded)

        explored.append(node)
        expanded += 1

        succs = node.successors()
        for move in succs:
            successor = succs[move]
            successor.parent = (node, move)
            weight = huristic(successor)
            if successor not in frontier and successor not in explored:
                frontier.add(successor, weight)
                frontier_added += 1
            elif successor in frontier and frontier.get(successor) > weight:
                frontier.remove(successor)
                frontier.add(successor, weight)
    
    return create_solution(None, initial, frontier_added, expanded, halted=frontier_added >= halt_value)


def bfs(initial):
    return search(initial, lambda state: 1)


def ucost(initial):
    return search(initial, lambda state: 1 if no_weight else state.cost)


def mod_manhattan(state):
    weight = 0
    for i in range(1, 9):
        weight += (i ** 2) * state.distance_from_goal(i)
    return weight


def manhattan(state):
    weight = 0
    for i in range(1, 9):
        weight += state.distance_from_goal(i)
    return weight

def greedy(initial):
    return search(initial, manhattan if no_weight else mod_manhattan)

def astar(initial):

    def f(state):
        return (manhattan(state) if no_weight else mod_manhattan(state)) + state.cost

    return search(initial, f)

#expects all nodes other than initial to have 'parent' field
def create_solution(goal, initial, frontier_added, expanded, halted=False):
    moves = []
    if goal is not None:
        node = goal
        while node != initial:
            moves.append((node, node.parent[1]))
            node = node.parent[0]
        moves.append((initial, 'start'))
        path_cost = goal.cost if not no_weight else len(moves) - 1
        return (moves[::-1], path_cost, frontier_added, expanded)
    elif halted:
        return ('search halted', None, frontier_added, expanded)
    else:
        return (None, None, frontier_added, expanded)
    


def print_sol(sol):
    if sol[0] == 'search halted':
        print('search halted')
    elif sol[0] == None:
        print('no solution')
        #shouldn't happen?
    else:
        for i in range(len(sol[0])):
            move = sol[0][i]
            print(str(i) + '\t' + move[1] + '\t' + str(move[0]))
        print('path cost: ', sol[1])
    
    print('frontier: ', sol[2])
    print('expanded: ', sol[3])

def run_algo(name, start_state, weight_flag):
    global no_weight
    no_weight = weight_flag
    algos = {'bfs': bfs, 'ucost': ucost, 'greedy': greedy, 'astar': astar}
    return algos[name](start_state)
    

def main():
    algo = argv[1]
    start_state = EightPuzzleBoard(argv[2])
    weight_flag = True if len(argv) > 3 and argv[3] == '--noweight' else False

    sol = run_algo(algo, start_state, weight_flag)
    
    print_sol(sol)


if __name__ == '__main__':
    main()
