/***
* Shyam Kishan
* Dictionary.cpp
* Implementation file for Dictionary ADT
***/

#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

// Private Constructor -------------------------------------------------
// Node constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = -1;
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if (R == nil || R == nullptr){
        return;
    }

    inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + "\n";
    inOrderString(s, R->right);
}

void Dictionary::WordsString(std::string& s, Node* R) const{
    if (R == nil || R == nullptr){
        return;
    }
    WordsString(s, R->left);
    s += R->key + "\n";
    WordsString(s, R->right);
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
void Dictionary::BST_insert(Node* M){
    // Basically redoing setValue() but not defining a new Node z, and using 
    // given node M as a replacement for z.
    Node* x = root;
    Node* y = nil;

    while (x != nil){
        y = x;
        if (M->key < x->key){
            x = x->left;
        } else {
            x = x->right;
        }
    }

    M->parent = y;

    if (y == nil){
        root = M;
    } else if (M->key < y->key){
        y->left = M;
    } else {
        y->right = M;
    }

    M->left = M->right = nil;
}

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string will consist of keys only, with the order determined by a pre-order
   // tree walk. The keys stored in black Nodes will be appended as "key\n", and
   // the keys stored in red Nodes will be appended as "key (RED)\n". The output 
   // of this function is demonstrated in /Examples/pa8/DictionaryClient-out. 
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R == nil || R == nullptr){
        return;
    }

    if (R->color == red){
        s += R->key + " (RED)\n";
    } else {
        s += R->key + "\n";
    }

    preOrderString(s, R->left);
    preOrderString(s, R->right);
}
// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    // New implementation of preOrderCopy()
    if (R != N){
        Node* M = new Node(R->key, R->val);
        BST_insert(M);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if (R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        num_pairs--;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if (R == nil || k == R->key){
        return R;
    } else if (k < R->key){
        return search(R->left, k);
    } else if (k > R->key){
        return search(R->right, k);
    }

    return nil;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if (R != nil){
        while (R->left != nil){
            R = R->left;
        }
        return R;
    }
    return nil;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if (R != nil){
        while (R->right != nil){
            R = R->right;
        }
        return R;
    }
    return nil;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if (N->right != nil){
        return findMin(N->right);
    }
    Node* y = N->parent;
    while(y != nil && N == y->right){
        N = y;
        y = y->parent;
    }

    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if (N->left != nil){
        return findMax(N->left);
    }

    Node *y = N->parent;
    while(y != nil && N == y->left){
        N = y;
        y = y->parent;
    }
    return y;
}

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    Node* y = N->right;
    N->right = y->left;
    if (y->left != nil){
        y->left->parent = N;
    }

    y->parent = N->parent;
    if (N->parent == nil){
        root = y;
    } else if (N == N->parent->left){
        N->parent->left = y;
    } else {
        N->parent->right = y;
    }
    y->left = N;
    N->parent = y;
}

// RightRotate()
// opposite of LeftRotate()
void Dictionary::RightRotate(Node* N){
    Node* y = N->left;
    N->left = y->right;

    if (y->right != nil){
        y->right->parent = N;
    }

    y->parent = N->parent;
    if (N->parent == nil){
        root = y;
    } else if (N == N->parent->right){
        N->parent->right = y;
    } else {
        N->parent->left = y;
    }
    y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    while(N->parent->color == red){
        if (N->parent == N->parent->parent->left){
            Node* y = N->parent->parent->right;
            if (y->color == red){
                // case 1
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = red;
                N = N->parent->parent;
            } else {
                // case 2
                if (N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                // case 3
                N->parent->color = BLACK;
                N->parent->parent->color = red;
                RightRotate(N->parent->parent);
            }
        } else {
            Node* y = N->parent->parent->left;
            if (y->color == red){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = red;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = red;
                LeftRotate(N->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if (u->parent == nil){
        root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    Node* w = nil;
    while(N != root && N->color == BLACK){
        if (N == N->parent->left){
            w = N->parent->right;
            if (w->color == red){
                w->color = BLACK;
                N->parent->color = red;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK){
                w->color = red;
                N = N->parent;
            } else {
                if (w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = red;
                    RightRotate(w);
                    w = N->parent->right;
                }

                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        } else {
            w = N->parent->left;
            if (w->color == red){
                w->color = BLACK;
                N->parent->color = red;
                RightRotate(N->parent);
                w = N->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK){
                w->color = red;
                N = N->parent;
            } else {
                if (w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = red;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}


// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node* y = N;
    Node* x = nil;
    int y_original_color = y->color;
    if (N->left == nil){
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil){
        x = N->left;
        RB_Transplant(N, N->left);
    } else {
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y != N->right){
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        } else {
            if (x != nil) {
                x->parent = y;
            }
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == BLACK){
        RB_DeleteFixUp(x);
    }
}

// Class Constructors & Destructors ------------------------------------

// Creates a new Dictionary in the empty state
Dictionary::Dictionary(){
    nil = new Node("", 0);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK;

    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("", 0);
    root = nil;
    current = nil;
    num_pairs = 0;

    if (D.root != D.nil){
        preOrderCopy(D.root, D.nil);
    }
}

// Destructor
Dictionary::~Dictionary(){
    clear();
    delete nil;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    if (num_pairs == 0){
        return false;
    }
    if (search(root, k) != nil){
        return true;
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if (!contains(k)){
        throw std::invalid_argument("Dictionary Error: getValue(): Key doesn't exist");
    }
    Node* N = search(root, k);
    return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if (current == nil){
        return false;
    }
    return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if (!hasCurrent()){
        throw std::invalid_argument("Dictionary Error: currentKey(): current is pointing to nil");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if (!hasCurrent()){
        throw std::invalid_argument("Dictionary Error: currentVal(): current is pointing to nil");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node* x = root;
    Node* y = nil;

    while(x != nil){
        y = x;
        if (k == x->key){
            x->val = v;
            return;
        } else if (k > x->key){
            x = x->right;
        } else {
            x = x->left;
        }
    }
    Node* M = new Node(k, v);
    M->parent = y;

    if (y == nil){
        root = M;
    } else if (M->key < y->key){
        y->left = M;
    } else {
        y->right = M;
    }
    M->left = M->right = nil;
    M->color = red;
    num_pairs++;
    RB_InsertFixUp(M);

}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if (!contains(k)){
        throw std::invalid_argument("Dictionary Error: remove(): Key doesn't exist");
    }

    // If current is on key pair,
    // set current to nil
    if (current->key == k){
        current = nil;
    }
    
    // start removal process
    Node* N = search(root, k);

    if (num_pairs == 1){
        delete(N);
        root = nil;
        current = nil;
        num_pairs = 0;
        return;
    }

    RB_Delete(N);
    num_pairs--;
}


// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if (num_pairs > 0){
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if (num_pairs > 0){
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if (!hasCurrent()){
        throw std::invalid_argument("Dictionary Error: next(): Current is undefined");
    }

    if (current == findMax(root)){
        current = nil;
    } else {
        current = findNext(current);
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if (!hasCurrent()){
        throw std::invalid_argument("Dictionary Error: prev(): Current is undefined");
    }

    if (current == findMin(root)){
        current = nil;
    } else {
        current = findPrev(current);
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    string s = "";
    inOrderString(s, root);
    return s;
}

std::string Dictionary::to_string2() const{
    string s = "";
    WordsString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    if (num_pairs != D.num_pairs){
        return false;
    }

    // Set new nodes to the roots
    Node* A = this->root;
    Node* B = D.root;
    // iterate Backwards towards min
    while(A != nil){
        keyType k = A->key;
        valType v = A->val;
        if (search(B, k) == nil){
            return false;
        }
        B = search(B, k);
        if (B->val != v){
            return false;
        }
        B = D.root;
        A = A->left;
    }

    A = this->root;
    B = D.root;

    while(A != nil){
        keyType k = A->key;
        valType v = A->val;
        if (search(B, k) == nil){
            return false;
        }
        B = search(B, k);
        if (B->val != v){
            return false;
        }
        B = D.root;
        A = A->right;
    }

    A = this->root;
    B = D.root;

    return true;
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if (this != &D){
        Dictionary temp = D;

        std::swap(num_pairs, temp.num_pairs);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(nil, temp.nil);
    }

    return *this;
}