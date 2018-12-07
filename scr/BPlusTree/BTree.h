//
// Created by Ivan Korotkii on 22/10/2018.
//


#ifndef SIMPLEB_TREE_BTREE_H
#define SIMPLEB_TREE_BTREE_H

#include "Node.h"
#include <iostream>
// Обертка дерева, с которой работаем

namespace tree {

    template<class T = int>
    class BTree {
        using main_ptr = std::shared_ptr<Node<T>>;
        using Pair = std::pair<T, main_ptr>;
        using week_ptr = std::weak_ptr<Node<T>>;

    public:

        BTree() = default;

        explicit BTree(unsigned long width) {
            _width_ = width;
            root = std::make_shared<Node<T>>(_width_);
        }

        ~BTree() = default;

        // Добавляет элемент в древо
        // Реализация возможность вставки дублирующихся элементов (официально не поддерживается)
        // Возвращает true если добавление прошло успешно
        bool insert(const T &data) {
            if(root == nullptr)
                root = std::make_shared<Node<T>>(_width_);
            put(data);
            _size_++;
            return true;
        }

        // Удаляем элемент из дерева
        // Возвращаем True если удаление прошло успешно
        // False если элемента не было
        bool remove(const T &data) {
            if(root == nullptr)
                return true;
            main_ptr tmp = get(root, data);
            Pair t = Pair(data, nullptr);
            Pair p;
            try {
                p = tmp->getFirst();
            } catch(std::domain_error e) {

            }
            if(tmp->remove(t)) {
                repair(tmp, p);
                _size_--;
                return true;
            }
            return false;
        };
        // Принимает элемент у которого перегружена операция сравнения
        // Возвращает ссылку на данные соответсвующие данному T
        const T * get(const T &data) {
            if (root == nullptr) {
                return nullptr;
            }
            main_ptr tmp = get(root, data);
            Pair t = Pair(data, nullptr);
            auto f = std::find(tmp->getData().begin(), tmp->getData().end(), t);
            if ((f != tmp->getData().end()) || (*tmp->getData().end() == t)) {
                const T * answer = &f->first;
                return answer;
            } else
                return nullptr;
        };

        // Производит поиск в дереве
        // Возвращает true если поиск прошел успешно и элемент существует в дереве
        bool search(const T &data) {
            if (root == nullptr) {
                return false;
            }
            main_ptr tmp = get(root, data);
            Pair t = Pair(data, nullptr);
            bool p = (std::find(tmp->getData().begin(), tmp->getData().end(), t) != tmp->getData().end());
            //Pair dt = *tmp->getData().end();
            //bool m = (dt == t);
            return  p;
        }

        const long size() const {
            return _size_;
        }

        void print() {
            main_ptr n = getMin(root);
            print(n);
        }

    private:

        main_ptr root;

        // Количество элементов в ноде
        unsigned long _size_ = 0;

        // Максимальная длинна каждой ноды
        unsigned long _width_ = 100;

        // Возвращает лист, в которой нужно класть текущий элемент.
        main_ptr get(main_ptr node, const T &element) const {
            if (node->getData().size() == 0)
                return node;
            int count = 0;
            while ((node->getData().size() > count) && (node->getData().at(count).first <= element))
                count++;
            if (count == 0) return node;
            if (node->getData().at(count-1).second == nullptr) return node;
            else return get(node->getData().at(count-1).second, element);
        }

        // Кладем в ноду что-то интересное возвращаем ноду, куда положили
        main_ptr &put(const T &data) {
            main_ptr leaf = get(root, data);
            Pair pair = Pair(data, nullptr);
            Pair f;
            try {
                f = leaf->getFirst();
            } catch(std::domain_error e) {

            }
            leaf->add(pair);
            repair(leaf, f);
            return leaf;
        }

        // Разрезаем вектор на два новых и возвращаем ссылку на пару новых векторов
        // TODO Можно как-то низкоуровнево оптимизировать чтобы не насиловать память копированием
        std::pair<std::vector<Pair>, std::vector<Pair>>
        restruct(const std::vector<Pair> &node) {

            std::vector<Pair> first = std::vector<Pair>();
            first.reserve(_width_);
            std::vector<Pair> second = std::vector<Pair>();
            second.reserve(_width_);


            for (long x = 0; x < node.size() / 2; x++) {
                first.push_back(node.at(x));
            }
            for (long x = node.size() / 2; x < node.size(); x++) {
                second.push_back(node.at(x));
            }
            std::pair<std::vector<Pair>, std::vector<Pair>> p = std::pair<std::vector<Pair>, std::vector<Pair>>(first,
                                                                                                                second);

            return p;
        }

        // Объединяем два отсортированных вектора в один и возвращаем его
        // Последний элемент первой ноды меньше чем первый элемент второй ноды
        // TODO Можно нормально оптимизировать для работы с памятью
        std::vector<Pair> connect(const std::vector<Pair> &one, const std::vector<Pair> &second) {
            std::vector<Pair> answer = std::vector<Pair>();
            answer.reserve(_width_);
            for (Pair iter: one) {
                answer.push_back(iter);
            }
            for (Pair iter: second) {
                answer.push_back(iter);
            }
            return answer;
        }

        // Рекурсивная починка текущей ноды
        void repair(main_ptr &node, Pair &f) {
            Pair t;
            Pair p;
            main_ptr right = node->getRight().lock();
            main_ptr left = node->getLeft().lock();
            main_ptr parent = node->getParent().lock();

            // Тут смотрим, можно ли что-то удалить
            if (node->getParent().lock() != nullptr)
                t = node->getParent().lock()->getFirst();

            // Теоретический должно работать!

            // Тут целиком и полностью случай, когда в данной ноде не осталось элементов
            // Когда эта нода - корень без элементов тоже тут рассматриваем
            if (node->getData().size() == 0) {
                    if (parent == nullptr)
                        root = nullptr;
                    else {
                        parent->remove(f);
                        if (node->getLeft().lock() != nullptr)
                            node->getLeft().lock()->setRight(node->getRight());
                        if (node->getRight().lock() != nullptr)
                            node->getRight().lock()->setLeft(node->getLeft());
                        repair(parent, t);
                    }
                return;
            } else
            if (((node->getData().size() < _width_ / 3) &&
                 (node->getLeft().lock() != nullptr) &&
                 (node->getLeft().lock()->getData().size() < _width_ / 3)) ||
                ((node->getData().size() < _width_ / 3) &&
                 (node->getRight().lock() != nullptr) &&
                 (node->getRight().lock()->getData().size() < _width_ / 3))) {

                // Удаляем ссылку на эту ноду.
                parent->remove(f);
                // С какой будем объединять
                if (left->getData().size() < right->getData().size()) {
                    left->getParent().lock()->remove(left->getFirst());
                    main_ptr n = get_new_node_decrease_size(left, node);
                    n->setParent(parent);
                    p = Pair(n->getFirst().first, n);
                    parent->add(p);
                    main_ptr m = left->getParent().lock();
                    // repair(m, left->getFirst());
                } else {
                    right->getParent().lock()->remove(right->getFirst());
                    main_ptr n = get_new_node_decrease_size(node, right);
                    n->setParent(parent);
                    p = Pair(n->getFirst().first, n);
                    parent->add(p);
                    main_ptr m = right->getParent().lock();
                    // repair(m, right->getFirst());
                }
                repair(parent, t);
                return;
            } else

            // Тут смотрим на то, требуется ли расширить древо
            // ОТЛАЖЕНО
            if (node->getData().size() > _width_) {
                std::pair<main_ptr, main_ptr> k = get_new_node_increase_size(node, f);
                main_ptr left_node = k.first;
                main_ptr right_node = k.second;
                if (parent != nullptr) {
                    parent->remove(f);
                    p = Pair(left_node->getFirst().first, left_node);
                    parent->add(p);
                    left_node->setParent(parent);
                    p = Pair(right_node->getFirst().first, right_node);
                    parent->add(p);
                    right_node->setParent(parent);
                    repair(parent, t);
                } else {
                    parent = std::make_shared<Node<T>>(_width_);
                    Pair p = make_pair(left_node->getFirst().first, left_node);
                    left_node->setParent(parent);
                    parent->add(p);
                    p = make_pair(right_node->getFirst().first, right_node);
                    right_node->setParent(parent);
                    parent->add(p);
                    root = parent;
                }
                return;
            } else
            if (parent != nullptr && (node->getFirst().first != f.first) && (parent->isExist(f))) {
                parent->remove(f);
                p = make_pair(node->getFirst().first, node);
                parent->add(p);
                repair(parent, f);
            }
        }

        void decrease_size(main_ptr &node, Pair &t) {

        }

        // Принимаем две ноды, при этом максимальный в 1 ноде больше чем минимальный во второй
        // Склеиваем их в одну НОВУЮ ноду
        // Проставляем parent ссылки у их потомков ЕСЛИ ОНИ ЕСТЬ на НОВУЮ ноду
        main_ptr &get_new_node_decrease_size(main_ptr &node1, main_ptr &node2) {
            std::vector<Pair> v = connect(node1->getData(), node2->getData());
            main_ptr n = std::make_shared<Node<T>>(std::move(v));
            n->setLeft(node1->getLeft());
            if (node1->getLeft().lock() != nullptr)
                node1->getLeft().lock()->setRight(n);
            n->setRight(node2->getRight());
            if (node2->getRight().lock() != nullptr)
                node1->getRight().lock()->setLeft(n);
            for(Pair x : n->getData()) {
                if (x.second != nullptr)
                    x.second->setParent(n);
            }
            return n;
        }

        std::pair<main_ptr, main_ptr> get_new_node_increase_size(main_ptr &node, Pair &t) {

                auto pair = restruct(node->getData());
                main_ptr right = node->getRight().lock();
                main_ptr left = node->getLeft().lock();
                main_ptr parent = node->getParent().lock();

                main_ptr left_node = std::make_shared<Node<T>>(move(pair.first));
                for(Pair p : left_node->getData()) {
                    if (p.second != nullptr) {
                        p.second->setParent(left_node);
                    }
                }

                main_ptr right_node = std::make_shared<Node<T>>(move(pair.second));
                for(Pair p : right_node->getData()) {
                    if (p.second != nullptr) {
                        p.second->setParent(right_node);
                    }
                }

                // Левая нода
                // Присойденяем в качестве сслыки на предыдущую ноду исходную ссылку на предыдущую ноду
                left_node->setLeft(left);
                if(left != nullptr)
                    left->setRight(left_node);
                // Присойденяем в качестве ссылки на следующую ноду ссылку на первый элемент правой ноды
                left_node->setRight(right_node);
                // Загружаем данные в ноду

                // Правая нода
                // Присойденяем в качестве ссылки на следующую ноду исходный указатель на следующую ноду
                right_node->setRight(right);
                if(right!= nullptr)
                    right->setLeft(right_node);
                // Присойденяем в качестве ссылки на предыдующую ноду последний элемент левой ноды
                right_node->setLeft(left_node);
                // Загружаем данные в ноду
                std::pair<main_ptr, main_ptr> d = std::pair<main_ptr, main_ptr>(left_node, right_node);
                return d;
        }

        main_ptr getMin(main_ptr node) {
            if (node->getFirst().second == nullptr)
                return node;
            else
                return getMin(node->getFirst().second);
        }

        void print(main_ptr node) {
             do {
                for (Pair x : node->getData())
                    std::cout << x.first << " ";
                node = node->getRight().lock();
            } while (node->getRight().lock() != nullptr);
        }
    };

}

#endif //SIMPLEB_TREE_BTREE_H
