// Unit tests for LinkedQueue and LinkedStack. Build & run: make test
#undef NDEBUG
#include <cassert>
#include <iostream>
#include <string>

#include "linked_queue.hpp"
#include "linked_stack.hpp"

static void test_queue_fifo_and_tail_reset() {
    LinkedQueue<int> q;
    assert(q.empty() && !q.pop() && q.front() == nullptr);
    q.push(1);
    q.push(2);
    assert(*q.front() == 1 && q.size() == 2);
    assert(*q.pop() == 1 && *q.pop() == 2 && q.empty());
    // After draining, the tail pointer must be reset or this push would corrupt the list.
    q.push(3);
    assert(*q.front() == 3 && *q.pop() == 3 && q.empty());
}

static void test_stack_lifo() {
    LinkedStack<std::string> s;
    assert(s.empty() && !s.pop() && s.top() == nullptr);
    s.push("A");
    s.push("B");
    s.push("C");
    std::string order;
    s.for_each([&](const std::string& v) { order += v; });
    assert(order == "CBA");
    assert(*s.pop() == "C" && *s.top() == "B" && s.size() == 2);
}

// Long lists must be torn down iteratively (no stack overflow) and without leaks;
// CI runs this under AddressSanitizer, which reports any leaked node.
static void test_large_teardown() {
    LinkedQueue<int> q;
    LinkedStack<int> s;
    for (int i = 0; i < 1000000; ++i) {
        q.push(i);
        s.push(i);
    }
    assert(q.size() == 1000000 && s.size() == 1000000);
}

int main() {
    test_queue_fifo_and_tail_reset();
    test_stack_lifo();
    test_large_teardown();
    std::cout << "All linked structure tests passed.\n";
    return 0;
}
