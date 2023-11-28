# Graph API For Project 3 (Done by Omar)

## Plans 
- Necessary functions:
    - add edge
    - remove edge
    - add vertex
    - remove vertex (and associated edges)
    - are two nodes neighbors
- Implementation details
    - nodes will be integers, weights also integers
    - negative weights are (sometimes) allowed
    - different graph algorithms will be class methods
    - graph is directed and weighted
- extra notes
    - non-simple graphs are not allowed
        - a vertex cannot connect to itself
        - there cannot be multiple edges between vertices in the same direction
- additional plans
    - split into two graphs
        - user_graph: meant for GUI, safeguards against being not simple, etc.
        - speed_graph: meant for testing the speed of algorithms, doesn't safeguard against anything, only should be used with randomly generated graphs to speed up insertions