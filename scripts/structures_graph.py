import subprocess
import sys
import os
import matplotlib.pyplot as plt

DIR_SCRIPT = os.path.dirname(sys.argv[0]) 

NAME_PROGRAM = "\"" + DIR_SCRIPT + "../build/bin/randomGraphs.exe" + "\""


ALGORITHMS = [("boruvka rpc", "Boruvka"), ("kruskall rpc", "Kruskall"), ("prim heap", "Prim")]
NUM_EDGES = [(lambda n: n*n/4, "dense"), (lambda n: 3*n, "sparse")]
GRAPH_STRUCTURES = [("adjm", "adj_matrix"), ("adjl", "adj_list"), ("edgl", "edge_list")]
NUM_VERTICES = [1000, 2000]

# "adjm" - get neighbours O(n), get all edges O(n^2)
# "adjl" - get neighbours O(1), get all edges O(m)
# "edgl" - get neighbours O(m), get all edges O(1)

COMMAND_ARGS = " %d %d %s %s"

for num_edges in NUM_EDGES:
    for algorithm in ALGORITHMS:
    
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)   
        plt.xlabel('n')
        plt.ylabel('time, ms')
        ax.grid()
        
        name = "structures_%s_%s" % (num_edges[1], algorithm[1])
        
        for graph in GRAPH_STRUCTURES:
        
            time = []
                    
            for n_vertices in NUM_VERTICES:
                command_args = COMMAND_ARGS % (n_vertices, num_edges[0](n_vertices), graph[0], algorithm[0])		    			
                process = subprocess.Popen(NAME_PROGRAM + command_args, stdout=subprocess.PIPE, shell=True)
                process.wait()
                
                print("%s %s %s %d completed" % (num_edges[1], algorithm[1], graph[1], n_vertices))
                
                time.append(int(str(process.stdout.readlines()[0]).split(" ")[2]))
                
            with open(name + ".csv", "w") as file:
                for t in time:
                    file.write(str(t) + "\n")
             
            ax.plot(NUM_VERTICES, time)             
        
        ax.legend([el[1] for el in GRAPH_STRUCTURES])
        plt.savefig(name)

