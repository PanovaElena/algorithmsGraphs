import matplotlib.pyplot as plt
import math as ma

NUM_VERTICES = [1000, 3000, 5000, 8000, 10000]
NUM_EDGES = { "sparse": [("sparse_3n", "m=3n", lambda n: 3*n), ("sparse_nlog(n)", "m=n*log(n)", lambda n: n*ma.log(n))],\
 "dense": [("dense_0_25n^2", "m=n^2/4", lambda n: n**2/4), ("dense_n^2_div_log(n)", "m=n^2/log(n)", lambda n: n**2/ma.log(n))] }   
ALGORITHMS = [("Kruskall", "Kruskall"), ("Boruvka", "Boruvka"), ("Prim", "Prim")]
UNION_FINDS = [("union-find_by_array", "union-find by array"), ("union-find_by_ranks", "union-find by ranks"),
 ("union-find_ranks_path_compr", "union-find by rpc")]
PRIORITY_QUEUES = [("priority_queue_by_array", "priority queue by array"), \
 ("priority_queue_by_2-heap", "priority queue by 2-heap")]
GRAPH_STRUCTURES = { "sparse":"adj_list", "dense":"adj_matrix"}

figures = ['d', '<', 'x', 'o', '*', 's', 'D', '>']
types = ['-', '--', '-.']

# Kruskall's algorithm complexity is 
# O(m*log(m)+m*n) ~ O(m*log(n)+m*n) for union-find by array
# O(m*log(m)+m*log(n)) ~ O(m*log(n)) for union-find by ranks
# O(m*log(m)+m*superlog(n)) ~ O(m*log(n)) for union-find by ranks with compressing paths

# Boruvka's algorithm complexity is
# O(n^2+m*log(n)) for union-find by array
# O(m*(log(n))^2+n*log(n)) ~ O(m*(log(n))^2) for union-find by ranks
# O((m*log(n)+n)*superlog(n)) ~ O(m*log(n)) for union-find by ranks with compressing paths

# Prim's algorithm complexity is
# O(n^2+m) ~ O(n^2) for array of weights of projections
# O((n+m)*log(n)) ~ O(m*log(n)) for d-heap of weights of projections

mlogn = lambda n, m: m*ma.log(n)
mlogn2 = lambda n, m: m*(ma.log(n)**2)
n2 = lambda n, m : n**2
mn = lambda n, m : m*n
n2_mlogn = lambda n, m : m*ma.log(n)+n**2
mn_mlogn = lambda n, m : m*ma.log(n)+m*n

complexity = {("Kruskall", "union-find_by_array"): n2_mlogn,
              ("Kruskall", "union-find_by_ranks"): mlogn,
              ("Kruskall", "union-find_ranks_path_compr"): mlogn,
              ("Boruvka", "union-find_by_array"): n2_mlogn,
              ("Boruvka", "union-find_by_ranks"): mlogn2,
              ("Boruvka", "union-find_ranks_path_compr"): mlogn,
              ("Prim", "priority_queue_by_array"): n2,
              ("Prim", "priority_queue_by_2-heap"): mlogn
             }


for dense in NUM_EDGES:
    for num_edges in NUM_EDGES[dense]:
    
        list_legend = []      
        nameTitle = "Time of all algorithms divided by complexity, %s" % (num_edges[1])
        namePNG = "All_algorithms_divided_%s" % (num_edges[0])
        
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
                    comp = complexity[(algorithm[0],pr_queue[0])]

                    with open("algorithms_%s_%s_%s_%s" % (num_edges[0],\
                            GRAPH_STRUCTURES[dense], algorithm[0], pr_queue[0]) + ".csv") as file:
                        i = 0
                        for line in file.readlines():
                            n = NUM_VERTICES[i]
                            time.append(int(line)/ comp(n, num_edges[2](n)))
                            i+=1
                            
                    ax.plot(NUM_VERTICES, time, '-'+figures[chf], label = "%s, %s" %(algorithm[1], pr_queue[1]))
                    chf += 1
                    cht += 1
                    
            else:
                for union_find in UNION_FINDS:
                    
                    time = []
                    comp = complexity[(algorithm[0],union_find[0])]
                    
                    with open("algorithms_%s_%s_%s_%s" % (num_edges[0],\
                            GRAPH_STRUCTURES[dense], algorithm[0], union_find[0]) + ".csv") as file:
                        i = 0
                        for line in file.readlines():
                            n = NUM_VERTICES[i]
                            time.append(int(line)/ comp(n, num_edges[2](n)))
                            i+=1
                    
                    ax.plot(NUM_VERTICES, time, types[cht % 3]+figures[chf], label = "%s, %s" % (algorithm[1], union_find[1]))
                    chf += 1
                    cht += 1
                    
        ax.legend(fontsize = 8)
        plt.savefig(namePNG, dpi = 1000)    