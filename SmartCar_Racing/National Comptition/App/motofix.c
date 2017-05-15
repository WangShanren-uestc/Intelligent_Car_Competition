#include "motofix.h"

double Moto_dead = 1;

void moto_fix(double * left,double * right){
  double y;
  y = AIM_A * (*left) + AIM_B;
  *left = (y - LEFT_B) / LEFT_A;
  if(*left<30)
    *left -= Moto_dead;
  y = AIM_A * (*right) + AIM_B;
  *right = (y - RIGHT_B) / RIGHT_A;
}