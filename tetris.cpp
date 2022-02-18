#include <iostream>
#include <windows.h>
#include <conio.h>

class Block {
  friend class Map;
  protected :
    int block_i = 9;
    int block_j = 9;
    int shape[9][9]=
    {
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0}
    };
  public :
    void show_block(){
      for(int i=0; i<9; i++){
        for (int j=0; j<9; j++){
          if(shape[i][j]){std::cout<<"o";}
          else{std::cout<<"-";}
        }
        std::cout<<std::endl;
      }
    }
    void rotate_block(); //회전함수
};

class Block_1 : public Block { // ㅡ 모양 블럭 ㅋㅋ
  public:
    Block_1(){
      shape[4][2] = 1;
      shape[4][3] = 1;
      shape[4][4] = 1;
      shape[4][5] = 1;
      shape[4][6] = 1;
    }
};
class Block_2 : public Block { //ㄱㄴ(대칭)
  public:
    Block_2(){
      shape[4][4] = 1;
      shape[4][5] = 1;
      shape[3][5] = 1;
      shape[3][6] = 1;
    }
};
class Block_3 : public Block { //ㅁ자 블럭
  public:
    Block_3(){
      shape[4][4] = 1;
      shape[4][5] = 1;
      shape[3][4] = 1;
      shape[3][5] = 1;
    }
};
class Block_4 : public Block { // +자 블럭
  public:
    Block_4(){
      shape[4][4] = 1;
      shape[3][4] = 1;
      shape[4][5] = 1;
      shape[4][3] = 1;
      shape[5][4] = 1;
    }
};

class Block_5 : public Block { //ㄴ자 블럭
  public:
    Block_5(){
      shape[4][4] = 1;
      shape[4][3] = 1;
      shape[4][5] = 1;
      shape[3][3] = 1;
    }
};

class Block_6 : public Block { //ㄴ자 역전블럭
  public:
    Block_6(){
      shape[4][4] = 1;
      shape[4][3] = 1;
      shape[4][5] = 1;
      shape[3][5] = 1;
    } 
};

class Block_7 : public Block {
  public:
    Block_7(){
      shape[4][4] = 1;
      shape[4][3] = 1;
      shape[5][4] = 1;
      shape[5][5] = 1;
    }
  
};

class Map {
  bool block_check = true;
  const int map_i = 15;
  const int map_j = 15;
  int map[15][15] = //동적할당으로 2차원배열 받는것 아직구현 안함
  {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };
  public:
    void block_setter(Block & block,int x, int y); // 새로운블럭 놓는 함수, i,j는 블럭 생성 시작 좌표
    void clear_block();  // 블럭 지우는 함수
    void block_down(Block & block, int x, int y); //블럭내리는 함수
    void block_remove(Block & block, int x, int y);
    void show_map();

    void block_move(Block & block, int x, int y, char input);

    bool letscheck_block(Block & block, int x, int y);

    void set_block_check(bool change){block_check = change;}
    bool get_block_check(){return block_check;};
};

void Map::block_remove(Block & block, int x, int y){
  for (int i=0; i<block.block_i; i++){
    for (int j=0; j<block.block_j; j++) {
      if(block.shape[i][j]==1){
        map[x+i][y+j] = 0;
      }
    }
  }
}

void Map::block_move(Block & block, int x, int y, char input){
  if (input == 'a'){
    block_remove(block, x, y);
    block_setter(block, x, y-1);
  }
  else if (input == 'd'){
    block_remove(block, x, y);
    block_setter(block, x, y+1);
  }
}

void Map::block_down(Block & block,int x, int y){
  block_remove(block,x,y);
  if(letscheck_block(block, x, y)){block_setter(block, x+1, y); }
  else{
    block_setter(block,x,y);
  }
}

bool Map::letscheck_block(Block & block, int x, int y){
  //상황 1. 바닥에 닿는경우
  //상황 2. 다른 블럭에 닿는경우
  for (int i=0; i< block.block_i; i++){
    for (int j=0; j<block.block_j; j++){
      if(x + i >= map_i && block.shape[i][j]==1){std::cout<<"1"<<std::endl;return false;} //상황1 구현
      if(y + j >= map_j && block.shape[i][j]==1){std::cout<<"2"<<std::endl;return false;}
      if(map[x+i][y+j]==1 && block.shape[i][j]==1){std::cout<<"3"<<std::endl;return false;}//상황2 구현
    }
  }
  return true;
}

void Map::block_setter(Block & block, int x, int y){ //y에 3이들어가면 오류가 생김 Block_1의 경우 2~6까지 y기준 5개의 1존재
  bool is_block_on = true;
  
  for (int i=0; i<block.block_i; i++){
    for (int j=0; j<block.block_j; j++){
      if(((x+i >= map_i) || (y+j >= map_j) )&& block.shape[i][j]==1){is_block_on = false;}
      if((x+i > map_i) || (y+j > map_j)){continue;}
      if(map[x+i][y+j] == 1 && block.shape[i][j]) {std::cout<<"??"<<std::endl; is_block_on = false;} // 애초에 맵에 놓으려는 곳에 블럭이 있을경우 못놓는다
    }
  }
  if(is_block_on){
    for(int i=0; i<block.block_i; i++){
      for(int j=0; j<block.block_j; j++){
        if((x+i > map_i) || (y+j > map_j)){continue;}
        if(block.shape[i][j]==1){map[i+x][j+y] = block.shape[i][j];}
         //빈공간에 블럭설치
      }
    }
  }
  if(!is_block_on){block_check = false;}
}
void Map::clear_block(){
  int * clear_list = new int[map_i];
  int total_break = 0;

  for (int i=0; i<map_i; i++){
    int sum=0;

    for (int j=0; j<map_j; j++){
      
      if (map[i][j] == 1) sum += 1;
    }
    if(sum==map_j){clear_list[total_break] = i; total_break++;}
  }

  for(int i=0; i<total_break; i++){
    for(int j=0; j<map_j; j++){
      map[clear_list[i]][j] = 0;
      std::cout<<i<<" i break block"<<std::endl;
    }
  }
}

void Map::show_map(){
  std::cout<<"**********"<<std::endl;
  for (int i=0; i<map_i; i++){
    for (int j=0; j<map_j; j++){
      if(map[i][j] == 1){std::cout<<"o";} //블럭
      else{std::cout<<"-";}; //빈공간
    }
    std::cout<<std::endl;
  }
  std::cout<<"**********"<<std::endl;
}

void Block::rotate_block(){//종결
  int temp[9][9];
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
      temp[i][j] = shape[9-1-j][i];
    }
  }
  for (int i=0; i<9; i++){
    for (int j=0; j<9; j++){
      shape[i][j] = temp[i][j];
    }
  }
}


class Game{
  Block * block_list = new Block[7];
  int * random_list = new int[10];



  public:
    Game(){

    }

    int get_random_list(int i){
      return random_list[i];
    }

    Block get_block_list(int i){
      return block_list[i];
    }

    void one_block(Block & block, Map & map){
      int q = -3; //떨어지기 시작하는 위치
      int r = 2;
      map.block_setter(block,q,r);
      char c = 0;
      map.set_block_check(true);
      while(c!=13 && map.get_block_check()) {
        if(_kbhit()){
          c = _getch();
          if(c == 'a' || c == 'd'){map.block_move(block,q,r,c);}
          if(c=='a'){r--;}
          else if(c=='d'){r++;}

          else if(c=='w'){
            map.block_remove(block,q,r);
            block.rotate_block();
            map.block_setter(block,q,r);
          }
        }
        //입력값 input
        map.block_remove(block,q,r);
        map.block_setter(block,q+1,r);
        q++;
        Sleep(800);
        if(map.get_block_check()){map.show_map();}
        
      }
      map.block_setter(block,q-1,r);
    }
};


int main(){

  int random_list[10];
  random_list[0] = 0;
  random_list[1] = 0;
  random_list[2] = 0;
  random_list[3] = 3;
  random_list[4] = 3;
  random_list[5] = 4;
  random_list[6] = 1;
  random_list[7] = 2;
  random_list[8] = 7;
  random_list[9] = 0;
  Block_1 block_1;
  Block_2 block_2;
  Block_3 block_3;
  Block_4 block_4;
  Block_5 block_5;
  Block_6 block_6;
  Block_7 block_7;

  Block block_list[7];
  block_list[0] = (block_1);
  block_list[1] = block_2;
  block_list[2] = block_3;
  block_list[3] = block_4;
  block_list[4] = block_5;
  block_list[5] = block_6;
  block_list[6] = block_7;
  
  Map map;


  Game game_1;
  for (int i=0; i<5; i++){
    game_1.one_block(block_list[random_list[i]],map);
    map.clear_block();
  }


  return 0;
}



