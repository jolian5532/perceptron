#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 50
#define HEIGHT 50
#define RANGE 100
#define ITERS 50
#define LR 0.01 /* LEARNING RATE */

float randFloat(float min, float max){
  float scale = rand() / (float)RAND_MAX;
  return min + scale * (max - min);
}

float activate(float x){
  return (0.0 < x) ? 1 : 0 ;
}

struct point {
  float in[2];
  float weights[2];
  float out;
};

float guess(struct point* point1){
  float sum = 0;
  for(int i = 0; i < 2; i++){
    sum += point1->in[i] * point1->weights[i];
  }
  return sum;
}

void train(struct point* point1,float w1,float w2){
  float sum = 0;
  int out;
  int error;
  int pointguess;
  int in1,in2;
  in1 = in1 - (WIDTH / 2);
  in2 = (HEIGHT / 2) - in2;
  for(int i = 0; i < ITERS; i++){
    sum = 0;
    in1 = (int)randFloat(0.0, WIDTH);
    in2 = (int)randFloat(0.0, HEIGHT);
    sum += (float)in1 * w1;
    sum += (float)in2 * w2;
    out = activate(sum);
    point1->in[0] =  in1;
    point1->in[1] =  in2;
    pointguess = activate(guess(point1));
    error = out - pointguess;
    for(int b = 0; b < 2; b++){
      point1->weights[b] += (float)error * point1->in[b] * LR;
    }
  }
}

int main(){
  struct point point1;
  srand(time(NULL));
  for(int i = 0; i < 2; i++){
    point1.weights[i] = randFloat(-1.0, 1.0);
  }

  /*** INPUT ***/
  int x = 41;
  int y = 23;
  int mX = x - (WIDTH / 2);
  int mY = (HEIGHT / 2) - y;
  printf("INPUT : %d , %d\n",mX,mY);
  point1.in[0] = mX;
  point1.in[1] = mY;
  printf("WEIGHTS : %f , %f\n",point1.weights[0],point1.weights[1]);
  /*** TARGET WEIGHTS : -0.965439 , 0.428486 ***/
  train(&point1,-0.965439,0.428486);

 /* after training */
  printf("WEIGHTS : %f , %f\n",point1.weights[0],point1.weights[1]);
  point1.in[0] = mX;
  point1.in[1] = mY;

  /*** DRAW IMAGE 
  FILE *file;
  char filename[] = "random.  ppm";
  file = fopen(filename, "w");
  if (file == NULL){
    printf("Failed to open file!\n");
    return 1;
  }
  char text[] = "P1\n%d %d \n";
  char formattedText[WIDTH*HEIGHT*2+HEIGHT*2];
  sprintf(formattedText, text, WIDTH, HEIGHT);
  fprintf(file, "%s", formattedText);
  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++){
      int mX = x - (WIDTH / 2);
      int mY = (HEIGHT / 2) - y;
      point1.in[0] = mX;
      point1.in[1] = mY;
      int myGuess = activate(guess(&point1));
      
    fprintf(file, "%d ", myGuess);
  }
  fprintf(file, "\n");
  }
  fclose(file);
***/
  
  return 0;
}
