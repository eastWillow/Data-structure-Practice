#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM 
#define TREE_SIZE 50

struct Node {
        struct Node *left;
        struct Node *right;
        uint16_t data;
        uint16_t same;
};

struct Node* addLeaf( _In_ struct Node *parents, uint16_t newData );
struct Node* removeLeaf( _In_ struct Node *parents, uint16_t targetData );
void printTree( _In_ struct Node *root );

uint8_t main( void )
{
#ifndef RANDOM
        uint16_t data[20] = { 0,1,2,3,7,7,8,4,11,12, 4, 14, 15, 17,19 };
        size_t size = sizeof( data ) / sizeof( data[0] );
        uint16_t rand1 = 4;
        uint16_t rand2 = 14;
        uint16_t rand3 = 4;
#endif // !RANDOM
#ifdef RANDOM
        uint16_t data[TREE_SIZE];
        uint16_t size = sizeof( data ) / sizeof( data[0] );
        srand( time( NULL ) );
        for ( int i = 0; i < size; i++ ) {
                data[i] = rand( ) % size;
        }
        uint16_t rand1 = rand( ) % size;
        uint16_t rand2 = rand( ) % size;
        uint16_t rand3 = rand( ) % size;
#endif // RANDOM

        struct Node* root = ( struct Node* )malloc( sizeof( struct Node ) );
        root->left = NULL;
        root->right = NULL;
        root->data = NULL;
        root->same = 0;
        for ( int i = 0; i < size; i++ ) {
                addLeaf( root, data[i] );
        }

        printf( "\nOrignial Tree\n" );
        printTree( root );

        printf( "\nAfter Add these %d %d Leaf\n", 30, 2000 );
        addLeaf( root, 30 );
        addLeaf( root, 2000 );
        printTree( root );

        printf( "\nAfter delete these %d %d %d Leaf\n", rand1, rand2, rand3 );
        removeLeaf( root, rand1 );
        removeLeaf( root, rand2 );
        removeLeaf( root, rand3 );
        printTree( root );

        printf( "\nPause! Please press any button" );
        getchar( );
        return 0;
}
void printTree( _In_ struct Node* parents )
{
        if ( parents->left != NULL ) {
                printTree( parents->left );
                printf( "%d ", parents->data );
        }
        if ( parents->right != NULL ) {
                if ( parents->left == NULL ) {
                        printf( "%d ", parents->data );
                }
                printTree( parents->right );
        }
        if ( parents->left == NULL && parents->right == NULL ) {
                printf( "%d ", parents->data );
        }
}

struct Node* addLeaf( _In_ struct Node *parents, uint16_t newData )
{
        if ( newData < parents->data ) {
                if ( parents->left == NULL ) {
                        parents->left = ( struct Node* )malloc( sizeof( struct Node ) );
                        parents->left->data = newData;
                        parents->left->left = NULL;
                        parents->left->right = NULL;
                        parents->left->same = 0;
                        return parents->left;
                }
                else {
                        addLeaf( parents->left, newData );
                }
        }
        else if ( newData > parents->data ) {
                if ( parents->right == NULL ) {
                        parents->right = ( struct Node* )malloc( sizeof( struct Node ) );
                        parents->right->data = newData;
                        parents->right->left = NULL;
                        parents->right->right = NULL;
                        parents->right->same = 0;
                        return parents->right;
                }
                else {
                        addLeaf( parents->right, newData );
                }
        }
        else {
                parents->same += 1;
                return parents;
        }
        return NULL;
}

struct Node* removeLeaf( _In_ struct Node *parents, uint16_t targetData )
{
        if ( targetData < parents->data ) {
                if ( parents->left != NULL ) {
                        if ( removeLeaf( parents->left, targetData ) == parents->left ) {//Turn Left
                                parents->left = NULL;
                        }
                }
                else {
                        printf( "\nNot Found%d\n", targetData );
                }
        }
        else if ( targetData > parents->data ) {
                if ( parents->right != NULL ) {
                        if ( removeLeaf( parents->right, targetData ) == parents->right ) {//Turn Right
                                parents->right = NULL;
                        }
                }
                else {
                        printf( "\nNot Found%d\n", targetData );
                }
        }
        else {
                if ( parents->left != NULL && parents->right == NULL ) { //Only Left
                        struct Node* targetLeftLeaf = ( parents->left );
                        parents->data = targetLeftLeaf->data;
                        parents->right = targetLeftLeaf->right;
                        parents->left = targetLeftLeaf->left;
                        free( targetLeftLeaf );//free memory
                }
                else if ( parents->left == NULL && parents->right != NULL ) { //Only Right
                        struct Node* targetRightLeaf = ( parents->right );
                        parents->data = targetRightLeaf->data;
                        parents->right = targetRightLeaf->right;
                        parents->left = targetRightLeaf->left;
                        free( targetRightLeaf );//free memory
                }
                else if ( parents->left != NULL && parents->right != NULL ) { //Both Side
                        printf( "\nYou cannot remove%d", targetData );
                        printf( "\nUnder %d Have two side leaf Left:%d Right:%d\n",
                                targetData, ( parents->left )->data, ( parents->right )->data );
                }
                else if ( parents->left == NULL && parents->right == NULL ) { //No Any Leaf
                        free( parents );
                        return parents;
                }
        }
        return NULL;
}
