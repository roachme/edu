# Slave
Язык программирования написанный в основном на С (C/С++, Python)<br/>
Синатаксис очень схож с 'C' + имеет фичи из языка Python (импорт модулей, ООП) <br/>
Простота логики кода делает его хорошим стартовым проектом для новичков



# Реализовано:
```
 * Полноценный ситаксис языка
  * Лексический анализатор
  * Парсер языка Slave
  * Генератор AST дерева
  * Управление памяти
  * Простой интертератор
```
# В разработке:
```
* ast-интерпретатор
  * генария кода под assembly x86
  * Полноценный memory management
  * Оптимизая кода до и после генеции машинного кода
```

# Исползуемые типы данных:
```
Linked list,
  Dynamic array,
  Stack,
  Queue (очередь),
```


slave: scripting-hobby programming lanaguage

# structure:
```
  + lexer
  + parser
  + ast generator
  - semantic part
  - optimization part
  - interpreter & code generator
```

# Features:
```
  compability with C (kind of C++)
  very similar to C + some stuffs from Python (import, class, ..)
  not archhitecture depended
```

# Как построить и запустить
```
  make      -> will build and run
  make re   -> rebuild project
```

# Вывод:
```
  Slave prints on the screen Abstract Syntax Tree (AST) of slave program. 
  It has one example of slave program in 'exm' forlder.
  Change content of exm/code.s file (according to syntax) to see different AST structure.
```

# Зависимисти:
```
    This project can be build in Linux and Windows, but tested it only in Linux.
    make - for building project
```


 


















