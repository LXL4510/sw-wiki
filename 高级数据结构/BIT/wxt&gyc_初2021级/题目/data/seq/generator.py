from cyaron import *
import random as ra
for i in range(2,11,1):
    io=IO(file_prefix="seq", data_id=i)
    sumn=100000
    t=ra.randint(1,10)
    io.input_writeln(t)
    for jj in range(t):
        n=ra.randint(1,sumn-t+jj-2)
        sumn=sumn-n
        io.input_writeln(n)
        for i in range(n):
            io.input_write(ra.randint(1,1000000)," ")
        io.input_write("\n")
    io.output_gen("~/OI/BIT/contest/data/seq/seq")