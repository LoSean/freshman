target:tree forest a.out b.out c.out
CPPFLAG = -O2 -std=c++11 

tree:4_2_1.cpp
	g++ $(CPPFLAG) 4_2_1.cpp -o tree

forest:4_2_2.cpp
	g++ $(CPPFLAG) 4_2_2.cpp -o forest

a.out:tree_predictor.cpp tree_pred_func.cpp
	g++ $(CPPFLAG) tree_predictor.cpp tree_pred_func.cpp -o a.out

b.out:forest_predictor.cpp forest_pred_func.cpp
	g++ $(CPPFLAG) forest_predictor.cpp forest_pred_func.cpp -o b.out

c.out:forest_predictor.cpp forest_pred_func.cpp
	g++ -std=c++11 forest_pred_func.cpp forest_predictor.cpp -o c.out

clean:
	rm -rf tree forest a.out b.out c.out
