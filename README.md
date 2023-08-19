# CPPContainers

В рамках данного проекта написана собственная шаблонная библиотека, реализующую основные стандартные контейнерные классы языка С++: list (список), map (словарь), queue (очередь), set (множество), stack (стек) и vector (вектор).

### List

<details>
  <summary>Общая информация</summary>
<br />

List (список) - это последовательный контейнер, хранящий набор элементов произвольного размера в виде узлов, последовательно связанных указателями. Каждый узел хранит значение, соответствующее элементу списка, и указатель на следующий элемент. Такое устройство контейнера позволяет уйти от жестко фиксированного рамера, как, например, в статическом массиве, и делает более интуитивно понятным процесс добавления нового элемента в контейнер. 

</details>

<details>
  <summary>Спецификация</summary>
<br />

*List Member type*

| Member type            | definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `value_type`             | `T` defines the type of an element (T is template parameter)                                  |
| `reference`              | `T &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const T &` defines the type of the constant reference                                         |
| `iterator`               | internal class `ListIterator<T>` defines the type for iterating through the container                                                 |
| `const_iterator`         | internal class `ListConstIterator<T>` defines the constant type for iterating through the container                                           |
| `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |

*List Functions*

| Functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `list()`  | default constructor, creates empty list                                  |
| `list(size_type n)`  | parameterized constructor, creates the list of size n                                 |
| `list(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates list initizialized using std::initializer_list<T>    |
| `list(const list &l)`  | copy constructor  |
| `list(list &&l)`  | move constructor  |
| `~list()`  | destructor  |
| `operator=(list &&l)`      | assignment operator overload for moving object                                |

*List Element access*

| Element access | Definition                                      |
|----------------|-------------------------------------------------|
| `const_reference front()`          | access the first element                        |
| `const_reference back()`           | access the last element                         |

*List Iterators*

| Iterators      | Definition                                      |
|----------------|-------------------------------------------------|
| `iterator begin()`    | returns an iterator to the beginning            |
| `iterator end()`        | returns an iterator to the end                  |

*List Capacity*

| Capacity       | Definition                                      |
|----------------|-------------------------------------------------|
| `bool empty()`          | checks whether the container is empty           |
| `size_type size()`           | returns the number of elements                  |
| `size_type max_size()`       | returns the maximum possible number of elements |

*List Modifiers*

| Modifiers      | Definition                                      |
|----------------|-------------------------------------------------|
| `void clear()`          | clears the contents                             |
| `iterator insert(iterator pos, const_reference value)`         | inserts element into concrete pos and returns the iterator that points to the new element     |
| `void erase(iterator pos)`          | erases element at pos                                 |
| `void push_back(const_reference value)`      | adds an element to the end                      |
| `void pop_back()`   | removes the last element        |
| `void push_front(const_reference value)`      | adds an element to the head                      |
| `void pop_front()`   | removes the first element        |
| `void swap(list& other)`                   | swaps the contents                                                                     |
| `void merge(list& other)`                   | merges two sorted lists                                                                      |
| `void splice(const_iterator pos, list& other)`                   | transfers elements from list other starting from pos             |
| `void reverse()`                   | reverses the order of the elements              |
| `void unique()`                   | removes consecutive duplicate elements               |
| `void sort()`                   | sorts the elements                |

</details>

### Map

<details>
  <summary>Общая информация</summary>
<br />

Map (словарь) - это ассоциативный контейнер, содержащий отсортированные по возрастанию ключа пары ключ-значение. То есть каждый элемент ассоциирован с некоторым уникальным ключом, и его положение в словаре определяется его ключом. Словари удобно применять, когда необходимо ассоциировать элементы с некоторым другим значением (не индексом). Например, предприятие осуществляет закупку оборудования, причем каждую позицию приходится закупать неоднократно. В таком случае удобно использовать словарь с парой идентификатор позиции - объем закупки. Здесь идентификатором может выступать не только число, но и строка. Таким образом, поиск в словаре осуществляется не по индексу, как в массиве, а по идентификатору - слову. 

</details>

<details>
  <summary>Спецификация</summary>
  <br />

*Map Member type*

| Member type            | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `key_type`               | `Key` the first template parameter (Key)                                                     |
| `mapped_type`           | `T` the second template parameter (T)                                                      |
| `value_type`             | `std::pair<const key_type,mapped_type>` Key-value pair                                                      |
| `reference`              | `value_type &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const value_type &` defines the type of the constant reference                                         |
| `iterator`               | internal class `MapIterator<K, T>` or `BinaryTree::iterator` as internal iterator of tree subclass; defines the type for iterating through the container                                                 |
| `const_iterator`         | internal class `MapConstIterator<K, T>` or `BinaryTree::const_iterator` as internal const iterator of tree subclass; defines the constant type for iterating through the container                                           |
| `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |

*Map Member functions*

| Member functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `map()`  | default constructor, creates empty map                                 |
| `map(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates the map initizialized using std::initializer_list<T>    |
| `map(const map &m)`  | copy constructor  |
| `map(map &&m)`  | move constructor  |
| `~map()`  | destructor  |
| `operator=(map &&m)`      | assignment operator overload for moving object                                |

*Map Element access*

| Element access         | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `T& at(const Key& key)`                     | access specified element with bounds checking                                          |
| `T& operator[](const Key& key)`             | access or insert specified element                                                     |

*Map Iterators*

| Iterators              | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `iterator begin()`            | returns an iterator to the beginning                                                   |
| `iterator end()`                | returns an iterator to the end                                                         |

*Map Capacity*

| Capacity               | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `bool empty()`                  | checks whether the container is empty                                                  |
| `size_type size()`                   | returns the number of elements                                                         |
| `size_type max_size()`               | returns the maximum possible number of elements                                        |

*Map Modifiers*

| Modifiers              | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `void clear()`                  | clears the contents                                                                    |
| `std::pair<iterator, bool> insert(const value_type& value)`                 | inserts node and returns iterator to where the element is in the container and bool denoting whether the insertion took place                                        |
| `std::pair<iterator, bool> insert(const Key& key, const T& obj)`                 | inserts value by key and returns iterator to where the element is in the container and bool denoting whether the insertion took place    |
| `std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);`       | inserts an element or assigns to the current element if the key already exists         |
| `void erase(iterator pos)`                  | erases element at pos                                                                        |
| `void swap(map& other)`                   | swaps the contents                                                                     |
| `void merge(map& other);`                  | splices nodes from another container                                                   |

*Map Lookup*

| Lookup                 | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `bool contains(const Key& key)`                  | checks if there is an element with key equivalent to key in the container                                   |

</details>

### Queue

<details>
  <summary>Общая информация</summary>
<br />

Queue (очередь) - это контейнер с элементами, организованными по принцнипу FIFO (First-In, First-Out). Так же как список, объект контейнерного класса очереди содержит в себе указатели на "хвост" и "голову" очереди, однако удаление производится строго из "головы", а запись, то есть добавление новых элементов, строго в "хвост". Очередь удобно представлять как своего рода трубу, в один конец которой попадают элементы, и убывают с другого конца.

</details>

<details>
  <summary>Спецификация</summary>
<br />

*Queue Member type*

| Member type      | Definition                                       |
|------------------|--------------------------------------------------|
| `value_type`       | `T` the template parameter T                   |
| `reference`              | `T &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const T &` defines the type of the constant reference                                         |
| `size_type`        | `size_t` defines the type of the container size (standard type is size_t) |

*Queue Member functions*

| Functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `queue()`  | default constructor, creates empty queue                                 |
| `queue(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates queue initizialized using std::initializer_list<T>    |
| `queue(const queue &q)`  | copy constructor  |
| `queue(queue &&q)`  | move constructor  |
| `~queue()`  | destructor  |
| `operator=(queue &&q)`      | assignment operator overload for moving object                                |

*Queue Element access*

| Element access | Definition                                      |
|----------------|-------------------------------------------------|
| `const_reference front()`          | access the first element                        |
| `const_reference back()`           | access the last element                         |

*Queue Capacity*

| Capacity       | Definition                                      |
|----------------|-------------------------------------------------|
| `bool empty()`          | checks whether the container is empty           |
| `size_type size()`           | returns the number of elements                  |

*Queue Modifiers*

| Modifiers        | Definition                                       |
|------------------|--------------------------------------------------|
| `void push(const_reference value)`             | inserts element at the end                       |
| `void pop()`              | removes the first element                        |
| `void swap(queue& other)`             | swaps the contents                               |

</details>

### Set

<details>
  <summary>Общая информация</summary>
<br />

Set (множество) - это ассоциативный контейнер уникальных элементов. Это означает, что в множество нельзя добавить один и тот же элемент дважды. Контейнер множество является ассоциативным, так как внутри он также представлен в виде дерева, как и контейнер map (словарь), и, соответственно, также хранит элементы в отсортированном порядке. Разница между словарем и множеством заключается в том, что уникальным в множестве является, не ключ а само значение, ровно как и поиск значения в дереве проверяется не по ключу, а по самому значению. При добавлении уже существующего элемента в множество возникает соответствующее исключение. 

</details>

<details>
  <summary>Спецификация</summary>
<br />

*Set Member type*

| Member type            | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `key_type`               | `Key` the first template parameter (Key)                                                     |
| `value_type`             | `Key` value type (the value itself is a key)                                                    |
| `reference`              | `value_type &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const value_type &` defines the type of the constant reference                                         |
| `iterator`               | internal class `SetIterator<T>` or `BinaryTree::iterator` as the internal iterator of tree subclass; defines the type for iterating through the container                                                 |
| `const_iterator`         | internal class `SetConstIterator<T>` or `BinaryTree::const_iterator` as the internal const iterator of tree subclass; defines the constant type for iterating through the container                                           |
| `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |

*Set Member functions*

| Member functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `set()`  | default constructor, creates empty set                                 |
| `set(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates the set initizialized using std::initializer_list<T>    |
| `set(const set &s)`  | copy constructor  |
| `set(set &&s)`  | move constructor  |
| `~set()`  | destructor  |
| `operator=(set &&s)`      | assignment operator overload for moving object                                |


*Set Iterators*

| Iterators              | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `iterator begin()`            | returns an iterator to the beginning                                                   |
| `iterator end()`                | returns an iterator to the end                                                         |


*Set Capacity*

| Capacity       | Definition                                      |
|----------------|-------------------------------------------------|
| `bool empty()`          | checks whether the container is empty           |
| `size_type size()`           | returns the number of elements                  |
| `size_type max_size()`       | returns the maximum possible number of elements |

*Set Modifiers*

| Modifiers              | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `void clear()`                  | clears the contents                                                                    |
| `std::pair<iterator, bool> insert(const value_type& value)`                 | inserts node and returns iterator to where the element is in the container and bool denoting whether the insertion took place                                        |
| `void erase(iterator pos)`                  | erases element at pos                                                                        |
| `void swap(set& other)`                   | swaps the contents                                                                     |
| `void merge(set& other);`                  | splices nodes from another container                                                   |

*Set Lookup*

| Lookup                 | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `iterator find(const Key& key)`                   | finds element with specific key                                                        |
| `bool contains(const Key& key)`               | checks if the container contains element with specific key                             |

</details>

### Stack

<details>
  <summary>Общая ифнормация</summary>
<br />

Stack (стек) - это контейнер с элементами, организованными по принцнипу LIFO (Last-In, First-Out). Объект контейнерного класса стека содержит в себе указатели на "голову" стека, удаление и добавление элементов производится строго из "головы". Стек удобно представлять как стакан или трубу с одним запаянным концом: для того чтобы добраться до элемента, помещенного в контейнер первым, требуется сначала вынуть все элементы, находящиеся сверху.

</details>

<details>
  <summary>Спецификация</summary>
<br />

*Stack Member type*

| Member type      | Definition                                       |
|------------------|--------------------------------------------------|
| `value_type`       | `T` the template parameter T                   |
| `reference`              | `T &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const T &` defines the type of the constant reference                                         |
| `size_type`        | `size_t` defines the type of the container size (standard type is size_t) |

*Stack Member functions*

| Functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `stack()`  | default constructor, creates empty stack                                 |
| `stack(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates stack initizialized using std::initializer_list<T>    |
| `stack(const stack &s)`  | copy constructor  |
| `stack(stack &&s)`  | move constructor  |
| `~stack()`  | destructor  |
| `operator=(stack &&s)`      | assignment operator overload for moving object                                |

*Stack Element access*   

| Element access   | Definition                                       |
|------------------|--------------------------------------------------|
| `const_reference top()`              | accesses the top element                         |

*Stack Capacity*   

| Capacity       | Definition                                      |
|----------------|-------------------------------------------------|
| `bool empty()`          | checks whether the container is empty           |
| `size_type size()`           | returns the number of elements                  |

*Stack Modifiers*        

| Modifiers        | Definition                                       |
|------------------|--------------------------------------------------|
| `void push(const_reference value)`             | inserts element at the top                       |
| `void pop()`              | removes the top element                        |
| `void swap(stack& other)`             | swaps the contents                               |

</details>

### Vector

<details>
  <summary>Общая информация</summary>
<br />

Vector (вектор) - это последовательный контейнер, инкапсулируюший в себе динамический массив для более интуитивной работы. Данный контейнер не требует ручного контроля памяти, как стандартные динамические массивы, вместо этого он позволяет добавлять через методы `push_back()` и `insert()` произвольное количество элементов, и, в отличие от списка, позволяет обратиться к любому элементу контейнера напрямую, по индексу. Элементы в векторе хранятся последовательно, что позволяет итерировать по вектору не только через предоставляемый итератор, но также и вручную смещая указатель на элемент вектора. Таким образом, указатель на первый элемент вектора может быть передан в качестве аргумента в любую функцию, ожидающую в качестве аргумента обыкновенный массив. Динамическое изменение размера массива происходит не при каждом добавлении или удалении элемента, а только в случае превышения размера заданного буфера. Таким образом, вектор хранит два значения, отвечающих за размер: размер хранимого массива (метод `size()`) и размер буффера (метод `capacity()`). 

</details>

<details>
  <summary>Спецификация</summary>
<br />

*Vector Member type*

| Member type            | definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `value_type`             | `T` defines the type of an element (T is template parameter)                                  |
| `reference`              | `T &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const T &` defines the type of the constant reference                                         |
| `iterator`               | `T *` or internal class `VectorIterator<T>` defines the type for iterating through the container                                                 |
| `const_iterator`         | `const T *` or internal class `VectorConstIterator<T>` defines the constant type for iterating through the container                                           |
| `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |

*Vector Member functions*

| Functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `vector()`  | default constructor, creates empty vector                                 |
| `vector(size_type n)`  | parameterized constructor, creates the vector of size n                                 |
| `vector(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates vector initizialized using std::initializer_list<T>    |
| `vector(const vector &v)`  | copy constructor  |
| `vector(vector &&v)`  | move constructor  |
| `~vector()`  | destructor  |
| `operator=(vector &&v)`      | assignment operator overload for moving object                                |

*Vector Element access*

| Element access         | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `reference at(size_type pos)`                     | access specified element with bounds checking                                          |
| `reference operator[](size_type pos);`             | access specified element                                                               |
| `const_reference front()`          | access the first element                        |
| `const_reference back()`           | access the last element                         |
| `T* data()`                   | direct access to the underlying array                                                  |

*Vector Iterators*

| Iterators      | Definition                                      |
|----------------|-------------------------------------------------|
| `iterator begin()`    | returns an iterator to the beginning            |
| `iterator end()`        | returns an iterator to the end                  |

*Vector Capacity*


| Capacity               | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `bool empty()`          | checks whether the container is empty           |
| `size_type size()`           | returns the number of elements                  |
| `size_type max_size()`       | returns the maximum possible number of elements |
| `void reserve(size_type size)`                | allocate storage of size elements and copies current array elements to a newely allocated array                                     |
| `size_type capacity()`               | returns the number of elements that can be held in currently allocated storage         |
| `void shrink_to_fit()`          | reduces memory usage by freeing unused memory                                          |

*Vector Modifiers*

| Modifiers      | Definition                                      |
|----------------|-------------------------------------------------|
| `void clear()`          | clears the contents                             |
| `iterator insert(iterator pos, const_reference value)`         | inserts elements into concrete pos and returns the iterator that points to the new element     |
| `void erase(iterator pos)`          | erases element at pos                                 |
| `void push_back(const_reference value)`      | adds an element to the end                      |
| `void pop_back()`   | removes the last element        |
| `void swap(vector& other)`                   | swaps the contents                                                                     |

</details>



## Сборка и тесты

Покрытие unit-тестами функций библиотеки c помощью библиотеки GTest, которые покрывают не менее 80% кода

Предусмотрен Makefile для сборки библиотеки и тестов (с целями all, clean, test, static_container.a)

В цели gcov_report формируется отчёт gcov в виде html страницы, где можно посмотреть покрытие кода
