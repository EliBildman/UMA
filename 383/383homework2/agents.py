import random
import math


BOT_NAME = "Annie Bot"


class RandomAgent:
    """Agent that picks a random available move.  You should be able to beat it."""
    def get_move(self, state, depth=None):
        return random.choice(state.successors())


class HumanAgent:
    """Prompts user to supply a valid move."""
    def get_move(self, state, depth=None):
        move__state = dict(state.successors())
        prompt = "Kindly enter your move {}: ".format(sorted(move__state.keys()))
        move = None
        while move not in move__state:
            try:
                move = int(input(prompt))
            except ValueError:
                continue
        return move, move__state[move]


class MinimaxAgent:
    """Artificially intelligent agent that uses minimax to optimally select the best move."""

    def get_move(self, state, depth=None):
        """Select the best available move, based on minimax value."""
        nextp = state.next_player()
        best_util = -math.inf if nextp == 1 else math.inf
        best_move = None
        best_state = None

        for move, state in state.successors():
            util = self.minimax(state, depth)
            if ((nextp == 1) and (util > best_util)) or ((nextp == -1) and (util < best_util)):
                best_util, best_move, best_state = util, move, state
        return best_move, best_state

    def minimax(self, state, depth):
        """Determine the minimax utility value of the given state.

        Args:
            state: a connect383.GameState object representing the current board
            depth: for this agent, the depth argument should be ignored!

        Returns: the exact minimax utility value of the state
        """

        moves = state.successors()

        if len(moves) == 0:
            return state.score()

        _dir = 'MAX' if state.next_player() == 1 else 'MIN'
        ext = -math.inf if _dir == 'MAX' else math.inf
        
        for move in moves:
            successor = move[1]
            succ_value = self.minimax(successor, depth)
            if (_dir == 'MAX' and succ_value > ext) or (_dir == 'MIN' and succ_value < ext):
                ext = succ_value

        return ext


class HeuristicAgent(MinimaxAgent):
    """Artificially intelligent agent that uses depth-limited minimax to select the best move."""

    def minimax(self, state, depth):
        return self.minimax_depth(state, depth)

    def minimax_depth(self, state, depth):
        """Determine the heuristically estimated minimax utility value of the given state.

        Args:
            state: a connect383.GameState object representing the current board
            depth: the maximum depth of the game tree that minimax should traverse before
                estimating the utility using the evaluation() function.  If depth is 0, no
                traversal is performed, and minimax returns the results of a call to evaluation().
                If depth is None, the entire game tree is traversed.

        Returns: the minimax utility value of the state
        """

        _depth = depth[0] if depth is not None else None

        moves = state.successors()

        if len(moves) == 0:
            return state.score()

        if _depth is not None and _depth == 0:
            return self.evaluation(state)

        _dir = 'MAX' if state.next_player() == 1 else 'MIN'
        ext = -math.inf if _dir == 'MAX' else math.inf
        
        for move in moves:
            successor = move[1]
            succ_value = self.minimax( successor, [_depth - 1 if _depth is not None else None] )
            if (_dir == 'MAX' and succ_value > ext) or (_dir == 'MIN' and succ_value < ext):
                ext = succ_value

        return ext

    def evaluation(self, state):
        """Estimate the utility value of the game state based on features.

        N.B.: This method must run in O(1) time!

        Args:
            state: a connect383.GameState object representing the current board

        Returns: a heusristic estimate of the utility value of the state
        """
        #
        # Fill this in!

        def get_possis(run, player): #possbilities lmao

            possis = [] # (length, num_filled)
            _len = 0
            num_filled = 0

            for c in run:
                if c == player:
                    _len += 1
                    num_filled += 1
                elif c == 0:
                    _len += 1
                else:
                    if _len > 0:
                        possis.append( (_len, num_filled) )
                        _len = 0
                        num_filled = 0
            if _len > 0:
                possis.append( (_len, num_filled) )

            return possis

        score = 0

        for run in state.get_all_rows() + state.get_all_cols() + state.get_all_diags():
            
            for possi in get_possis(run, 1):
                if possi[0] >= 3:
                    score += (possi[0] ** 2) * ( possi[1] / possi[0] ) #not sure about this maybe revisit
            for possi in get_possis(run, -1):
                if possi[0] >= 3:
                    score -= (possi[0] ** 2) * ( possi[1] / possi[0] )

        return score


class PruneAgent(HeuristicAgent):
    """Smarter computer agent that uses minimax with alpha-beta pruning to select the best move."""

    def minimax(self, state, depth):
        return self.minimax_prune(state, depth)

    def minimax_prune(self, state, depth):
        """Determine the minimax utility value the given state using alpha-beta pruning.

        The value should be equal to the one determined by ComputerAgent.minimax(), but the 
        algorithm should do less work.  You can check this by inspecting the class variables
        GameState.p1_state_count and GameState.p2_state_count, which keep track of how many
        GameState objects were created over time.

        N.B.: When exploring the game tree and expanding nodes, you must consider the child nodes
        in the order that they are returned by GameState.successors().  That is, you cannot prune
        the state reached by moving to column 4 before you've explored the state reached by a move
        to to column 1.

        Args: see ComputerDepthLimitAgent.minimax() above

        Returns: the minimax utility value of the state
        """

        def prune_find(state, a, b, _depth):

            moves = state.successors()

            if len(moves) == 0:
                return state.score()

            if _depth is not None and _depth == 0:
                return self.evaluation(state)

            _dir, ext = ('MAX', -math.inf) if state.next_player() == 1 else ('MIN', math.inf)
            
            for move in moves: 
                successor = move[1]

                if _dir == 'MAX':
                    succ_value = prune_find(successor, max(ext, a), b, _depth - 1 if _depth is not None else None)
                    if succ_value > ext:
                        ext = succ_value
                        if ext >= b:
                            return ext
                else:
                    succ_value = prune_find(successor, a, min(ext, b), _depth - 1 if _depth is not None else None)
                    if succ_value < ext:
                        ext = succ_value
                        if ext <= a:
                            return ext

            return ext

        return prune_find(state, -math.inf, math.inf, depth if depth is not None else None)


        


