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
	void insertInternal(const data_type& value, Node* temp, Node* hijo){
		if(temp->tam<B){  
			int i=0;
			for(;value>temp->clave[i] && i<temp->tam;i++);
			for(int j=temp->tam;j>i; j--){ 				
				temp->clave[j]=temp->clave[j-1]; 
			}
			for(int j=temp->tam+1;j>i+1; j--){ 
				temp->ptr[j]=temp->ptr[j-1]; 
			} 
			temp->clave[i]=value; 
			temp->tam++; 
			temp->ptr[i+1]=hijo; 
		}
		else{ 	
			Node* newInternal=new Node; 
			int virtualclave[B+1]; 
			Node* virtualPtr[B+2]; 
			for(int i=0; i<B; i++){ 
				virtualclave[i]=temp->clave[i]; 
			} 
			for(int i=0; i<B+1; i++){ 
				virtualPtr[i]=temp->ptr[i]; 
			} 
			int i=0, j;
			while(value>virtualclave[i] && i<B){ 
				i++; 
			} 
			for(int j=B+1;j>i; j--){ 
				virtualclave[j]=virtualclave[j-1]; 
			} 
			virtualclave[i]=value; 
			for(int j=B+2;j>i+1;j--){ 
				virtualPtr[j]=virtualPtr[j-1]; 
			} 
			virtualPtr[i+1]=hijo; 
			newInternal->hoja=false; 
			temp->tam=(B+1)/2;
			newInternal->tam=B-(B+1)/2; 
			for(i=0, j=temp->tam+1; i<newInternal->tam; i++, j++){ 
				newInternal->clave[i]=virtualclave[j]; 
			} 
			for(i=0, j=temp->tam+1; i<newInternal->tam+1; i++, j++){ 
				newInternal->ptr[i]=virtualPtr[j]; 
			} 
			if(temp==raiz){ 
				Node* newraiz=new Node(temp, newInternal);
				newraiz->clave[0]=temp->clave[temp->tam];
				raiz=newraiz; 
			}
			else{
				insertInternal(temp->clave[temp->tam], busquedaUp(raiz, temp), newInternal); 
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
	void insert(const data_type& value){ 
	if(raiz==NULL){ 
		raiz=new Node; 
		raiz->clave[0]=value; 
		raiz->hoja=true; 
		raiz->tam=1; 
	} 
	else{ 
		Node* temp=raiz; 
		Node* padre; 
		itebusqueda(value, temp);
		if(temp->tam<B){ 
			int i=0; 
			while(value>temp->clave[i] && i<temp->tam){ 
				i++; 
			} 
			for(int j=temp->tam;j>i; j--){ 
				temp->clave[j]=temp->clave[j-1]; 
			} 
			
			temp->clave[i]=value; 
			temp->tam++; 
			temp->ptr[temp->tam]=temp->ptr[temp->tam-1]; 
			temp->ptr[temp->tam-1]=NULL; 
		} 
		else{ 
			Node* newLeaf=new Node; 
			int virtualNode[B+1]; 
			for(int i=0; i<B; i++){ 
				virtualNode[i]=temp->clave[i]; 
			} 
			int i=0, j; 
			while(value>virtualNode[i] && i<B){ 
				i++; 
			} 
			for(int j=B+1;j>i;j--){ 
				virtualNode[j]=virtualNode[j-1]; 
			} 
			virtualNode[i]=value; 
			newLeaf->hoja=true; 
			temp->tam=(B+1)/2; 
			newLeaf->tam=B+1-(B+1)/2; 
			temp->ptr[temp->tam]=newLeaf; 
			newLeaf->ptr[newLeaf->tam]=temp->ptr[B]; 
			temp->ptr[B]=NULL; 
			for(i=0; i<temp->tam; i++){ 
				temp->clave[i]=virtualNode[i]; 
			}
			for(i=0, j=temp->tam; i<newLeaf->tam; i++, j++){ 
				newLeaf->clave[i]=virtualNode[j]; 
			} 
			if(temp==raiz){ 
				Node* newraiz=new Node;
				newraiz->clave[0]=newLeaf->clave[0];
				newraiz->ptr[0]=temp; 
				newraiz->ptr[1]=newLeaf; 
				newraiz->hoja=false; 
				newraiz->tam=1; 
				raiz=newraiz;
			}
			else{ 
				insertInternal(newLeaf->clave[0], padre, newLeaf); 
			} 
		} 
	} 
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
