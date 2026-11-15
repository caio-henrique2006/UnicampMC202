struct No
{
    int key;
    struct No *left;
    struct No *right;
};

int identifica_avl(struct No *raiz)
{
    int h_right = percorre_avl(raiz->right);
    int h_left = percorre_avl(raiz->left);
    if (h_right - h_left < 2 && h_right - h_left > -2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int percorre_avl(struct No *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    int h_right = percorre_avl(raiz->right);
    int h_left = percorre_avl(raiz->left);

    if (h_right > h_left)
    {
        return h_right + 1;
    }
    else
    {
        return h_left + 1;
    }
}