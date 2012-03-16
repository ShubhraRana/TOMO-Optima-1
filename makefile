TOMO-OPTIMA : underlying_topology.o
	c++ TOMO-OPTIMA.cc lib/underlying_topology.o -I./include -L./lib -L../build/ -I../build/ -lns3-core -lns3-internet -lns3-applications -lns3-network -lns3-csma -o TOMO-OPTIMA 

underlying_topology.o :
	c++ -c src/underlying_topology.cc -fPIC -Iinclude/ -I../build/ -o lib/underlying_topology.o

clean:
	rm -r lib/*.so lib/*.o

uninstall:
	rm -r *.o

exec:
	./TOMO-OPTIMA

install:
	mv TOMO-OPTIMA /usr/bin/ 
