#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

#include "b-link.hpp"

std::size_t NUMBER_THREADS = 4;

const std::size_t NUMBER_OPERATIONS = 100000;

int MIN_VALUE = 1;
int MAX_VALUE = 15000;

std::random_device rd;

class TreeSearcher {
public:
	TreeSearcher(unsigned int id, EDA::Concurrent::BLinkTree<3, int> *b_link)
		: id_(id), b_link_(b_link) {}
	
	void operator()() {
		std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
		for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
			//std::cout << distribution(rd) << "\n";
			 b_link_->search(distribution(rd));
		}
	}
	
private:
		unsigned int id_;
		EDA::Concurrent::BLinkTree<3, int> *b_link_;
};

void sequential_insert(EDA::Concurrent::BLinkTree<3, int> *b_link) {
	std::uniform_int_distribution<int> distribution(MIN_VALUE, MAX_VALUE);
	for (std::size_t i = 0; i < NUMBER_OPERATIONS; ++i) {
		//std::cout << distribution(rd) << "\n";
		 b_link->insert(distribution(rd));
	}
}

void run_test() {
	EDA::Concurrent::BLinkTree<3, int> b_link;
	
	sequential_insert(&b_link);
	
	std::thread *threads = new std::thread[NUMBER_THREADS];
	
	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		threads[i] = std::thread(TreeSearcher(i, &b_link));
	}
	for (std::size_t i = 0; i < NUMBER_THREADS; ++i) {
		threads[i].join();
		std::cout<<"HA, Paintbrush AIDS"<<std::endl;
	}
}

int main() {
//	run_test();
	EDA::Concurrent::BLinkTree<3, int> arbolon;
	arbolon.insert(8);
	arbolon.insert(9);
	arbolon.insert(10);
	arbolon.insert(6);
	arbolon.search(10);
	arbolon.search(9);
	arbolon.search(6);
	return 0;
}
