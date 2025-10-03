#include "dictionary.h"
#include "limitedDictionary.h"
#include <queue>
#include <iostream>

// ---------------- Constructor ----------------
LimitedDictionary::LimitedDictionary(int capacity, Policy policy) : Dictionary(capacity) {
    if (capacity < 1) {
        throw std::runtime_error("Cannot create dictionary with capacity less than 1");
    }
    this->capacity = capacity;
    this->policy = policy;
    this->size = 0;

    if (policy == LRU) init_lru();
}

// ---------------- FIFO ----------------
void LimitedDictionary::evict_fifo() {
    if (q.empty()) return;
    std::string evict_key = q.front();
    q.pop();
    Dictionary::remove(evict_key);
    --size;
    std::cerr << "evicted: " << evict_key << std::endl;
}

void LimitedDictionary::insert_fifo(Entry e) {
    Entry* existing = Dictionary::get(e.key);
    if (!existing) {
        if (size >= capacity) evict_fifo();
        if (Dictionary::put(e)) {
            ++size;
            q.push(e.key);
            std::cerr << "inserted: " << e.key << std::endl;
        }
    } else {
        existing->value = e.value;
        std::cerr << "inserted: " << e.key << std::endl;
    }
}

// ---------------- LRU ----------------
void LimitedDictionary::init_lru() {
    head = nullptr;
    tail = nullptr;
}

void LimitedDictionary::evict_lru() {
    if (!tail) return;
    std::string evict_key = tail->key;

    Dictionary::remove(evict_key);
    --size;

    ListEntry* prev_tail = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;

    delete prev_tail;
    std::cerr << "evicted: " << evict_key << std::endl;
}

void LimitedDictionary::insert_lru(Entry e) {
    Entry* existing = Dictionary::get(e.key);
    if (!existing) {
        if (size >= capacity) evict_lru();
        if (Dictionary::put(e)) {
            ++size;
            ListEntry* node = new ListEntry{e.key, nullptr, tail};
            if (!head) head = node;
            if (tail) tail->next = node;
            tail = node;
            std::cerr << "inserted: " << e.key << std::endl;
        }
    } else {
        existing->value = e.value;
        // Move node to tail
        ListEntry* node = head;
        while (node && node->key != e.key) node = node->next;
        if (node && node != tail) {
            if (node->prev) node->prev->next = node->next;
            if (node->next) node->next->prev = node->prev;
            if (node == head) head = node->next;

            node->prev = tail;
            node->next = nullptr;
            if (tail) tail->next = node;
            tail = node;
        }
        std::cerr << "inserted: " << e.key << std::endl;
    }
}

// ---------------- Public methods ----------------
bool LimitedDictionary::put(Entry e) {
    if (policy == FIFO) insert_fifo(e);
    else insert_lru(e);
    return true;
}

bool LimitedDictionary::remove(std::string key) {
    Entry* existing = Dictionary::get(key);
    if (!existing) return false;

    Dictionary::remove(key);
    --size;

    if (policy == FIFO) {
        std::queue<std::string> new_q;
        while (!q.empty()) {
            std::string k = q.front(); q.pop();
            if (k != key) new_q.push(k);
        }
        q = new_q;
    } else {
        ListEntry* node = head;
        while (node) {
            if (node->key == key) {
                if (node->prev) node->prev->next = node->next;
                if (node->next) node->next->prev = node->prev;
                if (node == head) head = node->next;
                if (node == tail) tail = node->prev;
                delete node;
                break;
            }
            node = node->next;
        }
    }
    return true;
}

Entry* LimitedDictionary::get(std::string key) {
    Entry* entry = Dictionary::get(key);
    if (!entry) return nullptr;

    if (policy == LRU) {
        ListEntry* node = head;
        while (node && node->key != key) node = node->next;
        if (node && node != tail) {
            if (node->prev) node->prev->next = node->next;
            if (node->next) node->next->prev = node->prev;
            if (node == head) head = node->next;

            node->prev = tail;
            node->next = nullptr;
            if (tail) tail->next = node;
            tail = node;
        }
    }
    return entry;
}
