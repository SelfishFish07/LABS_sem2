# Лабораторная работа №1: Асимптотическая сложность
## 1. Поиск

<img src="Images/Search_worst_per.png" alt="текст" height="250"/>
<img src="Images/Search_worst_bin.png" alt="текст" height="250"/>

<img src="Images/Search_mean_per.png" alt="текст" height="250"/>
<img src="Images/Search_mean_bin.png" alt="текст" height="250"/>

Прямые измерения времени выполнения программы подтвердили, что алгоритм поиска элемента перебором имеет асимптотическую сложность $O(n)$, алгоритм бинарного поиска для упорядоченного массива $-$ $O(\log(n))$.

## 2. Сумма

<img src="Images/Sum_worst_per.png" alt="текст" height="250"/>
<img src="Images/Sum_worst_bin.png" alt="текст" height="250"/>

<img src="Images/Sum_mean_per.png" alt="текст" height="250"/>
<img src="Images/Sum_mean_bin.png" alt="текст" height="250"/>

Прямые измерения времени выполнения программы подтвердили, что алгоритм поиска элемента перебором имеет асимптотическую сложность $O(n^2)$, алгоритм бинарного поиска для упорядоченного массива $-$ $O(n)$.

## 3. Часто используемый элемент

<img src="Images/Strat_uni_A.png" alt="текст" height="180"/>
<img src="Images/Strat_uni_B.png" alt="текст" height="180"/>
<img src="Images/Strat_uni_C.png" alt="текст" height="180"/>

<img src="Images/Strat_nonuni_A.png" alt="текст" height="180"/>
<img src="Images/Strat_nonuni_B.png" alt="текст" height="180"/>
<img src="Images/Strat_nonuni_C.png" alt="текст" height="180"/>

Алгоритмы A, B, C имеют линейную асимптотическую сложность, так как перемещения элементов не сильно влияют на общую производительность (использовался поиск перебором). Угловые коэффициенты наклона графиков показывают, что в среднем $t_A<t_C<t_B$ для обоих видов распределения запросов. Кроме того, время при неравномерном распределении запросов меньше, чем в при равномерном.