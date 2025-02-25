## Операционные системы 
### Лабораторная работа №1
#### Вариант: Windows ema-search-str sort </br>
#### Задание </br>
#### Задание Часть 1. Запуск программ </br>

Необходимо реализовать собственную оболочку командной строки - shell. Выбор ОС для реализации производится на усмотрение студента. Shell должен предоставлять пользователю возможность запускать программы на компьютере с 
переданными аргументами командной строки и после завершения программы показывать реальное время ее работы (подсчитать самостоятельно как «время завершения» – «время запуска»). </br>

#### Задание Часть 2. Мониторинг и профилирование </br>

Разработать комплекс программ-нагрузчиков по варианту, заданному преподавателем. Каждый нагрузчик должен, как минимум, принимать параметр, который определяет количество повторений для алгоритма, указанного в задании. 
Программы должны нагружать вычислительную систему, дисковую подсистему или обе подсистемы сразу. Необходимо скомпилировать их без опций оптимизации компилятора.
Перед запуском нагрузчика, попробуйте оценить время работы вашей программы или ее результаты (если по варианту вам досталось измерение чего либо).
Постарайтесь обосновать свои предположения. Предположение можно сделать, основываясь на свой опыт, знания ОС и характеристики используемого аппаратного обеспечения.
Запустите программу-нагрузчик и зафиксируйте метрики ее работы с помощью инструментов для профилирования. Сравните полученные результаты с ожидаемыми. Постарайтесь найти объяснение наблюдаемому.
Определите количество нагрузчиков, которое эффективно нагружает все ядра процессора на вашей системе. Как распределяются времена  USER%, SYS%, WAIT%, а 
также реальное время выполнения нагрузчика, какое количество переключений контекста (вынужденных и невынужденных) происходит при этом?
Увеличьте количество нагрузчиков вдвое, втрое, вчетверо. Как изменились времена, указанные на предыдущем шаге? Как ведет себя ваша система?
Объедините программы-нагрузчики в одну, реализованную при помощи потоков выполнения, чтобы один нагрузчик эффективно нагружал все ядра вашей системы. 
Как изменились времена для того же объема вычислений? Запустите одну, две, три таких программы.
Добавьте опции агрессивной оптимизации для компилятора. Как изменились времена? На сколько сократилось реальное время исполнения программы нагрузчика? </br>

#### Ограничения

Программа (комплекс программ) должна быть реализован на языке C, C++.
Дочерние процессы должны быть созданы через заданные системные вызовы выбранной операционной системы, с обеспечением корректного запуска и и завершения процессов.  
Запрещено использовать высокоуровневые абстракции над системными вызовами. Необходимо использовать, в случае Unix, процедуры libc. </br>

#### Предположения о свойствах программ нагрузчиков
`ema-search-int`: нагрузка на диск из-за множества операций чтения. Показатель USER% будет низким, потому что программа не выполняет сложных вычислений. 
SYS% будет высоким, так как системные вызовы (ввод-вывод) занимают значительное время. WAIT% (время ожидания) также будет значительным, так как процесс ожидает завершения операций чтения с диска. </br>

`sort`: USER% будет высоким, так как большая часть времени программы тратится на выполнение вычислений. WAIT% не должен становиться значительным, так как нет работы с диском. SYS% будет низким, так как операции ввода-вывода есть только в начале программы. Из ожидаемых системных вызовов остается только работа с памятью. </br>

#### Средства мониторинга
- Resmon – для мониторинга диска.
- Procexp – для отслеживания USER%, SYS% и переключений контекста.
- Диспетчер задач – для мониторинга процессора и диска.

#### Результаты измерений
`ema-search-str:` 
##### 1 нагрузчик
https://private-user-images.githubusercontent.com/90797542/416029495-dc931c83-f3f9-44ee-a898-ecfecaf20a17.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDA1MDc3MjUsIm5iZiI6MTc0MDUwNzQyNSwicGF0aCI6Ii85MDc5NzU0Mi80MTYwMjk0OTUtZGM5MzFjODMtZjNmOS00NGVlLWE4OTgtZWNmZWNhZjIwYTE3LnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNTAyMjUlMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjUwMjI1VDE4MTcwNVomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPTdjOWRjOGVmM2NiNGMwMjRjMTU4OWY5OGJlZWQyMDIwYmJiMjk5OTU3ZDVhYmMyZmUzNDUwMjk2Y2JiZWM0NWYmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0In0.yvzSD3upvmbDsI-kPkZ7-UWcPPzS0VpvW7XQph5zH3Y


##### 3 нагрузчика
![image](https://github.com/user-attachments/assets/248c61fc-209f-4f50-bb14-4025642c5c6c)
![image](https://github.com/user-attachments/assets/a439fa32-0875-4177-ae0d-e234ea5fc0c8)
![image](https://github.com/user-attachments/assets/bd9da691-f824-468a-8c12-6194a13f05a4)
![image](https://github.com/user-attachments/assets/128da663-112b-4e0f-9bc2-c8a36f04a8be)

##### 5 нагрузчиков
![image](https://github.com/user-attachments/assets/4edfcdf2-9d82-4df6-87f2-2306b7101dc1)
![image](https://github.com/user-attachments/assets/39280c9d-48f3-48e7-931e-8ee7cd9cc079)
![image](https://github.com/user-attachments/assets/8af1379b-de07-4e13-85ab-aeaf888fbec3)
![image](https://github.com/user-attachments/assets/149a0281-6e8e-4671-823a-cb91d72ddfac)

`sort:`
##### 1 нагрузчик
![image](https://github.com/user-attachments/assets/f992008f-ef7e-4371-afc7-ba6e51b99a8b)
![image](https://github.com/user-attachments/assets/2dd123e4-bc29-4aac-877b-ad9d84c05253)
![image](https://github.com/user-attachments/assets/17fe6221-9869-46f6-830f-2c15bdeb5f58)
![image](https://github.com/user-attachments/assets/0cf572d2-91f5-4a4f-9a0b-7c75033f5b7e)
##### 10 нагрузчиков
![image](https://github.com/user-attachments/assets/63cea7e0-59c7-40f7-82ea-338de47953b3)
![image](https://github.com/user-attachments/assets/ce4b6c57-f194-4b68-b400-18738a89bc5f)
![image](https://github.com/user-attachments/assets/3e4fe686-9bfa-466e-ae99-498df696f464)

А больше 10 запустить не выйдет, ноут не вывозит....


`multi-bench:`
##### 1 нагрузчик
![image](https://github.com/user-attachments/assets/6e9ed31a-cc2a-4d8c-b433-e2e41eda23c1)
![image](https://github.com/user-attachments/assets/99a048b9-0ef3-49da-a907-61631daf116b)
![image](https://github.com/user-attachments/assets/3a5d7abd-6aed-48aa-a3d1-66c180835f29)
![image](https://github.com/user-attachments/assets/86f8cb89-72da-4c16-ba7c-6fddbbe8902f)
##### 3 нагрузчика
![image](https://github.com/user-attachments/assets/93dac60c-04d0-4fbd-a7a0-ea252cb38827)
![image](https://github.com/user-attachments/assets/5ce8dbe5-b4d0-4b91-a813-04b7a7091a32)
![image](https://github.com/user-attachments/assets/955e9cbe-ab8a-4244-8403-a93ac70602ff)
![image](https://github.com/user-attachments/assets/3f1dbe50-520b-4883-ad43-f99d3450d85f)
##### 5 нагрузчиков
![image](https://github.com/user-attachments/assets/b1dc4c38-c8fb-4f64-9456-150d6cfbbafc)
![image](https://github.com/user-attachments/assets/5748efea-95a1-4c6a-9086-99aae3f341fc)
![image](https://github.com/user-attachments/assets/2ff6b5bd-0976-4cb3-8f19-e88340c9c492)
![image](https://github.com/user-attachments/assets/3d56decc-7474-4068-9b25-523d352231c0)

#### С оптимизацией:
`ema-search-str`

![image](https://github.com/user-attachments/assets/acacd58f-d3bd-44ae-8460-300aa18641bd)

`sort`

![image](https://github.com/user-attachments/assets/92e60733-1be4-42b2-a813-863e9a3ea551)

`multi-bench`

![image](https://github.com/user-attachments/assets/6df0c4c0-f06a-4c09-b0b8-2ce7a162a381)
#### Доп. нагрузчик

`collatz-conjecture:`

##### 1 нагрузчик

![image](https://github.com/user-attachments/assets/2c9d6e42-1854-4801-9676-1b464ca1a536)
![image](https://github.com/user-attachments/assets/4a9d643e-444e-4f77-a905-8daafdf81e9a)

##### 2 нагрузчика

![image](https://github.com/user-attachments/assets/465a24c3-dff6-4697-b490-15a7ae7bdd1d)
![image](https://github.com/user-attachments/assets/f0c0f6a3-480c-4ce6-b752-08ed4ae05bc4)
![image](https://github.com/user-attachments/assets/87a43cde-81a6-42cc-9c0a-0609b54c956e)

##### 3 нагрузчика

![image](https://github.com/user-attachments/assets/c06791ad-f23f-4195-8010-1eb7d3cac234)
![image](https://github.com/user-attachments/assets/b530f36f-4b46-4da1-962a-70b06973dba7)
#### Сравнительный анализ
- `ema-search-str` Диск удалось нагрузить только увеличением количества нагрузчиков до 3, ощутимый рост нагрузки был отслежен только на 5 нагрузчиках. USER% был выше, чем предполагалось, но с увеличением количества нагрузчиков стал меньше относительно SYS%. SYS% - высокий. WAIT% был низким. 
- `sort` ЦП нагружался без особых проблем, при попытке запуска 11 нагрузчиков сделать скриншот экрана даже не получилось. SYS%, как и ожидалось, низкий. USER% рос в геометрической прогрессии. На диспетчере задач видно, что при 10 нагрузчиках ЦП был загружен на 100% (это было страшно).
- `collatz-conjecture`  SYS% - высокий, так как результат вычислений каждого шага выводился на консоль. При увеличении количества нагрузчиков наблюдался рост SYS% и USER%. Однако, USER% был в n раз ниже, чем SYS%.
