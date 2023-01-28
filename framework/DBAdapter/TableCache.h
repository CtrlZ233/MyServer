//
// Created by ctrlz on 23-1-20.
//

#ifndef MYSERVER_TABLECACHE_H
#define MYSERVER_TABLECACHE_H

#include <map>
#include <list>

namespace DBAdapter {
#define MAX_CACHE_LEN 100

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

        ListNode<Table> *PopBack();

        size_t Size() const;

    private:
        ListNode<Table> *head;
        ListNode<Table> *start;
        ListNode<Table> *end;
        size_t size;
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

        private:
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
        head = new ListNode<Table>();
        end = new ListNode<Table>();
        head->next = end;
        end->prev = head;
        start = end;
        size = 0;
    }

    template<typename Table>
    void List<Table>::Delete(ListNode<Table> *node) {
        ListNode<Table> *prev = node->prev;
        prev->next = node->next;
        node->next->prev = prev;
        start = head->next;
        delete node;
    }

    template<typename Table>
    void List<Table>::PushFront(ListNode<Table> *node) {
        // delete node
        ListNode<Table> *prev = node->prev;
        prev->next = node->next;
        node->next->prev = prev;
        start = head->next;

        // add node to start
        head->next = node;
        node->prev = head;
        node->next = start;
        start->prev = node;
        start = node;
    }

    template<typename Table>
    ListNode<Table> *List<Table>::Add(typename Table::Key &key) {
        ListNode<Table> *node = new ListNode(key);
        head->next = node;
        node->prev = head;
        node->next = start;
        start->prev = node;
        start = node;
        return node;
    }

    template<typename Table>
    ListNode<Table> *List<Table>::PopBack() {
        if (size == 0) {
            return nullptr;
        }

        auto node = end->prev;
        node->prev->next = end;
        end->prev = node->prev;
        return node;
    }

    template<typename Table>
    size_t List<Table>::Size() const {
        return size;
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
        typename Table::Key key = Table::Key::From(t);

        if (LRU_list.Size() >= MAX_CACHE_LEN) {
            auto node = LRU_list.PopBack();
            auto old_key = node->value;
            delete node;
            cache.erase(old_key);
        }
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
