# Slave
Scripting programming language written in C/C++ and python<br/>
Syntax is similar to C and has features from Python language (modules, OOP)<br/>
The project is pretty which makes it good project to start as a beginners.


# Done:
```
 * Полноценный ситаксис языка
  * Лексический анализатор
  * Парсер языка Slave
  * Генератор AST дерева
  * Управление памяти
  * Простой интертератор
```
# Under development:
```
* ast-интерпретатор
  * генария кода под assembly x86
  * Полноценный memory management
  * Оптимизая кода до и после генеции машинного кода
```

# Used data structures:
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

# Build and run
```
  make      -> will build and run
  make re   -> rebuild project
```

# Output:
```
  Slave prints on the screen Abstract Syntax Tree (AST) of slave program. 
  It has one example of slave program in 'exm' forlder.
  Change content of exm/code.s file (according to syntax) to see different AST structure.
```

# Dependancies:
```
    This project can be build in Linux and Windows, but tested it only in Linux.
    make - for building project
```
