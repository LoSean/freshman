target:3_4_1.out 3_4_2.out 
CPPFLAGS = -O2 -std=c++11 -Wall -DPRINT

3_4_1.out:3_4_1.cpp
	g++ $(CPPFLAGS) 3_4_1.cpp -o 3_4_1.out
3_4_2.out:3_4_2.cpp
	g++ $(CPPFLAGS) 3_4_2.cpp -o 3_4_2.out
clean:
	rm -rf 3_4_1.out 3_4_2.out
