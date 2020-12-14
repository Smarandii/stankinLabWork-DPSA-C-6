// Двух-фазная Сортировка слиянием. 
// Серия - отсортированная подпоследовательность элементов. 
// 3 файла: f, g, t
// из f формируются файлы g, t (исходный файл f скопировать для сохранности)
// из g, t формируется f 
// f - 279 58 -1 7 29 45 8
// g - 279 | -1 | 29 | 8
// t - 58 | 7 | 45 |
// фаза слияния:
// сравниваем числа из t и g, меньшее записываем в f
// f - 58 279 | -1 7 | 29 45 | 8
// повторяем цикл сначала, пока в файле f не останется 1 серия.
// g - 58 279 | 29 45 |
// t - -1 7 | 8

// f - -1 7 58 279 | 8 29 45 |

// g - -1 7 58 279
// t - 8 29 45

// f - -1 7 8 29 45 58 279


// для ускорения считываем группы из k записей, сортируем их в оперативной памяти, отсортированные записи записать в файлы в виде серии длинны k 
// временные затраты пропорциональны числу требуемых проходов по файлам, следовательно надо стремиться сократить кол-во обращений к файлам

// Задание по лабе:
// знать теорию по 3 методам сортировки
// на 4 два метода внешней сортировки


void main() {

	

}