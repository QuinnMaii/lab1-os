## Операционные системы 
### Лабораторная работа №1
#### Вариант: Windows ema-search-int factorize </br>
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

`factorize`: USER% будет высоким, так как большая часть времени программы тратится на выполнение вычислений. WAIT% не должен становиться значительным, так как нет работы с диском. SYS% будет низким, так как операции ввода-вывода есть только в начале программы. Из ожидаемых системных вызовов остается только работа с памятью. </br>

#### Средства мониторинга
- Resmon – для мониторинга диска.
- Procexp – для отслеживания USER%, SYS% и переключений контекста.
- Диспетчер задач – для мониторинга процессора и диска.

#### Результаты измерений
`ema-search-int:` 
##### 1 нагрузчик
cs:34049
![Image](https://github.com/user-attachments/assets/dc931c83-f3f9-44ee-a898-ecfecaf20a17)

![Image](https://github.com/user-attachments/assets/3a60655f-19cf-4cf2-9c6a-55fe0c878a79)

![Image](https://github.com/user-attachments/assets/21b3157c-03a6-46dc-8787-5aa1d0f37f8d)

![Image](https://github.com/user-attachments/assets/24630c82-f760-42c3-8423-44959ea381d3)

##### 2 нагрузчика
cs:62543
![Image](https://github.com/user-attachments/assets/6d800b3b-5b2c-49e8-8ff0-4fdec08d31f0)

![Image](https://github.com/user-attachments/assets/cfc9bcac-c5bf-4adb-947e-f8c6c87020d9)

![Image](https://github.com/user-attachments/assets/8a959c13-1e00-4378-87e6-86f9cec13be0)

![Image](https://github.com/user-attachments/assets/c4ccbc01-b2ff-45c7-a66e-cb992e3c2dd4)

##### 3 нагрузчиков
cs:-
![Image](https://github.com/user-attachments/assets/ad78c75a-1b5b-4a52-89e2-c38bdbda53fa)

![Image](https://github.com/user-attachments/assets/2fa2bdab-ad0d-4e2c-bb40-81671d9b6319)

![Image](https://github.com/user-attachments/assets/50b69374-b512-4249-a311-e3cdee7eaff9)

![Image](https://github.com/user-attachments/assets/88e04f65-3256-4a27-9207-5ac640459668)

`factorize:`
##### 1 нагрузчик
cs=20630

![Image](https://github.com/user-attachments/assets/de2ba8e3-d4ef-4a72-a9e2-d778e241d6d6)


![Image](https://github.com/user-attachments/assets/847eac77-a861-45db-98ef-8d62a30eafad)

![Image](https://github.com/user-attachments/assets/ed2465a4-451e-4b83-9d1c-dd14950ed39d)

![Image](https://github.com/user-attachments/assets/3c3bd801-6fc1-4cc0-ac78-8f9e7366cc4e)
##### 2 нагрузчиков
cs: 61590
![Image](https://github.com/user-attachments/assets/e176213a-9dfb-479a-a6c9-ac40ced0f79d)

![Image](https://github.com/user-attachments/assets/be8ac0a9-fe23-4803-83a1-088529f5abe5)

![Image](https://github.com/user-attachments/assets/3253ba47-ac38-4247-83d0-1a16fefe4aa4)

![Image](https://github.com/user-attachments/assets/dfaf163d-0f47-4757-b595-b530bfdd6931)

![Image](https://github.com/user-attachments/assets/198f8e1b-9db7-4de4-908f-2c05a4be234b)
##### 3 нагрузчиков
cs:46016
![Image](https://github.com/user-attachments/assets/850e70d1-ad35-4a2a-b708-608bdfa22af7)

![Image](https://github.com/user-attachments/assets/162a4b8a-7372-49c4-9bb7-a9b32fbbbd45)

![Image](https://github.com/user-attachments/assets/e3bdd471-9a48-4b44-b8ce-7f4e8e046420)

![Image](https://github.com/user-attachments/assets/b78cb57a-3198-4b1a-9757-45872e948913)

![Image](https://github.com/user-attachments/assets/b8f22ffb-32a4-4914-9393-907dae614a1a)
##### 10 нагрузчиков
cs:22652
![image](https://github.com/user-attachments/assets/b933c2c8-1f51-459e-a3bd-898f3c69738b)

![image](https://github.com/user-attachments/assets/21750e9a-4420-4f84-8cf2-844a86462eca)
![image](https://github.com/user-attachments/assets/5cc3171e-c490-4811-8325-64899f092f7c)

![image](https://github.com/user-attachments/assets/355e664c-7966-4c03-b12a-f0fc2c61e722)
![image](https://github.com/user-attachments/assets/5c5d6cbc-35d7-4022-92b2-dfddea97157a)

`complex:`
##### 1 нагрузчик
![Image](https://github.com/user-attachments/assets/cd4b5f1a-d079-440a-af87-1eb3851a23f0)

![Image](https://github.com/user-attachments/assets/c26f3dd8-bff1-4513-828f-8b1669fa2dbe)

![Image](https://github.com/user-attachments/assets/cb25fe61-3cc3-451d-a226-388fedd202c9)

![Image](https://github.com/user-attachments/assets/ac6a4c29-643c-4379-94ce-8d9bbc53644b)
##### 2 нагрузчика
![Image](https://github.com/user-attachments/assets/0b43afce-25fc-47bf-89a3-d07fe760172a)

![Image](https://github.com/user-attachments/assets/afdd2d42-8a73-4e62-82b3-39385732c7e6)

![Image](https://github.com/user-attachments/assets/09f94a1c-68ea-43d6-b0ff-8e597b238cfb)

![Image](https://github.com/user-attachments/assets/540f7883-5c1b-4503-a69a-82fb236e1716)

![Image](https://github.com/user-attachments/assets/63585379-1bee-493b-b829-ef4e6ddc9333)
##### 3 нагрузчиков
![Image](https://github.com/user-attachments/assets/d7a59d81-9e9e-4ad9-9706-717ebfa402dd)

![Image](https://github.com/user-attachments/assets/16f6cf70-2a29-465a-a040-7f69af47de80)

![Image](https://github.com/user-attachments/assets/8b994b55-d455-445c-83a9-9d9d8aed30ff)

![Image](https://github.com/user-attachments/assets/eca0918e-ae4c-436e-920c-81c46425a94c)

![Image](https://github.com/user-attachments/assets/91244f10-da11-4e57-952e-14e94d3daade)



#### С оптимизацией -O3:
`ema-search-int`

![Image](https://github.com/user-attachments/assets/7b792c30-0e69-44c0-b590-3dfd9a58c651)

`factorize`

![Image](https://github.com/user-attachments/assets/f10c7e87-3412-41a6-b421-ac117c131af8)
`complex`

![Image](https://github.com/user-attachments/assets/bae61760-c1f1-4b5b-90a5-1b12e90f4298)

#### Сравнительный анализ
- `ema-search-srt` Диск удалось нагрузить только увеличением количества нагрузчиков до 3, но данных по 3 нагрузчикам нет, поэтому анализ ограничен. При увеличении количества нагрузчиков до 2 наблюдалось увеличение cs, но менее значительное, чем ожидалось. USER% выше предполагаемого, но с увеличением нагрузчиков стал меньше относительно SYS%. SYS% - высокий. WAIT% был низким. 
- `factorize` ЦП нагружался без особых проблем, но при увеличении нагрузчиков время выполнения резко возросло, что говорит о проблемах масштабируемости. SYS%, как и ожидалось, низкий. USER% рос в геометрической прогрессии. На 10 нагрузчиках наблюдается 100% загрузка ЦП, возможный bottleneck. Время выполнения увеличивалось, вместо ожидаемого сокращения.
