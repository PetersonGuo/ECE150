#include "geesespotter_lib.h"
#include <iostream>
#define r(n) return n;
#define X s x
#define Y s y
#define z c*_,X,Y
#define Z I(i,j)
#define I(_i,_j) (_j*x+_i)
#define A(_i,_t) (_[_i]&_t)
#define q (j+d[0])
#define Q (i+d[1])
#define L(_a) for(s i=0;i<x*y;++i)_a
typedef char c;typedef std::size_t s;const int M=0x10,H=0x20,V=0x0F,D[][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};c*create_board(X,Y){char *_{new char[x*y]{}};r(_)}void clean_board(c*_){delete[] _;_=nullptr;}void print_board(z){for(s j=0;j<y;++j){for(s i=0;i<x;++i)std::cout<<(c)(A(Z,M)?'M':A(Z,H)?'*':48+A(Z,V));std::cout<<'\n';}}void hide_board(z){L(_[i]|=H;)}int mark(z,s i,s j){return !A(Z,H)?2:_[Z]^=M,0;}void compute_neighbours(z){for(s j=0;j<y;++j)for(s i=0;i<x;++i)if(A(Z,V)==9)for(auto&d:D)if(Q<x&&q<y&&A(I(Q,q),V)!=9)++_[I(Q,q)];}bool is_game_won(z){L(if(A(i,H)&&A(i,V)!=9)r(0))r(1)}int reveal(z,s i,s j){if(A(Z,M))r(1)else if(!A(Z,H))r(2)_[Z]&=~H;if(A(Z,V)==9)r(9)else if(!A(Z,V))for(auto&d:D)if(Q<x&&q<y&&A(I(Q,q),V)!=9)_[I(Q,q)]&=~H;r(0)}
