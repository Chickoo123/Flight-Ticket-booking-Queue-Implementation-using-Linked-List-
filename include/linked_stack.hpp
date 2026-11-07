// linked_stack.hpp - unbounded LIFO stack on a singly linked list.
// push / pop / top are O(1). Nodes are owned by std::unique_ptr (no leaks).
#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

template <typename T>
class LinkedStack {
    struct Node {
        T value;
        std::unique_ptr<Node> next;
    };

public:
    LinkedStack() = default;
    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;
    ~LinkedStack() {
        while (top_) top_ = std::move(top_->next);
    }

    bool empty() const { return top_ == nullptr; }
    std::size_t size() const { return size_; }

    void push(T value) {
        top_ = std::make_unique<Node>(Node{std::move(value), std::move(top_)});
        ++size_;
    }

    std::optional<T> pop() {
        if (!top_) return std::nullopt;
        T value = std::move(top_->value);
        top_ = std::move(top_->next);
        --size_;
        return value;
    }

    const T* top() const { return top_ ? &top_->value : nullptr; }

    // Visits newest -> oldest.
    template <typename Fn>
    void for_each(Fn fn) const {
        for (const Node* n = top_.get(); n; n = n->next.get()) fn(n->value);
    }

private:
    std::unique_ptr<Node> top_;
    std::size_t size_ = 0;
};
