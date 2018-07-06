#include "Objects.h"

sf::View view;
sf::Vector2f playerPos;
float PassedTime;
int** Ground;

int width = 51, height = 25;

void setArray(int *** arr)
{
	*arr = new int*[width];
	for (int i = 0; i < width; i++)
		(*arr)[i] = new int[height];
	for (int i = 0; i<width; i++)
		for (int y = 0; y<height; y++)
			(*arr)[i][y] = 0;
}

int intersection(sf::Vector2i a1, sf::Vector2i a2, sf::Vector2i b)
{
	float ax1, ay1, ax2, ay2, bx1, by1, bx2, by2;
	float v1, v2, v3, v4, size;
	b.x += 16;
	b.y += 16;

	size = 20;
	ax1 = a1.x;
	ay1 = a1.y;
	ax2 = a2.x;
	ay2 = a2.y;
	bx1 = b.x + size;
	by1 = b.y - size;
	bx2 = b.x - size;
	by2 = b.y + size;
	for (int i = 0; i < 2; i++)
	{
		if (i == 1)
		{
			bx1 = b.x - size;
			by1 = b.y - size;
			bx2 = b.x + size;
			by2 = b.y + size;
		}
		v1 = (bx2 - bx1)*(ay1 - by1) - (by2 - by1)*(ax1 - bx1);
		v2 = (bx2 - bx1)*(ay2 - by1) - (by2 - by1)*(ax2 - bx1);
		v3 = (ax2 - ax1)*(by1 - ay1) - (ay2 - ay1)*(bx1 - ax1);
		v4 = (ax2 - ax1)*(by2 - ay1) - (ay2 - ay1)*(bx2 - ax1);

		if (v1*v2<0 && v3*v4<0)
		{
			//cout << "True X:Y" <<b.x<<":"<<b.y << endl;
			return true;
		}
	}
	//cout << "False" << endl;
	return false;
}

std::list <sf::Vector2i> search(sf::Vector2i s, sf::Vector2i finP)
{
	struct history { int x, y, step; history(int a, int b, int c) { x = a;	y = b;	step = c; } };
	std::list <sf::Vector2i> Sort;
	std::list <history> wave;
	std::list <history>::iterator itWave;
	sf::Vector2i fin(finP.x, finP.y);
	int** finishRay, **step;
	setArray(&finishRay); setArray(&step);
	int waveCol = 0, x = fin.x, y = fin.y;
	s.x /= 32; s.y /= 32;
	wave.push_back(history(s.x, s.y, 1));
	step[s.x][s.y] = 1;
	for (itWave = wave.begin(); itWave != wave.end();)
	{
		waveCol++;
		if (waveCol>50 * 25)	return Sort;
		history b = *itWave;
		if (fin == sf::Vector2i(b.x, b.y))	goto Search2;
		if (step[b.x - 1][b.y] == 0 && Ground[b.x - 1][b.y] == 0) { wave.push_back(history(b.x - 1, b.y, b.step + 1));	step[b.x - 1][b.y] = b.step + 1; }
		if (step[b.x + 1][b.y] == 0 && Ground[b.x + 1][b.y] == 0) { wave.push_back(history(b.x + 1, b.y, b.step + 1));	step[b.x + 1][b.y] = b.step + 1; }
		if (step[b.x][b.y - 1] == 0 && Ground[b.x][b.y - 1] == 0) { wave.push_back(history(b.x, b.y - 1, b.step + 1));	step[b.x][b.y - 1] = b.step + 1; }
		if (step[b.x][b.y + 1] == 0 && Ground[b.x][b.y + 1] == 0) { wave.push_back(history(b.x, b.y + 1, b.step + 1));	step[b.x][b.y + 1] = b.step + 1; }
		itWave++;
	}
	return Sort;
Search2:
	finishRay[x][y] = step[x][y];
	Sort.push_back(sf::Vector2i(x, y));
	while (finishRay[x][y]>1)
	{
		if (finishRay[x][y] == step[x - 1][y] + 1 && finishRay[x][y]>1) { finishRay[x - 1][y] = step[x - 1][y];	x -= 1;	Sort.push_back(sf::Vector2i(x, y)); }
		if (finishRay[x][y] == step[x + 1][y] + 1 && finishRay[x][y]>1) { finishRay[x + 1][y] = step[x + 1][y];	x += 1;	Sort.push_back(sf::Vector2i(x, y)); }
		if (finishRay[x][y] == step[x][y - 1] + 1 && finishRay[x][y]>1) { finishRay[x][y - 1] = step[x][y - 1];	y -= 1;	Sort.push_back(sf::Vector2i(x, y)); }
		if (finishRay[x][y] == step[x][y + 1] + 1 && finishRay[x][y]>1) { finishRay[x][y + 1] = step[x][y + 1];	y += 1;	Sort.push_back(sf::Vector2i(x, y)); }
	}
	return Sort;
}

