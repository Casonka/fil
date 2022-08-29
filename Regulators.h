    /*!
    *   --------------------------------------------------------------------------
    *                       ///Regulators\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin
    *   @date 02/08/2022 - last update version Regulators
    *
    *       @note [RCR:Regulators] Configuration file Regulators
    */
#pragma once
#include "BoardSelection.h"
#if(CALC_REGULATOR == 1)

    /*!
    *   @list P_Regulator Settings
    */
    typedef struct
    {
          float p_k; //П коэфициент
          float target; //Целевое значение
          float current; //Текущее (необходимо обновлять извне перед каждым расчетом)
          float max_output; //Максимальный выход, что бы поправка не выходила за рамки
          float min_output;
          float output; //Поправка, результат работы П
          char p_on; //Вкл/Выкл П если выкл то output всегда равен 0, однако все остальное продолжает расчитываться
          char p_finish;
          float error_dir;
          float p_error_end;
          float p_output_end;
    }P_Regulator;

void init_P_Regulator(P_Regulator Regulator);

    /*!
    *   @list PI_Regulator Settings
    */
    typedef struct
    {
          float p_k; //П коэфициент
          float i_k; //И коэфициент
          float target; //Целевое значение
          float current; //Текущее (необходимо обновлять извне перед каждым расчетом)
          float sum_error; //Суммарная ошибка (для И регулятора)
          float max_sum_error; //Максимальная суммарная ошибка (что бы И регулятор не уходил до максимума если невозможно добиться требуемого значения)
          float max_output; //Максимальный выход, что бы поправка не выходила за рамки
          float min_output;
          float cut_output;
          float output; //Поправка, результат работы ПИ
          char pi_on; //Вкл/Выкл ПИ если выкл то output всегда равен 0, однако все остальное продолжает расчитываться
          char pi_finish;
          float pi_error_end;
          float pi_output_end;
    }PI_Regulator;

void Regulator_PI_Init(PI_Regulator Regulator);

    /*!
    *   @list PID_Regulator Settings
    */
    typedef struct
    {
          float p_k; //П коэфициент
          float i_k; //И коэфициент
          float d_k; //Д коэфициент
          float target; //Целевое значение
          float current; //Текущее (необходимо обновлять извне перед каждым расчетом)
          float prev_error; //Предыдущее значение ошибки (для Д регулятора)
          float error;  // обычная ошибка
          float sum_error; //Суммарная ошибка (для И регулятора)
          float max_sum_error; //Максимальная суммарная ошибка (что бы И регулятор не уходил до максимума если невозможно добиться требуемого значения)
          float dif_error; // ошибка для дифференциальной составляющей регулятора
          float max_output; //Максимальный выход, что бы поправка не выходила за рамки
          float min_output;
          float output; //Поправка, результат работы ПИД
          char pid_on; //Вкл/Выкл ПИД если выкл то output всегда равен 0, однако все остальное продолжает расчитываться
          char pid_finish;
          float pid_error_end;
          float pid_output_end;
    }PID_Regulator;

    float EnginePWM;
    void Regulator_PID_init(void);

    void RegulatorPIDLowLevel(void);

#endif /*CALC_REGULATOR*/
