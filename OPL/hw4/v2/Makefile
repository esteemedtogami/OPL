C=g++ -g -Wall --std=c++11
E=.cpp
O=tombstones.o
P=a4
test: $(P)
$(P):$(O)
	$(C) -o $(P) $(O)
$(E).o:
	$(C) -c $<  -o $@
clean:
	rm $(O) $(P)

.PHONY: clean all
