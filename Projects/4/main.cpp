#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
  History trans_history{};
  trans_history.read_history();

  std::cout << "[Starting history]:" << std::endl;
  trans_history.print();
  trans_history.sort_by_date();

  std::cout << "[Sorted          ]:" << std::endl;
  trans_history.print();

  std::cout << std::endl;

  trans_history.update_acb_cgl();
  trans_history.print();

  for (int i = 2010; i < 2023; ++i) {
	  std::cout << "[CGL for " << i << "    ]: " << trans_history.compute_cgl(i) << std::endl;
  }

  return 0;
}
#endif
