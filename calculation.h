/* 
 * File:   calculation.h
 * Author: Kopranov_IN
 *
 * Created on 28 ???? 2016 ?., 13:10
 */

#include <stdio.h>
#include <math.h>
#include "fifo.h"
#include "led_dro.h"

#define Fmax //
#define Fmin //
#define N 10// 
#define VALUE_LIMIT 1023
#define OVERFLOW 0xFFFFFFFF

extern unsigned long int freq_max, freq_min;

/*
 * функция вычисляет необходимое значение ЦАП для корректировки 
 * отклонения частоты
 * принимает double_long freq_meas - значение измеренной частоты
 * unsigned int DAC_value - текущее значение ЦАП
 * double_long perfect_freq - необходимое значение частоты
 * возвращает  unsigned int значение ЦАП для корректировки частоты
 */
unsigned int calcul_freq(double_long freq_meas, unsigned int DAC_value,\
        double_long perfect_freq,  unsigned long Range_Freq);
//unsigned long summa_array(unsigned long buffer[]);

/*
 * функция округления типа float
 * принимает float n округляет его до целого числа
 * возвращает unsigned int округленное число
 */ 
unsigned int rounding(float n);

/*
 * функция умножения 64 - разрядного числа разбитого на два 32 - разрядных 
 * принимает множимое: структуру из двух 32-разрядных переменных, и 
 * и множитель число unsigned int 16 разрадное
 * возвращает структуру из двух 32-разрядных помноженных переменных,
 * которые при обьединении состовляют 64-разрядное цело число
 * примерное количество тактов для этой функции при множителе 1023 равно 88000 тактов
 * при частоте контроллера fclk = 32МГц длительность выполнения программы примерно равна t = 27,5мс 
*/
double_long multiplication_x64(double_long value, unsigned int multiplier);

/*
 * функция вычитания 64-разрядного числа из 64-разрядного числа оба
 * разделены на high-byte и low-byte хронящиеся в 32-разрядных числах
 * принимает две структуры double_long first_value и double_long second_value
 * выполняет first_value - second_value
 * возвращает структуру double_long содержащую разность
 * ограничения: вычитание производить только когда first_value > second_value
 */
double_long subtraction(double_long first_value, double_long second_value);

/*
 * функция деления двух чисел 64-разрядных друг на друга
 * принимает double_long first_value и double_long second_value
 * выполняет first_value/second_value
 * возвращает unsigned int значение с округлением после запятой
 */
unsigned int division_64x(double_long first_value, double_long second_value);

/*
 * функция сложения двух чисел 64-разрядных 
 * принимает double_long first_value и double_long second_value
 * выполняет first_value+second_value
 * возвращает double_long 
 */
double_long addition_x64(double_long first_value, double_long second_value);

unsigned int calcul_freq_validate(double_long freq_meas, unsigned int DAC_value,\
        double_long perfect_freq);
