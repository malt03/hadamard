#include <stdio.h>
#include <stdlib.h>

/**********テンソル積を求める**********
answer		- 答えを入れる
x,y			- 元の値
x_len,y_len	- 二次元配列の一辺の長さ
返り値		- 何となくanswerのポインタ
************************************/
double** tensor(double** answer, double** x, int x_len, double** y, int y_len){
  int i, j;
  //コピー
  double **_x, **_y;
  _x = malloc(sizeof(double*) * x_len);
  _y = malloc(sizeof(double*) * y_len);
  for(i=0 ; i<x_len ; i++){
	_x[i] = malloc(sizeof(double) * x_len);
	for(j=0 ; j<x_len ; j++) _x[i][j] = x[i][j];
  }
  for(i=0 ; i<y_len ; i++){
	_y[i] = malloc(sizeof(double) * y_len);
	for(j=0 ; j<y_len ; j++) _y[i][j] = y[i][j];
  }

  //計算
  int answer_len = x_len * y_len;
  for(i=0 ; i<answer_len ; i++)
	for(j=0 ; j<answer_len ; j++)
	  answer[i][j] = _x[i/y_len][j/y_len] * _y[i%y_len][j%y_len];

  //開放
  for(i=0 ; i<x_len ; i++) free(_x[i]);
  for(i=0 ; i<y_len ; i++) free(_y[i]);
  free(_x); free(_y);

  return answer;
}

/************int同士の冪乗************
返り値	- a^b
************************************/
int powi(int a, int b){
  int i, answer=1;
  for(i=0 ; i<b ; i++) answer *= a;
  return answer;
}

/*********Hadamardゲート生成*********
answer		- 答えを入れる
qubit_num	- ゲートをかけるqubitの数
返り値		- 何となくanswerのポインタ
************************************/
double** makeHadamard(double** answer, int qubit_num){
  int i, j;
  //とりあえずhadamard_1を作る
  double** hadamard_1 = malloc(sizeof(double*) * 2);
  for(i=0;i<2;i++){
	hadamard_1[i] = malloc(sizeof(double) * 2);
	for(j=0;j<2;j++){
	  if(i==1 && j==1)	hadamard_1[i][j] = -1.0/1.41421356;
	  else				hadamard_1[i][j] = 1.0/1.41421356;
	}
  }
  //ここまで

  //生成
  answer[0][0] = 1;
  for(i=0 ; i<qubit_num ; i++)	tensor(answer, hadamard_1, 2, answer, powi(2,i));

  //開放
  for(i=0 ; i<2 ; i++)	free(hadamard_1[i]);
  free(hadamard_1);
  
  return answer;
}

/***********論理ゲートをdump***********
answer		- dumpするゲート
qubit_num	- ゲートをかけるqubitの数
************************************/
void dumpGate(double** gate, int qubit_num){
  int i, j;
  int gate_len = powi(2, qubit_num);
  for(i=0 ; i<gate_len ; i++){
	for(j=0 ; j<gate_len ; j++){
	  printf("%6.2lf", gate[i][j]);
	}
	printf("\n");
  }
}
