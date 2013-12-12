#include "hadamard.h"

int main(){
  int i;
  int answer_len, qubit_num;
  double** answer;

  //入力
  printf("Input number (2^?) ");
  scanf("%d", &qubit_num);
  answer_len = powi(2, qubit_num);

  //answerのメモリ確保
  answer = malloc(sizeof(double*) * answer_len);
  for(i=0 ; i<answer_len ; i++) answer[i] = malloc(sizeof(double) * answer_len);

  //生成と出力
  makeHadamard(answer, qubit_num);
  dumpGate(answer, qubit_num);

  //メモリ解放
  for(i=0 ; i<answer_len ; i++) free(answer[i]);
  free(answer);
  
  return 0;
}
