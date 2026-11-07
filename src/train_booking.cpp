// Train Ticket Booking - "undo the most recent booking" semantics.
// Data structure: LinkedStack<std::string> (O(1) push/pop, unbounded).
#include <iostream>
#include <string>

#include "input.hpp"
#include "linked_stack.hpp"

int main() {
    LinkedStack<std::string> tickets;

    while (true) {
        std::cout << "\n1. Book a new ticket\n2. Cancel most recent ticket\n3. View current ticket\n"
                     "4. Show all booked tickets\n5. Exit\n";
        auto choice = read_int("Enter choice: ", 1, 5);
        if (!choice || *choice == 5) break;

        switch (*choice) {
            case 1:
                if (auto t = read_line("Ticket number: ")) {
                    tickets.push(*t);
                    std::cout << "Ticket booked: " << *t << '\n';
                }
                break;
            case 2:
                if (auto t = tickets.pop())
                    std::cout << "Cancelling ticket: " << *t << '\n';
                else
                    std::cout << "No tickets to cancel.\n";
                break;
            case 3:
                if (const auto* t = tickets.top())
                    std::cout << "Current ticket: " << *t << '\n';
                else
                    std::cout << "No tickets booked yet.\n";
                break;
            case 4:
                if (tickets.empty()) {
                    std::cout << "No tickets booked.\n";
                } else {
                    std::cout << "Booked tickets (" << tickets.size() << ", newest first):\n";
                    tickets.for_each([](const std::string& t) { std::cout << "  " << t << '\n'; });
                }
                break;
        }
    }
    std::cout << "Thank you for using the train booking system!\n";
    return 0;
}
