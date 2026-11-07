# Flight & Train Booking — Linked-List Queue and Stack in C++

[![Build & test](https://github.com/Chickoo123/Flight-Ticket-booking-Queue-Implementation-using-Linked-List-/actions/workflows/ci.yml/badge.svg)](https://github.com/Chickoo123/Flight-Ticket-booking-Queue-Implementation-using-Linked-List-/actions/workflows/ci.yml)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)

Two console booking systems that show when to choose a **queue** and when to choose a **stack**. Both are built on generic, leak-free linked-list containers.

| Program | Behaviour | Structure | Why |
|---|---|---|---|
| `flight_booking` | Passengers processed first come, first served | `LinkedQueue<Booking>` | Fairness means FIFO |
| `train_booking` | "Cancel my most recent booking" | `LinkedStack<std::string>` | Undo means LIFO |

## Engineering highlights

- **No memory leaks.** Nodes are owned by `std::unique_ptr`. The original code used raw `new` and leaked every node still in the list at exit. CI checks this with AddressSanitizer.
- **No stack overflow on teardown.** Destructors unlink iteratively, so a list of 1,000,000 nodes is freed safely. A plain recursive `unique_ptr` chain would overflow the stack.
- **O(1) everything.** The queue keeps a tail pointer, so `push`, `pop`, and `front`/`top` are all constant time.
- **Robust input.** Names with spaces work, blank names are rejected, non-numeric menu input is recovered from, and EOF exits cleanly instead of looping forever.
- **Tested.** Unit tests cover FIFO/LIFO order, tail reset after draining, and million-node teardown. Scripted smoke tests drive both programs end to end. CI runs everything with g++ and clang++ under `-Werror` and ASan + UBSan.

## Build & run

```bash
make          # build/flight_booking, build/train_booking
make test     # unit + smoke tests
./build/flight_booking
```

## Layout

```
include/linked_queue.hpp   FIFO queue (head + tail pointer)
include/linked_stack.hpp   LIFO stack
include/input.hpp          safe int / line input
src/flight_booking.cpp
src/train_booking.cpp
tests/test_structures.cpp
tests/smoke.sh
```

See also: [ring-buffer (array) queue booking systems](https://github.com/Chickoo123/Booking-System-). Comparing the two repos shows the trade-off between fixed-capacity arrays and unbounded linked lists.
