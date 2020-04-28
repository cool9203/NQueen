/*@@人工智慧作業-2
  @@使用爬山演算法實作八皇后*/

#include <iostream>
#include <random>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

class NQueen {
protected:
	std::vector<std::vector<int>> map;
	int _size, top, * X, * Y;
	std::default_random_engine generator; //偽亂數產生器
	std::random_device rd; //利用硬體系統給的值來得到一個隨機數
	std::uniform_int_distribution<int> distribution;

public:
	NQueen(int _size) {
		this->_size = _size;
		this->top = 0;
		this->X = new int[this->_size];
		this->Y = new int[this->_size];
		generator.seed(rd()); //設定偽亂數產生器的seed
		//設定亂數分布範圍
		std::uniform_int_distribution<int>::param_type param(0, this->_size - 1);
		distribution.param(param);
	}


	~NQueen() {
		delete[] this->X;
		delete[] this->Y;
	}


	void set_map() {
		map.clear();
		//初始化棋盤
		for (int i = 0; i < this->_size; i++) {
			std::vector<int> tempv;
			for (int j = 0; j < this->_size; j++) {
				tempv.push_back(0);
			}
			map.push_back(tempv);
		}

		for (int i = 0; i < this->top; i++) {
			map[X[i]][Y[i]] = 1;
		}
	}


	void print() {
		set_map();

		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (map[i][j] == 1)
					std::cout << "╳ ";
				else
					std::cout << "ˍ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}


	//heuristic function
	int price(int *x, int *y) {
		int count = 0;
		for (int i = 0; i < this->top - 1; i++) {
			double _x = static_cast<double>(x[i]) - static_cast<double>(x[this->top - 1]);
			double _y = static_cast<double>(y[i]) - static_cast<double>(y[this->top - 1]);
			double m = _y / _x;
			if (_x == 0.0 || _y == 0.0 || m == 1.0 || m == -1.0) {
				count++;
				continue;
			}
		}
		return count;
	}


	int price_check(int* x, int* y) {
		int count = 0;
		for (int i = 0; i < _size; i++) {
			for (int j = i + 1; j < _size; j++) {
				double _x = static_cast<double>(x[i]) - static_cast<double>(x[j]);
				double _y = static_cast<double>(y[i]) - static_cast<double>(y[j]);
				double m = _y / _x;
				if (_x == 0.0 || _y == 0.0 || m == 1.0 || m == -1.0) {
					count++;
					continue;
				}
			}
		}

		return count;
	}


	void rand_push() {
		push(this->distribution(this->generator));
	}


	void push(int index) {
		
		this->X[this->top] = top;
		this->Y[this->top] = index;
		this->top++;
	}


	void pop() {
		this->top--;
	}


	void shuffle(int *data) {
		int size = (this->distribution(this->generator) + 1) * this->_size;
		for (int i = 0; i < size; i++)
		{
			int l = this->distribution(this->generator);
			int r = this->distribution(this->generator);
			std::swap(data[l], data[r]);
		}
	}


	void clear() {
		this->top = 0;
	}


	bool next() {
		int* temp = new int[this->_size];
		for (int i = 0; i < this->_size; i++)
			temp[i] = i;

		shuffle(temp);

		for (int i = 0; i < this->_size; i++) {
			push(temp[i]);
			if (price(this->X, this->Y) == 0)
			{
				delete[] temp;
				return true;
			}
			else
				pop();
		}

		return false;
	}


	void start() {
		int restart = 0;
		while (true) {
			bool flag = true;
			while (true) {
				if (this->top == this->_size / 4)
					break;

				rand_push();
				if (price(this->X, this->Y) != 0)
					pop();
			}

			while (true) {
				flag = next();
				if (!flag || this->top == this->_size)
					break;
			}

			if (flag) {
				print();
				std::cout << price_check(this->X, this->Y) << std::endl;
				break;
			}
			else {
				clear();
				restart++;
			}
		}
		
		std::cout << "restart:" << restart << std::endl;
		
	}
};


int main() {
	int n;
	while (true) {
		std::cin >> n;
		if (n <= 3)
			break;
		LARGE_INTEGER start_time, end_time, frequency_time;
		QueryPerformanceFrequency(&frequency_time);
		QueryPerformanceCounter(&start_time);

		NQueen queen(n);
		queen.start();

		QueryPerformanceCounter(&end_time);
		printf("used:%lf s\n\n", (end_time.QuadPart - start_time.QuadPart) / (double)(frequency_time.QuadPart));
	}


	system("pause");
	return 0;
}
