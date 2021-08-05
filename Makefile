INC = /home/pplp/include
LIB = /home/pplp/lib
LD = -lsdsl 

test1: *.cpp
	g++ *.cpp -o test1 --std=c++11 -I${INC} -L${LIB} ${LD} 
	
clean:
	rm -f *.o test1

