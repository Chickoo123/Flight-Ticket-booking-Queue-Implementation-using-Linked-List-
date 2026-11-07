// Flight Ticket Booking - passengers are processed first come, first served.
// Data structure: LinkedQueue<Booking> (O(1) enqueue/dequeue, unbounded).
#include <iostream>
#include <string>

#include "input.hpp"
#include "linked_queue.hpp"

namespace {
struct Booking {
    int ticket_id;
    std::string passenger;
};
}  // namespace

int main() {
    LinkedQueue<Booking> queue;
    int next_ticket = 1;

    while (true) {
        std::cout << "\n1. Book ticket\n2. Process next booking\n3. Display bookings\n4. Exit\n";
        auto choice = read_int("Enter choice: ", 1, 4);
        if (!choice || *choice == 4) break;

        if (*choice == 1) {
            auto name = read_line("Passenger name: ");
            if (!name) break;
            queue.push({next_ticket, *name});
            std::cout << "Booking successful! Ticket ID: " << next_ticket++ << " (position "
                      << queue.size() << " in queue)\n";
        } else if (*choice == 2) {
            if (auto b = queue.pop())
                std::cout << "Processing booking for " << b->passenger << " (Ticket ID " << b->ticket_id
                          << ")\n";
            else
                std::cout << "Queue is empty.\n";
        } else if (queue.empty()) {
            std::cout << "No bookings.\n";
        } else {
            std::cout << "Bookings (" << queue.size() << ", next first):\n";
            queue.for_each([](const Booking& b) {
                std::cout << "  #" << b.ticket_id << "  " << b.passenger << '\n';
            });
        }
    }
    std::cout << "Thank you!\n";
    return 0;
}
