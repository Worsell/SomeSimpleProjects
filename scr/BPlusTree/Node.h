//
// Created by Ivan Korotkii on 22/10/2018.
//

#ifndef SIMPLEB_TREE_NODE_H
#define SIMPLEB_TREE_NODE_H
#include <vector>
// Два типа нод - лист и узел
// Различия - в узлах в качестве value вектора хранятся ссылки на Node, в листах хранятся сами значения
//

namespace tree {

    template<class T>
    class Node {

// В каждой ноде хранятся элементы не превосходящие, которые будет смотреть на нее из корня.
    public:
        using ptr_node_main = std::shared_ptr<Node<T>>;
        using ptr_node_week = std::weak_ptr<Node<T>>;

        using pair = std::pair<T, ptr_node_main>;
        using vec = std::vector<pair>;

        Node() = default;

        Node(unsigned long size) {
            data = vec();
            data.reserve(size);
        }

        Node(vec &&vector) {
            data = std::move(vector);
        }

        ~Node() = default;

        const vec &getData() const {
            return data;
        }

        pair &getFirst() {
            if (data.size() > 0)
                return data.at(0);
            else
                throw std::domain_error("error");
        }

        pair &getLast() {
            if (data.size() > 0)
                return data.at(data.size() - 1);
            else
                throw std::domain_error("error");
        }

        bool add(pair element) {
            auto item = std::lower_bound(data.begin(), data.end(), element);
            data.insert(item, element);
            return true;
        }

        bool isExist(pair &element) {
            return std::find_if(data.begin(), data.end(), [&](pair p1) { return(element.first == p1.first);}) != data.end();
        }

        bool remove(pair &element) {
            auto it = std::find_if(data.begin(), data.end(), [&](pair p1) { return(element.first == p1.first);});
            if(it != data.end()) {
                data.erase(it);
                return true;
            }
            return false;
        }

        ptr_node_week getParent() {
            return parent;
        }

        void setParent(ptr_node_week parent) {
            Node::parent = parent;
        }

        ptr_node_week getLeft() {
            return left;
        }

        void setLeft(ptr_node_week left) {
            if (left.lock() != nullptr)
                Node::left = left;
        }

        ptr_node_week getRight() {
            return right;
        }

        void setRight(ptr_node_week right) {
            if(right.lock() != nullptr)
                Node::right = right;
        }

        Node(const Node<T> &element) = delete;

    private:
        // Содержание ноды
        vec data = vec();

        ptr_node_week parent;

        ptr_node_week left;
        ptr_node_week right;


    };


}

#endif //SIMPLEB_TREE_NODE_H
