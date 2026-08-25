#include <initializer_list>
#include <deque>
#include <chrono>
#include <thread>

struct Process {
    int id;
    int priority;
    int ticks;
};

class Scheduler {
public:
    Scheduler(std::initializer_list<Process> in) {
        for (auto& ps :in) {
            if (ps.priority > 5) {
                high_.push_back(ps);
            } else {
                low_.push_back(ps);
            }
        }
    }

    void run() {
        for (; ; ) {
            int ticks = runDeque(high_, second_);

            if (ticks > 0) {
                ticks = runDeque(low_, second_);
            }

            if (high_.empty() && low_.empty()) {
                return;
            }

            std::this_thread::sleep_for(std::chrono::seconds(second_));
        }
    }
private:
    int runDeque(std::deque<Process>& in, int ticks) {
        if (in.empty()){
            return ticks;
        }

        for (;!in.empty();) {
            if (in.front().ticks > ticks) {
                in.front().ticks -= ticks;

                return 0;
            }

            ticks -= in.front().ticks;
            in.pop_front();
        }

        return ticks;
    }

    std::deque<Process> high_;
    std::deque<Process> low_;
    static const int second_ = 2;
};

int main() {
    Scheduler scheduler{{1, 1, 2}, {2, 6, 10}, {3, 3, 2}};
    scheduler.run();

    return 0;
} 