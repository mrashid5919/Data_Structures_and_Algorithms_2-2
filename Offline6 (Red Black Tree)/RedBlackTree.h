#ifndef _RED_BLACK_TREE_H
#define _RED_BLACK_TREE_H

#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct Node
{
    T val;
    int color; //1 stands for red, 0 stands for black
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    int subCount;
};

template<typename T>
class RedBlackTree
{
    private:
        Node<T>* root;
        Node<T>* tnil;

        void initNode(Node<T>* node, Node<T>* parent)
        {
            node->parent = parent;
            node->left = nullptr;
            node->right = nullptr;
            node->color = 0;
        }
        int nodeCount;

        void rotateLeft(Node<T>* x)
        {
            Node<T>* y=x->right;
            x->right=y->left;
            if(y->left!=tnil)
                y->left->parent=x;
            y->parent=x->parent;
            if(x->parent==nullptr)
                root=y;
            else if(x==x->parent->left)
                x->parent->left=y;
            else
                x->parent->right=y;
            y->left=x;
            x->parent=y;
            y->subCount=x->subCount;
            x->subCount=x->left->subCount+x->right->subCount+1;
        }

        void rotateRight(Node<T>* x)
        {
            Node<T>* y=x->left;
            x->left=y->right;
            if(y->right!=tnil)
                y->right->parent=x;
            y->parent=x->parent;
            if(x->parent==nullptr)
                root=y;
            else if(x==x->parent->left)
                x->parent->left=y;
            else
                x->parent->right=y;
            y->right=x;
            x->parent=y;
            y->subCount=x->subCount;
            x->subCount=x->left->subCount+x->right->subCount+1;
        }

        void rb_insert(Node<T>* z)
        {
            Node<T>* y=nullptr;
            Node<T>* x=root;
            while(x!=tnil)
            {
                y=x;
                y->subCount++;
                if(z->val<x->val)
                    x=x->left;
                else
                    x=x->right;
            }
            z->parent=y;
            if(y==nullptr)
                root=z;
            else if(z->val<y->val)
                y->left=z;
            else
                y->right=z;
            if(z->parent==nullptr)
            {
                z->color=0;
                return;
            }
            if(z->parent->parent==nullptr)
            {
                return;
            }
            /*z->left=nullptr;
            z->right=nullptr;
            z->color=1;*/
            rb_insert_fixup(z);
            nodeCount++;
        }

        void rb_insert_fixup(Node<T>* z)
        {
            Node<T>* y;
            while(z->parent->color==1)
            {
                if(z->parent==z->parent->parent->left)
                {
                    y=z->parent->parent->right;

                    if(y->color==1)
                    {
                        z->parent->color=0;
                        y->color=0;
                        z->parent->parent->color=1;
                        z=z->parent->parent;
                    }
                    else
                    {
                        if(z==z->parent->right)
                        {
                            z=z->parent;
                            rotateLeft(z);
                        }
                        z->parent->color=0;
                        z->parent->parent->color=1;
                        rotateRight(z->parent->parent);
                    }
                }

                else
                {
                    y=z->parent->parent->left;

                    if(y->color==1)
                    {
                        z->parent->color=0;
                        y->color=0;
                        z->parent->parent->color=1;
                        z=z->parent->parent;
                    }
                    else
                    {
                        if(z==z->parent->left)
                        {
                            z=z->parent;
                            rotateRight(z);
                        }
                        z->parent->color=0;
                        z->parent->parent->color=1;
                        rotateLeft(z->parent->parent);
                    }
                }
                if(z==root)
                    break;
            }
            root->color=0;
        }

        Node<T>* tree_min(Node<T>* x)
        {
            while(x->left!=tnil)
                x=x->left;
            return x;
        }

        Node<T>* tree_successor(Node<T>* x)
        {
            if(x->right!=tnil)
                return tree_min(x->right);
            Node<T>* y=x->parent;
            while(y!=tnil && x==y->right)
            {
                x=y;
                y=y->parent;
            }
            return y;
        }

        void rb_transplant(Node<T>* u,Node<T>* v)
        {
            if(u->parent==nullptr)
                root=v;
            else if(u==u->parent->left)
                u->parent->left=v;
            else
                u->parent->right=v;
            v->parent=u->parent;
        }

        void rb_delete(Node<T>* z)
        {
            if(z!=root)
            {
                Node<T>* temp=z->parent;
                while(temp!=root)
                {
                    temp->subCount--;
                    temp=temp->parent;
                }
                root->subCount--;
            }
            Node<T>* x;
            Node<T>* y=z;
            int y_original_color=y->color;
            if(z->left==tnil)
            {
                x=z->right;
                rb_transplant(z,z->right);
            }
            else if(z->right==tnil)
            {
                x=z->left;
                rb_transplant(z,z->left);
            }
            else
            {
                y = tree_min(z->right);
                y_original_color = y->color;
                x = y->right;
                if (y->parent == z)
                    x->parent = y;
                else
                {
                    rb_transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                    Node<T>* temp=x->parent;
                    while(temp!=y)
                    {
                        temp->subCount--;
                        temp=temp->parent;
                    }
                    y->subCount=y->left->subCount+1;
                }
                rb_transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
                y->subCount=y->left->subCount+y->right->subCount+1;
            }
            delete z;
            if(y_original_color==0)
                rb_delete_fixup(x);
            nodeCount--;
        }

        void rb_delete_fixup(Node<T>* x)
        {
            while(x!=root && x->color==0)
            {
                if(x==x->parent->left)
                {
                    Node<T>* w=x->parent->right;
                    if(w->color==1)
                    {
                        w->color=0;
                        x->parent->color=1;
                        rotateLeft(x->parent);
                        w=x->parent->right;
                    }
                    if(w->left->color==0 && w->right->color==0)
                    {
                        w->color=1;
                        x=x->parent;
                    }
                    else
                    {
                        if(w->right->color==0)
                        {
                            w->left->color=0;
                            w->color=1;
                            rotateRight(w);
                            w=x->parent->right;
                        }
                        w->color=x->parent->color;
                        x->parent->color=0;
                        w->right->color=0;
                        rotateLeft(x->parent);
                        x=root;
                    }
                }
                else
                {
                    Node<T>* w=x->parent->left;
                    if(w->color==1)
                    {
                        w->color=0;
                        x->parent->color=1;
                        rotateRight(x->parent);
                        w=x->parent->left;
                    }
                    if(w->left->color==0 && w->right->color==0)
                    {
                        w->color=1;
                        x=x->parent;
                    }
                    else
                    {
                        if(w->left->color==0)
                        {
                            w->right->color=0;
                            w->color=1;
                            rotateLeft(w);
                            w=x->parent->left;
                        }
                        w->color=x->parent->color;
                        x->parent->color=0;
                        w->left->color=0;
                        rotateRight(x->parent);
                        x=root;
                    }
                }
            }
            x->color=0;
        }

        Node<T>* tree_search(Node<T>* x,const T& key)
        {
            Node<T>* z=tnil;
            while(x!=tnil)
            {
                if(x->val==key)
                    z=x;
                if(key<x->val)
                    x=x->left;
                else
                    x=x->right;
            }
            return z;
        }

    public:
        RedBlackTree()
        {
            tnil= new Node<T>;
		    tnil->color = 0;
		    tnil->left = nullptr;
		    tnil->right = nullptr;
		    root = tnil;
        }

        ~RedBlackTree()
        {

        }

        bool ins(const T& val)
        {
            Node<T>* x=new Node<T>;
            x->parent=nullptr;
            x->val=val;
            x->left=tnil;
            x->right=tnil;
            x->color=1;
            x->subCount=1;
            if(tree_search(root,val)!=tnil)
                return false;
            else
            {
                rb_insert(x);
                return true;
            }
        }

        bool del(const T& val)
        {
            if(tree_search(root,val)==tnil)
                return false;
            else
            {
                Node<T>* x=tree_search(root,val);
                rb_delete(x);
                return true;
            }
            //return true;
        }

        bool search(const T& val)
        {
            if(tree_search(root,val)==tnil)
                return false;
            return true;
        }

        int cnt(const T& val)
        {
            int c=0;
            Node<T>* x=root;
            while(x!=tnil)
            {
                if(x->val>val)
                    x=x->left;
                else if(x->val<val)
                {
                    c=c+x->left->subCount+1;
                    x=x->right;
                }
                else
                    return c+x->left->subCount;
            }
            return c;
        }
};
#endif
