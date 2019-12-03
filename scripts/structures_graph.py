import subprocess
import sys
import os
import matplotlib.pyplot as plt

DIR_SCRIPT = os.path.dirname(sys.argv[0]) 

NAME_PROGRAM = "\"" + DIR_SCRIPT + "../build/bin/randomGraphs.exe" + "\""


ALGORITHMS = [("boruvka rpc", "Boruvka"), ("kruskall rpc", "Kruskall"), ("prim heap", "Prim")]
NUM_EDGES = [(lambda n: 3*n, "sparse")] #[(lambda n: n*n/4, "dense")]#, (lambda n: 3*n, "sparse")]
GRAPH_STRUCTURES = [("adjm", "adj_matrix"), ("adjl", "adj_list"), ("edgl", "edge_list")]
NUM_VERTICES = { NUM_EDGES[0] : [1000, 3000, 5000, 8000, 10000] }#{ NUM_EDGES[0] : [1000, 2000, 3000, 5000, 8000]}
    #NUM_EDGES[1] : [1000, 3000, 5000, 8000, 10000] }

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
            
            name = "structures_%s_%s" % (num_edges[1], algorithm[1])
            
            for graph in GRAPH_STRUCTURES:
            
                time = []
                        
                for n_vertices in NUM_VERTICES[num_edges]:
                
                    if (num_edges[1] == "dense" and algorithm[1] == "Prim" and n_vertices > 2001):
                        continue
                    
                    command_args = COMMAND_ARGS % (n_vertices, num_edges[0](n_vertices), graph[0], algorithm[0])		    			
                    process = subprocess.Popen(NAME_PROGRAM + command_args, stdout=subprocess.PIPE, shell=True)
                    process.wait()
                    
                    t = int(str(process.stdout.readlines()[0]).split(" ")[2])
                    
                    time.append(t)
                    
                    print("%s %s %s %d completed, time is %d" % (num_edges[1], algorithm[1], graph[1], n_vertices, t))
                    
                with open("structures_%s_%s_%s" % (num_edges[1], algorithm[1], graph[1]) + ".csv", "w") as file:
                    for t in time:
                        file.write(str(t) + "\n")
                
                ax.plot(NUM_VERTICES[num_edges][:len(time)], time, '-*')      
            
            ax.legend([el[1] for el in GRAPH_STRUCTURES])
            plt.savefig(name)

