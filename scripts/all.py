import subprocess
import sys
import os
import matplotlib.pyplot as plt
import math as ma

DIR_SCRIPT = os.path.dirname(sys.argv[0]) 

NAME_PROGRAM = "\"" + DIR_SCRIPT + "../build/bin/randomGraphs.exe" + "\""

NUM_VERTICES = [1000, 3000, 5000, 8000, 10000]
NUM_EDGES = { #"sparse": [(lambda n: 3*n, "sparse_3n"), (lambda n: int(n*ma.log(n)), "sparse_nlog(n)")], \
    "dense": [  (lambda n: int(n*n/ma.log(n)), "dense_n^2_div_log(n)")] }  #(lambda n: n*n/4, "dense_0_25n^2"), (lambda n: int(n*n/ma.log(n)), "dense_n^2_div_log(n)")] }   
ALGORITHMS = [("boruvka", "Boruvka"), ("kruskall", "Kruskall"), ("prim", "Prim")]
UNION_FINDS = [("array", "union-find_by_array"), ("ranks", "union-find_by_ranks"), ("rpc", "union-find_ranks_path_compr")]
PRIORITY_QUEUES = [("array", "priority_queue_by_array"), ("heap", "priority_queue_by_2-heap")]
GRAPH_STRUCTURES = { #"sparse":("adjl", "adj_list"),
 "dense":("adjm", "adj_matrix")}

COMMAND_ARGS = " %d %d %s %s %s"


for dense in NUM_EDGES:
    for num_edges in NUM_EDGES[dense]:
    
        list_legend = []
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)   
        plt.xlabel('n')
        plt.ylabel('time, ms')
        ax.grid()
        
        name = "algorithms_%s" % (num_edges[1])
    
        for algorithm in ALGORITHMS:
            
            if (algorithm[1] == "Prim"):
                for pr_queue in PRIORITY_QUEUES:
                    
                    time = []
                    list_legend.append("%s, %s" %(algorithm[1], pr_queue[1]))
                    
                    for n_vertices in NUM_VERTICES:
                        command_args = COMMAND_ARGS % (n_vertices, num_edges[0](n_vertices),\
                            GRAPH_STRUCTURES[dense][0], algorithm[0], pr_queue[0])		    			
                        process = subprocess.Popen(NAME_PROGRAM + command_args, stdout=subprocess.PIPE, shell=True)
                        process.wait()
                        
                        t = int(str(process.stdout.readlines()[0]).split(" ")[2])
                        
                        time.append(t)
                        
                        print("%d %s %s %s %s completed, time is %d" % (n_vertices, num_edges[1],\
                            GRAPH_STRUCTURES[dense][1], algorithm[1], pr_queue[1], t))
                        
                    with open("algorithms_%s_%s_%s_%s" % (num_edges[1],\
                            GRAPH_STRUCTURES[dense][1], algorithm[1], pr_queue[1]) + ".csv", "w") as file:
                        for t in time:
                            file.write(str(t) + "\n")
                    
                    ax.plot(NUM_VERTICES[:len(time)], time, '-*')
                    
            else:
                for union_find in UNION_FINDS:
                    
                    time = []
                    list_legend.append("%s, %s" % (algorithm[1], union_find[1]))
                    
                    for n_vertices in NUM_VERTICES:
                        command_args = COMMAND_ARGS % (n_vertices, num_edges[0](n_vertices),\
                            GRAPH_STRUCTURES[dense][0], algorithm[0], union_find[0])		    			
                        process = subprocess.Popen(NAME_PROGRAM + command_args, stdout=subprocess.PIPE, shell=True)
                        process.wait()
                        
                        t = int(str(process.stdout.readlines()[0]).split(" ")[2])
                        
                        time.append(t)
                        
                        print("%d %s %s %s %s completed, time is %d" % (n_vertices, num_edges[1],\
                            GRAPH_STRUCTURES[dense][1], algorithm[1], union_find[1], t))
                        
                    with open("algorithms_%s_%s_%s_%s" % (num_edges[1],\
                            GRAPH_STRUCTURES[dense][1], algorithm[1], union_find[1]) + ".csv", "w") as file:
                        for t in time:
                            file.write(str(t) + "\n")
                    
                    ax.plot(NUM_VERTICES[:len(time)], time, '-*')
                    
        ax.legend(list_legend)
        plt.savefig(name)    
