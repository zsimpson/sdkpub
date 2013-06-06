/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#ifdef WIN32

#ifdef  CVH_DECLARE_STORAGE

#ifndef CVH_STORAGE_DECLARED
#define CVH_STORAGE_DECLARED

template<class Val, class Idx> struct _CvTreeNode
{
    typedef  Val  value_type;
    typedef  Idx  idx_type;
    typedef  _CvTreeNode<value_type, idx_type> node_type;

    value_type  val;
    idx_type    idx;
    int         balance;
    node_type*  link[3]; /* links to nodes (left, right, up) */

    enum{ left  = 0,
          right = 1,
          up    = 2,
          center = 2 };

    _CvTreeNode()
        { link[0] = link[1] = link[2] = 0; idx = 0; balance = 0; val = 0; }
    node_type*&  next() { return link[0]; }
};


template<class Node> struct _CvNodeBlock
{
    typedef  Node  node_type;
    typedef  _CvNodeBlock<node_type>  block_type;

    enum { block_size = 4096, 
           block_nodes = sizeof(node_type) < block_size ?
                         block_size/sizeof(node_type) : 1 };

    _CvNodeBlock();

    node_type& operator[](int idx){ return data[idx]; }

    node_type      data[block_nodes];
    block_type*    next;
};

template<typename Node> class CvNodeIterator
{
public:
    typedef  Node                       node_type;
    typedef  node_type::value_type      value_type;
    typedef  node_type::idx_type        idx_type;
    typedef  CvNodeIterator<node_type> iterator;
    typedef  _CvNodeBlock<node_type>   block_type;

    value_type& operator *() const { return current_block->data[idx].val; }
    idx_type   get_idx() const { return current_block->data[idx].idx; }
    node_type* get_node() const { return &current_block->data[idx]; }
    
    iterator&  operator ++();  // prefix ++
    const iterator  operator ++(int); // postfix ++

    CvNodeIterator() { current_block = 0; idx = 0; }
    CvNodeIterator( block_type* _current_block )
        { current_block = _current_block; idx = 0; } 
    CvNodeIterator( block_type* _current_block, idx_type _idx )
        { current_block = _current_block; idx = _idx; }

    bool operator == ( const iterator& another ) const
        { return (current_block == another.current_block) && (idx == another.idx); }
    bool operator != ( const iterator& another ) const
        { return (current_block != another.current_block) || (idx != another.idx); }
 protected:
    block_type* current_block;
    idx_type    idx;
};

#endif
#endif


#ifdef  CVH_IMPLEMENT_STORAGE

#ifndef CVH_STORAGE_IMPLEMENTED
#define CVH_STORAGE_IMPLEMENTED

#include <math.h>

/****************************************************************************************\
*                            CvArray storage implementation                             *
\****************************************************************************************/

template <class Val> CvArray<Val>::CvArray( idx_type _size )
{
    _size = _size > 0 ? _size : 1;
    array = new value_type[_size];
    size = capacity = _size;
}


template <class Val> CvArray<Val>::CvArray( idx_type _size,
                                              idx_type _capacity )
{
    if( _size > _capacity ) _capacity = _size;

    size = _size;
    capacity = _capacity;
    array = new value_type[_capacity];
}


template <class Val> CvArray<Val>::CvArray( const storage& another )
{
    size = another.size;
    capacity = another.capacity;
    array = new value_type[capacity];

    for( idx_type i = 0; i < size; i++ ) array[i] = another.array[i];
}


template <class Val> CvArray<Val>& CvArray<Val>:: operator = ( const storage& another )
{
    /* Check for not empty storage */
    if( another.size > 0 && another.capacity > 0 && another.array != 0 )
    {
        size = another.size;
        capacity = another.capacity;
        delete array;
        array = new value_type[capacity];
        
        for( idx_type i = 0; i < size; i++ ) array[i] = another.array[i];
    }
    else /* If storage is empty */
    {
        size = 0;
        capacity = 0;
        if( array != 0 ) delete array;
        array = 0;
    }
    return *this;
}


template <class Val> CvArray<Val>::iterator CvArray<Val>::begin() const
{
    if( array != 0 ) return iterator( &array[0], &array[0] );
    else return iterator();
}


template <class Val> CvArray<Val>::iterator CvArray<Val>::end() const
{
    if( array != 0 ) return iterator( &array[0], &array[size - 1] );
    else return iterator();
}


template <class Val> CvArray<Val>::raw_iterator CvArray<Val>::raw_begin() const
{
    if( array != 0 ) return iterator( &array[0], &array[0] );
    else return iterator();
}


template <class Val> CvArray<Val>::raw_iterator CvArray<Val>::raw_end() const
{
    if( array != 0 ) return iterator( &array[0], &array[size - 1] );
    else return iterator();
}


template <class Val> void CvArray<Val>::clear()
{
    if( array == 0 ) return;
    for( idx_type i = 0; i < size; i++ ) array[i] = 0;
}


template <class Val> void CvArray<Val>::destroy()
{
    size = capacity = 0;
    if( array != 0 ) delete array;
    array = 0;
}


template <class Val> void CvArray<Val>::remove( idx_type idx )
{
    if( array != 0 && idx < size ) array[idx] = 0;
}


template <class Val> void CvArray<Val>::set_size( idx_type _size )
{
    if( _size < capacity )
    {
        for( idx_type i = size; i < _size; i++ ) {
            array[i] = value_type();
        }
        size = _size;
    }
    else
    {                                                            
        value_type* bak = new value_type[_size];
        for( idx_type i = 0; i < size; i++ ) bak[i] = array[i];
        for( i = size; i < _size; i++ ) bak[i] = value_type();
        size = capacity = _size;
        delete array;
        array = bak;                                  
    }
}


template <class Val> void CvArray<Val>::set_capacity( idx_type _capacity )
{
    if( size < _capacity )
    {
        value_type* bak = new value_type[_capacity];
        for( idx_type i = 0; i < size; i++ ) bak[i] = array[i];
        capacity = _capacity;
        delete array;
        array = bak;
    }
}


/****************************************************************************************\
*                               _CvNodeBlock implementation                             *
\****************************************************************************************/
template <class Node> _CvNodeBlock<Node>::_CvNodeBlock()
{
    next = 0;
    /* Links all nodes to next node */
    for( node_type::idx_type i = 0; i < block_nodes - 1; i++ )
        data[i].next() = &data[i + 1];
}


/****************************************************************************************\
*                             _CvNodeManager implementation                             *
\****************************************************************************************/
template <class Node> _CvNodeManager<Node>::_CvNodeManager()
{
    first_free  = 0;
    first_block = 0;
    last_block  = 0;
}


template <class Node> _CvNodeManager<Node>::node_type*
                      _CvNodeManager<Node>::allocate_new_block()
{
    if( last_block != 0 ) /* blocks present */
    {
        /* Making links in new block */
        last_block->next = new block_type;
        ((*last_block->next)[block_type::block_nodes - 1]).next() = first_free;
        
        /* Setting link to first/last block & node */
        last_block = last_block->next;
        first_free = &((*last_block)[0]);
    }
    else /* no blocks present */
    {
        first_block = last_block = new block_type;
        first_free = &((*first_block)[0]);
    }
    return &(*last_block)[0];
}


template <class Node> _CvNodeManager<Node>::node_type* _CvNodeManager<Node>::new_node()
{
    if( first_free == 0 ) first_free = allocate_new_block();
    node_type* _node = first_free;

    first_free = first_free->next();
    _node->link[0] = _node->link[1] = _node->link[2] = 0;
    return _node;
}


template <class Node> void _CvNodeManager<Node>::release_node( Node* _node )
{
    _node->link[1] = _node->link[2] = 0;
    _node->idx = 0;
    _node->balance = 0;
    _node->val = 0;
    _node->next() = first_free;
    first_free = _node;
}


template <class Node> void _CvNodeManager<Node>::destroy()
{
    block_type* _block = first_block;
    while( _block != 0 )
    {
        first_block = _block->next;
        delete _block;
        _block = first_block;
    }

    first_free = 0;
    first_block = 0;
    last_block = 0;
}


template <class Node> void _CvNodeManager<Node>::clear()
{
    if( first_block == 0 ) return;
    iterator iter_first( first_block, 1 );
    iterator iter_second( first_block );

    while( iter_first != iter_second )
        (iter_second++).get_node()->next() = (iter_first++).get_node();
}


/****************************************************************************************\
*                                    CvTree implementation                              *
\****************************************************************************************/
template <class Val, class Idx> CvTree<Val, Idx>::node_type*
            CvTree<Val, Idx>::create_node(CvTree<Val, Idx>::idx_type idx)
{
    assert( size == 0 || idx < size );

    if( root == 0 ) /* if tree is empty */
    {
        root = manager.new_node();
        root->idx = idx;
        root->balance = node_type::center;
        return root;
    }

    node_type* nodeA = root;
    node_type* nodeB;
    node_type* nodeC;

    if( root->idx == idx ) return root; /* if node exists alredy return this node */
    
    /* Find point, where this node must be placed */
    while( nodeA->link[idx > nodeA->idx] != 0 )
    {
        nodeA = nodeA->link[idx > nodeA->idx];
        if( nodeA->idx == idx ) return nodeA; /* if node exists alredy return this node */
    }
    if( nodeA->idx == idx ) return nodeA; /* if node exists alredy return this node */

    node_type* node = manager.new_node();
    node->link[node_type::up] = nodeA;
    node->idx = idx;
    node->balance = node_type::center;
    nodeA->link[idx > nodeA->idx] = node;

    /* Balancing tree :( */
    do{
        switch( nodeA->balance )
        {
        case node_type::left:
            if( idx > nodeA->idx )
            {
                nodeA->balance = node_type::center;
                return node;
            }
            else /* idx < nodeA->idx */
            {
                nodeB = nodeA->link[node_type::left];
                switch( nodeB->balance )
                {
                case node_type::left:
                    nodeA->link[node_type::left] = nodeB->link[node_type::right];
                    if( nodeA->link[node_type::left] != 0 )
                        nodeA->link[node_type::left]->link[node_type::up] = nodeA;
                    nodeB->link[node_type::right] = nodeA;
                    nodeB->link[node_type::up] = nodeA->link[node_type::up];
                    nodeA->link[node_type::up] = nodeB;
                    nodeA->balance = nodeB->balance = node_type::center;
                    if( nodeB->link[node_type::up] != 0 )
                        nodeB->link[node_type::up]->
                        link[idx > nodeB->link[node_type::up]->idx] = nodeB;
                    else root = nodeB;
                    return node;
                case node_type::right:
                    nodeC = nodeB->link[node_type::right];
                    nodeC->link[node_type::up] = nodeA->link[node_type::up];
                    nodeA->link[node_type::left] = nodeC->link[node_type::right];
                    if( nodeA->link[node_type::left] != 0 )
                        nodeA->link[node_type::left]->link[node_type::up] = nodeA;
                    nodeB->link[node_type::right] = nodeC->link[node_type::left];
                    if( nodeB->link[node_type::right] != 0 )
                        nodeB->link[node_type::right]->link[node_type::up] = nodeB;
                    nodeC->link[node_type::right] = nodeA;
                    nodeC->link[node_type::left] = nodeB;
                    nodeA->link[node_type::up] = nodeB->link[node_type::up] = nodeC;
                    nodeA->balance = 2 - (idx < nodeC->idx);
                    nodeB->balance = (idx <= nodeC->idx) << 1;
                    nodeC->balance = node_type::center;
                    if( nodeC->link[node_type::up] != 0 )
                        nodeC->link[node_type::up]->
                        link[idx > nodeC->link[node_type::up]->idx] = nodeC;
                    else root = nodeC;
                    return node;
                default:
                    assert( 0 );
                    return node;
                } /* switch */
            } /* if( idx > nodeA->idx ) */
        case node_type::center:
            nodeA->balance = idx > nodeA->idx;
            break;
        case node_type::right:
            if( idx < nodeA->idx )
            {
                nodeA->balance = node_type::center;
                return node;
            }
            else /* idx > nodeA->idx */
            {
                nodeB = nodeA->link[node_type::right];
                switch( nodeB->balance )
                {
                case node_type::right:
                    nodeA->link[node_type::right] = nodeB->link[node_type::left];
                    if( nodeA->link[node_type::right] != 0 )
                        nodeA->link[node_type::right]->link[node_type::up] = nodeA;
                    nodeB->link[node_type::left] = nodeA;
                    nodeB->link[node_type::up] = nodeA->link[node_type::up];
                    nodeA->link[node_type::up] = nodeB;
                    nodeA->balance = nodeB->balance = node_type::center;
                    if( nodeB->link[node_type::up] != 0 )
                        nodeB->link[node_type::up]->
                        link[idx > nodeB->link[node_type::up]->idx] = nodeB;
                    else root = nodeB;
                    return node;
                case node_type::left:
                    nodeC = nodeB->link[node_type::left];
                    nodeC->link[node_type::up] = nodeA->link[node_type::up];
                    nodeA->link[node_type::right] = nodeC->link[node_type::left];
                    if( nodeA->link[node_type::right] != 0 )
                        nodeA->link[node_type::right]->link[node_type::up] = nodeA;
                    nodeB->link[node_type::left] = nodeC->link[node_type::right];
                    if( nodeB->link[node_type::left] != 0 )
                        nodeB->link[node_type::left]->link[node_type::up] = nodeB;
                    nodeC->link[node_type::left] = nodeA;
                    nodeC->link[node_type::right] = nodeB;
                    nodeA->link[node_type::up] = nodeB->link[node_type::up] = nodeC;
                    nodeA->balance = (idx <= nodeC->idx) << 1;
                    nodeB->balance = 2 - (idx < nodeC->idx);
                    nodeC->balance = node_type::center;
                    if( nodeC->link[node_type::up] != 0 )
                        nodeC->link[node_type::up]->
                        link[idx > nodeC->link[node_type::up]->idx] = nodeC;
                    else root = nodeC;
                    return node;
                default:
                    assert( 0 );
                    return node;
                } /* switch */
            } /* if( idx < nodeA->idx ) */
        } /* switch */
    }while( (nodeA = nodeA->link[node_type::up]) != 0 );
    return node;
} /* CvTree<Val, Idx>::create_node */


template <class Val, class Idx> CvTree<Val, Idx>::value_type
                        CvTree<Val, Idx>::query( CvTree<Val, Idx>::idx_type idx ) const
{
    assert( size == 0 || idx < size );
    node_type* node = root;
    while( node != 0 )
    {
        if( node->idx == idx ) return node->val;
        node = node->link[idx > node->idx];
    }
    return 0;
}


template <class Val, class Idx> void CvTree<Val, Idx>::remove( idx_type idx )
{
    assert( size == 0 || idx < size );

    node_type* nodeA = root;
    node_type* nodeB;
    node_type* nodeC;

    /* Find node to be removed */
    while( nodeA != 0 && nodeA->idx != idx ) nodeA = nodeA->link[idx > nodeA->idx];

    /* If node not found return */
    if( nodeA == 0 ) return;

    /* Find node to be placed on deleted node */
    switch( nodeA->balance )
    {
    case node_type::left:
        /* Find top right node */
        assert( nodeA->link[node_type::left] != 0 );
        nodeB = nodeA->link[node_type::left];
        while( nodeB->link[node_type::right] != 0 ) nodeB = nodeB->link[node_type::right];
        break;
    case node_type::right:
        /* Find top left node */
        assert( nodeA->link[node_type::right] != 0 );
        nodeB = nodeA->link[node_type::right];
        while( nodeB->link[node_type::left] != 0 ) nodeB = nodeB->link[node_type::left];
        break;
    case node_type::center:
        /* Is this node terminal ? */
        assert( !((nodeA->link[node_type::left] != 0) ^
                  (nodeA->link[node_type::right] != 0)) );
        if( nodeA->link[node_type::right] != 0 ) /* non terminal node */
        {
            /* Select left branch & find top right node*/
            nodeB = nodeA->link[node_type::left];
            while( nodeB->link[node_type::right] != 0 )
                nodeB = nodeB->link[node_type::right];
        }
        else nodeB = nodeA; /* terminal node */
        break;
    default:
        assert( 0 );
        return;
    }

    /* Copying nodeB to nodeA (replacing node) */
    if( nodeB->link[node_type::up] != 0 )
    {
        nodeB->link[node_type::up]->link[nodeB->idx>nodeB->link[node_type::up]->idx] = 
            nodeB->link[nodeA->balance == node_type::right];
        if( nodeB->link[nodeA->balance == node_type::right] != 0 )
            nodeB->link[nodeA->balance == node_type::right]->link[node_type::up] =
            nodeB->link[node_type::up];
    }
    else /* Deleted node is root node and last */
    {
        root = 0;
        manager.release_node( nodeB );
        return;
    }
    nodeA->idx = nodeB->idx;
    nodeA->val = nodeB->val;
    nodeA = nodeB->link[node_type::up];
    idx = nodeB->idx;
    manager.release_node( nodeB );

    /* Balancing tree :(E3) */
    do{
        switch( nodeA->balance )
        {
        case node_type::left:
            if( idx <= nodeA->idx )
            {
                nodeA->balance = node_type::center;
                break;
            }
            else
            {
                nodeB = nodeA->link[node_type::left];
                switch( nodeB->balance )
                {
                case node_type::left:
                case node_type::center:
                    nodeA->link[node_type::left] = nodeB->link[node_type::right];
                    if( nodeA->link[node_type::left] != 0 )
                        nodeA->link[node_type::left]->link[node_type::up] = nodeA;
                    nodeB->link[node_type::right] = nodeA;
                    nodeB->link[node_type::up] = nodeA->link[node_type::up];
                    nodeA->link[node_type::up] = nodeB;
                    nodeA->balance = 2 - nodeB->balance;
                    nodeB->balance = 2 - (nodeB->balance == node_type::center);
                    if( nodeB->link[node_type::up] != 0 )
                        nodeB->link[node_type::up]->
                        link[nodeB->idx > nodeB->link[node_type::up]->idx] = nodeB;
                    else root = nodeB;
                    nodeA = nodeB;
                    continue;
                case node_type::right:
                    nodeC = nodeB->link[node_type::right];
                    nodeC->link[node_type::up] = nodeA->link[node_type::up];
                    nodeA->link[node_type::left] = nodeC->link[node_type::right];
                    if( nodeA->link[node_type::left] != 0 )
                        nodeA->link[node_type::left]->link[node_type::up] = nodeA;
                    nodeB->link[node_type::right] = nodeC->link[node_type::left];
                    if( nodeB->link[node_type::right] != 0 )
                        nodeB->link[node_type::right]->link[node_type::up] = nodeB;
                    nodeC->link[node_type::right] = nodeA;
                    nodeC->link[node_type::left] = nodeB;
                    nodeA->link[node_type::up] = nodeB->link[node_type::up] = nodeC;
                    nodeA->balance = (nodeC->balance != node_type::left) + 1;
                    nodeB->balance = (nodeC->balance != node_type::right) << 1;
                    nodeC->balance = node_type::center;
                    if( nodeC->link[node_type::up] != 0 )
                        nodeC->link[node_type::up]->
                        link[idx > nodeC->link[node_type::up]->idx] = nodeC;
                    else root = nodeC;
                    nodeA = nodeC;
                    continue;
                default:
                    assert( 0 );
                    return;
                } /* switch( nodeB->balance ) */
            } /* else */
            break;
        case node_type::right:
            if( idx >= nodeA->idx )
            {
                nodeA->balance = node_type::center;
                break;
            }
            else /* idx > nodeA->idx */
            {
                nodeB = nodeA->link[node_type::right];
                switch( nodeB->balance )
                {
                case node_type::right:
                case node_type::center:
                    nodeA->link[node_type::right] = nodeB->link[node_type::left];
                    if( nodeA->link[node_type::right] != 0 )
                        nodeA->link[node_type::right]->link[node_type::up] = nodeA;
                    nodeB->link[node_type::left] = nodeA;
                    nodeB->link[node_type::up] = nodeA->link[node_type::up];
                    nodeA->link[node_type::up] = nodeB;
                    nodeA->balance = 2 - (nodeB->balance == node_type::center);
                    nodeB->balance = (nodeB->balance == node_type::right) << 1;
                    if( nodeB->link[node_type::up] != 0 )
                        nodeB->link[node_type::up]->
                        link[idx >= nodeB->link[node_type::up]->idx] = nodeB;
                    else root = nodeB;
                    nodeA = nodeB;
                    continue;
                case node_type::left:
                    nodeC = nodeB->link[node_type::left];
                    nodeC->link[node_type::up] = nodeA->link[node_type::up];
                    nodeA->link[node_type::right] = nodeC->link[node_type::left];
                    if( nodeA->link[node_type::right] != 0 )
                        nodeA->link[node_type::right]->link[node_type::up] = nodeA;
                    nodeB->link[node_type::left] = nodeC->link[node_type::right];
                    if( nodeB->link[node_type::left] != 0 )
                        nodeB->link[node_type::left]->link[node_type::up] = nodeB;
                    nodeC->link[node_type::left] = nodeA;
                    nodeC->link[node_type::right] = nodeB;
                    nodeA->link[node_type::up] = nodeB->link[node_type::up] = nodeC;
                    nodeA->balance = (nodeC->balance != node_type::right) << 1;
                    nodeB->balance = (nodeC->balance != node_type::left) + 1;
                    nodeC->balance = node_type::center;
                    if( nodeC->link[node_type::up] != 0 )
                        nodeC->link[node_type::up]->
                        link[idx >= nodeC->link[node_type::up]->idx] = nodeC;
                    else root = nodeC;
                    nodeA = nodeC;
                    continue;
                default:
                    assert( 0 );
                    return;
                } /* switch( nodeB->balance ) */
                break;
            }
        case node_type::center:
            nodeA->balance = idx <= nodeA->idx;
            break;
        } /* switch( nodeA->balance ) */
    }while( idx = nodeA->idx, nodeA->balance == node_type::center &&
           (nodeA = nodeA->link[node_type::up]) != 0 );
}


template <class Val, class Idx> CvTree<Val, Idx>::iterator
                                CvTree<Val, Idx>::begin() const
{
    node_type* node = root;
    if( node == 0 ) return CvTreeIterator<node_type>( node );
    while( node->link[node_type::left] != 0 ) node = node->link[node_type::left];
    return CvTreeIterator<node_type>( node );
}


template <class Val, class Idx> CvTree<Val, Idx>::iterator
                                CvTree<Val, Idx>::end() const
{
    node_type* node = root;
    if( node == 0 ) return CvTreeIterator<node_type>( node );
    while( node->link[node_type::right] != 0 ) node = node->link[node_type::right];
    return CvTreeIterator<node_type>( node );
}


template <class Val, class Idx> CvTree<Val, Idx>::storage&
                                CvTree<Val, Idx>::operator =( const storage& another )
{
    clear();
    if( another.get_root() == 0 ) return *this;

    iterator iter = another.begin();
    iterator end = another.end();

    while( iter != end )
    {
        (*this)[iter.get_idx()] = *iter;
        iter++;
    }
    (*this)[iter.get_idx()] = *iter;

    return *this;
}


/****************************************************************************************\
*                                CvNodeIterator implementation                          *
\****************************************************************************************/
template <class Node> CvNodeIterator<Node>::iterator& CvNodeIterator<Node>::operator++()
{
    if( idx < block_type::block_nodes - 1 ) idx++;
    else if( current_block->next != 0 )
    {
        current_block = current_block->next;
        idx = 0;
    }
    return *this;
}


template <class Node> const CvNodeIterator<Node>::iterator
                            CvNodeIterator<Node>::operator++(int)
{
    iterator temp = *this;
    if( idx < block_type::block_nodes - 1 ) idx++;
    else if( current_block->next != 0 )
    {
        current_block = current_block->next;
        idx = 0;
    }
    return temp;
}


/****************************************************************************************\
*                                CvTreeIterator implementation                            *
\****************************************************************************************/
template <class Node> CvTreeIterator<Node>::node_type* CvTreeIterator<Node>::next()
{
    node_type* temp;

    if( node->link[node_type::right] != 0 )
    {
        temp = node->link[node_type::right];
        while( temp->link[node_type::left] != 0 ) temp = temp->link[node_type::left];
        return node = temp;
    }

    temp = node;

    while( temp->link[node_type::up] != 0 )
    {
        if( temp->idx < temp->link[node_type::up]->idx ) break;
        temp = temp->link[node_type::up];
    }

    if( temp->link[node_type::up] == 0 ) return node;

    node = temp->link[node_type::up];
    return node;
}


template <class Node> CvTreeIterator<Node>::iterator
                      CvTreeIterator<Node>::operator++()
{
    next();
    return *this;
}


template <class Node> CvTreeIterator<Node>::iterator
                      CvTreeIterator<Node>::operator++(int)
{
    iterator temp = *this;
    next();
    return temp;
}


/****************************************************************************************\
*                                  CVHistogram imlpementation                           *
\****************************************************************************************/
template <class Storage> void
                      CVHistogram<Storage>::create( int bins0, int bins1, int bins2,
                                                     int bins3, int bins4, int bins5 )
{
    mbins[0] = 1;
    mbins[1] = bins1;
    mbins[2] = mbins[1] * bins2;
    mbins[3] = mbins[2] * bins3;
    mbins[4] = mbins[3] * bins4;
    mbins[5] = mbins[4] * bins5;

    bins[0] = bins0;
    bins[1] = bins1;
    bins[2] = bins2;
    bins[3] = bins3;
    bins[4] = bins4;
    bins[5] = bins5;

    storage.clear();

    if( bins0 == 0 ) {dims = 0; return;}
    if( bins1 == 0 ) {dims = 1; storage.set_size( bins0 ); return;}
    if( bins2 == 0 ) {dims = 2; storage.set_size( bins0 * mbins[1] ); return;}
    if( bins3 == 0 ) {dims = 3; storage.set_size( bins0 * mbins[2] ); return;}
    if( bins4 == 0 ) {dims = 4; storage.set_size( bins0 * mbins[3] ); return;}
    if( bins5 == 0 ) {dims = 5; storage.set_size( bins0 * mbins[4] ); return;}
    dims = 6;
    storage.set_size( (idx_type)bins0 * mbins[5] );
}


template<class Storage> void CVHistogram<Storage>::normalize( value_type norm_factor )
{
    double sum = 0;

    iterator iter = begin();
    iterator _end = end();
    do
    {
        sum += *iter;
    }while( iter++ != _end );

    if( sum == 0 ) return;

    sum = 1.0 / sum * norm_factor;

    raw_iterator raw_iter = raw_begin();
    raw_iterator _raw_end = raw_end();
    do
    {
        *raw_iter = (value_type)(sum * (*raw_iter));
    }while( raw_iter++ != _raw_end );
}


template<class Storage> void CVHistogram<Storage>::
                        normalize( histogram& result, value_type norm_factor ) const
{
    double sum = 0;

    iterator iter = begin();
    iterator bak = iter;
    iterator _end = end();
    do
    {
        sum += *iter;
    }while( iter++ != _end );

    if( sum == 0 ) return;

    sum = 1.0 / sum * norm_factor;

    result.clear();

    iter = bak;
    do
    {
        result[iter.get_idx()] = (value_type)(sum * (*iter));
    }while( iter++ != _end );
}


template<class Storage> void CVHistogram<Storage>::threshold( value_type threshold )
{
    raw_iterator iter = raw_begin();
    raw_iterator _raw_end = raw_end();

    do
    {
        *iter = (value_type)(*iter >= threshold ? *iter : 0);
    }while( iter++ != _raw_end );
}


template<class Storage> void 
    CVHistogram<Storage>::threshold( value_type threshold, histogram& result )
{
    raw_iterator iter = raw_begin();
    raw_iterator _raw_end = raw_end();

    result.clear();

    do
    {
        result[iter.get_idx()] = (value_type)(*iter >= threshold ? *iter : 0);
    }while( iter++ != _raw_end );
}


template<class Storage> CVHistogram<Storage>::histogram&
    CVHistogram<Storage>::operator =( const histogram& another )
{
    raw_iterator iter = another.raw_begin();
    raw_iterator _raw_end = another.raw_end();

    create( another.bins[0], another.bins[1], another.bins[2], 
            another.bins[3], another.bins[4], another.bins[5] );

    if( &(*iter) == 0 ) return *this;
    do
    {
        (*this)[iter.get_idx()] = *iter;
    }while( iter++ != _raw_end );

    return *this;
}


template<class Storage> CVHistogram<Storage>::histogram&
    CVHistogram<Storage>::operator -= ( value_type val )
{
    raw_iterator iter = raw_begin();
    raw_iterator _end = raw_end();

    do
    {
        *iter = (value_type)(*iter > val ? *iter - val : 0);
    }while(iter++ != _end);

    return *this;
}


template<class Storage> CVHistogram<Storage>::histogram&
    CVHistogram<Storage>::operator *= ( value_type val )
{
    raw_iterator iter = raw_begin();
    raw_iterator _end = raw_end();

    do *iter = (value_type)(*iter * val); while(iter++ != _end);

    return *this;
}


template<class Storage> double CVHistogram<Storage>::mean() const
{
    iterator iter = begin();
    iterator _end = end();

    double s = 0;

    do
    s += *iter;
    while(iter++ != _end);

    return s / (bins[0] * mbins[dims - 1]);
}


template<class Storage> CVHistogram<Storage>::value_type&
    CVHistogram<Storage>::operator () (const int* idxs)
{
    switch( dims )
    {
    case 1:
        return (*this)(idxs[0]);
    case 2:
        return (*this)(idxs[0], idxs[1]);
    case 3:
        return (*this)(idxs[0], idxs[1], idxs[2]);
    case 4:
        return (*this)(idxs[0], idxs[1], idxs[2], idxs[3]);
    case 5:
        return (*this)(idxs[0], idxs[1], idxs[2], idxs[3], idxs[4]);
    case 6:
        return (*this)(idxs[0], idxs[1], idxs[2], idxs[3], idxs[4], idxs[5]);
    default:
        assert( 0 );
        return (*this)[*idxs];
    }
}


template<class Storage> CVHistogram<Storage>::value_type
    CVHistogram<Storage>::query(const int* idxs) const
{
    switch( dims )
    {
    case 0:
        return 0;
    case 1:
        return (*this).query(idxs[0]);
    case 2:
        return (*this).query(idxs[0], idxs[1]);
    case 3:
        return (*this).query(idxs[0], idxs[1], idxs[2]);
    case 4:
        return (*this).query(idxs[0], idxs[1], idxs[2], idxs[3]);
    case 5:
        return (*this).query(idxs[0], idxs[1], idxs[2], idxs[3], idxs[4]);
    case 6:
        return (*this).query(idxs[0], idxs[1], idxs[2], idxs[3], idxs[4], idxs[5]);
    default:
        assert( 0 );
        return 0;
    }
}


/****************************************************************************************\
*                            Histogram calculation functions                             *
\****************************************************************************************/

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    CvCalculateC1  
//    Purpose: Calculating the histogram from C1 data type
//    Context:   
//    Parameters:
//      hist   - destination histogram
//      src    - source image
//      roi    - region fo interest
//      step   - width step
//      thresh - threshold values for each dimension of histogram
//    Returns:   
//    Notes:     
//F*/
template<class Histogram, class SrcType, class ThreshType> void
    CvCalculateC1( Histogram&   hist,
                    SrcType**    src,
                    CvSize      roi,
                    int          step,
                    ThreshType** thresh )
{
    assert( roi.width * (int)sizeof( SrcType ) <= step );

    int offset = 0;
    step /= sizeof( SrcType );


    for( int y = 0; y < roi.height; y++ )
    {
        for( int x = 0; x < roi.width; x++ )
        {
            int addr[Histogram::max_dims];
            for( int plan = 0; plan < hist.get_dims(); plan++ )
            {
                SrcType p = src[plan][offset + x];
                int nums = hist.get_dim_size(plan);

                if( p < thresh[plan][0] || p > thresh[plan][nums] ) goto _next_point;
                for( int num = 1; num < nums; num++ )
                    if( p <= thresh[plan][num] ) break;
                addr[plan] = num - 1;
            }
            hist(addr)++;
_next_point:;
        }
        offset += step;
    }
}


template<class Histogram, class SrcType, class ThreshType, class DstType> void 
    CvBackProject( Histogram&   hist,
                    SrcType**    src,
                    CvSize      roi,
                    int          src_step,
                    ThreshType** thresh,
                    DstType*     measure,
                    int          dst_step,
                    DstType      threshold )
{
    assert( roi.width * (int)sizeof( SrcType ) <= src_step );
    assert( roi.width * (int)sizeof( DstType ) <= dst_step );

    int src_offset = 0;
    int dst_offset = 0;
    src_step /= sizeof( SrcType );
    dst_step /= sizeof( DstType );

    for( int y = 0; y < roi.height; y++ )
    {
        for( int x = 0; x < roi.width; x++ )
        {
            int addr[Histogram::max_dims];
            for( int plan = 0; plan < hist.get_dims(); plan++ )
            {
                SrcType p = src[plan][src_offset + x];
                int nums = hist.get_dim_size(plan);

                if( p < thresh[plan][0] || p > thresh[plan][nums] )
                {
                    measure[dst_offset + x] = 0;
                    goto _next_point;
                }
                for( int num = 1; num < nums; num++ )
                    if( p <= thresh[plan][num] ) break;
                addr[plan] = num - 1;
            }
            measure[dst_offset + x] = (DstType)(hist.query(addr));
            if( measure[dst_offset + x] < threshold ) measure[dst_offset + x] = 0;
_next_point:;
        }
        src_offset += src_step;
        dst_offset += dst_step;
    }
}

/****************************************************************************************\
*                                  Operations implementation                             *
\****************************************************************************************/

/****************************************************************************************\
*                                       Intersection                                     *
\****************************************************************************************/
class Intersection
{
public:
    typedef double result_type;

    template<class Val> double operator () ( double s, const Val val1, const Val val2 )
        { return s + (val1 > val2 ? val2 : val1); }
};

template <class Hist> inline double calc_histogram_intersection( const Hist& hist1,
                                                                 const Hist& hist2 )
{ return hist1.operate_with( hist2, Intersection() ); }

/****************************************************************************************\
*                                       ChiSqr                                           *
\****************************************************************************************/
class ChiSqr
{
public:
    typedef double result_type;

    template<class Val> double operator () ( double s, Val val1, Val val2 )
    { return s + (double)(val1 - val2) * (val1 - val2) / (val1 + val2); }
};

template <class Hist> inline double calc_histogram_chi_square( const Hist& hist1,
                                                               const Hist& hist2 )
{ return hist1.operate_with( hist2, ChiSqr() ); }

/****************************************************************************************\
*                                       Correl                                           *
\****************************************************************************************/
class _Correl
{
public:
    double Nom;
    double DeNom1, DeNom2;

    _Correl( double val ) { Nom = DeNom1 = DeNom2 = val; }
    void operator=( double val ) { Nom = DeNom1 = DeNom2 = val; }
    operator double() { return Nom / sqrt( DeNom1 * DeNom2 ); }
};

class Correl
{
public:
    typedef _Correl result_type;

    Correl() { mean1 = mean2 = 0; }
    Correl( double _mean1, double _mean2 = 0 ) { mean1 = _mean1; mean2 = _mean2; }

    template<class Val> result_type operator () ( result_type s, Val val1, Val val2 )
        {
            double v1 = val1 - mean1;
            double v2 = val2 - mean2;
            s.Nom += v1 * v2;
            s.DeNom1 += v1 * v1;
            s.DeNom2 += v2 * v2;
            return s;
        }
protected:
    double mean1;
    double mean2;
};

template <class Hist> inline double calc_histogram_correlation( const Hist& hist1,
                                                                const Hist& hist2 )
{ return hist1.operate_with( hist2, Correl( hist1.mean(), hist2.mean() ) ); }

#endif
#endif

#endif /* WIN32 */

/* End of file. */
