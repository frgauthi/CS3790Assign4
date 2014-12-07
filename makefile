cc = g++
obj = format.o
bin = format


$(bin):	$(obj)
	$(cc) $(obj) -o $(bin)

.cpp.o:
	$(cc) -c $<

clean:
	rm *.o $(bin) Floppy.mfs cat dir delete
