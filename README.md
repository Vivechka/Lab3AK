## Лабораторна робота №3 з Архітектури комп'ютерів.

### Ключі, які пітримуються:
    --help, -h => виводить довідкову інформацію
    --version, -v => виводить версію. Якщо рядку, який міг би її визначати, немає, виводить певне значення, задане за замовуванням  
   

### Приклади виконання
    $ ./main.exe -vh --help --version = 1.0.3
    Version: 1.0.3
    This is demo help. Try -h or --help.
---
    $ ./main.exe --version = 10.0.0 -h
    Version: 10.0.0
    This is demo help. Try -h or --help.
---
    $ ./main.exe --version = 20.0.a --help
    Version: 1.0.3
    This is demo help. Try -h or --help.
