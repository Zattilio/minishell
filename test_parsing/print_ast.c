/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:32:42 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 12:41:06 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#define COUNT 10

t_node *make_node(int id, int token_type, char *token)
{
    t_node	*node;
	
	node = malloc(sizeof(t_node));
	node->id = id;
    node->token_type = token_type;
	node->token = token;
    node->left = NULL;
	node->right = NULL;
    return (node);
}
 
void print2DUtil(t_node *root, int space)
{
	if (root == NULL)
		return ;
	space += COUNT;
     // Process right child first
    print2DUtil(root->right, space);
     // Print current node after space
    // count
    printf("\n");
    /*for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->id);*/
	for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->token_type);
	for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s\n", root->token);
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print_ast(t_node *root)
{
    print2DUtil(root, 0);
}
 
// Driver program to test above functions
int main()
{
    t_node *root;
	
	root = make_node(1, TK_WORD, "word");
    root->left = make_node(2, TK_PIPE, "|");
    root->right = make_node(3, TK_AMP, "&");
 
    root->left->left = make_node(4, TK_INF, "<");
    root->left->right = make_node(5, TK_SUP, ">");
    root->right->left = make_node(6, TK_DOLLAR, "$");
    root->right->right = make_node(7, TK_SQUOTE, "\'");
 
    root->left->left->left = make_node(8, TK_WORD, "word");
    root->left->left->right = make_node(9, TK_DQUOTE, "\"");
    root->left->right->left = make_node(10, TK_WILDCARD, "*");
    root->left->right->right = make_node(11, TK_SUP, ">");
    root->right->left->left = make_node(12, TK_DOLLAR, "$");
    root->right->left->right = make_node(13, TK_INF, "<");
    root->right->right->left = make_node(14, TK_PIPE, "|");
 
    print_ast(root);
 
    return 0;
}