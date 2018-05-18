#include "../desired_values.h"
#include "../control_parameters.h"
#include "../pd_control.h"
#include "../leg_info.h"
#include "../gait_parameters.h"

#include <stdio.h>      /* printf */
#include <fstream>
#include <math.h>


int main(){

  remove("../../txt/data.txt");
  std::ofstream dataFile("../../txt/data.txt");
  float curr;
  int li = 1;
  int gait = WALK;
  
  
  update_gait(li, gait, 0);
  leg l = legs[li];
  l.gait = gait;
  printf("%d\n", l.t_c);

  for (int i = 0; i <= 1*l.t_c; i = i + 1){
    curr = get_desired_vals(i, l).global_theta;
    
    dataFile << i << ", " << curr << "\n";
    
    printf("%d, %f\n", i, curr);
  }
  //pd_controller(70, 180, 0.0, 1.0, 0.1, 0.5);
  dataFile.close();
}
