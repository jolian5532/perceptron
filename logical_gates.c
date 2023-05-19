#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ITERS 3000
#define LR 0.00001f /*LEARNING RATE */ 
#define H 1e-4
#define HB 0.00001f

float sigmoid(float x)
{
	return 1 / (1 + exp(-x));
}

float randFloat(float min, float max)
{
	float scale = rand() / (float) RAND_MAX;
	return min + scale *(max - min);
}

float activate(float x)
{
	return (0.0 < x) ? 1 : 0;
}

struct point
{
	float in[3];
	float weights[3];
};

float guess(struct point *point1)
{
	float sum = 0;
	for (int i = 0; i < 3; i++)
	{
		sum += point1->in[i] *point1->weights[i];
	}

	return sum;
}

float or_data[4][3] = {
	{ 0,0,0 },
	{ 0,1,1 },
	{ 1,0,1 },
	{ 1,1,1 }
};

float cost(struct point *point1, float data[0][3], int train_count)
{
	float myGuess, answer, d, res = 0.0;
	for (size_t i = 0; i < train_count; i++)
	{
		for (size_t i = 0; i < 4; i++)
		{
			point1->in[0] = data[i][0];
			point1->in[1] = data[i][1];
			point1->in[2] = 1;
			myGuess = sigmoid(guess(point1));
			answer = data[i][2];
			d = myGuess - answer;
			res += d * d;
		}
	}

	res /= (float) train_count;
	return res;
}

int main()
{
	struct point point1;
	srand(time(NULL));
	for (int i = 0; i < 2; i++)
	{
		point1.weights[i] = randFloat(-1.0, 1.0);
	}

	for (int i = 0; i < 25000; i++)
	{
		float icost = cost(&point1, or_data, ITERS);
		printf("%f\n", icost);

		for (int i = 0; i < 2; i++)
		{
			point1.weights[i] += H;
		}

		float hcost = cost(&point1, or_data, ITERS);

		point1.weights[2] += HB;
		float bcost = cost(&point1, or_data, ITERS);

		float dw = (hcost - icost) / H;
		float db = (bcost - icost) / HB;

		for (int i = 0; i < 2; i++)
		{
			point1.weights[i] -= LR * dw;
		}

		point1.weights[2] -= LR * db;
	}

	for (size_t j = 0; j < 4; j++)
	{
		point1.in[0] = or_data[j][0];
		point1.in[1] = or_data[j][1];
		point1.in[2] = 1;
		float myGuess = sigmoid(guess(&point1));
		printf("x1: %f, x2: %f, out:%f, guess: %f\n", or_data[j][0], or_data[j][1], or_data[j][2], myGuess);
	}

	return 0;
}