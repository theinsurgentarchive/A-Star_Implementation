all: a_star

quick:
	@$(MAKE) all QUICK=1 --no-print-directory

ifdef QUICK
a_star: test.cpp aStar.cpp
	@g++ test.cpp aStar.cpp -o a_star
	./astar

else
a_star: test.cpp aStar.cpp
	g++ test.cpp aStar.cpp -o a_star

endif

clean:
	rm -rf a_star