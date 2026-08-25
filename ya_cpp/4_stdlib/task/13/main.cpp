#include <iostream>
#include <print>
#include <cassert>
#include <vector>
#include <utility>
#include <algorithm>

// Класс, реализующий задачу на исполнение
struct Task {
  Task(int id, int* executed)
    : id(id)
    , executed(executed)
  { }

  void execute() {
    std::println("execute id={}", id);
    ++(*executed);
    done = true;
  }

  bool done = false;
  int id;
  int* executed;
};

// Класс, реализующий очередь задач
class TaskQ {
public:
  TaskQ(){}

  void add(Task&& task) {
    tasks_.push_back(std::move(task));
  }
  // Исполняет не более n задач
  void run(int n = 5) {
    for (int i = 0; current_ < tasks_.size() && i < n; ++i, ++current_) {
      try {
        tasks_[current_].execute();
      } catch (...) {
        tasks_[current_].done = true;
      }
    }
  }
  // Очищает очередь задач от исполненных
  void clean() {
        auto new_end = std::remove_if(tasks_.begin(), tasks_.end(),  [](const Task& task) { return task.done; });
        
        tasks_.erase(new_end, tasks_.end());
        
        current_ = 0;
  }
private:
  std::vector<Task> tasks_;
  size_t current_ = 0;
};

int main() {
  { 
      TaskQ q;
      q.run();
  }
  { 
      TaskQ q;
      q.run();
      q.run();
  }
  { 
      int executed = 0;
      TaskQ q;
      for (int i = 0; i < 6; ++i) {
          q.add(Task{i, &executed});    
      }
      q.run();
      q.run();
      assert(executed == 6);
  }
  { 
      int executed = 0;
      TaskQ q;
      for (int i = 0; i < 10; ++i) {
          q.add(Task{i, &executed});    
      }
      q.run();
      q.clean();
      q.run();
      assert(executed == 10);
  }
} 
