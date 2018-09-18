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

        Node(T const element, std::shared_ptr<Node<T>> left, std::weak_ptr<Node<T>> parent, std::shared_ptr<Node<T>> right) {
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

        std::shared_ptr<Node<T>> getLeft() {
            return left;
        }

        void setLeft(std::shared_ptr<Node<T>> lefts) {
            if (lefts == nullptr)
                left = nullptr;
            else
                left = lefts;
        }

        std::shared_ptr<Node<T>> getRight() {
            return right;
        }

        std::weak_ptr<Node<T>> getParent() {
            return parent;
        }

        void setParent(std::weak_ptr<Node<T>> parents) {
            if (parents.lock() == nullptr)
                throw new std::invalid_argument("Null pointer exception");
            else
                parent = parents;
        }

        void setRight(std::shared_ptr<Node<T>>rights) {
            if (rights == nullptr)
                right = nullptr;
            else
                right = rights;
        }

        virtual ~Node() {
            right = nullptr;
            left = nullptr;
        }


    private:

        T element;
        std::weak_ptr<Node<T>> parent = std::weak_ptr<Node<T>>();
        std::shared_ptr<Node<T>> left = nullptr;
        std::shared_ptr<Node<T>> right = nullptr;
    };
}

#endif //SEARCHTREE_NODE_H
