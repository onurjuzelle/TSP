#include "tree.h"
#include <iostream>
using namespace std;

tree_node::tree_node() : tree_city(NULL), left(NULL), right(NULL) {}

tree_node *& tree_node::get_left()
{
    return left;
}

tree_node *& tree_node::get_right()
{
    return right;
}

int tree_node::set_city(city *& city_in)
{
    if (!city_in)
        return 0;
        
    tree_city = city_in;
    
    return 1;
}

city *& tree_node::get_city()
{
    return tree_city;
}

tree::tree() : owner_city(NULL), root(NULL) {}

tree::tree(city * city_in) : owner_city(city_in), root(NULL) {}

tree::~tree()
{
    clear_tree();
}

tree::tree(tree & source)
{
    copy(source.root, root);
}

void tree::copy(tree_node * source, tree_node *& dest)
{
    if (!source)
        dest = NULL;
        
    else
    {
        dest = new tree_node;
        dest->set_city(source->get_city());
        copy(source->get_left(), dest->get_left());
        copy(source->get_right(), dest->get_right());
    }
}

void tree::add_to_tree(city *& to_add)
{
    insert(root, to_add);
}

void tree::insert(tree_node *& root, city *& to_add)
{
    if (!root)
    {
        root = new tree_node;
        root->set_city(to_add);
        root->get_left() = root->get_right() = NULL;
    }
    
    else if (root->get_city()->dist(owner_city) < owner_city->dist(to_add))
    {
        insert(root->get_left(), to_add);
    }
        
    else
    {
        insert(root->get_right(), to_add);
    }
}


void tree::display_detailed_tree()
{
    traverse_and_display(root);
}

void tree::traverse_and_display(tree_node * root)
{
    if (!root) 
    {
      return; 
    }

    else
    {
        traverse_and_display(root->get_right());
        cout << root->get_city()->dist(owner_city) << endl;
        traverse_and_display(root->get_left());
    }
}

void tree::traverse_and_add(tree_node * source, tree & dest)
{
    if (!source)
    {
        return;
    }
        
    else
    {
        traverse_and_add(source->get_left(), dest);
        traverse_and_add(source->get_right(), dest);
        dest.add_to_tree(source->get_city());
    }
}

void tree::clear_tree()
{
    remove_all(root);
}

void tree::remove_all(tree_node *& root)
{
    if (!root)
    {
        return;
    }
        
    remove_all(root->get_left());
    remove_all(root->get_right());
    
    delete root;
    root = NULL;
}

bool tree::is_equal(tree_node * root_one, tree_node * root_two)
{   
    if ((!root_one && root_two) || (root_one && !root_two))
    {
        return false;
    }
        
    else if (!root_one && !root_two)
    {
        return true;
    }
        
    return (!root_one->get_city()->compare(root_two->get_city())
        && is_equal(root_one->get_left(), root_two->get_left())
        && is_equal(root_one->get_right(), root_two->get_right()));
}

void tree::build_list(deque <city*> & neighbor_list, int size)
{
    traverse_and_build(root, neighbor_list, size);
}

void tree::traverse_and_build(tree_node * root, deque <city*> & neighbor_list, int size)
{
    if (!root)
        return;
           
    else
    {
        traverse_and_build(root->get_right(), neighbor_list, size-1);
        neighbor_list.push_back(root->get_city());
        traverse_and_build(root->get_left(), neighbor_list, size-1);
    }
}

tree & tree::operator += ( city * to_add)
{
    add_to_tree(to_add); 
    return *this;
}


tree & tree::operator += ( tree & to_add)
{
    tree temp;
    if (this == &to_add) 
    {
        temp = to_add;
        traverse_and_add(temp.root, *this);
        return *this;
    }
    
    traverse_and_add(to_add.root, *this);
    return *this;
}

tree & tree::operator = ( tree & source)
{
    if (this == &source)
        return *this;
        
    if (root)
        clear_tree();
        
    copy(source.root, root);
    return *this;
}
 
tree tree::operator + ( city * to_add)
{
    tree temp;
    copy(root, temp.root);
    temp.add_to_tree(to_add);
    return temp;
}

tree tree::operator + ( tree & tree_in)
{
    tree temp = tree_in;
    traverse_and_add(root, temp);
    return temp;
}

bool tree::operator == ( tree & tree_in)
{
    if (this == &tree_in)
    {
        return true;
    }
        
    else if (!root && !tree_in.root)
    {
        return true;
    }
    
    else
    {
        return is_equal(root, tree_in.root);
    }
}

bool tree::operator != ( tree & tree_in)
{
    if (this == &tree_in)
    {
        return false;
    }
        
    else if (!root && !tree_in.root)
    {
        return false;
    }
    
    else
    {
        return !is_equal(root, tree_in.root);
    }
}

tree operator + ( city * item_in,  tree & tree_in)
{
    tree temp = tree_in;
    temp.add_to_tree(item_in);
    return temp;
}

ostream & operator << (ostream & output,  tree & source)
{
    traverse_and_output(output, source.root);
    return output;
}

void traverse_and_output(ostream & output, tree_node * root)
{
        if (!root)
        {
            return;
        }
            
        traverse_and_output(output, root->get_left());
        root->get_city()->output_id(output);
        output << endl;
        traverse_and_output(output, root->get_right());
}    
