// linked_queue.hpp - unbounded FIFO queue on a singly linked list.
//
// Owns its nodes via std::unique_ptr, so every node is freed automatically
// (the original version leaked every booking still queued at exit).
// push / pop / front are O(1); a tail pointer avoids walking the list.
#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

template <typename T>
class LinkedQueue {
    struct Node {
        T value;
        std::unique_ptr<Node> next;
    };

public:
    LinkedQueue() = default;
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    // Iterative teardown: default recursive unique_ptr destruction could
    // overflow the stack for very long queues.
    ~LinkedQueue() {
        while (head_) head_ = std::move(head_->next);
    }

    bool empty() const { return head_ == nullptr; }
    std::size_t size() const { return size_; }

    void push(T value) {
        auto node = std::make_unique<Node>(Node{std::move(value), nullptr});
        Node* raw = node.get();
        if (tail_)
            tail_->next = std::move(node);
        else
            head_ = std::move(node);
        tail_ = raw;
        ++size_;
    }

    std::optional<T> pop() {
        if (!head_) return std::nullopt;
        T value = std::move(head_->value);
        head_ = std::move(head_->next);
        if (!head_) tail_ = nullptr;
        --size_;
        return value;
    }

    const T* front() const { return head_ ? &head_->value : nullptr; }

    template <typename Fn>
    void for_each(Fn fn) const {
        for (const Node* n = head_.get(); n; n = n->next.get()) fn(n->value);
    }

private:
    std::unique_ptr<Node> head_;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};
