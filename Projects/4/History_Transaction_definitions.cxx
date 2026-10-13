#include <cassert>
#include <iomanip>
#include <iostream>
#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"
#define N(Z) set_next(Z)
#define R get_next()
#define _ p_head
#define A T*t=_
#define M month
#define Y year
#define D day
#define G get_trans_type()
#define B get_amount()
#define C get_shares()
#define E(Z) set_acb(Z)
#define F get_acb()
#define I get_acb_per_share()
#define J get_share_balance()
using namespace ece150;typedef History H;typedef Transaction T;typedef double db;T::Transaction(std::string a,uint b,uint c,uint d,bool e,uint f,db g):symbol{a},D{b},M{c},Y{d},trans_type{e?"Buy":"Sell"},shares{f},amount{g},p_next{NULL}{trans_id=assigned_trans_id++,acb=0,acb_per_share=0,share_balance=0,cgl=0;}T::~Transaction(){}bool T::operator<(const T&o){return Y!=o.Y?Y<o.Y:M!=o.M?M<o.M:D!=o.D?D<o.D:trans_id<o.trans_id;}H::History(){_=NULL;}H::~H(){while(_){A->R;delete _;_=t;}}void H::insert(T*n){if(_){A,*p=NULL;while(t)p=t,t=t->R;p->N(n);}else _=n;}void H::read_history(){open_file();while(next_trans_entry())insert(new T(get_trans_symbol(),get_trans_day(),get_trans_month(),get_trans_year(),G,get_trans_shares(),get_trans_amount()));close_file();}void H::print(){std::cout<<"========== BEGIN TRANSACTION HISTORY ============\n";A;while(t)t->print(),t=t->R;std::cout<<"========== END TRANSACTION HISTORY ============\n";}T*m(T*l,T*r){if(!l)return r;if(!r)return l;T*t,*h;if(*l<*r)t=l,l=l->R;else t=r,r=r->R;h=t;while(l&&r){if(*l<*r)t->N(l),l=l->R;else t->N(r),r=r->R;t=t->R;}return l?t->N(l):t->N(r),h;}T*S(T*h){if(!h||!h->R)return h;T*s=h,*f=h->R;while(f&&f->R)s=s->R,f=f->R->R;return f=s->R,s->N(NULL),m(S(h),S(f));}void H::sort_by_date(){_=S(_);}void u(T*_,T*p){if(_->G)_->E((p?p->F:0)+_->B),_->set_share_balance((p?p->J:0)+_->C);else _->E(p->F-_->C*p->I),_->set_share_balance(p->J-_->C),_->set_cgl(_->B-p->I*_->C);}void H::update_acb_cgl(){A,*p=NULL;while(t)::u(t, p),t->set_acb_per_share(t->F/t->J),p=t,t=t->R;}db H::compute_cgl(uint y){A,*p=NULL;db cgl=0;while(t)::u(t,p),cgl+=t->get_year()==y?t->get_cgl():0,p=t,t=t->R;return cgl;}

// GIVEN
Transaction *H::get_p_head() { return p_head; }
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if( get_trans_type() ) {
   	std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}
