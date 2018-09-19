//
// Created by Ivan Korotkii on 06/09/2018.
//

#ifndef SEARCHTREE_SIMPLESEARCHTREE_H
#define SEARCHTREE_SIMPLESEARCHTREE_H


#include "Node.h"
#include <vector>
#include <queue>
#include <algorithm>

namespace myLibrary {

    template<typename T>
    class SimpleSearchTree {
    public:

        SimpleSearchTree() = default;

        explicit SimpleSearchTree(std::shared_ptr<Node<T>> root) : root(root) {

        }

        virtual ~SimpleSearchTree() {
            root = nullptr;
        }

        bool insert(T const element) {
            if (root == nullptr) {
                root = std::make_shared<Node<T>> (element, nullptr, std::weak_ptr<Node<T>>(), nullptr);
                size++;
                return true;
            }
            std::shared_ptr<Node<T>> const previous = getParent(element, root);
            if (element < previous->getElement()) {
                previous->setLeft(std::make_shared<Node<T>>(element, nullptr,
                        previous, std::make_shared<Node<T>>()));
            } else {
                previous->setRight(std::make_shared<Node<T>>(element, nullptr,
                        previous, nullptr));
            }
            size++;
            return true;
        }

        bool remove(T const element) {
            std::shared_ptr<Node<T>> const node = deleteNode(element, root);
            size--;
            return isValideTree(root);
        }

        T find(T element) {
            return findPtr(element);
        }

        T const findPtr(T const element) {
            std::shared_ptr<Node<T>> const ptr = getNode(element, root);
            if (ptr != nullptr) {
                return ptr->getElement();
            } else
                throw std::out_of_range("Element not found");
        }

        bool contains(T element) {
            return (getNode(element, root) != nullptr);
        }

        T const getMax() {
            if (root != nullptr)
                return getMaxNode(root)->getElement();
            return nullptr;
        }

        T const getMin() {
            if (root != nullptr)
                return getMinNode(root)->getElement();
            return nullptr;
        }

        // TODO можно оч эффективно реализовать через not look queue с асин созданием деревьев
        // При добавлении балансировки это просто хаос
        // Прикольно сделать чтобы константа подбиралась динамический
        // только для отсортированных данных
        // Ну тут нет утечек, вне зависимости от того, что показывает анализатор
        template<typename iter>
        bool insertAll(iter begin, iter end) {
            //std::sort(begin, end, std::less<T>());
            auto tmp = std::make_shared<SimpleSearchTree<T>>();
            int b = 100;
            for (auto i = begin; i != end; i++) {
                tmp->insert(*i);
                if ((tmp->size != 0) && (tmp->size % b == 0)) {
                    if (root == nullptr) {
                        root = tmp->root;

                    } else {
                        std::shared_ptr<Node<T>> const node = getParent(tmp->root->getElement(), root);
                        if (node->getElement() > tmp->root->getElement()) {
                            node->setLeft(tmp->root);
                            tmp->root->setParent(node);
                        } else {
                            node->setRight(tmp->root);
                            tmp->root->setParent(node);
                        }
                    }
                    size += (tmp->size);
                    tmp = nullptr;
                    tmp = std::make_shared<SimpleSearchTree<T>>();
                }
            }
            if (root == nullptr) {
                root = tmp->root;
            } else {
                if (tmp->size != 0) {
                    std::shared_ptr<Node<T>> const node = getParent(tmp->root->getElement(), root);
                    if (node->getElement() > tmp->root->getElement()) {
                        node->setLeft(tmp->root);
                        tmp->root->setParent(node);
                    } else {
                        node->setRight(tmp->root);
                        tmp->root->setParent(node);
                    }
                }
            }
            size += (tmp->size);
            tmp = nullptr;
            return true;
        }


        template<typename r>
        void inOrderLeft(std::function<r(T)> function) {
            if (root != nullptr) {
                inOrder(root->getLeft());
                function(root->getElement());
                inOrder(root->getRight());
            }
        }

        template<typename r>
        void preOrderRight(std::function<r(T)> function) {
            if (root != nullptr) {
                inOrder(root->getRight());
                function(root->getElement());
                inOrder(root->getLeft());

            }
        }

        int getSize() const {
            return size;
        }

    protected:

    private:
    public:
        std::shared_ptr<Node<T>> root = nullptr;
    private:
        int size = 0;

        // тут возвращаем указатель на ноду по элементу или нулевой указатель если такой не существует
        std::shared_ptr<Node<T>> const getNode(T const iter, std::shared_ptr<Node<T>> const tmp) {
            if (tmp == nullptr) return nullptr;
            if (iter == tmp->getElement()) return tmp;
            if (iter < tmp->getElement()) {
                if (tmp->getLeft() != nullptr)
                    return getNode(iter, tmp->getLeft());
                else
                    return nullptr;
            } else {
                if (tmp->getRight() != nullptr)
                    return getNode(iter, tmp->getRight());
                else
                    return nullptr;
            }
        }

        // тут возвращаем предыдущую ноду к которой надо присойденять элемент который преедается в функцию
        std::shared_ptr<Node<T>> const getParent(T const iter, std::shared_ptr<Node<T>> const tmp) {
            if (iter == tmp->getElement()) return tmp;
            if (iter < tmp->getElement()) {
                if (tmp->getLeft() == nullptr) {
                    return tmp;
                } else {
                    return getParent(iter, tmp->getLeft());
                }
            } else {
                if (tmp->getRight() == nullptr) {
                    return tmp;
                } else {
                    return getParent(iter, tmp->getRight());
                }
            }
        }

        // минимальная нода в древе по его корню
        std::shared_ptr<Node<T>> const getMinNode(std::shared_ptr<Node<T>> const node) {
            if (node->getLeft() == nullptr) {
                return node;
            } else
                return getMinNode(node->getLeft());
        }

        // максимальная нода в древе по его корню
        std::shared_ptr<Node<T>> const getMaxNode(std::shared_ptr<Node<T>> const node) {
            if (node->getRight() == nullptr) {
                return node;
            } else {
                return getMaxNode(node->getRight());
            }
        }
        // TODO реализовать
        // следующий элемент при обходе древа итератором
        std::shared_ptr<Node<T>> const getNext(std::shared_ptr<Node<T>> const node) {
            if (node == nullptr) throw std::invalid_argument("Null pointer exception");

            if (node->getRight() != nullptr)
                return getMinNode(node->getRight());

            Node<T> tmp = node;
            if (tmp.getParent() == nullptr) return nullptr;
            while (tmp.getParent()->getLeft() != tmp) {
                tmp = tmp.getParent();
            }
            return tmp;
        }


        // TODO реализовать
        // предыдущий элемент при обходе древа итератором
        std::shared_ptr<Node<T>> const getPrevious(std::shared_ptr<Node<T>> const node) {
            if (node == nullptr) throw std::invalid_argument("Null pointer exception");

            if (node->getLeft() != nullptr)
                return getMaxNode(node->getLeft());

            Node<T> tmp = node;
            if (tmp.getParent() == nullptr) return nullptr;
            while (tmp.getParent()->getRight() != tmp) {
                tmp = tmp.getParent();
            }
            return tmp;

        }

        // выводим ноду из древа по итератору
        std::shared_ptr<Node<T>> const deleteNode(T const element, std::shared_ptr<Node<T>> const node) {
            if ((node->getLeft() == nullptr) && (node->getRight() == nullptr) && (element == node->getElement()))
                return node;
            if (element < node->getElement())
                return deleteNode(element, node->getLeft());
            else if (element > node->getElement())
                return deleteNode(element, node->getRight());
            else if ((node->getLeft() != nullptr) && (node->getRight() != nullptr)) {
                std::shared_ptr<Node<T>> tmp = getMinNode(node->getRight());
                tmp = deleteNode(element, tmp);
                tmp->setLeft(node->getLeft());
                tmp->setRight(node->getRight());
                tmp->setParent(node->getParent());
                node->setLeft(nullptr);
                node->setRight(nullptr);
                return node;
            } else if (node->getLeft() != nullptr) {
                connectLeft(node->getLeft(), node->getParent());
                node->setLeft(nullptr);
                return node;
            } else {
                connectRight(node->getRight(), node->getParent());
                node->setRight(nullptr);
                return node;
            }
        }

        bool connectLeft(std::shared_ptr<Node<T>> const left, std::weak_ptr<Node<T>> const parent) {
            if (left != nullptr)
                left->setParent(parent);
            if (parent.lock() != nullptr)
                parent.lock()->setLeft(left);
            return true;
        }

        bool connectRight(std::shared_ptr<Node<T>> const right, std::weak_ptr<Node<T>> const parent) {
            if (right != nullptr)
                right->setParent(parent);
            if (parent.lock() != nullptr)
                parent.lock()->setRight(right);
            return true;
        }

    public:
        bool isValideTree(std::shared_ptr<Node<T>> const node) {
            if ((node->getLeft() == nullptr) && (node->getRight() == nullptr))
                return true;
            bool l = true;
            bool r = true;
            if (node->getLeft() != nullptr) {
                if (node->getLeft()->getElement() >= node->getElement()) return false;
                l = isValideTree(node->getLeft());
            }
            if (node->getRight() != nullptr) {
                if (node->getRight()->getElement() <= node->getElement()) return false;
                r = isValideTree(node->getRight());
            }
            return l && r;
        }
    };


}

#endif //SEARCHTREE_SIMPLESEARCHTREE_H
