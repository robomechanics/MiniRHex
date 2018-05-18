#include "../conversions.h"
#include <stdio.h>

int main(){
  float V1 = 0.98;
  int D1 = V_to_dynV(V1);
  float V2 = 2.5;
  int D2 = V_to_dynV(V2);
  float V3 = 0;
  int D3 = V_to_dynV(V3);
  float V4 = -0.4;
  int D4 = V_to_dynV(V4);
  float V5 = -2.8;
  int D5 = V_to_dynV(V5);
  printf("V to dynV\n");
  printf("%f -> %d \n", V1, D1);
  printf("%f -> %d \n", V2, D2);
  printf("%f -> %d \n", V3, D3);
  printf("%f -> %d \n", V4, D4);
  printf("%f -> %d \n", V5, D5);

  D1 = 1000;
  V1 = dynV_to_V(D1);
  D2 = -1000;
  V2 = dynV_to_V(D2);
  D3 = 0;
  V3 = dynV_to_V(D3);
  D4 = 120;
  V4 = dynV_to_V(D4);
  D5 = -120;
  V5 = dynV_to_V(D5);

  printf("\ndynV to V\n");
  printf("%d -> %f \n", D1, V1);
  printf("%d -> %f \n", D2, V2);
  printf("%d -> %f \n", D3, V3);
  printf("%d -> %f \n", D4, V4);
  printf("%d -> %f \n", D5, V5);


  printf("\ndynV to V and back\n");
  D1 = 923;
  V1 = dynV_to_V(D1);
  D2 = V_to_dynV(V1);
  printf("%d -> %f -> %d \n", D1, V1, D2);

  printf("\nP to theta\n");
  int P1 = 0;
  float T1 = P_to_Theta(P1);
  int P2 =  1020;
  float T2 = P_to_Theta(P2);
  int P3 = 375;
  float T3 = P_to_Theta(P3);
  printf("%d -> %f \n", P1, T1);
  printf("%d -> %f \n", P2, T2);
  printf("%d -> %f \n", P3, T3);

  printf("\nTheta to p\n");
  T1 = 0;
  P1 = Theta_to_P(T1);
  T2 =  -81;
  P2 = Theta_to_P(T2);
  T3 = 174;
  P3 = Theta_to_P(T3);
  printf("%f -> %d \n", T1, P1);
  printf("%f -> %d \n", T2, P2);
  printf("%f -> %d \n", T3, P3);

  printf("\nTheta to ThetaR\n");
  for (int i = -180; i <= 180; i = i + 10){
    T1 = i;
    float TR1 = Theta_to_ThetaR(T1);
    printf("%f -> %f \n", T1, TR1);
  }
}
