// Copyright OpenSource
#ifndef SOURCE_B_enlace_HPP_
#define SOURCE_B_enlace_HPP_

#include <utility>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <shared_mutex>
#include <queue>
#include <mutex>

using namespace std;

namespace EDA::Concurrent {
template<std::size_t B, typename Type>
	class BLinkTree {
		struct Node {
		Node(){
			this->hoja=true;
			this->enlace=nullptr;
			//this->ptrs.resize(tam_ptrs);
		}
		bool hoja{};
		vector<Type> data;
		Node *enlace;
		vector<Node *> ptrs;
		};
		mutex mtx;
		BLinkTree::Node* root;
		BLinkTree::Node* nodoAncestro;
		int tam_datos{};
		int tam_ptrs{};
    size_t tam_nodos{};

	public:
		typedef Type data_type;
    shared_mutex mutex;
		BLinkTree(){
			this->tam_datos=B;
			this->tam_ptrs=B+1;
			this->tam_nodos=0;
			this->root=nullptr;
			nodoAncestro=nullptr;
		}
		bool empty() const;
            ///////////////////////////////////////
		bool search(data_type value){
			mtx.lock();
			if(root==nullptr){
				mtx.unlock();
				return false;
			} 
			else {
				BLinkTree::Node *dummy=root;
				while(!dummy->hoja){
					int iwi=upper_bound(dummy->data.begin(), dummy->data.end(), value)-dummy->data.begin();
					dummy=dummy->ptrs[iwi];
				}
				int segundo_iwi=lower_bound(dummy->data.begin(), dummy->data.end(), value)-dummy->data.begin();
				mtx.unlock();
				return !(segundo_iwi==dummy->data.size() || dummy->data[segundo_iwi] != value);
			}
		}
		void insert(data_type value){
			if(!this->root){
				this->root=new BLinkTree::Node;
				//this->root->hoja=true;
				this->root->claves.push_back(value);
				return;
			}
			else{
				Node* dummy=root;
				Node* nodoAncestro=nullptr;
				while(dummy->hoja==0){
				}
			}
		}
		void remove(data_type value);
		bool searchParallel(data_type value, Node **&p){
			mtx.lock();
			ptr=&root;
			if(root==nullptr){
				mtx.unlock();
				return false;
			}
//			queue<BLinkTree::Node*> cola;
//			int idx;
//			cola.push_back(root);
//			while(!cola.empty()){
//				int cont=cola.size();
//				while(cont > 0){
//					BLinkTree::Node* dummy=cola.front();
//					idx=upper_bound(dummy->data.begin(),dummy->data.end(),value)-dummy->data.begin();
//					cola.pop();
//					int i=0;
//		
//						}
//					}
//				}
//			if(ptr){
//				BLinkTree::Node *dummy=root;
//				while(!dummy->hoja){
//					int iwi=upper_bound(dummy->data.begin(),dummy->data.end(),value)-dummy->data.begin();
//					dummy=dummy->ptrs[iwi];
//				}
//				int segundo_iwi=lower_bound(dummy->data.begin(),dummy->data.end(),value)-dummy->data.begin();
//				mtx.unlock();
//				return !(segundo_iwi==dummy->data.size()||dummy->data[segundo_iwi]!=value);
//			}
//			return true;
		}


	};
}
#endif  // SOURCE_B_enlace_HPP_
