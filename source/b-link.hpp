// Copyright
#ifndef SOURCE_B_LINK_HPP_
#define SOURCE_B_LINK_HPP_

#include <utility>

namespace EDA {
namespace Concurrent {

template <std::size_t B, typename Type>
class BLinkTree {
  struct Node{
		typedef Type data_type;
		bool hoja; 
		data_type *clave, tam; 
		Node** ptr; 
		Node(){
			clave=new data_type[B]; 
			ptr=new Node*[B+1]; 
		}
		Node(Node* &temp, Node* &Nuevo){
			this->ptr[0]=temp;
			this->ptr[1]=Nuevo;
			this->hoja=false;
			this->tam=1;
		}
	}; 
	typedef Type data_type;
	void itebusqueda(const data_type& value, Node* &temp) const{
		while(temp->hoja==false){
			for(int i=0; i<temp->tam; i++){ 
				if(value<temp->clave[i]){ 
					temp=temp->ptr[i]; 
					break; 
				} 
				if(i==temp->tam-1){ 
					temp=temp->ptr[i+1]; 
					break; 
				} 
			} 
		} 
	}

	Node* busquedaUp(Node* temp, Node* hijo){
		Node* padre;
		if(temp->hoja||(temp->ptr[0])->hoja){ 
			return nullptr; 
		} 
		for(int i=0;i<temp->tam+1; i++){ 
			if(temp->ptr[i]==hijo){ 
				padre=temp; 
				return padre; 
			}
			else{ 
				padre=busquedaUp(temp->ptr[i], hijo); 
				if(padre!=nullptr) 
					return padre; 
			} 
		}
		return padre; 
	}
 public:
  
  Node* raiz;
  BLinkTree() {
    this->raiz=nullptr;
  }
/*
  ~BLinkTree() {}

  std::size_t size() const {}
*/
  bool empty() const {
		if(raiz==nullptr){
			return true;
		}
		else{ return false; }
	}
  bool search(const data_type& value) const {
		Node* temp=raiz;
		itebusqueda(value, temp);
			for(auto i=0;i<temp->tam;i++){ 
				if(temp->clave[i]==value){ 
					std::cout<<"Manin"<<std::endl;
					return true; 
				} 
			}
			std::cout<<"NO"<<std::endl;
			return false;
  }
  void setVariable(Node* &pNode, int uValor, int uIte, Node* prevNode, Node* nextNode) {
    pNode->key.insert(pNode->key.begin()+uIte, uValor);
    pNode->ptr[pNode->key.size()] = nextNode;
    pNode->ptr[pNode->key.size()-1] = prevNode;
  }

 
};//not
/*
  void remove(const data_type& value) {}

 private:
  data_type* data_;
};
*/
 
	 }//	 namespace Concurrent
  }//namespace EDA

#endif  // SOURCE_B_LINK_HPP_
