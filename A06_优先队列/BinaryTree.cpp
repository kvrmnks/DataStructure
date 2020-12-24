#include<iostream>
#include<stack>
class BinaryTree{
private:
    struct Node{
        int leftChild, rightChild, father;
    };
    Node *nodeList;
    int root, size;
    int _buildPreAndInOrder(int *, int *, int , int , int , int , int, int );
    int _buildInAndPostOrder(int *, int *, int , int , int , int ,int, int );
public:
    BinaryTree(int size, int root);
    void clear();
    void addNode(int x, int xLeftChild, int xRightChild, int xFather);
    void preOrder(int *outList);
    void inOrder(int *outList);
    void postOrder(int *dataOut);
    void buildByPreAndInOrder(int *preorder, int *inorder, int length);
    void buildByInAndPostOrder(int *inorder, int *postorder, int length);
    
};

BinaryTree::BinaryTree(int size, int root){
        nodeList = new BinaryTree::Node[size+1];
        for(int i=1;i<=size;i++)
            nodeList[i].leftChild = nodeList[i].rightChild = nodeList[i].father = -1;
        this->root = root;
        this->size = size;
}

void BinaryTree::clear(){
    if(nodeList != NULL){
        delete[] nodeList;
    }
}

void BinaryTree::addNode(int x, int xLeftChild, int xRightChild, int xFather){
    nodeList[x].leftChild = xLeftChild;
    nodeList[x].rightChild = xRightChild;
    nodeList[x].father = xFather;
}

void BinaryTree::preOrder(int *outList){
    std::stack<int> S;
    S.push(this->root);
    while(!S.empty()){
        int current = S.top();
        S.pop();
        *outList = current;
        outList ++;
        if(nodeList[current].rightChild != -1)
            S.push(nodeList[current].rightChild);
        if(nodeList[current].leftChild != -1)
            S.push(nodeList[current].leftChild);
    }
}

void BinaryTree::inOrder(int *outList){
    std::stack<std::pair<int,int> > S;
    S.push(std::make_pair(this->root, 1));
    while(!S.empty()){
    std::pair<int, int> cur = S.top();
        S.pop();
        if(cur.second == 1){
            S.push(std::make_pair(cur.first, 2));
            int leftChild = nodeList[cur.first].leftChild;
            if(leftChild != -1)
                S.push(std::make_pair(leftChild, 1));
        }else{
            *outList = cur.first;
            outList ++;
            int rightChild = nodeList[cur.first].rightChild;
            if(rightChild != -1)
                S.push(std::make_pair(rightChild, 1));
        }
    }
}

void BinaryTree::postOrder(int *dataOut){
    int node, state, leftChild, rightChild;
    std::stack<std::pair<int, int> > S;
    S.push(std::make_pair(this->root, 1));
    while(!S.empty()){
        std::pair<int, int> cur = S.top();
        S.pop();
        node = cur.first; state = cur.second;
        leftChild = nodeList[node].leftChild;
        rightChild = nodeList[node].rightChild;
        if(state == 1){
            S.push(std::make_pair(node, 2));
            if(leftChild != -1)
                S.push(std::make_pair(leftChild, 1));
        }else if(state == 2){
            S.push(std::make_pair(node, 3));
            if(rightChild != -1)
                S.push(std::make_pair(rightChild, 1));
        }else{
            *dataOut = node;
            dataOut++;
        }
    }
}

int BinaryTree::_buildPreAndInOrder(int *p, int *in, int n, int L1, int R1, int L2, int R2, int fa){
    if(R1<L1 || R2<L2) return -1;
    nodeList[p[L1]].father = fa;
    int loc = -1;
    for(int i=L2;i<=R2;i++)if(in[i] == p[L1])loc = i;
    nodeList[p[L1]].leftChild = _buildPreAndInOrder(p,in,n,L1+1,L1+loc-L2,L2,loc-1,p[L1]);
    nodeList[p[L1]].rightChild = _buildPreAndInOrder(p,in,n,L1+loc-L2+1,R1,loc+1,R2,p[L1]);
    return p[L1];
}

int BinaryTree::_buildInAndPostOrder(int *in, int *p, int n, int L1, int R1, int L2, int R2, int fa){
    if(R1<L1 || R2<L2)return -1;
    nodeList[p[R2]].father = fa;
    int loc = -1;
    for(int i=L1;i<=R1;i++)if(in[i]==p[R2])loc=i;
    nodeList[p[R2]].leftChild = _buildInAndPostOrder(in,p,n,L1,loc-1,L2,L2+loc-L1-1,p[R2]);
    nodeList[p[R2]].rightChild = _buildInAndPostOrder(in,p,n,loc+1,R1,L2+loc-L1,R2-1,p[R2]);
    return p[R2];
}

void BinaryTree::buildByPreAndInOrder(int *preorder, int *inorder, int length){
    clear();
    nodeList = new BinaryTree::Node[length+1];
    this->size = length;
    for(int i=0;i<=length;i++)nodeList[i] = {-1,-1,-1};
    root = _buildPreAndInOrder(preorder, inorder, length, 1, length, 1, length, -1);
}

void BinaryTree::buildByInAndPostOrder(int *inorder, int *postorder, int length){
    clear();
    nodeList = new BinaryTree::Node[length+1];
    this->size = length;
    for(int i=0;i<=length;i++)nodeList[i] = {-1,-1,-1};
    root = _buildInAndPostOrder(inorder, postorder, length, 1, length, 1, length, -1);
}

int _preArray[] = {0, 1, 2, 4, 5, 3};
int _inArray[] = {0, 4, 5, 2, 1, 3};
int _postArray[] = {0, 5, 4, 2, 3, 1};
int data[100];
int main(){
    BinaryTree T1(2,1);
    T1.buildByPreAndInOrder(_preArray, _inArray, 5);
    std::cout << "use pre and in order to build the tree and output the postorder:\n";
    T1.postOrder(data+1);
    for(int i=1;i<=5;i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;

    BinaryTree B(2, 1);
    B.buildByInAndPostOrder(_inArray, _postArray, 5);
    std::cout << "use in and post order to build the tree and output the preorder:\n";
    B.preOrder(data+1);
    for(int i=1;i<=5;i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;    

/*
test data for 3 kinds of orders
5 1
1 2 3 -1
2 4 -1 1
3 -1 -1 1
4 -1 5 2
5 -1 -1 4   
*/
    int size, root;
    scanf("%d%d", &size, &root);
    BinaryTree T(size, root);
    for(int i=1;i<=size;i++){
        int a,b,c,d;
        scanf("%d%d%d%d", &a,&b,&c,&d);
        T.addNode(a,b,c,d);
    }

    int *data = new int[size +1];
    std::cout << "preOrder:\n";
    T.preOrder(data);
    for(int i=0;i<size;i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;

    std::cout << "inOrder:\n";
    T.inOrder(data);
    for(int i=0;i<size;i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
    
    std::cout << "postOrder:\n";
    T.postOrder(data);
    for(int i=0;i<size;i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
//    system("pause");
    return 0;
}
