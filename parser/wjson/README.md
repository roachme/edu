**wjson (write to json): утилита для программного запонения JSON-файла.**

  Утилита помогает заполнять JSON-файл, при возникновении ситаксической ошибки выводит предупреждение об ошибке и закрывает файл. <br/>
  Те кто устал заполнять SJON-файл вручную и проводить часы и дни для поиска ошибок, просто скачивайте репу. <br/>
  Постройте проект  <br/>
```
   gcc -c wjson.c  -fpic
   gcc wjson.o -shared -o lwjson.so
```
  как динамическую библиотеку и в бой! <br/>
  ```-fpic - position indepentent code```
  
****Зависимоти:****
```
  make
  Unix-like (e.g. Linux)
```

**Исползованные структуры данных и алгоритмы:**
  - динамический массив
  - стек
  - рекурсия
  
  - алгоритм разворота строки
  - превращение int в string
  - сортировка

***Вывод***
```
A JSON object example:

{
    "key": "value",
    "int": 1,
    "nullThing": null,
    "bool": true,
    "EmptyArray": [],
    "anArray": [
        "array one",
        -2,
        null,
        false,
        {
            "obj3_one": "one",
            "obj3_two": "two"
        },
        [
            0,
            1,
            2
        ]
    ],
    "EmptyObject": {},
    "anObject": {
        "msg": "object in object",
        "msg2": "object in object 2nd entry"
    },
    "ObjEntry": "This is the last one"
}

``` 
Вы можете заполнить json-файл смоими данными и структурами <br/>
используя функции из библиотеки

# Далее:
  Написать утилиту rjson (read from json).
