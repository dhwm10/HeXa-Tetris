#include <iostream>
#include <windows.h>
#include <conio.h>

/* **********************일지 및 작동법***********************

1. w(회전) 후 같은블록이 나오면 코드가 멈추는 현상이 발생 
=> 클래스의 shape자체를 수정하지 말고 temp에 넣어놨다가 map에 복사 (2월 20일 수정완료후 해결됨)
=> 애초에 복사생성자로 블럭을 수많이 만들어놓고 map에 놓으면 해결될일이었음, 하나의 객체로 복사하고 붙여넣으려다보니까 문제가 발생함

2. 이동키 너무 빨리누르면 버그 발생

3. 왼쪽벽 넘어가면 오른쪽벽에서 나오는 버그발생 (임시 블럭 벽 만들면 해결될듯)



추가할 사항 :
  1. Game class 만들어서 게임 시작, 종료, 목숨 변수 추가
  2. 랜덤함수 구현
  3. 블럭 내려오는 속도 변화 구현

작동법 : 
  a : 왼쪽이동
  d : 오른쪽이동
  w : 회전
*/

class Block {
  friend class Map;
  friend class Block_rotate;
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
    void copy_block(Block & block_copy);
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

//버그 해결 전략1 => temp 만들어서 복사하고 그거를 ㅇㅋ?
void Block::copy_block(Block & block_copy){
  for(int i=0; i<block_i; i++){
    for(int j=0; j<block_j; j++){
      shape[i][j] = block_copy.shape[i][j];
    }
  }
}

class Block_rotate : public Block {
  public:
    Block_rotate(Block & block){
      for(int i=0; i<block_i; i++){
        for(int j=0; j<block_j; j++){
          shape[i][j] = block.shape[i][j];
        }
      }
    }
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
  bool block_check;
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
      if(((x+i >= map_i) || (y+j >= map_j) )&& block.shape[i][j]==1){is_block_on = false; break;}
      if((x+i >= map_i) || (y+j >= map_j)){continue;}
      if(map[x+i][y+j] == 1 && block.shape[i][j]) {is_block_on = false; break;} // 애초에 맵에 놓으려는 곳에 블럭이 있을경우 못놓는다
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
  std::cout<<"***************"<<std::endl;
  for (int i=0; i<map_i; i++){
    for (int j=0; j<map_j; j++){
      if(map[i][j] == 1){std::cout<<"o";} //블럭
      else{std::cout<<"-";}; //빈공간
    }
    std::cout<<std::endl;
  }
  std::cout<<"***************"<<std::endl;
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
    int get_random_list(int i){ //아직 구현 안함
      return random_list[i];
    }

    Block get_block_list(int i){ //아직 구현안함
      return block_list[i];
    }

    void one_block(Block & block, Map & map){
      int q = -3; //떨어지기 시작하는 위치
      int r = 2;
      map.block_setter(block,q,r);
 
      char c;
      //std::cout<<"bug test1"<<std::endl;
      map.set_block_check(true); //버그 원인 <= 이 코드가 실행되려하면 코드가 멈추는 현상 발생
      //std::cout<<"bug test2"<<std::endl;

      Block_rotate temp(block); //원본 저장
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
        
        map.block_remove(block,q,r);
        map.block_setter(block,q+1,r);
        q++;
        Sleep(500);
        if(map.get_block_check()){map.show_map();}
        
      }
      map.block_setter(block,q-1,r);
      map.show_map();
      block.copy_block(temp);
      //block = temp; //다시 복사
    }
};


int main(){

  int random_list[10]; //임시로 랜덤리스트 설정함
  random_list[0] = 0;
  random_list[1] = 4;
  random_list[2] = 7;
  random_list[3] = 0;
  random_list[4] = 4;
  random_list[5] = 7;
  random_list[6] = 0;
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
  block_list[0] = block_1;
  block_list[1] = block_2;
  block_list[2] = block_3;
  block_list[3] = block_4;
  block_list[4] = block_5;
  block_list[5] = block_6;
  block_list[6] = block_7;
  
  Map map;


  Game game_1;
  for (int a=0; a<7; a++){
    game_1.one_block(block_list[random_list[a]],map);
    //std::cout<<"1"<<std::endl;
    map.clear_block();
    //std::cout<<"2"<<std::endl;
    //block_list[random_list[a]].show_block();

  }


  return 0;
}



