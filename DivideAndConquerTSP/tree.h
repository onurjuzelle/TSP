#ifndef _tree_h
#define _tree_h

#include "city.h"
using namespace std;

class tree_node
{
    public:
        tree_node();
        tree_node *& get_left();
        tree_node *& get_right(); 
        int set_city(city *& city_in); 
        city *& get_city(); 
    protected:
        city * tree_city;
        tree_node * left;
        tree_node * right;
};

class tree
{
    public:
        tree();
        tree(city * city_in);
        ~tree();
        tree(tree & source);
        void add_to_tree(city *& to_add); 
        void display_detailed_tree(); 
        void clear_tree(); 
        void build_list(deque <city*> & neighbor_list, int size);
        bool operator == (tree & tree_in);
        bool operator != (tree & tree_in);
        tree & operator += (city * to_add);
        tree & operator += (tree & to_add);
        tree & operator = (tree & source);
        tree operator + (city * to_add);
        tree operator + (tree & tree_in);
        friend tree operator + (city * city_in,  tree & tree_in);
        friend ostream & operator << (ostream & output,  tree & source);
    private:
        city * owner_city;
        tree_node * root;
        void copy(tree_node * source, tree_node *& dest); 
        void insert(tree_node *& root, city *& to_add); 
        void traverse_and_display(tree_node * root); 
        void traverse_and_add(tree_node * source, tree & dest); 
        void remove_all(tree_node *& root); 
        void traverse_and_build(tree_node * root, deque <city*> & neighbor_list, int size);
        bool is_equal(tree_node * root_one = NULL, tree_node * root_two = NULL);
};

void traverse_and_output(ostream & output, tree_node * root);
#endif
