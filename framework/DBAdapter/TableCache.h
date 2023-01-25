//
// Created by ctrlz on 23-1-20.
//

#ifndef MYSERVER_TABLECACHE_H
#define MYSERVER_TABLECACHE_H

#include <map>

namespace DBAdapter {
#define MAX_CACHE_LEN = 100;

    template<typename Table>
    struct ListNode {
        explicit ListNode(typename Table::Key &key);

        ListNode() = default;

        typename Table::Key value;
        ListNode *prev;
        ListNode *next;
    };

    template<typename Table>
    class List {
    public:
        List();

        ListNode<Table> *Add(typename Table::Key &key);

        void Delete(ListNode<Table> *node);

        void PushFront(ListNode<Table> *node);

    private:
        ListNode<Table> *head;
        ListNode<Table> *tail;
    };

    template<typename Table>
    class TableCache {
        typedef std::pair<std::shared_ptr<TableCache>, ListNode<Table> *> CacheData;
        public:
            TableCache<Table> &Instance();

            TableCache(const TableCache &) = delete;

            TableCache operator = (const TableCache &) = delete;

            bool Add(std::shared_ptr<Table> t);

            bool Delete(typename Table::Key &key);

            std::shared_ptr<Table> Query(const typename Table::Key &key);

        private:new ListNode<Table>()
            TableCache() = default;

        private:
            std::map<typename Table::Key, CacheData> cache;
            std::mutex cache_mutex;
            List<Table> LRU_list;
    };

    template<typename Table>
    ListNode<Table>::ListNode(typename Table::Key &key) : value(key) {
        prev = nullptr;
        next = nullptr;
    }

    template<typename Table>
    List<Table>::List() {
        head =
        tail = nullptr;
    }

    template<typename Table>
    void List<Table>::Delete(ListNode<Table> *node) {
        auto prev = node->prev;
        auto next = node->next;
        if (prev != nullptr) {
            prev->next = next;
        } else {
            head = next;
        }

        if (next != nullptr) {
            next->prev = prev;
        }

        delete node;
    }

    template<typename Table>
    void List<Table>::PushFront(ListNode<Table> *node) {
        auto prev = node->prev;
        auto next = node->next;
        if (prev != nullptr) {
            prev->next = next;
        } else {
            head = next;
        }

        if (next != nullptr) {
            next->prev = prev;
        }

        node->next = head;
        head->prev = node;
        head = node;
    }

    template<typename Table>
    ListNode<Table> *List<Table>::Add(typename Table::Key &key) {
        ListNode<Table> *node = new ListNode(key);
        node->next = head;
        head->prev = node;
        head = node;
        return node;
    }


    template<typename Table>
    TableCache<Table> &TableCache<Table>::Instance() {
        static TableCache<Table> instance;
        return instance;
    }

    template<typename Table>
    std::shared_ptr<Table> TableCache<Table>::Query(const typename Table::Key &key) {
        std::lock_guard<std::mutex> lock(cache_mutex);
        auto iter = cache.find(key);
        if (iter != cache.end()) {
            auto node = iter->second.second;
            LRU_list.PushFront(node);
            return iter->second.first;
        }
        return nullptr;
    }

    template<typename Table>
    bool TableCache<Table>::Delete(typename Table::Key &key) {
        std::lock_guard<std::mutex> lock(cache_mutex);
        auto iter = cache.find(key);
        if (iter != cache.end()) {
            auto node = iter->second.second;
            LRU_list.Delete(node);
            cache.erase(iter);
            return true;
        }
        return false;
    }

    template<typename Table>
    bool TableCache<Table>::Add(std::shared_ptr<Table> t) {
        std::lock_guard<std::mutex> lock(cache_mutex);
        typename Table::Key key = Table::Key::from(t);
        auto node = LRU_list.Add(key);
        auto iter = cache.find(key);
        if (iter != cache.end()) {
            return false;
        }
        cache[key] = std::make_pair(t, node);
        return false;
    }
}



#endif //MYSERVER_TABLECACHE_H
