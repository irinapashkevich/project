#include <iostream>

using namespace std;

struct tree_element{
   int value;
   int height;
   struct tree_element* left;
   struct tree_element* right;
};

struct tree_element* create_tree_element (int a)
{
    struct tree_element* el = new struct tree_element;
    el->value=a;
    el->height=1;
    el->left=NULL;
    el->right=NULL;
    return el;
};

int height (struct tree_element* root)
{
    if (root==NULL)
    {
        return 0;
    }
    else
    {
        return root->height;
    }
}

tree_element *left_rotate(struct tree_element* root)
{
    tree_element *a=root;
    tree_element *b=root->right;
    tree_element *c=root->right->left;
    b->left=a;
    a->right=c;
    a->height=max(height(a->left), height(a->right))+1;
    b->height=max(height(b->left), height(b->right))+1;
    return b;
}

tree_element *right_rotate(struct tree_element* root)
{
    tree_element *a=root;
    tree_element *b=root->left;
    tree_element *c=root->left->right;
    b->right=a;
    a->left=c;
    a->height=max(height(a->left), height(a->right))+1;
    b->height=max(height(b->left), height(b->right))+1;
    return b;
}

tree_element *incert_into_tree(struct tree_element* root, struct tree_element* el)
{
    if (root->value>el->value)
    {
        if (root->left==NULL)
        {
            root->left=el;
        }
        else
        {
           root->left=incert_into_tree(root->left, el);
        }
    }
    if (root->value<el->value)
    {
        if (root->right==NULL)
        {
           root->right=el;
        }
        else
        {
           root->right=incert_into_tree(root->right, el);
        }
    }

    root->height=1+max(height(root->left), height(root->right));

    if ((height(root->left)>height(root->right)+1) && (el->value<root->left->value))
    {
        return right_rotate(root);
    }
    if ((height(root->right)>height(root->left)+1) && (el->value>root->right->value))
    {
        return left_rotate(root);
    }
    if ((height(root->left)>height(root->right)+1) && (el->value>root->left->value))
    {
        root->left=left_rotate(root->left);
        return right_rotate(root);
    }
    if ((height(root->right)>height(root->left)+1) && (el->value<root->right->value))
    {
        root->right=right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

void delete_tree (tree_element* root)
{
    if (root->right!=NULL)
    {
        delete_tree (root->right);
    }
    if (root->left!=NULL)
    {
        delete_tree (root->left);
    }
    delete (root);
}


int max_of_tree(struct tree_element* root)
{
    int a;
    if (root->right!=NULL)
    {
        a=max_of_tree(root->right);
        if (root->right->value==a)
        {
            delete (root->right);
            root->right=NULL;
        }
        if (height(root->left)>height(root->right)+1)
        {
            if (height(root->left->right)>height(root->left->left))
            {
                root->left=left_rotate(root->left);
            }
            root=right_rotate(root);
        }
    }
    else
    {
        a=root->value;
        if (root->left!=NULL)
        {
            root->value=root->left->value;
            delete (root->left);
            root->left=NULL;
        }
    }
    return a;
}

int min_of_tree(struct tree_element* root)
{
    int a;
    if (root->left!=NULL)
    {
        a=min_of_tree(root->right);
        if (root->left->value==a)
        {
            delete (root->left);
            root->left=NULL;
        }
        if (height(root->right)>height(root->left)+1)
        {
            if (height(root->right->left)>height(root->right->right))
            {
                root->right=right_rotate(root->right);
            }
            root=left_rotate(root);
        }
    }
    else
    {
        a=root->value;
        if (root->right!=NULL)
        {
            root->value=root->right->value;
            delete (root->right);
            root->right=NULL;
        }
    }
    return a;
}

tree_element *delete_tree_element (struct tree_element* root, int value)
{
    if (root->value==value)
    {
        if ((root->right==NULL) || (root->left==NULL))
        {
            if ((root->right==NULL) && (root->left==NULL))
            {
                delete (root);
                return NULL;
            }
            if (root->left==NULL)
            {
                root->value=root->right->value;
                delete (root->right);
                root->right=NULL;
                root->height=1;
                return root;

            }
            if (root->right==NULL)
            {
                root->value=root->left->value;
                delete (root->left);
                root->left=NULL;
                root->height=1;
                return root;
            }
        }
        else
        {
            if (root->left->height>root->right->height)
            {
               root->value=max_of_tree(root->left);
               if (root->left->value==root->value)
               {
                   delete(root->left);
                   root->left=NULL;
               }
            }
            else
            {
               root->value=min_of_tree(root->right);
               if (root->right->height==root->value);
               {
                   delete(root->right);
                   root->right=NULL;
               }
            }
            root->height=max(height(root->right), height(root->left))+1;
            return root;
        }
    }
    else
    {
        if ((value>root->value) && (root->right!=NULL))
        {
            root->right=delete_tree_element(root->right, value);
            root->height=max(height(root->right), height(root->left))+1;
            if (height(root->left)>height(root->right)+1)
            {
                if (height(root->left->right)>height(root->left->left))
                {
                    root->left=left_rotate(root->left);
                }
                return right_rotate(root);
            }
        }
        if ((value<root->value) && (root->left!=NULL))
        {
            root->left=delete_tree_element(root->left, value);
            root->height=max(height(root->right), height(root->left))+1;
            if (height(root->right)>height(root->left)+1);
            {
                if (height(root->right->left)>height(root->right->right))
                {
                    root->right=right_rotate(root->right);
                }
                return left_rotate(root);
            }

        }
    }
    return root;
}

struct tree_element *find_element(struct tree_element* root, int a)
{
    if (root->value==a)
    {
        return root;
    }
    if ((root->value<a) && (root->right!=NULL))
    {
        return find_element(root->right, a);
    }
    if ((root->value>a) && (root->left!=NULL))
    {
        return find_element(root->left, a);
    }
    return NULL;
}

void print_tree (struct tree_element* root)
{
    if (root->left!=NULL)
        print_tree(root->left);
    cout<<"value="<<root->value<<endl;
    if (root->right!=NULL)
        print_tree(root->right);
}

int main()
{
    int n, a;
    cout << "kol-vo elementov=";
    cin>>n;
    cin>>a;
    struct tree_element* p=create_tree_element(a);
    for (int i=0; i<n-1; i++)
    {
        cin>>a;
        struct tree_element* el=create_tree_element(a);
        p=incert_into_tree(p, el);
    }
    print_tree(p);
    cout<<p->height<<endl;
    cout<<endl;
    cout<<"kol-vo delete=";
    cin>>n;
    struct tree_element* q=create_tree_element(0);
    for (int i=0; i<n; i++)
    {
       cin>>a;
       if (find_element(p, a)!=NULL)
          p=delete_tree_element(p, a);
    }
    print_tree(p);
    cout<<p->height<<endl;
    cout<<endl;
    cout<<"find element:";
    cin>>a;
    q=find_element(p, a);
    if (q!=NULL)
    {
        if (q->left!=NULL)
           cout<<"left "<<q->left->value<<endl;
        if (q->right!=NULL)
           cout<<"right "<<q->right->value<<endl;
        cout<<"h="<<q->height<<endl;
    }
    else
        cout<<"net";
    delete(q);
    delete_tree(p);
    return 0;
}
