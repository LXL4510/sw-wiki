from cyaron import *
import random as ra
for i in range(1,6,1):
    io=IO(file_prefix="easy", data_id=i)
    n=ra.randint(100,1000)
    m=ra.randint(1000,10000)
    io.input_writeln(n,m)
    for j in range(m):
        if ra.randint(0,1)==0:
            l=ra.randint(1,n)
            r=ra.randint(1,n);
            if l>r:
                t=l
                l=r
                r=t
            io.input_writeln(1,l,r)
        else:
            io.input_writeln(2,ra.randint(1,n))
    io.output_gen("~/OI/BIT/contest/data/easy/easy")
for i in range(6,10,1):
    io=IO(file_prefix="easy", data_id=i)
    n=ra.randint(10000,100000)
    m=ra.randint(100000,500000)
    io.input_writeln(n,m)
    for j in range(m):
        if ra.randint(0,1)==0:
            l=ra.randint(1,n)
            r=ra.randint(1,n);
            if l>r:
                t=l
                l=r
                r=t
            io.input_writeln(1,l,r)
        else:
            io.input_writeln(2,ra.randint(1,n))
    io.output_gen("~/OI/BIT/contest/data/easy/easy")
        