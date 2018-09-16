//
// Created by Ivan Korotkii on 06/09/2018.
//

#ifndef SEARCHTREE_NODE_H
#define SEARCHTREE_NODE_H

#include <iostream>

namespace myLibrary {

    template<typename T>
    class Node {
    public:
        Node() = default;

        Node(T element, Node *left, Node *parent, Node *right) {
            setLeft(left);
            setElement(element);
            setRight(right);
            setParent(parent);
        }

        T getElement() const {
            return this->element;
        }


        void setElement(T elements) {
            element = elements;
        }

        Node *getLeft() {
            return left;
        }

        void setLeft(Node *lefts) {
            if (lefts == nullptr)
                left = nullptr;
            else
                left = lefts;
        }

        Node *getRight() {
            return right;
        }

        Node *getParent() {
            return parent;
        }

        void setParent(Node *parents) {
            if (parents == nullptr)
                parent = nullptr;
            else
                parent = parents;
        }

        void setRight(Node *rights) {
            if (rights == nullptr)
                right = nullptr;
            else
                right = rights;
        }

        virtual ~Node() {
            delete left;
            delete right;
            right = nullptr;
            parent = nullptr;
            left = nullptr;
        }


    private:
        T element;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
    };
}

#endif //SEARCHTREE_NODE_H
