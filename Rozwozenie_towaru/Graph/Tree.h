#ifndef TREE_H
#define TREE_H

#include <vector>
#include <iostream>
#include <sstream>

template <class T>
class Tree
{

    T _value;
    Tree<T>* _parent;
    std::vector<Tree<T>*> _children;


public:
    Tree(): _parent(nullptr) {}
    Tree(const T& value): _value(value), _parent(nullptr) {}
    ~Tree(){
        if(_parent != nullptr){
            _parent->eraseChild(this);
        }

        while(_children.size() != 0){
            delete _children[0];
        }
    }

    const T& value() const{
        return _value;
    }

    T& value() {
        return _value;
    }

    const Tree <T>& parent() const{
        return *_parent;
    }

    Tree <T>& parent() {
        return *_parent;
    }

    void setParent(Tree<T> * parent){
        _parent = parent;
    }

    const Tree <T>& child(unsigned int position) const {
        return *(_children.at(position));
    }

    Tree <T>& child(unsigned int position) {
        return *(_children.at(position));
    }

    unsigned int childrenCount() const {
        return _children.size();
    }

    void pushChild(Tree<T>* child){
        child->setParent(this);
        _children.push_back(child);
    }

    void eraseChild(Tree<T>* child){
        for(unsigned int i=0;i<_children.size();++i){
            if(child == _children.at(i)){
                child->setParent(nullptr);
                _children.erase(_children.begin() + i);
                return;
            }
        }
    }


    std::vector<std::vector<T> > paths() const{
        std::vector<std::vector<T> > beanches;
        pathsRecursive(std::vector<T>(), beanches, *this);

        return beanches;
    }

    /**
     * @brief existsInUpTree function checks if value exists in any ancestor.
     * @param value
     * @return
     */
    bool existsInUpTree(const T& value) const {
        Tree<T>* node = _parent;

        while (node != nullptr) {
            if(node->value() == value)
                return true;
            node = node->_parent;
        }
        return false;
    }

private:
    void pathsRecursive(std::vector<T> currentBeanch, std::vector<std::vector<T> >& beanches, const Tree<T>& tree) const{
        currentBeanch.push_back(tree.value());

        if(tree.childrenCount() == 0){
            beanches.push_back(currentBeanch);
        }

        for(unsigned int i=0;i<tree.childrenCount();++i){
            pathsRecursive(currentBeanch, beanches, tree.child(i));
        }
    }
};

template <class T>
std::ostream& operator<<(std::ostream& str, const Tree<T>& tree){

    str<<tree.value()<<" ";

    for(unsigned int i=0;i<tree.childrenCount();++i){
        str<<tree.child(i);
    }

    return str;
}

#endif // TREE_H
