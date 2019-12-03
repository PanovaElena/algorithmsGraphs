import subprocess
import sys
import os
import math as ma

DIR_SCRIPT = os.path.dirname(sys.argv[0]) 

NAME_PROGRAM = "\"" + DIR_SCRIPT + "../build/bin/realData.exe" + "\""

ALGORITHMS = [("boruvka", "Boruvka"), ("kruskall", "Kruskall"), ("prim", "Prim")]
UNION_FINDS = [("array", "union-find_by_array"), ("ranks", "union-find_by_ranks"), ("rpc", "union-find_ranks_path_compr")]
PRIORITY_QUEUES = [("array", "priority_queue_by_array"), ("heap", "priority_queue_by_2-heap")]
GRAPH_STRUCTURE = ("adjl" ,"adj_list")

COMMAND_ARGS = " 1 1 %s %s %s"

with open("res_real_data.csv", "w") as file:
    for algorithm in ALGORITHMS:
                
        if (algorithm[1] == "Prim"):
            for pr_queue in PRIORITY_QUEUES:
                
                command_args = COMMAND_ARGS % (GRAPH_STRUCTURE[0], algorithm[0], pr_queue[0])	               
                process = subprocess.Popen(NAME_PROGRAM + command_args, stdout=subprocess.PIPE, shell=True)
                process.wait()
                
                t = int(str(process.stdout.readlines()[0]).split(" ")[2])
                
                file.write("%s, %s;%d\n" % (algorithm[1], pr_queue[1], t))
                
                print("%s, %s completed, time is %d" % (algorithm[1], pr_queue[1], t))
                    
                
        else:
            for union_find in UNION_FINDS:
            
                command_args = COMMAND_ARGS % (GRAPH_STRUCTURE[0], algorithm[0], union_find[0])		    			
                process = subprocess.Popen(NAME_PROGRAM + command_args, stdout=subprocess.PIPE, shell=True)
                process.wait()
                
                t = int(str(process.stdout.readlines()[0]).split(" ")[2])
                
                file.write("%s, %s;%d\n" % (algorithm[1], union_find[1], t))
                
                print("%s, %s completed, time is %d" % (algorithm[1], union_find[1], t))
                