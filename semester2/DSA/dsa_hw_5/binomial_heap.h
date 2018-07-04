#include <utility>
#include <list>
#include <cassert>
using namespace std;

struct EmptyHeap: public std::exception {};

template<class T>
class BinomialHeap {
    private:
        /* inner class: binomial tree */
        struct BinomialTree {
            int _size;
            T element;
            std::list<BinomialTree*> children;

            BinomialTree(T _ele): _size(1), element(_ele) {
                children.clear();
            }

            /* return the size of BinomialTree
             * #note that nullptr->size() == 0
             * (nullptr is a null pointer (like NULL in C))
             */
            int size() {
                return (this!=nullptr)?this->_size:0;
            }
        };
        /* some definition for convinience
         */
        typedef BinomialTree BT;
        typedef BinomialHeap<T> BH;
        typedef std::pair<BT*, BT*> CarrySum;
        typedef std::pair<T, BH> MaxRemainder;

        /* Merge three binomial trees which have the same sizes
         *
         * INPUT:   a: operand a, b: operand b, c: carry in
         *          (each of them are either nullptr or a pointer of BinomialTree with size 2^n)
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: carry out (nullptr or a pointer of BinomialTree with size 2^(n+1))
         *          second: sum (nullptr or a pointer of BinomialTree with size 2^n)
         *
         * (just as a full adder: http://en.wikipedia.org/wiki/Adder_%28electronics%29#Full_adder )
         */
        CarrySum merge_tree(BT *a, BT *b, BT *c) {
            if(a == nullptr && b == nullptr && c == nullptr)
                return(make_pair(nullptr, nullptr));
            else if(a == nullptr && b == nullptr)
                return(make_pair(nullptr, c));
            else if(c == nullptr){
                if(b == nullptr)
                    return(make_pair(nullptr, a));
                else if(a == nullptr)
                    return(make_pair(nullptr, b));
                else{
                    if(a->element > b->element){
                        assert(a->_size == b->_size);
                        a->children.push_back(b);
                        a->_size += b->_size;
                        return(make_pair(a, nullptr));
                    }
                    else{
                        assert(a->_size == b->_size);
                        b->children.push_back(a);
                        b->_size += a->_size;
                        return(make_pair(b, nullptr));
                    }      
                }
            }
            else{
                if(b == nullptr)
                    if(a->element > c->element){
                        assert(a->_size == c->_size);
                        a->children.push_back(c);
                        a->_size += c->_size;
                        return(make_pair(a, nullptr));
                    }
                    else{
                        assert(a->_size == c->_size);
                        c->children.push_back(a);
                        c->_size += a->_size;
                        return(make_pair(c, nullptr));
                    }
                else if(a == nullptr){
                    if(b->element > c->element){
                        assert(c->_size == b->_size);
                        b->children.push_back(c);
                        b->_size += c->_size;
                        return(make_pair(b, nullptr));
                    }
                    else{
                        assert(c->_size == b->_size);
                        c->children.push_back(b);
                        c->_size += b->_size;
                        return(make_pair(c, nullptr));
                    }
                }
                else{
                    if(a->element > b->element){
                        assert(a->_size == b->_size);
                        a->children.push_back(b);
                        a->_size += b->_size;
                        return(make_pair(a, c));
                    }
                    else{
                        assert(a->_size == b->_size);
                        b->children.push_back(a);
                        b->_size += a->_size;
                        return(make_pair(b, c));
                    }  
                }
            }
        };

        /* Pop the maximum element of a binomial tree and make other elements a binomial heap.
         *
         * INPUT:   a: a pointer of BinomialTree
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: the maximum element
         *          second: a binomial heap consists of other elements
         */
        MaxRemainder pop_max(BT *a) {
            T max = a->element;
            BH htmp;
            htmp.size = a->_size - 1;
            typename std::list<BinomialTree*>::iterator btptr;
            int count = 0;
            
            for(btptr = a->children.begin(); btptr != a->children.end(); btptr++){
                if((*btptr)->_size != 0){
                    htmp.trees[count] = *btptr;
                    count++;
                }
            }
            return(make_pair(max, htmp));
        }

        int size;
        BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.

    public:
        BinomialHeap(): size(0) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
        }
        BinomialHeap(T element): size(1) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
            trees[0] = new BT(element);
        }

        /* merge all elements in the binomial heap b into *this, and clear the binomial heap b.
         *
         * INPUT:   b: a reference of BinomialHeap
         */
        void merge(BH &b) {
            this->size += b.size;
            CarrySum cstmp = make_pair(nullptr, nullptr);
            for(int i = 0; i < 32; i++){
                cstmp = merge_tree(this->trees[i], b.trees[i], cstmp.first);
                this->trees[i] = cstmp.second;
            }
            b.size = 0;
            for(int i = 0; i < 32; i++){
                b.trees[i] = nullptr;
            }
        }

        void insert(const T &element) {
            BH tmp = BH(element);
            merge(tmp);
        }
        T pop() {
            if(size==0) throw EmptyHeap();
            else {
                int max_tree = -1;
                for(int i=0; i<32; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;
                MaxRemainder m_r = pop_max(trees[max_tree]);
                T &max_element = m_r.first;
                BH &remainder = m_r.second;

                size -= trees[max_tree]->size();
                trees[max_tree] = nullptr;
                merge(remainder);

                return max_element;
            }
        }

        int getsize(){
            return size;
        }

        int getmaxp(){
            int maxp = -1;
            for(int i = 0; i < 32; i++){
                if(trees[i] != nullptr && trees[i]->element.second > maxp){
                    maxp = trees[i]->element.second;
                }
            }
            return maxp;
        }
};

class MyPair{
public:
    int first;
    int second;
    MyPair(){first = 0; second = 0;}
    MyPair(int id, int priority){first = id; second = priority;}
    bool operator>(const MyPair b){
        if(second != b.second)
            return (second > b.second);
        else
            return(first < b.first);
    }
};
