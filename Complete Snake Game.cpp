#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int highScore = 0;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

// Hàm đặt màu cho console
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Hàm ẩn con trỏ console
void HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Hàm hiển thị menu
void ShowMenu() {
    system("cls");
    SetColor(11); // Màu cyan sáng
    cout << "\n\n";
    cout << "  ╔═══════════════════════════════════════════╗\n";
    cout << "  ║                                           ║\n";
    SetColor(10); // Màu xanh lá
    cout << "  ║      🐍  SNAKE GAME - PAL 🐍      ║\n";
    SetColor(11);
    cout << "  ║                                           ║\n";
    cout << "  ╚═══════════════════════════════════════════╝\n\n";
    
    SetColor(14); // Màu vàng
    cout << "  ┌─────────────────────────────────────────┐\n";
    cout << "  │         TUTORIAL                  │\n";
    cout << "  ├─────────────────────────────────────────┤\n";
    SetColor(7);  // Màu trắng
    cout << "  │  W, A, S, D  - MOVEMENT          │\n";
    cout << "  │  X           - COLLAPSE game               │\n";
    SetColor(14);
    cout << "  └─────────────────────────────────────────┘\n\n";
    
    SetColor(13); // Màu hồng
    cout << "  ★HIGHEST SCORE: " << highScore << "\n\n";
    
    SetColor(10);
    cout << "  ► PRESS ANY KEY TO PLAY...\n";
    SetColor(7);
    
    _getch();
}
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width/2;
	y = height/2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	nTail = 0;
	HideCursor();
}
void Draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
	
	// Vẽ tiêu đề
	SetColor(11);
	cout << "  ╔══════════════════════════════════╗\n";
	cout << "  ║   ";
	SetColor(10);
	cout << "🐍  SNAKE GAME -PAL  🐍";
	SetColor(11);
	cout << "   ║\n";
	cout << "  ╚══════════════════════════════════╝\n\n";
	
	// Vẽ viền trên
	SetColor(14); // Màu vàng cho viền
	cout << "  ";
	for (int i = 0; i < width+2; i++)
		cout << "═";
	cout << endl;
	
	// Vẽ game board
	for (int i = 0; i < height; i++){
		cout << "  ";
		for (int j = 0; j < width; j++ ){
			if (j == 0) {
				SetColor(14);
				cout << "║";
			}
			
			// Vẽ đầu rắn
			if (i == y && j == x) {
				SetColor(10); // Màu xanh lá cho đầu rắn
				cout << "●";
			}
			// Vẽ quả
			else if (i == fruitY && j == fruitX) {
				SetColor(12); // Màu đỏ cho quả
				cout << "★";
			}
			else {
				bool print = false;
				// Vẽ thân rắn
				for (int k = 0; k < nTail; k++){
					if (tailX[k] == j && tailY[k] == i) {
						SetColor(2); // Màu xanh đậm cho thân
						cout << "○";
						print = true;
						break;
					}
				}
				if (!print)
					cout << " ";
			}
				
			if (j == width - 1) {
				SetColor(14);
				cout << "║";
			}
		}
		cout << endl;
	}
	
	// Vẽ viền dưới
	SetColor(14);
	cout << "  ";
	for (int i = 0; i < width+2; i++)
		cout << "═";
	cout << endl;
	
	// Hiển thị điểm
	SetColor(13); // Màu hồng
	cout << "  ► Điểm: ";
	SetColor(15); // Màu trắng sáng
	cout << score;
	
	SetColor(13);
	cout << "  │  Cao nhất: ";
	SetColor(15);
	cout << highScore;
	
	SetColor(13);
	cout << "  │  Độ dài: ";
	SetColor(15);
	cout << nTail + 1;
	
	SetColor(8); // Màu xám
	cout << "  │  (X = Thoát)";
	cout << "   " << endl; // Thêm khoảng trắng để xóa ký tự cũ
	SetColor(7); // Reset màu
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a' :
			dir = LEFT;	
			break;
		case 'd' :
			dir = RIGHT;
			break;
		case 'w' :
			dir = UP;
			break;
		case 's' :
			dir = DOWN;
			break;
		case 'x' :
			gameOver = true;
		break;
		}
	}	
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0]= x;
	tailY[0]= y;
	for(int i=1; i <nTail; i++){
		prev2X = tailX[i];	
		prev2Y = tailY[i];
		tailX[i]= prevX;
		tailY[i]=prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	switch (dir)
	{
		case LEFT :
			x--;
			break;
		case RIGHT :
			x++;
			break;
		case UP :
			y--;
			break;
		case DOWN :
			y++;
			break;
		default :
			break;
	}
	
	// Rắn đi xuyên tường (wrap around)
	if( x >= width) x = 0; 
	else if( x < 0) x = width - 1;
	if( y >= height) y = 0; 
	else if( y < 0) y = height - 1;
	
	// Kiểm tra va chạm với thân
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	
	// Kiểm tra ăn quả
	if (x == fruitX && y == fruitY){
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
		
		// Hiệu ứng âm thanh khi ăn quả
		Beep(800, 50);
	}
}
int main(){
	srand(time(0));
	
	while(true) {
		ShowMenu();
		Setup();
		
		while (!gameOver){
			Draw();
			Input();
			Logic();
			int delay = (50 > 200 - score) ? 50 : (200 - score); 
			this_thread::sleep_for(chrono::milliseconds(delay));
		}
		
		// Game Over screen
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
		system("cls");
		SetColor(12); // Màu đỏ
		cout << "\n\n";
		cout << "  ╔═══════════════════════════════════╗\n";
		cout << "  ║                                   ║\n";
		cout << "  ║        ☠  GAME OVER!  ☠          ║\n";
		cout << "  ║                                   ║\n";
		cout << "  ╚═══════════════════════════════════╝\n\n";
		
		SetColor(14);
		cout << "  YOUR SCORE: ";
		SetColor(15);
		cout << score << endl;
		
		// Cập nhật điểm cao
		if (score > highScore) {
			highScore = score;
			SetColor(10);
			cout << "\n  🎉 CONGRATULATION 🎉\n";
			SetColor(13);
			cout << "  NEW HIGHSCORE: " << highScore << endl;
			
			// Hiệu ứng âm thanh phá kỷ lục
			for(int i = 0; i < 5; i++) {
				Beep(500 + i*100, 100);
			}
		}
		
		SetColor(11);
		cout << "\n PRESS ANY KEY TO PLAY AGAIN...\n";
		SetColor(8);
		cout << " X TO ESCAPE\n";
		SetColor(7);
		
		char choice = _getch();
		if (choice == 'x' || choice == 'X') {
			SetColor(10);
			cout << "\n TKS FOR PLAYING MY GAME SEE YA! 👋\n\n";
			SetColor(7);
			break;
		}
	}
	
	return 0;
}
	
	
