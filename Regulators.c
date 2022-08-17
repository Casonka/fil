    /*!
    *   --------------------------------------------------------------------------
    *                       ///Regulators\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin, Caska
    *   @date 02/08/2022 - last update version Regulators
    *
    *       @note [RCR:Regulators] Regulators source file
    */
#include "FilConfig.h"

#if (CALC_REGULATOR == 1)
#include "Regulators.h"

/*!
*   @code PID Regulator Sector
*/
PID_Regulator EngineReg;
float Motor_Coord;
float EnginePWM = 0.0;
void init_PID_Regulator(void)  // инициализация регуляторов
{

    /*!
    *   @note [RCR:Regulators] Configuration PID
    *   @file RCR_DevBoard_3_Setup.h - main configuration file
    */
  	EngineReg.p_k = __config_Regulator_P_K;
  	EngineReg.i_k = __config_Regulator_I_K;
  	EngineReg.d_k = __config_Regulator_D_K;
  	EngineReg.pid_on = __config_Regulator_ON;
  	EngineReg.pid_error_end  = __config_Regulator_ERROR_END;
  	EngineReg.pid_output_end = __config_OUTPUT_END;
  	EngineReg.max_sum_error = __config_MAX_SUM_ERROR;
  	EngineReg.max_output = __config_MAX_OUTPUT;
  	EngineReg.min_output = __config_MIN_OUTPUT;

    // zeroing errors
    EngineReg.prev_error = 0.0;
    EngineReg.error = 0.0;
    EngineReg.sum_error = 0.0;
    EngineReg.dif_error = 0.0;
    Motor_Coord = 0.0;
}

/*!
*   @attention Static function
*   @attention Speed must be less then 0.85 (sum error will upper that max_sum_error)
*   @brief PID_Parse_EncoderData(int32_t encoderdata) - check value from encoder and calculate speed
*/
static void PID_Calc(PID_Regulator *pid_control)
{
  pid_control->error = pid_control->target - pid_control->current;
  pid_control->dif_error = pid_control->error - pid_control->prev_error;
  pid_control->prev_error = pid_control->error;
  pid_control->sum_error += pid_control->error;

  if (pid_control->sum_error > pid_control->max_sum_error)
    pid_control->sum_error = pid_control->max_sum_error;
  if (pid_control->sum_error < -pid_control->max_sum_error)
    pid_control->sum_error = -pid_control->max_sum_error;

  if (pid_control->pid_on)
  {
    pid_control->output = ((float)(pid_control->p_k * pid_control->error)+(pid_control->i_k * pid_control->sum_error)+
            (pid_control->d_k * pid_control->dif_error));

    if (pid_control->output > pid_control->max_output)
      pid_control->output = pid_control->max_output;
    else if (pid_control->output < -pid_control->max_output)
      pid_control->output = -pid_control->max_output;

    if (pid_control->output < pid_control->min_output && pid_control->output > -pid_control->min_output)
      pid_control->output = 0;

    if ((pid_control->output <= pid_control->pid_output_end) &&(
        pid_control->output >= -pid_control->pid_output_end) &&(
        pid_control->error <= pid_control->pid_error_end) && (pid_control->error >= -pid_control->pid_error_end))
      pid_control->pid_finish = 1;
    else
      pid_control->pid_finish = 0;
  }
  else
  {
    pid_control->output = 0;
    pid_control->pid_finish = 0;
  }
}

/*!
*   @attention Static function
*   @brief PID_Parse_EncoderData(int32_t encoderdata) - check value from encoder and calculate speed
*/
static void PID_Parse_EncoderData(int32_t encoderdata)
{
    EngineReg.current = ((((float)(encoderdata)) * DISK_TO_REAL) / TIME);
    Motor_Coord += EngineReg.current * TIME;
}


int16_t EncData;
/*!
*   @brief PID_Low_Level(void) - General PID calculating engine
*/
void PID_Low_Level(void)
{
    EncData = ((int16_t)*ENCODER1_CNT);
    if(EnginePWM > 1.0) EnginePWM = 1.0;
    if(EnginePWM < -1.0) EnginePWM = -1.0;
    EngineReg.target = EnginePWM;
    PID_Parse_EncoderData(EncData);
    *ENCODER1_CNT = 0;
    PID_Calc(&EngineReg);
    SetVoltage(EngineReg.output);
}

#endif /*CALC_REGULATOR*/
