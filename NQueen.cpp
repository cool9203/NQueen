/*@@人工智慧作業-2
  @@使用爬山演算法實作八皇后*/

#include <iostream>
#include <random>
#include <vector>

class NQueen {
protected:
	std::vector<std::vector<int>> map;

public:
	NQueen(int assign) {
		//初始化棋盤
		for (int i = 0; i < assign; i++) {
			std::vector<int> tempv;
			for (int j = 0; j < assign; j++) {
				tempv.push_back(0);
			}
			map.push_back(tempv);
		}
	}


	//複製vector : main_vector  to  copy_vector
	void vector_cpy(std::vector<std::vector<int>> &main_vector, std::vector<std::vector<int>> &copy_vector) {
		copy_vector.clear();
		copy_vector.assign(main_vector.begin(), main_vector.end());
	}


	//清空map
	void clean() {
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			for (int j = 0; j < static_cast<int>(map.size()); j++) {
				map.at(i).at(j) = 0;
			}
		}
	}


	//隨機給map一個盤面(固定每直行只有1個皇后)
	void rand() {
		clean();
		std::random_device rd; //利用硬體系統給的值來取值
		std::default_random_engine generator(rd()); //初始化，並利用rd()的值找出相對應的種子碼??
		std::uniform_int_distribution<int> distribution(0, map.size() - 1); //設定範圍與決定要產生什麼類型的亂數 ex:int float..
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			int randnumber = distribution(generator);
			if (map.at(i).at(randnumber)!=1)
				map.at(i).at(randnumber) = 1;
		}
	}


	//顯示
	void print() {
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			for (int j = 0; j < static_cast<int>(map.size()); j++) {
				std::cout << map.at(j).at(i) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}


	//顯示座標(0 ~ N-1)
	void print_coordinate() {
		std::vector<int> x, y;
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			for (int j = 0; j < static_cast<int>(map.size()); j++) {
				if (map[i][j] == 1) {
					x.push_back(i);
					y.push_back(j);
				}
				if (map.size() == x.size())
					break;
			}
			if (map.size() == x.size())
				break;
		}
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			std::cout << "(" << x.at(i) << "," << y.at(i) << ")\n";
		}
	}


	//利用斜率來計算
	int price_slope(std::vector<std::vector<int>> v) {
		std::vector<int> x, y;
		for (int i = 0; i < static_cast<int>(v.size()); i++) {
			for (int j = 0; j < static_cast<int>(v.size()); j++) {
				if (v[i][j] == 1) {
					x.push_back(i);
					y.push_back(j);
				}
				if (v.size() == x.size())
					break;
			}
			if (v.size() == x.size())
				break;
		}
		return slope(v, x, y);
		
	}


	//斜率計算 - 如果xy=0，即直橫行有其他子    如果(y/x)==1.0 or -1.0 即斜行有其他子
	int slope(std::vector<std::vector<int>> v, std::vector<int> _x, std::vector<int> _y) {
		int count = 0;
		for (int i = 0; i < static_cast<int>(v.size()); i++) {
			for (int j = i + 1; j < static_cast<int>(v.size()); j++) {
				double x = _x[i] - _x[j];
				double y = _y[i] - _y[j];
				double m = y / x;
				if (x == 0.0 || y == 0.0 || m == 1.0 || m == -1.0) {
					count++;
					continue;
				}
			}
		}
		return count;
	}


	//利用該子是否有與其他子衝突到來計算(皇后走法：該點直、橫行、斜行)
	int price_conflict(std::vector<std::vector<int>> v) {
		int count = 0;
		for (int i = 0; i < static_cast<int>(v.size()); i++) {
			for (int j = 0; j < static_cast<int>(v.size()); j++) {
				if (v.at(i).at(j) == 1) {
					count += conflict(v, i, j);
					//std::cout << count << " ";
				}
			}
		}
		//std::cout << std::endl;
		return count;
	}


	int conflict(std::vector<std::vector<int>> v, int row,int col) {
		int count = 0;
		int utdl_row = row, dtul_row = row;
		int utdl_col = col, dtul_col = col;
		bool utd_b = false, dtu_b = false;
		//計算該點直排橫排的衝突數
		for (int i = 0; i < static_cast<int>(v.size()); i++) {
			if (v[row][i] == 1 && i != col)
				count++;

			if (v[i][col] == 1 && i != row)
				count++;

			//先算下面斜邊會用的到變數
			if (utdl_row != 0 && utdl_col != 0) {
				utdl_row--;
				utdl_col--;
			}
			if (dtul_row != 0 && dtul_col != v.size() - 1) {
				dtul_row--;
				dtul_col++;
			}
		}
		//計算該點斜邊的衝突數
		
		while (true) {
			if (utd_b && dtu_b)
				break;

			if (utdl_row != v.size() && utdl_col != v.size()) {
				if (v[utdl_row][utdl_col] == 1 && utdl_row != row && utdl_col != col)
					count++;
				utdl_row++;
				utdl_col++;
			}
			else {
				utd_b = true;
			}

			if (dtul_row != v.size() && dtul_col != -1) {
				if (v[dtul_row][dtul_col] == 1 && dtul_row != row && dtul_col != col)
					count++;
				dtul_row++;
				dtul_col--;
			}
			else {
				dtu_b = true;
			}
		}
		return count;
	}


	//展開直行並實際執行，看是否有減少的price   if price減少 return true
	bool move(std::vector<std::vector<int>> &v, int _row, int func) {
		int price;
		if (func == 1)
			price = price_slope(v);
		else
			price = price_conflict(v);
		for (int col = 0; col < static_cast<int>(v.size()); col++) {
			for (int i = 0; i < static_cast<int>(v.size()); i++) { //先清空那排
				v[_row][i] = 0;
			}

			v[_row][col] = 1; //set
			int vp;
			if (func == 1)
				vp = price_slope(v);
			else
				vp = price_conflict(v);

			if (vp < price) //如果價格減少 than
				return true;
		}
		return false;
	}


	//展開所有，找到下一步有減少price的   if price減少 return true
	bool search(int func) {
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			std::vector<std::vector<int>> v;
			vector_cpy(map, v);
			if (move(v, i, func)) { //if 價格減少 than
				vector_cpy(v, map);
				if (func==1)
					std::cout << "End of Search.  price_slope=" << price_slope(map) << std::endl;
				else
					std::cout << "End of Search.  price_conflict=" << price_conflict(map) << std::endl;
				return true;
			}
		}
		return false;
	}


	//先隨機給一盤面 -> 看price能否到0(即理想狀態) -> if price==0 return and print   else loop
	void start_slope() {
		while (true) {
			rand();
			while (true) {
				if (!search(1)) {
					if (price_slope(map) == 0) {
						print();
						std::cout << "\n" << "price_conflict:" << price_conflict(map) << std::endl;
						return;
					}
					else {
						break;
					}
				}
			}
			std::cout << "\n";
		}
	}


	void start_conflict() {
		while (true) {
			rand();
			while (true) {
				if (!search(0)) {
					if (price_conflict(map) == 0) {
						print();
						std::cout << "\n" << "price_slope:" << price_slope(map) << std::endl;
						return;
					}
					else {
						break;
					}
				}
			}
			std::cout << "\n";
		}
	}
};


/*
int main() {
	NQueen queen(8);
	//queen.start_slope();
	queen.start_conflict();
	queen.print_coordinate();
	
	system("pause");
	return 0;
}
*/