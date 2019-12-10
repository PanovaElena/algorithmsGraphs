import subprocess
import sys
import os
import matplotlib.pyplot as plt

ALGORITHMS = [("boruvka rpc", "Boruvka"), ("kruskall rpc", "Kruskall"), ("prim heap", "Prim")]
NUM_EDGES = [("dense", "m=n^2/4"), ("sparse", "m=3n")]
GRAPH_STRUCTURES = [("adj_matrix", "adjencency matrix"), ("adj_list", "adjencency list"), ("edge_list", "edge list")]
NUM_VERTICES = { NUM_EDGES[0] : [1000, 2000, 3000, 5000, 8000], NUM_EDGES[1] : [1000, 3000, 5000, 8000, 10000] }

# "adjm" - get neighbours O(n), get all edges O(n^2)
# "adjl" - get neighbours O(1), get all edges O(m)
# "edgl" - get neighbours O(m), get all edges O(1)

COMMAND_ARGS = " %d %d %s %s"

start = False

for num_edges in NUM_EDGES:
    for algorithm in ALGORITHMS:
    
        #if (algorithm[1] == "Prim"):
        start = True
    
        if (start == True):
        
            fig = plt.figure()
            ax = fig.add_subplot(1, 1, 1)   
            plt.xlabel('n')
            plt.ylabel('time, ms')
            ax.grid()
            plt.yscale('log')
            plt.title("Graph storage structure for %s's algorithm (%s)" % (algorithm[1], num_edges[1]))
            
            name = "structures_2_%s_%s" % (num_edges[0], algorithm[1])
            
            for graph in GRAPH_STRUCTURES:
            
                time = []
                    
                with open("structures_%s_%s_%s" % (num_edges[0], algorithm[1], graph[0]) + ".csv") as file:
                    for line in file.readlines():
                        time.append(int(line))
                
                ax.plot(NUM_VERTICES[num_edges][:len(time)], time, '-*', label = graph[1])      
            
            ax.legend(fontsize = 8)
            plt.savefig(name, dpi = 1000)

