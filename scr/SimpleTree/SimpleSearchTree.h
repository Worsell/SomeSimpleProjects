//
// Created by Ivan Korotkii on 06/09/2018.
//

#ifndef SEARCHTREE_SIMPLESEARCHTREE_H
#define SEARCHTREE_SIMPLESEARCHTREE_H


#include "Node.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

namespace myLibrary {

    template<typename T>
    class SimpleSearchTree {
    public:

        SimpleSearchTree() = default;

        explicit SimpleSearchTree(std::shared_ptr<Node<T>> root) : root(root) {
            size++;
        }
        // Эффективно создаем сбалансированное(на будущее) древо по отсортированной последовательности
        template <typename iter>
        SimpleSearchTree(const iter begin, const iter end) {
            if (begin <= end) {
                int a = 0;
                for (auto i = begin; i < end; i++) a++;
                int b = a / 2;
                iter midle = (begin + b);
                root = std::make_shared<Node<T>>(*midle, nullptr, std::make_shared<Node<T>>(), nullptr);
                if (begin <= (midle - 1 )) {
                    auto l = SimpleSearchTree(begin, midle - 1);
                    root->setLeft(l.root);
                    if (l.root != nullptr)
                        l.root->setParent(root);
                }

                if ((midle+ 1) <= end) {
                    auto r = SimpleSearchTree(midle + 1, end);
                    root->setRight(r.root);
                    if (r.root != nullptr)
                        r.root->setParent(root);
                }
            }
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
                        previous, nullptr));
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
        // Ну это очень тупо для замеров производительности
        template<typename iter>
        bool insertAllbad(iter begin, iter end) {
            //std::sort(begin, end, std::less<T>());
            auto tmp = SimpleSearchTree<T>();
            int b = 10;
            for (auto i = begin; i != end; i++) {
                tmp.insert(*i);
                if ((tmp.size != 0) && (tmp.size % b == 0)) {
                    if (root == nullptr) {
                        root = tmp.root;

                    } else {
                        std::shared_ptr<Node<T>> const node = getParent(tmp.root->getElement(), root);
                        if (node->getElement() > tmp.root->getElement()) {
                            node->setLeft(tmp.root);
                            tmp.root->setParent(node);
                        } else {
                            node->setRight(tmp.root);
                            tmp.root->setParent(node);
                        }
                    }
                    size += (tmp.size);
                    tmp = SimpleSearchTree<T>();
                }
            }
            if (root == nullptr) {
                root = tmp.root;
            } else {
                if (tmp.size != 0) {
                    std::shared_ptr<Node<T>> const node = getParent(tmp.root->getElement(), root);
                    if (node->getElement() > tmp.root->getElement()) {
                        node->setLeft(tmp.root);
                        tmp.root->setParent(node);
                    } else {
                        node->setRight(tmp.root);
                        tmp.root->setParent(node);
                    }
                }
            }
            size += (tmp.size);
            return true;
        }

        template<typename iter>
        bool insertAll1(const iter begin, const iter end) {
            // Получаем из дерева линейную последовательность за линию но не эффективно
            // эффективно - лень
            std::shared_ptr<std::queue<std::shared_ptr<Node<T>>>> queue = std::make_shared<std::queue<std::shared_ptr<Node<T>>>>();
            lndOrder(root, queue);
            int a = queue->size();
            iter b = begin;
            std::vector<T> tmp = std::vector<T>();
            while ((queue->size() > 0) && (b != end)){
                if ((queue->front()->getElement() < *b)) {
                    tmp.push_back(queue->front()->getElement());
                    queue->pop();
                }else {
                    tmp.push_back(*b);
                    b++;
                }
            }
            while (queue->size() > 0) {
                tmp.push_back(queue->front()->getElement());
                queue->pop();
            }
            while (b != end) {
                tmp.push_back(*b);
                b++;
            }
            SimpleSearchTree<T> tree = SimpleSearchTree(tmp.begin(), tmp.end()-1);
            root = tree.root;
            return true;
        }

        template<typename iter>
        bool insertAll(const iter begin, const iter end) {
            if (root == nullptr) {
                ::std::shared_ptr<::myLibrary::SimpleSearchTree<T>> tmp = std::make_shared<SimpleSearchTree<T>>(begin, end);
                root = tmp->root;
            } else {
                iter midle  = begin;
                while ((*midle < root->getElement()) && (midle != end))
                    midle++;
                if ((root->getLeft() != nullptr) && (root->getRight() != nullptr)) {
                    if (midle < end) {
                        insertSubsequence(begin, midle-1, root->getLeft());
                        insertSubsequence(midle, end, root->getRight());
                    } else if (midle != begin) {
                        insertSubsequence(begin, end, root->getLeft());
                    } else {
                        insertSubsequence(begin, end, root->getRight());

                    }
                }
                else {
                    if (root->getLeft() == nullptr) {
                        ::std::shared_ptr<::myLibrary::SimpleSearchTree<T>> tmp = std::make_shared<SimpleSearchTree<T>>(begin, midle - 1);
                        root->setLeft(tmp->root);
                        tmp->root->setParent(root);
                    }
                    if (root->getRight() == nullptr) {
                        ::std::shared_ptr<::myLibrary::SimpleSearchTree<T>> tmp = std::make_shared<SimpleSearchTree<T>>(midle, end);
                        root->setRight(tmp->root);
                        tmp->root->setParent(root);
                    }
                }
            }
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
        template <typename itera>
        std::shared_ptr<Node<T>> const insertSubsequence(const itera begin, const itera end, std::shared_ptr<Node<T>> node) {
            itera midle  = begin;
            while ((*midle < node->getElement()) && (midle != end))
                midle++;
            if ((node->getLeft() != nullptr) && (node->getRight() != nullptr)) {
                if (midle < end) {
                    insertSubsequence(begin, midle-1, node->getLeft());
                    insertSubsequence(midle, end, node->getRight());
                } else if (midle != begin) {
                    insertSubsequence(begin, end, node->getLeft());
                } else {
                    insertSubsequence(begin, end, node->getRight());

                }
            }
            else {
                if (node->getLeft() == nullptr) {
                    ::std::shared_ptr<::myLibrary::SimpleSearchTree<T>> tmp = std::make_shared<SimpleSearchTree<T>>(begin, midle - 1);
                    node->setLeft(tmp->root);
                    if(tmp->root != nullptr)
                        tmp->root->setParent(node);
                }
                if (node->getRight() == nullptr) {
                    ::std::shared_ptr<::myLibrary::SimpleSearchTree<T>> tmp = std::make_shared<SimpleSearchTree<T>>(midle, end);
                    node->setRight(tmp->root);
                    if(tmp->root != nullptr)
                        tmp->root->setParent(node);
                }
            }
            return node;
        }

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
        // TODO дебаг
        // следующий элемент при обходе древа итератором
        std::shared_ptr<Node<T>> const getNext(std::shared_ptr<Node<T>> const node) {
            if (node == nullptr) throw std::invalid_argument("Null pointer exception");

            if (node->getRight() != nullptr)
                return getMinNode(node->getRight());

            std::shared_ptr<Node<T>> tmp = node;
            if (tmp->getParent().lock() == nullptr) return nullptr;
            while (tmp->getParent().lock()->getLeft() != tmp) {
                tmp = tmp->getParent().lock();

            }
            return tmp;
        }


        // TODO дебаг
        // предыдущий элемент при обходе древа итератором
        std::shared_ptr<Node<T>> const getPrevious(std::shared_ptr<Node<T>> const node) {
            if (node == nullptr) throw std::invalid_argument("Null pointer exception");

            if (node->getLeft() != nullptr)
                return getMaxNode(node->getLeft());

            std::shared_ptr<Node<T>> tmp = node;
            if (tmp->getParent().lock() == nullptr) return nullptr;
            while (tmp->getParent().lock()->getRight() != tmp) {
                tmp = tmp->getParent().lock();
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

        void lndOrder(std::shared_ptr<Node<T>> node, std::shared_ptr<std::queue<std::shared_ptr<Node<T>>>> queue){
            if(node != nullptr) {
                lndOrder(node->getLeft(), queue);
                queue->push(node);
                lndOrder(node->getRight(), queue);
            }

        }



    public:
        // Оно неоч корректно от слова совсем
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
