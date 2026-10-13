#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////

// Constructor

Transaction::Transaction( std::string ticker_symbol, unsigned int day_date, unsigned int month_date,
		unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount ) : 
	symbol{ticker_symbol}, day{day_date}, month{month_date}, year{year_date}, trans_type{buy_sell_trans ? "Buy" : "Sell"},
	shares{number_shares}, amount{trans_amount}, p_next{nullptr} {trans_id = assigned_trans_id++, acb = 0, acb_per_share = 0, share_balance = 0, cgl = 0;}

// Destructor

Transaction::~Transaction(){}

// Overloaded < operator.

bool Transaction::operator<(const Transaction &other) {
	return year != other.year ? year < other.year : month != other.month ? month < other.month : day != other.day ? day < other.day : trans_id < other.trans_id;
}

////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor

History::History() : p_head{nullptr} {}

// Destructor

History::~History() {
	while (p_head) {
		Transaction *p_temp = p_head;
		p_head = p_head->get_next();
		delete p_temp;
	}
}

// insert(...): Insert Transaction into linked list.

void History::insert(Transaction *new_trans) {
	if (p_head) {
		Transaction *p_temp = p_head, *p_prev = nullptr;
		while (p_temp) {
			p_prev = p_temp;
			p_temp = p_temp->get_next();
		}
		p_prev->set_next(new_trans);
	} else {
		p_head = new_trans;
	}
}

// read_history(...): Read the Transaction history from file.

void History::read_history() {
	ece150::open_file();
	while (ece150::next_trans_entry()) {
		insert(new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(),
					ece150::get_trans_month(), ece150::get_trans_year(),
					ece150::get_trans_type(), ece150::get_trans_shares(),
					ece150::get_trans_amount()));
	}
	ece150::close_file();
}

// print() Print the Transaction history.

void History::print() {
	std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
	Transaction *p_temp = p_head;
	while (p_temp) {
		p_temp->print();
		p_temp = p_temp->get_next();
	}
	std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
}

// sort_by_date(): Sort the linked list by trade date.

Transaction *merge(Transaction *l, Transaction *r) {
	if (!l) {
		return r;
	}

	if (!r) {
		return l;
	}

	Transaction *temp, *head;
	if (*l < *r) {
		temp = l;
		l = l->get_next();
	} else {
		temp = r;
		r = r->get_next();
	}

	head = temp;
	while (l && r) {
		if (*l < *r) {
			temp->set_next(l);
			l = l->get_next();
		} else {
			temp->set_next(r);
			r = r->get_next();
		}
		temp = temp->get_next();
	}
	
	if (l) {
		temp->set_next(l);
	}
	if (r) {
		temp->set_next(r);
	}
	return head;
}

Transaction *sort(Transaction *head) {
	if (!head || !head->get_next()) {
		return head;
	}

	Transaction *p_slow = head, *p_fast = head->get_next();
	while (p_fast && p_fast->get_next()) {
		p_slow = p_slow->get_next();
		p_fast = p_fast->get_next()->get_next();
	}
	p_fast = p_slow->get_next();
	p_slow->set_next(nullptr);
	
	return merge(sort(head), sort(p_fast));
}

void History::sort_by_date() {p_head = sort(p_head);}

void update_acb_cgl(Transaction *point, Transaction *prev) {
	if (prev) {
		if (point->get_trans_type()) {
			point->set_acb(prev->get_acb() + point->get_amount());
			point->set_share_balance(prev->get_share_balance() + point->get_shares());
		} else {
			point->set_acb(prev->get_acb() - point->get_shares()*prev->get_acb_per_share());
			point->set_share_balance(prev->get_share_balance() - point->get_shares());
			point->set_cgl(point->get_amount() - prev->get_acb_per_share()*point->get_shares());
		}
	} else {
		point->set_acb(point->get_amount());
		point->set_share_balance(point->get_shares());
		point->set_acb_per_share(point->get_acb() / point->get_share_balance());
	}
}
// update_acb_cgl(): Updates the ACB and CGL values.

void History::update_acb_cgl() {
	Transaction *p_temp = p_head, *p_prev = nullptr;
	while (p_temp) {
		::update_acb_cgl(p_temp, p_prev);
		p_temp->set_acb_per_share(p_temp->get_acb() / p_temp->get_share_balance());
		p_prev = p_temp;
		p_temp = p_temp->get_next();
	}
}

// compute_cgl(): )Compute the ACB, and CGL.

double History::compute_cgl(uint year) {
	Transaction *p_temp = p_head, *p_prev = nullptr;
	double cgl = 0;

	while (p_temp) {
		::update_acb_cgl(p_temp, p_prev);
		if (p_temp->get_year() == year) {
			cgl += p_temp->get_cgl();
		}
		p_prev = p_temp;
		p_temp = p_temp->get_next();
	}

	return cgl;
}

// GIVEN
// get_p_head(): Full access to the linked list.

Transaction *History::get_p_head() { return p_head; }

// Member functions to get values.

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

// Member functions to set values.

void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// Print the Transaction.

void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
   	std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}

