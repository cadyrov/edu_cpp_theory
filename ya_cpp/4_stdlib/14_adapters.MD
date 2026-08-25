# 14. Адаптеры

## Суть

Адаптер контейнера дает специальный ограниченный интерфейс поверх другого контейнера.

В стандартной библиотеке есть:

- `std::stack`;
- `std::queue`;
- `std::priority_queue`.

Они скрывают лишние операции базового контейнера и оставляют только нужную модель доступа.

## std::stack

`std::stack` моделирует стек.

Правило: LIFO - last in, first out.

Последний добавленный элемент извлекается первым.

```cpp
#include <stack>

std::stack<int> s;

s.push(10);
s.push(20);
s.push(30);

int x = s.top(); // 30
s.pop();
```

`top()` возвращает верхний элемент.

`pop()` удаляет верхний элемент, но не возвращает его.

По умолчанию `std::stack` использует `std::deque`.

Можно указать другой базовый контейнер, если у него есть `back()`, `push_back()`, `pop_back()`.

```cpp
std::stack<int, std::vector<int>> s1;
std::stack<int, std::list<int>> s2;
```

## DFS через stack

`std::stack` удобно использовать для обхода графа в глубину без рекурсии.

```cpp
void dfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> visited(graph.size(), 0);
    std::stack<int> st;

    st.push(start);

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (visited[node]) {
            continue;
        }

        visited[node] = 1;

        for (int next : graph[node]) {
            if (!visited[next]) {
                st.push(next);
            }
        }
    }
}
```

Стек хранит вершины, которые еще нужно обработать.

## std::queue

`std::queue` моделирует очередь.

Правило: FIFO - first in, first out.

Первый добавленный элемент извлекается первым.

```cpp
#include <queue>

std::queue<int> q;

q.push(10);
q.push(20);
q.push(30);

int first = q.front(); // 10
int last = q.back();   // 30

q.pop();
```

`front()` возвращает первый элемент.

`back()` возвращает последний элемент.

`pop()` удаляет первый элемент, но не возвращает его.

По умолчанию `std::queue` использует `std::deque`.

Базовый контейнер должен иметь `back()`, `front()`, `push_back()`, `pop_front()`.

```cpp
std::queue<int, std::list<int>> q;
```

## BFS через queue

`std::queue` удобно использовать для обхода графа в ширину.

```cpp
void bfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> visited(graph.size(), 0);
    std::queue<int> q;

    visited[start] = 1;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int next : graph[node]) {
            if (!visited[next]) {
                visited[next] = 1;
                q.push(next);
            }
        }
    }
}
```

Очередь сначала обрабатывает вершины текущего уровня, потом следующего.

## std::priority_queue

`std::priority_queue` - очередь с приоритетом.

Элемент с максимальным приоритетом всегда доступен через `top()`.

```cpp
#include <queue>

std::priority_queue<int> q;

q.push(10);
q.push(30);
q.push(20);

q.top(); // 30
```

По умолчанию это max-heap: сверху наибольший элемент.

Для min-heap можно использовать `std::greater`.

```cpp
std::priority_queue<
    int,
    std::vector<int>,
    std::greater<int>
> q;
```

## Куча

`std::priority_queue` обычно реализован поверх кучи.

Куча хранит частичный порядок:

- родитель не меньше потомков для max-heap;
- максимум быстро доступен сверху;
- полного порядка между всеми элементами нет.

Основные операции:

- `top()` - `O(1)`;
- `push()` / `emplace()` - `O(log N)`;
- `pop()` - `O(log N)`.

Свободные алгоритмы для кучи:

- `std::make_heap`;
- `std::push_heap`;
- `std::pop_heap`;
- `std::sort_heap`;
- `std::is_heap`;
- `std::is_heap_until`.

Они работают с контейнером напрямую.

`std::priority_queue` инкапсулирует кучу и не дает случайно сломать ее инвариант.

## Базовый контейнер priority_queue

По умолчанию используется `std::vector`.

Можно использовать другой контейнер с random access iterator, `front()`, `push_back()`, `pop_back()`.

```cpp
std::priority_queue<int, std::deque<int>> q;
```

`std::list` не подходит, потому что у него нет произвольного доступа.

## Подводные камни

## 1. pop не возвращает значение

```cpp
int x = s.top();
s.pop();
```

Сначала читаем, потом удаляем.

Для `queue` сначала `front()`, потом `pop()`.

## 2. Нельзя итерироваться по адаптеру

```cpp
// for (int x : s) {} // нет такого интерфейса
```

Адаптер специально скрывает внутренний контейнер.

## 3. top/front на пустом контейнере

```cpp
if (!s.empty()) {
    std::cout << s.top();
}
```

Перед доступом нужно проверять `empty()`.

## 4. priority_queue не сортированный контейнер

Она быстро отдает только самый приоритетный элемент.

Итерироваться по всем элементам в отсортированном порядке нельзя.

## 5. priority_queue не ищет элементы

Куча не поддерживает быстрый поиск произвольного элемента.

Если нужен поиск по ключу, нужен другой контейнер.

## 6. stack и queue не быстрее сами по себе

Они задают модель доступа.

Скорость зависит от базового контейнера и операций.

## Когда использовать

- `std::stack` - LIFO, DFS, откат операций, парсинг скобок.
- `std::queue` - FIFO, BFS, обработка задач в порядке поступления.
- `std::priority_queue` - всегда нужен самый приоритетный элемент.

## Саммари

- Адаптер ограничивает интерфейс существующего контейнера.
- `std::stack` реализует LIFO.
- `std::queue` реализует FIFO.
- `std::priority_queue` реализует очередь с приоритетом.
- `stack` и `queue` по умолчанию используют `std::deque`.
- `priority_queue` по умолчанию использует `std::vector` и `std::less`.
- `pop()` удаляет, но не возвращает значение.
- Перед `top()`, `front()` и `back()` проверяй `empty()`.
- `std::stack` удобен для DFS.
- `std::queue` удобен для BFS.
- `std::priority_queue::top()` стоит `O(1)`.
- `push()` и `pop()` у `priority_queue` стоят `O(log N)`.
- `priority_queue` хранит кучу, а не полностью отсортированный контейнер.
