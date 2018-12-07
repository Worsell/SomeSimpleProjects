//
// Created by Ivan Korotkii on 04/11/2018.
//

#ifndef SIMPLETREE_SMARTBTREE_H
#define SIMPLETREE_SMARTBTREE_H

#include <vector>

template <class K=int, class V = std::string>
struct SmartPair {
    K first;
    V second;
    SmartPair(K key, V value) {
        first = key;
        second = value;
    }
    SmartPair() = default;

};

template <class K=int, class V=std::string>
const bool operator < (const SmartPair<K, V> &p1, const SmartPair<K, V> &p2) {
    return p1.first < p2.first;
}

template <class K, class V>
const bool operator == (const SmartPair<K, V> &p1, const SmartPair<K, V> &p2) {
    return p1.first == p2.first;
}
template <class K, class V>
const bool operator <= (const SmartPair<K, V> &p1, const SmartPair<K, V> &p2) {
    return (p1 < p2) || (p1 == p2);
}

template <class K, class V>
const bool operator != (const SmartPair<K, V> &p1, const SmartPair<K, V> &p2) {
    return !(p1 == p2);
}

template <class K, class V>
const bool operator > (const SmartPair<K, V> &p1, const SmartPair<K, V> &p2) {
    return !(p1 < p2) && (p1 != p2);
}
template <class K, class V>
const bool operator >= (const SmartPair<K, V> &p1, const SmartPair<K, V> &p2) {
    return (p1 > p2) || (p1 == p2);
}

#include <BTree.h>
namespace tree {



    template<class K = int, class V = std::string>
    class SmartBTree {
        using pair = SmartPair<K, V>;


    public:
        SmartBTree() = delete;

        // Передаем размер буфера, ширину древа, и начальное состояние ленивости
        SmartBTree(const unsigned long buffer_removing, const unsigned long buffer_adding, const unsigned long width, const bool isLazy){
            _isLazy_ = isLazy;
            _size_buffer_removing_ = buffer_removing;
            _size_buffer_adding_ = buffer_adding;
            tree = BTree<pair>(width);
            removing_elements = std::vector<pair>();
            removing_elements.reserve(_size_buffer_removing_);
            adding_elements = std::vector<pair>();
            adding_elements.reserve(_size_buffer_adding_);
        }

        // Добавляем элемент в древо
        // Возвращется true если при данном добавлении произошел сброс буфера
        bool add(K key, V value) {
            if (isLazy()) {
                pair p = SmartPair(key, value);
                tree.insert(p);
                return true;
            }
            pair p = SmartPair(key, value);
            adding_elements.push_back(p);
            if (adding_elements.size() > _size_buffer_adding_) {
                for (pair x : adding_elements)
                    tree.insert(x);
                adding_elements = std::vector<pair>();
                adding_elements.reserve(_size_buffer_adding_);
                return true;
            }
            return false;
        }

        // Удаляем элемент из древа по ключу
        // Возвращается подтверждение - удалено или нет фактический
        bool remove(K key) {
            if (isLazy()) {
                tree.remove(SmartPair(key, V()));
                return true;
            }
            auto it = std::find_if(adding_elements.begin(), adding_elements.end(), [&](pair p1) { return(key == p1.first);});
            if(it != adding_elements.end()) {
                adding_elements.erase(it);
                return false;
            }
            removing_elements.push_back(SmartPair(key, V()));
            if (removing_elements.size() > _size_buffer_removing_) {
                for (pair x : removing_elements)
                    tree.remove(x);
                adding_elements = std::vector<SmartPair<K, V>>();
                adding_elements.reserve(_size_buffer_adding_);
                return true;
            }
            return false;
        }

        // Поиск в древе по ключу возвращающий ссылку на значение при наличии элемента или nullptr если его нет
        const V *search(K key) {
            pair p1 = SmartPair(key, V());

            const pair *p = tree.get(p1);
            if (p == nullptr)
                return nullptr;
            if (p->first == key)
                return &p->second;
            else
                return nullptr;
        }


        // True если в древе включен буфер при удалении/добавлении
        bool isLazy() const {
            return _isLazy_;
        }

        // Переводим древо в ленивый/активный режим
        void setLazy(bool isLazy) {
            SmartBTree::_isLazy_ = isLazy;
            force();
        }

        // Сбрасываем весб буфер удаляя/добавля элементы из него.
        bool force() {
            for (pair y : removing_elements)
                tree.remove(y);

            for (pair x : adding_elements)
                tree.insert(x);

            removing_elements = std::vector<pair>();
            removing_elements.reserve(_size_buffer_removing_);
            adding_elements = std::vector<pair>();
            adding_elements.reserve(_size_buffer_adding_);
        }


    private:
        BTree<pair> tree;

        unsigned long _size_buffer_removing_;

        unsigned long _size_buffer_adding_;

        bool _isLazy_;

        std::vector<pair> removing_elements;

        std::vector<pair> adding_elements;

    };
}
#endif //SIMPLETREE_SMARTBTREE_H
