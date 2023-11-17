#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
// typedef pair<int,int> pii;
typedef long long ll;
#define MAX_N 100001

int n,l,q;

int board[42][42];
int knight_board[42][42];

int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};

int total_damage;

struct Knight{
   int r,c,h,w,k;
   bool alive;
};

Knight knights[32];

void make_knightboard(){
   for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++) knight_board[i][j]=0;
   }

   for(int ii=1;ii<=l;ii++){
      Knight k=knights[ii];
      if(!k.alive) continue;
      for(int i=0;i<k.h;i++){
         for(int j=0;j<k.w;j++){
            knight_board[k.r+i][k.c+j]=ii;
         }
      }
   }  
}

bool visited[32];

bool is_inrange(int x,int y){
   if(1<=x && x<=n && 1<=y && y<=n) return true;
   else return false;
}

void move_damage(int index, int dir){
   for(int ii=1;ii<=l;ii++){
      if(!visited[ii]) continue;
      Knight k=knights[ii];
      if(!k.alive) continue;

      int getDamage=0;
      k.r+=dx[dir];
      k.c+=dy[dir];
      for(int i=0;i<k.h;i++){
         for(int j=0;j<k.w;j++){
            int ni=k.r+i, nj = k.c+j;
            if(board[ni][nj]==1) getDamage++;
         }
      }
      if(getDamage>=k.k){
         total_damage+=k.k;
         k.k=0;
         k.alive=false;
      }
      else{
         total_damage+=getDamage;
         k.k-=total_damage;
      }
      knights[ii]=k;
   }
}

bool movable(int index, int dir){
   Knight k = knights[index];
   for(int i=0;i<k.h;i++){
      for(int j=0;j<k.w;j++){
         int ii=k.r+i+dx[dir], jj = k.c+j+dy[dir];
         if(!is_inrange(ii,jj) || board[ii][jj]==2){
            return false;
         }
         if(knight_board[ii][jj]!=index && knight_board[ii][jj]>0){
            int idx=knight_board[ii][jj];
            if(!visited[idx]){
               visited[idx]=true;
               if(!movable(idx, dir)){
                  return false;
               }
            }
         }
      }
   }
   return true;
}

void move_knight(int index, int dir){
   memset(visited, false, sizeof(visited));
   visited[index]=true;
   if(movable(index, dir)){
      move_damage(index,dir);
   }
   else return;
}

int main(){
   ios::sync_with_stdio(false);
   cin.tie(NULL); cout.tie(NULL);

   cin >> n >> l >> q;

   for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++) cin >> board[i][j];
   }

   for(int i=1;i<=l;i++){
      int r1,c1,h1,w1,k1; cin >> r1 >> c1 >> h1 >> w1 >> k1;
      Knight input_knight;
      input_knight.r=r1;
      input_knight.c=c1;
      input_knight.h=h1;
      input_knight.w=w1;
      input_knight.k=k1;
      input_knight.alive=true;
      knights[i]=input_knight;
   }

   make_knightboard();
   for(int i=0;i<q;i++){
      int cmd1, cmd2; cin >> cmd1 >> cmd2;

      move_knight(cmd1, cmd2);
      make_knightboard();
   }

   cout << total_damage << "\n";
}