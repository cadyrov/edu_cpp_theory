# Тест по теории быстродействия алгоритмов

## Вопрос 1
Какая асимптотическая сложность у следующего кода?
```cpp
for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
        std::cout << i << " " << j << std::endl;
    }
}
```
a) O(n)
b) O(n²)
c) O(n log n)
d) O(2^n)

## Вопрос 2
Что означает амортизированная сложность O(1)?
a) Операция всегда выполняется за константное время
b) В среднем операция выполняется за константное время при многократном вызове
c) Операция выполняется за время, не превышающее константу
d) Операция имеет лучший случай O(1)

## Вопрос 3
Какая сложность у вставки элемента в начало std::vector размером n?
a) O(1)
b) O(log n)
c) O(n)
d) O(n²)

## Вопрос 4
Оцените сложность следующего алгоритма:
```cpp
bool findDuplicate(const std::vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = i + 1; j < vec.size(); ++j) {
            if (vec[i] == vec[j]) {
                return true;
            }
        }
    }
    return false;
}
```
a) O(n)
b) O(n log n)
c) O(n²)
d) O(2^n)

## Вопрос 5
Какая сложность у поиска элемента в std::set?
a) O(1)
b) O(log n)
c) O(n)
d) O(n²)

## Вопрос 6
Что лучше использовать для частых поисков по ключу?
a) std::vector<std::pair<Key, Value>>
b) std::map<Key, Value>
c) std::unordered_map<Key, Value>
d) std::list<std::pair<Key, Value>>

## Вопрос 7
Какая сложность у следующего кода?
```cpp
void processMatrix(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        std::sort(matrix[i].begin(), matrix[i].end());
    }
}
```
a) O(n²)
b) O(n² log n)
c) O(n³)
d) O(n log n)

## Вопрос 8
Какое правило асимптотики применяется в выражении O(n + n² + n³)?
a) Правило суммирования
b) Правило умножения
c) Правило поглощения
d) Правило логарифма

## Вопрос 9
Что происходит при многократном вызове push_back() для std::vector без reserve()?
a) Каждая вставка O(1)
b) Амортизированная сложность O(1)
c) Каждая вставка O(n)
d) Сложность O(n²)

## Вопрос 10
Какая сложность у бинарного поиска в отсортированном массиве размером n?
a) O(1)
b) O(log n)
c) O(n)
d) O(n log n)

## Вопрос 11
Оцените сложность:
```cpp
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
```
a) O(n)
b) O(n²)
c) O(2^n)
d) O(log n)

## Вопрос 12
Какая сложность у сортировки слиянием?
a) O(n)
b) O(n log n)
c) O(n²)
d) O(2^n)

## Вопрос 13
Что показывает следующий код в плане сложности?
```cpp
for (int i = 1; i < n; i *= 2) {
    process(i);
}
```
a) O(n)
b) O(log n)
c) O(n²)
d) O(2^n)

## Вопрос 14
Какая операция с std::list имеет сложность O(1)?
a) Поиск элемента
b) Доступ к элементу по индексу
c) Вставка в произвольное место по итератору
d) Сортировка

## Вопрос 15
Оцените сложность:
```cpp
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}
```
a) O(n)
b) O(n log n)
c) O(n²)
d) O(n³)

## Вопрос 16
Какая сложность у std::unordered_map::find() в среднем случае?
a) O(1)
b) O(log n)
c) O(n)
d) O(n²)

## Вопрос 17
Что лучше для cache-friendly обхода данных?
a) std::list
b) std::vector
c) std::set
d) std::map

## Вопрос 18
Какая сложность у следующего алгоритма?
```cpp
void printPairs(const std::vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec.size(); ++j) {
            std::cout << vec[i] << " " << vec[j] << std::endl;
        }
    }
}
```
a) O(n)
b) O(n log n)
c) O(n²)
d) O(2^n)

## Вопрос 19
Какая сложность у удаления элемента из середины std::vector?
a) O(1)
b) O(log n)
c) O(n)
d) O(n²)

## Вопрос 20
Что означает O(n log n) в контексте сортировки?
a) Это худший случай для всех алгоритмов сортировки
b) Это теоретический минимум для сортировки сравнениями
c) Это сложность только быстрой сортировки
d) Это средний случай пузырьковой сортировки

## Вопрос 21
Оцените сложность:
```cpp
int countInversions(const std::vector<int>& arr) {
    int count = 0;
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[i] > arr[j]) {
                count++;
            }
        }
    }
    return count;
}
```
a) O(n)
b) O(n log n)
c) O(n²)
d) O(n³)

## Вопрос 22
Какая сложность у std::lower_bound на отсортированном std::vector?
a) O(1)
b) O(log n)
c) O(n)
d) O(n log n)

## Вопрос 23
Что происходит при использовании std::string_view вместо std::string?
a) Увеличивается время выполнения
b) Уменьшается количество копирований
c) Увеличивается потребление памяти
d) Ничего не изменяется

## Вопрос 24
Какая сложность у следующего кода?
```cpp
std::string concatenate(const std::vector<std::string>& strings) {
    std::string result;
    for (const auto& s : strings) {
        result += s;
    }
    return result;
}
```
a) O(n)
b) O(n log n)
c) O(n²)
d) O(2^n)

## Вопрос 25
Какое преимущество у std::deque перед std::vector?
a) Быстрее произвольный доступ
b) Меньше потребление памяти
c) O(1) вставка в начало и конец
d) Лучше cache locality

## Вопрос 26
Оцените сложность:
```cpp
bool isPalindrome(const std::string& s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
```
a) O(1)
b) O(log n)
c) O(n)
d) O(n²)

## Вопрос 27
Какая сложность у вставки в std::priority_queue?
a) O(1)
b) O(log n)
c) O(n)
d) O(n log n)

## Вопрос 28
Что лучше использовать для конкатенации множества строк?
a) Оператор +=
b) std::ostringstream
c) std::string::append()
d) Все варианты одинаковы

## Вопрос 29
Какая сложность у следующего алгоритма?
```cpp
void selectionSort(std::vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(arr[i], arr[minIdx]);
    }
}
```
a) O(n)
b) O(n log n)
c) O(n²)
d) O(n³)

## Вопрос 30
Какая сложность у std::set::insert()?
a) O(1)
b) O(log n)
c) O(n)
d) O(n log n)

## Вопрос 31
Оцените сложность:
```cpp
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```
a) O(1)
b) O(log n)
c) O(n)
d) O(n²)

## Вопрос 32
Какая сложность у std::vector::reserve()?
a) O(1)
b) O(log n)
c) O(n)
d) O(n²)

## Вопрос 33
Что означает cache-friendly код?
a) Код, который использует много памяти
b) Код, который обращается к памяти последовательно
c) Код, который использует много процессорного времени
d) Код, который использует много кэша

## Вопрос 34
Какая сложность у следующего кода?
```cpp
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right); // O(n)
    }
}
```
a) O(n)
b) O(n log n)
c) O(n²)
d) O(2^n)

## Вопрос 35
Какая операция с std::map имеет сложность O(n)?
a) insert()
b) find()
c) erase(key)
d) clear()

## Вопрос 36
Оцените сложность:
```cpp
int findMax(const std::vector<int>& arr) {
    int maxVal = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}
```
a) O(1)
b) O(log n)
c) O(n)
d) O(n²)

## Вопрос 37
Какая сложность у std::sort() в стандартной библиотеке?
a) O(n)
b) O(n log n)
c) O(n²)
d) O(2^n)

## Вопрос 38
Что лучше для частых вставок и удалений в произвольных местах?
a) std::vector
b) std::deque
c) std::list
d) std::array

## Вопрос 39
Какая сложность у следующего кода?
```cpp
void printSubsets(const std::vector<int>& arr, int index, std::vector<int>& current) {
    if (index == arr.size()) {
        printVector(current);
        return;
    }
    printSubsets(arr, index + 1, current);
    current.push_back(arr[index]);
    printSubsets(arr, index + 1, current);
    current.pop_back();
}
```
a) O(n)
b) O(n²)
c) O(n!)
d) O(2^n)

## Вопрос 40
Какая основная причина использовать std::move?
a) Увеличить скорость выполнения
b) Уменьшить потребление памяти
c) Избежать ненужных копирований
d) Улучшить читаемость кода 