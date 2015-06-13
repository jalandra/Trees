#include <iostream>
#include<queue>

using namespace std;

template<class T>
class Trees{
	private:
		struct node{
				T data;
				node *left;
				node *right;
				node(T data);
		};
		node *m_root; //node of tree
		void deleteTree(node **root); //to delete the tree
		node* insertNode(node *root,T data);
		void printTreeInorder(node *root);
		void printLevelOrder(node *root);
		T getMinValueItr(node *root);
		T getMinValueRec(node *root);
		T getMaxValueItr(node *root);
		T getMaxValueRec(node *root);
	public:
		Trees(T data);
		~Trees();
		void insertNode(T data);
		void printTree(void);
		T getMinValue(void);
		T getMaxValue(void);
};

/*constructor for inner class*/
template<class T>
Trees<T>::node::node(T data):left(NULL),right(NULL){
	this->data = data;
}
/* Constructor*/
template<class T>
Trees<T>::Trees(T data){
	try{
		m_root = new node(data);
	}catch (std::bad_alloc& ba){
		cerr << "bad_alloc caught: " << ba.what() << '\n';
	}
}

/*Destructor*/
template<class T>
Trees<T>::~Trees(){
	//deleteTree(&m_root);
}
 
/*member function to delete node*/
template<class T>
void Trees<T>::deleteTree(node **root){
	deleteTree(&((*root)->left));
	deleteTree(&((*root)->right));
	cout<<"deleting node: "<<(*root)->data<<endl;
	delete *root;
	*root = NULL;
}

/*insert node into tree*/\
template<class T>
void Trees<T>::insertNode(T data){
	m_root = insertNode(m_root,data);
}

/*insert a new node*/
template<class T>
typename Trees<T>::node* Trees<T>::insertNode(node *root, T data){
	if(!root){
		root = new node(data);
		return root;
	}
	if(data < root->data)
		root->left = insertNode(root->left,data);
	else
		root->right = insertNode(root->right,data);
	
	return root;
}

/*print Tree*/
template<class T>
void Trees<T>::printTree(void){
	//printTreeInorder(m_root);
	printLevelOrder(m_root);

}

template<class T>
void Trees<T>::printTreeInorder(node *root){
	if(!root)
		return;
	printTreeInorder(root->left);
	cout<<root->data<<" ";
	printTreeInorder(root->right);
}

template<class T>
void Trees<T>::printLevelOrder(node *root){
	queue<node> treeQueue;
	treeQueue.push(*root);
	node *dummyNode = new node(-1);
	treeQueue.push(*dummyNode);
	while(!treeQueue.empty()){
		node temp = static_cast<node>(treeQueue.front());
		treeQueue.pop();
		if(!treeQueue.empty()){
				if(temp.data != -1){
				cout<<temp.data<<" ";
				if(temp.left)
					treeQueue.push(*(temp.left));
				if(temp.right)
					treeQueue.push(*(temp.right));
			} else{
				treeQueue.push(*dummyNode);
				cout<<endl;
			}
		}
	}
	
}

//find Min Value
template<class T>
T Trees<T>::getMinValue(void){
	if(m_root != NULL)
		//return getMinValueItr(m_root);
		return getMinValueRec(m_root);
}

template<class T>
T Trees<T>::getMinValueItr(node *root){
	while(root->left != NULL) {
		root = root->left;
	}
	return root->data;
}

template<class T>
T Trees<T>::getMinValueRec(node *root){
	if(root->left != NULL)
		return getMinValueRec(root->left);
	else
		return root->data;
}

//find Max Value
template<class T>
T Trees<T>::getMaxValue(void){
	if(m_root != NULL)
		//return getMinValueItr(m_root);
		return getMaxValueRec(m_root);
}

template<class T>
T Trees<T>::getMaxValueItr(node *root){
	while(root->right != NULL) {
		root = root->right;
	}
	return root->data;
}

template<class T>
T Trees<T>::getMaxValueRec(node *root){
	if(root->right != NULL)
		return getMaxValueRec(root->right);
	else
		return root->data;
}

int main(int argc, char **argv)
{
	Trees<int> tree(2);
	tree.insertNode(4);
	tree.insertNode(5);
	tree.insertNode(10);
	tree.insertNode(9);
	tree.insertNode(7);
	tree.insertNode(1);
	tree.insertNode(3);
	tree.insertNode(6);
	tree.printTree();
	cout<<endl;
	cout<<tree.getMinValue()<<endl;
	cout<<tree.getMaxValue()<<endl;
	return 0;
}
