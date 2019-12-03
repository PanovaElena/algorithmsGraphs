import matplotlib.pyplot as plt
import math as ma


NUM_VERTICES = [1000, 3000, 5000, 8000, 10000]
NUM_EDGES = { "sparse": [("sparse_3n", "m=3n"), ("sparse_nlog(n)", "m=n*log(n)")],\
 "dense": [("dense_0_25n^2", "m=n^2/4"), ("dense_n^2_div_log(n)", "m=n^2/log(n)")] }   
ALGORITHMS = [("Kruskall", "Kruskall"), ("Boruvka", "Boruvka"), ("Prim", "Prim")]
UNION_FINDS = [("union-find_by_array", "union-find by array"), ("union-find_by_ranks", "union-find by ranks"),
 ("union-find_ranks_path_compr", "union-find by rpc")]
PRIORITY_QUEUES = [("priority_queue_by_array", "priority queue by array"), \
 ("priority_queue_by_2-heap", "priority queue by 2-heap")]
GRAPH_STRUCTURES = { "sparse":"adj_list", "dense":"adj_matrix"}

figures = ['d', '<', 'x', 'o', '*', 's', 'D', '>']
types = ['-', '--', '-.']

for dense in NUM_EDGES:
    for num_edges in NUM_EDGES[dense]:
    
        list_legend = []      
        nameTitle = "Time of all algorithms, %s" % (num_edges[1])
        namePNG = "All_algorithms_time_%s" % (num_edges[0])
        
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)   
        plt.xlabel('n')
        plt.ylabel('time, ms')
        ax.grid()   
        plt.title(nameTitle)
        plt.yscale('log')
        
        chf = 0
        cht = 0
    
        for algorithm in ALGORITHMS:
            
            if (algorithm[0] == "Prim"):
                for pr_queue in PRIORITY_QUEUES:
                    
                    time = []

                    with open("algorithms_%s_%s_%s_%s" % (num_edges[0],\
                            GRAPH_STRUCTURES[dense], algorithm[0], pr_queue[0]) + ".csv") as file:
                        for line in file.readlines():
                            time.append(int(line))
                            
                    ax.plot(NUM_VERTICES, time, '-'+figures[chf], label = "%s, %s" %(algorithm[1], pr_queue[1]))
                    chf += 1
                    cht += 1
                    
            else:
                for union_find in UNION_FINDS:
                    
                    time = []
                    
                    with open("algorithms_%s_%s_%s_%s" % (num_edges[0],\
                            GRAPH_STRUCTURES[dense], algorithm[0], union_find[0]) + ".csv") as file:
                        for line in file.readlines():
                            time.append(int(line))
                    
                    ax.plot(NUM_VERTICES, time, types[cht % 3]+figures[chf], label = "%s, %s" % (algorithm[1], union_find[1]))
                    chf += 1
                    cht += 1
                    
        ax.legend(fontsize = 8)
        plt.savefig(namePNG)    