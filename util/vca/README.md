./vca: util for process optimization of SCHOOL21 students projects

Привет, всем

Весной я учавствовал в Проекте School21. Проект в котором за 14 дней ты решаешь ряз задач (от легких до сложных), учишся и 	общаешься с программистами разных направлений круглые сутки.
Во время прохождения Бассейна я написал ```Linux script``` что бы избавиться от рутины повседневных дней.
     
     Script принимает несколько флагов и выполняет рутины типа:
```
	создать необходимый папки и файлы данного дня
	автоматически затестить написанный код через ряд проверок: gcc, norminette, Mulinette
	вывести ошибки на экран
	и работа и git: add, commit, log, push, etc..
```

Казань 2.03.20 бассейн проект Школа 21

* put vca into day** dir
	  [ex00 ex01 ex02 .. ex09 vca ]


	[ Use commands ..] 
./vca -i        `path`    make copy ./vca into currently work directory

./vca norm       	      check all files throgh `norminette` 
./vca gcc -c   		      create debug.c file in each `ex*` dir to execute your code
./vca gcc -fc   	      make debug.c again from stratch
./vca git       `repo`	  push all execises to be examined by `Mulinette`

./vca --stopless          clean all ./vca garbage from your PC
