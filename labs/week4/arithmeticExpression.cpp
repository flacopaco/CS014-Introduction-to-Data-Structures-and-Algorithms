#include "arithmeticExpression.h"
#include <fstream>
#include <stack>
#include <sstream>
using namespace std;

arithmeticExpression::arithmeticExpression(const string &infixExpression) {
    root = 0;
    this -> infixExpression = infixExpression;
}

void arithmeticExpression::buildTree() {
    string postfix = infix_to_postfix();
    stack<TreeNode *> nodeStack;
    char key = 'a';
    
    for (unsigned i = 0; i < postfix.size(); ++i) {
        if (priority(postfix.at(i)) == 0) {
            TreeNode * tempNode = new TreeNode(postfix.at(i), key);
            
            ++key;
            nodeStack.push(tempNode);
        }
        else if(priority(postfix.at(i)) == 2 || priority(postfix.at(i)) == 1) {
            TreeNode* tempNode = new TreeNode(postfix.at(i), key);
            ++key;
            tempNode -> right = nodeStack.top();
            nodeStack.pop();
            tempNode -> left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(tempNode);
        }
        
    }
    
    root = nodeStack.top();
    
}

void arithmeticExpression::infix() {
    infix(root);
}

void arithmeticExpression::prefix() {
    prefix(root);
}

void arithmeticExpression::postfix() {
    postfix(root);
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::infix(TreeNode *start) {
    if(start) {
        if (start -> left && start -> right) {
            cout << "(";
        }
        infix(start -> left);
        cout << start -> data;
        infix(start -> right);
        if (start -> left && start -> right) {
            cout << ")";
        }
    }
}

void arithmeticExpression::prefix(TreeNode *start) {
    if(start) {
        cout << start -> data;
        prefix(start -> left);
        prefix(start -> right);
    }
}

void arithmeticExpression::postfix(TreeNode *start) {
    if(start) {
        postfix(start -> left);
        postfix(start -> right);
        cout << start -> data;
    }
}

void arithmeticExpression::visualizeTree(ofstream & oFS, TreeNode * start){
    
    if (start) {
        oFS << start -> key << " [color = lightblue, style = filled, label=\"" << start->data << "\"];" << endl;
    }
    if (start -> left) {
        visualizeTree(oFS, start->left);
    }
    
    if (start -> right) {
        visualizeTree(oFS, start -> right);
    }
    
    if (start -> left) {
        oFS << start -> key << " -> " << start -> left -> key << ";" << endl;
    }
    
    if (start -> right) {
        oFS << start -> key << " -> " << start -> right -> key << ";" << endl;
    }    
    
}
