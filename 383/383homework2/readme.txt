
Name: Eli Bildman

Tourney Bot Name: Annie Bot

Evaluation Explaination: My evaluation function first looks for all the possible runs of >3 that both players could fill given the current board. It then gives each player score equal to (length of run ^ 2 * (num tiles filled in length / length of run)). This gives each player points as a fraction of the points the could attain in the run based on how much they've already achieved. This also means that having a filled connect-3 gives less points (9) than 3 filled slots in a connect that could be 4 (16 * 0.75 = 12) making it move valuable, as it should be.

Tests: I used p_test to test the logic of the prune agent on a board it wouldn't stall on. I used hur_test to step through the logic of my huristic agent.

Notes: All of it should work