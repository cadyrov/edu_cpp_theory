Представьте, что ваша программа периодически сбоит: то выдает какой-то «мусор», то просто «падает». Вы стали разбираться в проблеме и локализовали ситуацию до класса TaskQ, который активно работает с вектором. 

Скопируйте код ниже к себе, разберитесь, есть ли в нём ошибки, которые могут приводить к сбоям, и исправьте их.

```cpp
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
  TaskQ()
    : current(tasks.begin())
  { }
  void add(Task&& task) {
    tasks.push_back(std::move(task));
  }
  // Исполняет не более n задач
  void run(int n = 5) {
    for (int i = 0; current != tasks.end() && i < n; ++i, ++current) {
      auto& task = *current;
      try {
        task.execute();
      } catch (...) {
        task.done = true;
      }
    }
  }
  // Очищает очередь задач от исполненных
  void clean() {
    for (auto begin = tasks.begin(); begin != tasks.end(); ++begin) {
      if (begin->done) {
        tasks.erase(begin);
      }
    }
  }
private:
  std::vector<Task> tasks;
  std::vector<Task>::iterator current;
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
```

- Вместо итератора используйте обращение по индексу.
- Для удаления элементов из вектора используйте идиому std::remove_if + std::erase.