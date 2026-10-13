#include <iostream>
#include <climits>
#define L(_,l,f) for(s i=0;i<l;i++)_[i]=f(_[i]);
#define g get_checksum
#define a add_checksum
#define r remove_checksum
#define v verify_checksum
typedef std::size_t s;typedef uint u;u g(u n){u _=0;for(int i=8;n/=10;--i){u j=n%10<<(i&1?0:1);_+=j/10+j%10;}return _*9%10;}u a(u n){return n>99999999?UINT_MAX:n*10+g(n*10);}void a(u _[],s l){L(_,l,a);}bool v(u n){return n>999999999?0:g(n)==n%10;}u r(u n){return v(n)?n/10:UINT_MAX;}void r(u _[],s l){L(_,l,r);}
