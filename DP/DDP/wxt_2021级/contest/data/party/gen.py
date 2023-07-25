from cyaron import *
import random as r
for i in range(1,21,1):
    io=IO(file_prefix="party",data_id=i,input_suffix=".in",output_suffix=".out")
    n=r.randint(25000,50000)
    m=r.randint(25000,50000)
    io.input_writeln(n,m)
    for i in range(n):
        io.input_write(r.randint(-10,10000))
        io.input_write(' ')
    io.input_write('\n')
    tree=Graph.tree(n)
    io.input_writeln(tree.to_str(shuffle=True,output=Edge.unweighted_edge))
    for i in range(m):
        io.input_writeln(r.randint(1,n),r.randint(-10,10000))
    io.output_gen("D:\OI\party.exe")