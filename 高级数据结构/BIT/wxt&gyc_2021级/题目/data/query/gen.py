from cyaron import *
import random as ra
for i in range(1,11,1):
    io=IO(file_prefix="query", data_id=i)
    sumn=500000
    summ=500000
    t=ra.randint(1,100)
    io.input_writeln(t)
    for jj in range(t):
        n=ra.randint(1,sumn-t+jj-2)
        m=ra.randint(1,summ-t+jj-2)
        sumn=sumn-n
        summ=summ-m
        print(n,m,sumn,summ,t-jj+2)
        io.input_writeln(n,m)
        for i in range(n):
            io.input_write(ra.randint(1,1000)," ")
        io.input_write("\n")
        for j in range(m):
            if ra.randint(0,1)==0:
                l=ra.randint(1,n)
                r=ra.randint(1,n)
                if l>r:
                    tt=l
                    l=r
                    r=tt
                io.input_writeln(2,l,r)
            else:
                io.input_writeln(1,ra.randint(1,n),ra.randint(1,10000))
    io.output_gen("~/OI/BIT/contest/data/query/query")