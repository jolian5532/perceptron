#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 500
#define HEIGHT 500
#define ITERS 25000
#define LR 0.0003 /* LEARNING RATE */

float randFloat(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

float activate(float x) {
  return (0.0 < x) ? 1 : 0;
}

struct point {
  float in[3];
  float weights[3];
};

float guess(struct point* point1) {
  float sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += point1->in[i] * point1->weights[i];
  }
  return sum;
}

void train(struct point* point1, float w1, float w2, float w3) {
  int out, error, pointguess, in1, in2, in3;
  for (int i = 0; i < ITERS; i++) {
    in1 = (int)randFloat(0.0, WIDTH);
    in2 = (int)randFloat(0.0, HEIGHT);
    in3 = 1;
    
    float sum = (float)in1 * w1 + (float)in2 * w2 + (float)in3 * w3;
    out = activate(sum);
    
    point1->in[0] = in1;
    point1->in[1] = in2;
    
    pointguess = activate(guess(point1));
    error = out - pointguess;
    
    for (int b = 0; b < 3; b++) {
      point1->weights[b] += (float)error * point1->in[b] * LR;
    }
  }
}

int main() {
  struct point point1;
  srand(time(NULL));
  
  for (int i = 0; i < 3; i++) {
    point1.weights[i] = randFloat(-1.0, 1.0);
  }
  
  printf("WEIGHTS: %f, %f, %f\n", point1.weights[0], point1.weights[1], point1.weights[2]);

  /* TARGET WEIGHTS:  0.965439, -0.428486, -0.1428486 */
  train(&point1, -0.965439, 0.428486, -0.1428486);

  /* After training */
  printf("WEIGHTS: %f, %f, %f\n", point1.weights[0], point1.weights[1], point1.weights[2]);

  return 0;
}