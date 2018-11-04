//
// Created by Ivan Korotkii on 04/11/2018.
//

#ifndef SIMPLETREE_SMARTBTREE_H
#define SIMPLETREE_SMARTBTREE_H

#include <BTree.h>
#include <vector>

namespace tree {

    template<class K = int, class V = std::string>
    class SmartBTree {
        using pair = std::pair<K, V>;

    public:
        SmartBTree() = delete;

        // Передаем размер буфера, ширину древа, и начальное состояние ленивости
        SmartBTree(const unsigned long buffer, const unsigned long width, const bool isLazy){
            _isLazy_ = isLazy;
            _size_buffer_ = buffer;
            tree = BTree<pair>(width);
            removing_elements = std::vector<pair>();
            removing_elements.reserve(_size_buffer_);
            adding_elements = std::vector<pair>();
            adding_elements.reserve(_size_buffer_);
        }

        // Добавляем элемент в древо
        // Возвращется true если при данном добавлении произошел сброс буфера
        bool add(K &key, V &value);

        // Удаляем элемент из древа по ключу
        // Возвращается указатель на элемент если фактический произошло удаление или nullptr если его не было
        V *remove(K &key);

        // Поиск в древе по ключу возвращающий указатель на значение при наличии элемента или nullptr если его нет
        V *search(K &key);

        // Возвращает true если элемент находится в буфере или самом дереве
        bool find(K &key);

        // True если в древе включен буфер при удалении/добавлении
        bool isLazy() const {
            return _isLazy_;
        }

        // Переводим древо в ленивый/активный режим
        void setLazy(bool isLazy) {
            SmartBTree::_isLazy_ = isLazy;
            force();
        }

        // Сбрасываем буфер удаляя/добавля элементы из него.
        bool force();


    private:
        BTree<pair> tree;

        unsigned long _size_buffer_;

        bool _isLazy_;

        std::vector<pair> removing_elements;

        std::vector<pair> adding_elements;
    };
}
#endif //SIMPLETREE_SMARTBTREE_H
