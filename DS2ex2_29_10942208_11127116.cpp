// 11127116 æ›¾è©®æ·³ 10942208 é™³æ´ºå®‰
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct schooltype {
    string sname = "";                   // school name
    string dname = "";                   // department name
    string type = "";                    // either day or night
    string level = "";                   // graduate or undergraduate
    int num = 0;                        //input order of data
    int nstud;                      // number of students
    int ngrad;                      // number of school data
};

class threeTwoTree {
	
	struct nodeType {

    };
    
}; // ¤G¤T¾ð 

class AVLTree {
    struct nodeType {
        vector <schooltype> key;                  // search key
        nodeType *lchild = NULL;     // left child
        nodeType *rchild = NULL;     // right child
    };

    nodeType *root;
    void clearNode(nodeType* node);

public:
    AVLTree() : root(NULL) {}   // constructor of an empty tree
    nodeType* getRoot (){
        return root;
    }
    void intsertAVL( nodeType* cur ,schooltype allR );

    void clearUp() {                    // cut off the entire tree
        clearNode(root);
        root = NULL;
    } // end clearUp

    ~AVLTree() { clearUp(); }
};

class schoolList {
    vector<schooltype> allR;                      // set of data records
    AVLTree theAVLTree;


public:
    string fileID;                                // number to form a file name
    schoolList() { clearUp(); }   // constructor: do nothing
    bool isEmpty() ;            // check if there is nothing
    void readF( string );               // read records from a file
    void insertAVL();
    void clearUp() {            // erase the object content
        allR.clear();
        fileID.clear();
        theAVLTree.clearUp();
        // remenber to build destructor
    } // end clearUp


    ~schoolList() { clearUp(); }      // destructor: destroy the object
};

int main() {
    int cmd = 1;
    string fileName;
    schoolList aList;
    while (cmd != 0) {

        // UI
        cout << endl << "**** Balanced Search Trees ****";
        cout << endl << "* 0. QUIT                     *";
        cout << endl << "* 1. Build 23 tree            *";
        cout << endl << "* 2. Build AVL tree           *";
        cout << endl << "****************************";
        cout << endl << "Input a choice(0, 1, 2): ";
        cin >> cmd;

        // sort the file
        if (cmd == 1) {
            aList.clearUp();
            cout << endl << "Input a file number ([0] Quit): ";
            cin >> fileName;
            if ( fileName != "0" ) {
                aList.readF( fileName );
            }
        } // if
        else if (cmd == 2) {
            if ( aList.isEmpty() )
                cout << endl << "### Choose 1 first. ###";
            else {
                aList.insertAVL();
            }

        } // else if


        else if (cmd == 0)
            break; // end the program

        else
            cout << endl << "command does not exist" << endl; // wrong comment


    } // while

    cout << "pause";
    return 0;
}

//-----------------------------------------------------------------------------------
void AVLTree :: intsertAVL( nodeType* cur, schooltype newNode ) {
    if ( root == NULL ) {
        root = new nodeType;
        root->key.push_back(newNode);
    }
    else if ( newNode.nstud == cur->key[0].nstud ){
        cur->key.push_back(newNode);
    }
    else if ( newNode.nstud > cur->key[0].nstud ) {
        if ( cur->rchild == NULL ) {
            cur->rchild = new nodeType;
            cur->rchild->key.push_back(newNode);
        }
        else
            intsertAVL( cur->rchild, newNode );
    }
    else if ( newNode.nstud < cur->key[0].nstud ) {
        if ( cur->lchild == NULL ) {
            cur->lchild = new nodeType;
            cur->lchild->key.push_back(newNode);
        }
        else
            intsertAVL( cur->lchild, newNode );
    }

    
}

void AVLTree :: clearNode(nodeType* node) {
    if (node == nullptr) {
        return; // Base case: node is null
    }

    clearNode(node->lchild); // Delete left subtree
    clearNode(node->rchild); // Delete right subtree

    delete node; // Delete the current node
}


// schoolList-------------------------------------------------------------------------
void schoolList ::insertAVL() {
    for ( int i = 0; i < allR.size(); i++ ) {
        theAVLTree.intsertAVL( theAVLTree.getRoot(), allR[i]);
    }
    return;
}

bool schoolList :: isEmpty() {
    if (  allR.size() == 0)
        return true;
    else
        return false;
}

void schoolList :: readF( string fileName ) {          // definition: read all from a file
    int count = 0;

    fstream inFile;                 // file handle

    string fileID = fileName;
    fileName = "input" + fileID + ".txt";
    inFile.open(fileName.c_str(), fstream::in); // open file to read

    while (!inFile.is_open()) {                              // unable to open file
        cout << endl << "### " << fileName << " does not exist! ###" << endl;
        cout << endl << "Input a file number ([0] Quit): ";
        cin >> fileName;
        fileID = fileName;
        fileName = "input" + fileID + ".txt";
        inFile.open(fileName.c_str(), fstream::in); // open file to read

    } // while

    bool jump = false ;
    char cstr[255];
    int fNo = 0, pre = 0, pos = 0 ;
    inFile.getline(cstr, 255, '\n');     // skip the 1st header line
    inFile.getline(cstr, 255, '\n');     // skip the 2nd header line
    inFile.getline(cstr, 255, '\n');     // skip the list of column names
    int num = 0;
    while ( inFile.getline(cstr, 255, '\n') ) {  // get all records
        schooltype oneR;
        string buf, cut;
        fNo = 0;
        pre = 0;
        buf.assign(cstr);

        do {
            pos = buf.find_first_of('\t', pre);
            cut = buf.substr(pre, pos - pre);
            switch (++fNo) {
                case 2: oneR.sname = cut;               // college name
                    break;
                case 4: oneR.dname = cut;               // department name
                    break;
                case 5: oneR.type = cut;                // either day or night
                    break;
                case 6: oneR.level = cut;               // graduate or undergraduate
                    break;
                case 7:
                    while (count < cut.size()) {
                        if (cut[count] > '9' || cut[count] < '0')
                            cut.erase(count, 1);

                        count++;
                    } // while
                    count = 0;
                    oneR.nstud = atoi(cut.c_str());
                    break;
                case 9:
                    while ( count < cut.size() ) {
                        if ( cut[count] > '9' || cut[count] < '0' ) {
                            cut.erase(count, 1);
                        }
                        count++;
                    }
                    count = 0;
                    oneR.ngrad = atoi(cut.c_str()); // get the number of graduates
                    break;
                default:
                    break; //end switch
            }

            pre = ++pos;
        } while ((pos > 0) && (fNo < 8));

        num++;
        oneR.num = num;
        allR.push_back(oneR);
        fNo = 1;

        oneR.ngrad = 0;
        oneR.num = 0;
        oneR.nstud = 0 ;

    }

} // end readFile



