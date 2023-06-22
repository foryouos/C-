#include <stdio.h>
#include <stdlib.h>


//�����ͺڽڵ����
#define RED 0
#define BLACK 1

//�������д������
typedef int KEY_TYPE;
//�궨��
#define RBTREE_ENTRY(name,type)      \
    struct name                      \
    {                                \
        /* data */                   \
        struct type *right;          \
        struct type *left;           \
        struct type *parent;         \
        unsigned char color;         \
    }
//������ڵ㶨��
//���ڵ㲻�ɸ��ã�
typedef struct _rbtree_node  //���ɸ��� _
{
    KEY_TYPE key;  //��
    void* value; //ֵ
#if 1   //������ָ��ɺ����ģ��
    struct _rbtree_node* right;  //�ҽڵ�
    struct _rbtree_node* left;  //��ڵ�

    struct _rbtree_node* parent; //���ڵ�
    unsigned char color;   //���������ɫ����ʡһ��ռ䣬�ֽڶ���
#else
    RBTREE_ENTRY(, _rbtree_node) node;
#endif
}rbtree_node;

//һ���ṹ����Զ����������
/*
typedef struct thread  //���ɸ��� _
{
    KEY_TYPE key;  //��
    void* value; //ֵ
#if 0   //������ָ��ɺ����ģ��
    struct _rbtree_node *right;  //�ҽڵ�
    struct _rbtree_node *left;  //��ڵ�

    struct _rbtree_node *parent; //���ڵ�
    unsigned char color;   //���������ɫ����ʡһ��ռ䣬�ֽڶ���
#else
    RBTREE_ENTRY( ,thread) ready;
    RBTREE_ENTRY( ,thread) wait;
    RBTREE_ENTRY( ,thread) sleep;
#endif
}rbtree_node;
*/


// ���ڵ�ָ��ͷ����Ҷ�ӽ��
typedef struct _rbtree
{
    struct _rbtree_node* root;   //ͷ�ڵ�
    struct _rbtree_node* nil;   //Ҷ�ӽڵ���Ϊ�ռ��,(����Ҷ�ӽڵ������Ҷ������ص�)nil���ж�,�����ڴ治����

}rbtree;



//����ת  T����� ��ǰ��ת�ĸ��ڵ�  x �������
void rbtree_left_rotate(rbtree* T, rbtree_node* x)
{
    rbtree_node* y = x->right; // yΪĿǰ�׶�x���ҽڵ�
    // 1������x���ҽڵ��Ϊ�����ڵ�
    x->right = y->left;
    if (y->left != T->nil)        // ���y����ڵ㲻ΪҶ�ӽڵ� ����ڵ㣬��Ҷ�ӽڵ�Ͳ��ø���
    {
        y->left->parent = x;     //��y����ڵ�ĸ��ڵ�����x
    }
    // 2,����y�ĸ��ڵ�
    y->parent = x->parent;
    //x �ĸ��ڵ�Ҫô�Ǹ��ڵ㣬Ҫô�ǿ�     
    if (x->parent == T->nil) //��x�Ľڵ㲻ΪҶ�ӽڵ�
    {
        T->root = y;        //��T�ĸ��ڵ���Ϊy
    }
    else if (x == x->parent->left) //��xΪ���ڵ����ڵ�
    {
        x->parent->left = y;   //��x�ĸ��ڵ����ڵ���Ϊy
    }
    else                         //��xΪ���ڵ����ڵ�
    {
        x->parent->right = y;   //��x�ĸ��ڵ���ҽڵ���Ϊy
    }
    // 3,����y����ڵ�
    y->left = x;
    // ���� x�ĸ��ڵ�
    x->parent = y;
}
//����,yΪ��ת�Ľڵ��������
void rbtree_right_rotate(rbtree* T, rbtree_node* y)
{
    rbtree_node* x = y->left;
    //1,
    y->left = x->right;
    if (x->right != T->nil) //���x���ҽڵ㲻��Ҷ�ӽڵ�
    {
        x->right->parent = y;
    }
    // 2,
    x->parent = y->parent;
    if (y->parent == T->nil) //����ڵ�
    {
        T->root = x;
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }
    else
    {
        y->parent->left = x;
    }
    //����x��y�Ķ���
    x->right = y;
    y->parent = x;
}

//����ڵ�z�Ǻ�ɫ���ж��丸�ڵ�
//������ɫ ������������ڵ㣬�ͽڵ�z����ɫ�Ǻ�ɫ
void rbtree_insert_fixup(rbtree* T, rbtree_node* z)
{
    //����ڵ�z�Ǻ�ɫ���ж��丸�ڵ��Ǻ�ɫ��Υ��������4
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left) //��zλ����ڵ�
        {
            rbtree_node* y = z->parent->parent->right; //yΪz���常�ڵ�
            if (y->color == RED) //����常�ڵ��Ǻ�ɫ
            {
                z->parent->color = BLACK;  //z�ĸ��ڵ㻻λ��ɫ
                y->color = BLACK;          // z���常�ڵ�

                //�����游����

                z->parent->parent->color = RED; //z���游�ڵ�Ϊ��ɫ
                //z�Ǻ�ɫ��z���游�Ѿ���������z����
                z = z->parent->parent;  //z��ÿ�λ��ݵ�ʱ���Ǻ�ɫ��

            }
            else //z���常�ڵ��Ǻ�ɫ��
            {
                if (z == z->parent->right) //��zλ���ұ߲���ʱ��Ҫ��ת����߽����м�״̬
                {
                    //��Ҫ���ε���,
                    z = z->parent;
                    rbtree_left_rotate(T, z);
                    
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                //����
                rbtree_right_rotate(T, z->parent->parent);
            }
        }
        else  //��zΪλ���ұ���
        {
            //��ȡ���常�ڵ�
            rbtree_node* y = z->parent->parent->left; //yΪz���常�ڵ�
            //�ж����常�ڵ��Ǻ�ɫ���Ǻ�ɫ
            if (y->color == RED)  //�常����ɫ�Ǻ�ɫ
            {
                z->parent->color = BLACK;  //z�ĸ��ڵ㻻λ��ɫ
                y->color = BLACK;          // z���常�ڵ�
                z->parent->parent->color = RED; //z���游�ڵ�Ϊ��ɫ
                //z�Ǻ�ɫ��z���游�Ѿ���������z����
                //���z���游Ϊ��
                z = z->parent->parent;  //z��ÿ�λ��ݵ�ʱ���Ǻ�ɫ��
               
            }
            else //���常����ɫ�Ǻ���
            {
                if (z == z->parent->left) //��zλ���ұ߲���ʱ��Ҫ��ת����߽����м�״̬
                {
                    //��Ҫ���ε���,
                    // //  zλ�÷����仯
                    z = z->parent;
                    rbtree_right_rotate(T, z);
                    
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                //����
                    
                rbtree_left_rotate(T, z->parent->parent);
            }

        }
    }
    T->root->color = BLACK; //��ֹ���ڵ�ı��

}


// ����
// ����뵽��Ͳ�
//������� T������Ľڵ� z
void rbtree_insert(rbtree* T, rbtree_node* z)
{
    rbtree_node* y = T->root; //��¼x֮ǰ��λ�ã����½ڵ��z�Ĳ����
    rbtree_node* x = T->root; //ָ��ͷ���
    //��ʼѭ������x������Ҷ�ӽڵ�ʱ��һֱѭ��
    while (x != T->nil)
    {
        y = x; //yʼ�ձ�x��һ��;
        if (z->key < x->key)
        {
            //����������
            x = x->left;
        }
        else if (z->key > x->key)
        {
            //����������
            x = x->right;

        }
        else  //�������
        {
            //ȡ����ҵ��
            return; //��������
        }
    } //�õ���x��Ҷ�ӽ��
    z->parent = y;
    // ԭ������Ϊ�գ��²���Ľڵ���Ϊ���ڵ�
    if (y == T->nil) //��ʱ�����û���κνڵ�
    {
        T->root = z;
    }
    else if (z->key < y->key)  //���뵽��ڵ�
    {
        //���ڲ��뵽y���ĸ�λ��
        y->left = z;

    }
    else
    {
        y->right = z;
    }
    z->left = T->nil;
    z->right = T->nil;
    //�������ɫ(��ʲô ��ɫ)
    z->color = RED; //һ��ʼ��ɫ ��ɫ �����ı����ʺ���
    //��ɫ����
     rbtree_insert_fixup(T, z);
}


//ɾ��
//�ҵ��������е���С�ڵ�
rbtree_node* rbtee_right_mini(rbtree* T, rbtree_node* x)
{
    while (x->left != T->nil)
    {
        x = x->left;
    }
    return x;
}
//�ҵ����������е����ڵ�
rbtree_node* rbtee_left_max(rbtree* T, rbtree_node* x)
{
    while (x->right != T->nil)
    {
        x = x->right;
    }
    return x;
}
// ��ɾ���ڵ�����������ʱ
rbtree_node* rbtree_twice(rbtree* T, rbtree_node* z)
{
    rbtree_node* k = z->parent;
    // ��̽ڵ�����������ʱ�������ĵ�һ���ڵ�
    if (z->right != T->nil)
    {
        return rbtee_right_mini(T, z->right);
    }

    // ����Ӧ�ò��ᱻִ�е�����Ϊ��ʱ�Ĵ�ɾ���ڵ��Ȼ���������ӽڵ�
    // ���û�����������Ǿ�����Ϊ������ʱ�ĸ��ڵ�
    while ((k != T->nil) && (z == k->right))
    {
        z = k;
        k = k->parent;
    }
    return k;
}
//ɾ����������

void rbtree_delete_fixup(rbtree* T, rbtree_node* x)
{
    while ((x != T->root) && (x->color == BLACK)) //���Ǹ��ڵ���ɾ���Ľڵ�Ϊ��
    {
        //���xλ�ڸ��ڵ�����
        if (x == x->parent->left)
        {
            //�ҵ��ֵܽڵ�
            rbtree_node* w = x->parent->right;
            //���1���ֵܽڵ�Ϊ��ɫ
            if (w->color == RED)
            {
                //1.1�ֵܽڵ��ɺ�ɫ
                w->color = BLACK;
                //1.2 ���ڵ��ɺ�ɫ
                x->parent->color = RED;
                //1.3 ���ڵ�����
                rbtree_left_rotate(T, x->parent);
                //��������x���ֵܽڵ�
                w = x->parent->right;
            }
            // ���2
            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                //�ֵܽڵ��Ϊ��ɫ
                w->color = RED;
                x = x->parent;
            }
            else
            {
                //���3 x���ֵܽڵ��Ǻ�ɫ�ģ��ֵܵ������Ǻ�ɫ���Һ����Ǻ�ɫ
                if ((w->right->color == BLACK))
                {
                    //3.1�ֵܽڵ���
                    w->color = RED;
                    //�����ӱ��
                    w->left->color = BLACK;
                    // ���ֵܽڵ�����
                    rbtree_right_rotate(T, w);
                    //����x���ֵܽڵ�
                    w = x->parent->right;
                }
                //���4 x���ֵܽڵ��Ǻ�ɫ��x���ֵܽڵ���Һ����Ǻ�ɫ��
                //���ֵܽڵ㻻�ɸ��ڵ����ɫ
                w->color = x->parent->color;
                //�Ѹ��������ֵܽڵ���Һ���Ϳ��
                w->parent->color = BLACK;
                w->right->color = BLACK;
                //�Ը��ڵ�����
                rbtree_left_rotate(T, x->parent);
                // ����xָ�룬ָ����ڵ�
                x = T->root;  //��������
            }
        }
        else //���xλ��x���ڵ���ұ�
        {
            rbtree_node* w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rbtree_right_rotate(T, x->parent);
                w = x->parent->left;
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {

                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbtree_left_rotate(T, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbtree_right_rotate(T, x->parent);

                x = T->root;
            }
        }
    }
    // �̳нڵ��Ϊ��ɫ��Ϊ���ֲ�ʧȥ�ĺڸ�
    x->color = BLACK;
}
//���ڵ���Ҫɾ�����ӽڵ�
rbtree_node* rbtree_delete(rbtree* T, rbtree_node* z)
{
    rbtree_node* y = T->nil;// yָ��Ҫɾ��/�ƶ��滻�Ľ��
    rbtree_node* x = T->nil;  //��������������ʱ��ת������ڵ�
    // 1,2���z����ڵ�����ҽڵ�Ϊ��
    if ((z->left == T->nil) || (z->right == T->nil))
    {
        y = z; //������Ҫ�ͷŵĽڵ�

    }
    else //ɾ���Ľڵ��������ڵ�
    {
        // ���ӽڵ����������ӣ��ú�̽ڵ��滻��ɾ���Ľڵ㣬����ת��Ϊɾ�������̽ڵ�
        
        //����z��λ��ȥ��ͬ��ֵ
        // z���нڵ㲻Ϊ�գ�ȡ�ұ���С��ֵ��Ϊɾ���ĵ�
        y = rbtree_twice(T, z); 
        // ��Ҫ�� y���ֵ��z��ֵ���� �� 3.2
    }
    // ������ӽڵ��ж����ӣ���ô���������ֱ�Ӽ̳�������λ��

    //��Ҫ�ͷŵ�y�����ӽڵ㣬xȡ���ӽڵ㸨��
    if (y->left != T->nil)
    {
        x = y->left;
    }
    else if (y->right != T->nil)
    {
        x = y->right;
    }

    // ���ڼ�λ�ڵ��parentָ��ָ��
    x->parent = y->parent;  //����ɾ���Ľڵ�y����û����Ϊ root->nil
    // ���ڸ��ڵ�ĺ���ָ��ָ��
    // 
    // y�ĸ��ڵ���ӽڵ㻥��λ��
    //���ڵ�λ��
    if (y->parent == T->nil)
    {
        // ���ڵ㽫��ɾ�������¸��ڵ�
        T->root = x;  //Ҫɾ���Ľڵ��Ǹ��ڵ㣬��x���ϸ��ڵ�
    }
    else if (y == y->parent->left)  //���ɾ���Ľڵ�λ�����
    {
        y->parent->left = x; 
    }
    else
    {
        y->parent->right = x;
    }

    // 3.2 ���y������������С�ڵ㣬�ͽ�y�ŵ�z��λ�ã�Ȼ��ɾ��ԭ����z
    if (y != z)
    {
        z->key = y->key;
        z->value = y->value;
    }

    //���ɾ���Ľڵ��Ǻ�ɫ�ģ���Ҫά��һ�º����������
    if (y->color == BLACK) //�ƻ��˺ڸ�
    {
        //��������������ڵ㣬��ǰҪɾ���Ľ��
        rbtree_delete_fixup(T, x);
    }
    return y;
}

//���ҽڵ�
rbtree_node* rbtree_search(rbtree* T, KEY_TYPE key)
{
    rbtree_node* node = T->root;
    while (node != T->nil)
    {
        if (key < node->key)
        {
            node = node->left;
        }
        else if (key > node->key)
        {
            node = node->right;
        }
        else
        {
            return node;  //���ز鵽�Ľڵ�
        }
    }
    return T->nil; //û���ҵ�
}

//�������  node������ʼ��ͷ���
void rbtree_traversal_center(rbtree* T, rbtree_node* node)
{
    if (node != T->nil)
    {
        rbtree_traversal_center(T, node->left);
        printf("key:%d,color:%d\n", node->key, node->color);
        rbtree_traversal_center(T, node->right);
    }
}
//ǰ�����  node������ʼ��ͷ���
void rbtree_traversal_front(rbtree* T, rbtree_node* node)
{
    if (node != T->nil)
    {
        printf("key:%d,color:%d\n", node->key, node->color);
        rbtree_traversal_front(T, node->left);
        rbtree_traversal_front(T, node->right);
    }
}
//ǰ�����  node������ʼ��ͷ���
void rbtree_traversal_tail(rbtree* T, rbtree_node* node)
{
    if (node != T->nil)
    {
        rbtree_traversal_tail(T, node->left);
        rbtree_traversal_tail(T, node->right);
        printf("key:%d,color:%d\n", node->key, node->color);
    }
}

int main()
{
    int keyArray[20] = { 24,25,13,35,23, 26,67,47,38,98, 20,19,17,49,12, 21,9,18,14,15 };
    rbtree* T = (rbtree*)malloc(sizeof(rbtree));
    if (T == NULL)
    {
        printf("malloc failed");
        return -1;
    }
    T->nil = (rbtree_node*)malloc(sizeof(rbtree_node));
    T->nil->color = BLACK;
    T->root = T->nil;

    rbtree_node* node = T->nil;
    int i = 0;
    for (i = 0; i < 20; i++)
    {
        node = (rbtree_node*)malloc(sizeof(rbtree_node));
        node->key = keyArray[i];
        node->value = NULL;

        rbtree_insert(T, node);
    }
    //�����������
    rbtree_traversal_center(T, T->root);
    printf("----------------------------------------\n");
    for (i = 0; i < 20; i++)
    {
        rbtree_node* node = rbtree_search(T, keyArray[i]);
        rbtree_node* cur = rbtree_delete(T, node);   
        free(cur);
        rbtree_traversal_center(T, T->root);
        printf("----------------------------------------\n");

    }

}