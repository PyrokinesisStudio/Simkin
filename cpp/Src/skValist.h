/*
  Copyright 1996-2001
  Simon Whiteside

* $Id: skValist.h,v 1.4 2001/03/05 16:46:28 sdw Exp $
*/

#ifndef skVALIST_H
#define skVALIST_H


#include "skGeneral.h"
#include "skBoundsException.h"
    
/**
 * This class gives a value and array-based list
 */
template <class T> class skTVAList 
{         
 public:
  /**
   * Default Constructor - creates an empty list
   */
  skTVAList();
  /**
   * Copy Constructor - copies the contents of the other list into this one
   */
  skTVAList(const skTVAList<T>&);
  /**
   * Constructor - taking initial size and growth increment for the list
   */
  skTVAList(USize initial_size,USize growth_increment);
  /**
   * Destructor
   */
  virtual ~skTVAList();					
  /**
   * Assignment operator - copies the contents of the other list
   */
  skTVAList& operator=(const skTVAList<T>&);
  /**
   * Clears this list
   */
  void	clear();					
  /**
   * Returns the number of entries in the list
   */
  USize entries() const;
  /**
   * deletes the nth item in the list
   * @exception skBoundsException is thrown if the index is invalid
   */
  void	deleteElt(USize  n);
  /**
   * Adds the given item to the start of the list
   */
  void	prepend(const T &t);
  /**
   * Inserts the given item *before* the specified index
   * @exception skBoundsException is thrown if the index is invalid
   */
  void	insert(const T &t,USize index);
  /**
   * adds the given item to the list
   */
  void	append(const T &t);
  /**
   * removes the given item from the list
   */
  void	remove(const T &t);	
  /**
   * retrieves the nth item from the list
   * @exception skBoundsException is thrown if the index is invalid
   * @return a reference to the item
   */
  T& operator[](USize  n) const;
  /**
   * returns the index of the item within the list.
   * @return the index, or -1 if not found
   */
  int index(const T &t) const;
  /**
   * checks if the given item is in the list
   * @return true if the list contains the item, otherwise false
   */
  bool	contains(const T &t) const;
  /**
   * instructs the list to grow to the given size (which must be greater than the current size). The existing items are copied across
   */
  void	growTo(USize new_size);
 protected:
  /**
   * returns the index of the given item in the list, or -1 if not found
   */
  int	findElt(const T &t) const;
  /**
   * grows the array that represents the list by the growth increment
   */
  void	grow();
  /**
   * the array used to represent the list
   */
  T*  m_Array;	
  /**
   * the size of the array
   */
  USize	m_ArraySize;
  /**
   * the number of items being used in the list
   */
  USize m_Entries;
  /**
   * the amount to grow the array by
   */
  USize m_GrowthIncrement;
};        
const int TVALIST_DEFAULT_SIZE = 0;					// so array not allocated until needed
const int TVALIST_DEFAULT_GROWTH_INCREMENT = 4;	// value of 0 means 'double in size'

#ifdef __gnuc__
#define TVALIST_PRE template <class T> 
#else
#define TVALIST_PRE template <class T> 
#endif


//-----------------------------------------------------------------
TVALIST_PRE inline skTVAList<T>::skTVAList()
     //-----------------------------------------------------------------
  :m_ArraySize(TVALIST_DEFAULT_SIZE),m_GrowthIncrement(TVALIST_DEFAULT_GROWTH_INCREMENT),m_Entries(0)
{
  if(TVALIST_DEFAULT_SIZE != 0)
    m_Array=new T[TVALIST_DEFAULT_SIZE];
  else
    m_Array = 0;		// don't allocate space until needed
}
//-----------------------------------------------------------------
TVALIST_PRE inline skTVAList<T>::skTVAList(USize initial_size,USize growth_increment)
     //-----------------------------------------------------------------
  :m_ArraySize(initial_size),m_GrowthIncrement(growth_increment),m_Entries(0)
{
  if(m_ArraySize != 0)
    m_Array=new T[m_ArraySize];
  else
    m_Array = 0;		// don't allocate space until needed
}
//-----------------------------------------------------------------
TVALIST_PRE inline skTVAList<T>::skTVAList(const skTVAList& l)
     //-----------------------------------------------------------------
  : m_ArraySize(l.m_ArraySize),m_Entries(l.m_Entries),m_GrowthIncrement(l.m_GrowthIncrement)
{
  if(m_ArraySize){
    m_Array=new T[m_ArraySize];
    for (USize x=0;x<m_Entries;x++)
      m_Array[x]=l.m_Array[x];
  }else
    m_Array = 0;
}
//-----------------------------------------------------------------
TVALIST_PRE inline skTVAList<T>::~skTVAList()
     //-----------------------------------------------------------------
{
  if(m_Array)
    delete [] m_Array;
}
//-----------------------------------------------------------------
TVALIST_PRE inline void skTVAList<T>::clear()
     //-----------------------------------------------------------------
{
  m_Entries=0;
  if(m_Array)
    delete [] m_Array;
  m_Array=0;
  m_ArraySize=0;
}
//-----------------------------------------------------------------
TVALIST_PRE inline USize skTVAList<T>::entries() const
     //-----------------------------------------------------------------
{
  return m_Entries;
}
//-----------------------------------------------------------------
TVALIST_PRE void skTVAList<T>::deleteElt(USize  n)
     //-----------------------------------------------------------------
{
  assert(n<m_Entries);
  if (n>=m_Entries)
    throw skBoundsException("Invalid index to DeleteElt",__FILE__,__LINE__);
  for (USize x=n;x<m_Entries-1;x++)
    m_Array[x]=m_Array[x+1];
  m_Entries--;
}
//-----------------------------------------------------------------
TVALIST_PRE void skTVAList<T>::insert(const T &t,USize index)
     //-----------------------------------------------------------------
{
  assert(index<=m_Entries);
  if (index>m_Entries)
    throw skBoundsException("Invalid index to Insert",__FILE__,__LINE__);
  if (m_ArraySize==m_Entries)
    grow();
  if (index<m_Entries){
    for (USize x=m_Entries;x>index;x--)
      m_Array[x]=m_Array[x-1];
  }
  m_Array[index]=t;
  m_Entries++;
}
//-----------------------------------------------------------------
TVALIST_PRE void skTVAList<T>::prepend(const T &t)
     //-----------------------------------------------------------------
{
  if (m_ArraySize==m_Entries)
    grow();
  m_Entries++;
  for (USize x=m_Entries-1;x>=1;x--)
    m_Array[x]=m_Array[x-1];
  m_Array[0]=t;
}
//-----------------------------------------------------------------
TVALIST_PRE inline void skTVAList<T>::append(const T &t)
     //-----------------------------------------------------------------
{
  if (m_ArraySize==m_Entries)
    grow();
  m_Array[m_Entries]=t;
  m_Entries++;
}
//-----------------------------------------------------------------
TVALIST_PRE void skTVAList<T>::remove(const T &t)
     //-----------------------------------------------------------------
{
  int index = findElt(t);
  assert(index>=0 && "VAList does not contain item"!=0);
  if (index>=0){
    for (USize x=(USize)index;x<m_Entries-1;x++)
      m_Array[x]=m_Array[x+1];

    m_Entries--;
  }
}
//-----------------------------------------------------------------
TVALIST_PRE inline T& skTVAList<T>::operator[](USize  n) const
     //-----------------------------------------------------------------
{
  assert(n<m_Entries);
  if (n>=m_Entries)
    throw skBoundsException("Invalid index to []",__FILE__,__LINE__);
  return m_Array[n];
}
//-----------------------------------------------------------------
TVALIST_PRE inline int skTVAList<T>::index(const T &t) const
     //-----------------------------------------------------------------
{
  return (USize)findElt(t);
}
//-----------------------------------------------------------------
TVALIST_PRE inline bool skTVAList<T>::contains(const T &t) const
     //-----------------------------------------------------------------
{
  return (bool)(findElt(t) >= 0);
}
//-----------------------------------------------------------------
TVALIST_PRE skTVAList<T>& skTVAList<T>::operator=(const skTVAList<T>& l)
     //-----------------------------------------------------------------
{
  if (&l!=this){
    clear();
    m_ArraySize=l.m_ArraySize;
    m_Entries=l.m_Entries;
    m_GrowthIncrement=l.m_GrowthIncrement;
    if(m_Entries){
      m_Array=new T[m_ArraySize];
      for (USize x=0;x<m_Entries;x++)		//??use memcopy for speed
	m_Array[x]=l.m_Array[x];
    }else{
      m_Array=0;	// don't allocate until needed
      m_ArraySize=0;
    }
  }
  return *this;
}
// Returns -1 if not found.
//-----------------------------------------------------------------
TVALIST_PRE inline int skTVAList<T>::findElt(const T &t) const
     //-----------------------------------------------------------------
{
  for (USize index=0;index<m_Entries;index++){
    if (m_Array[index]==t)
      return (int)index;		// jump out
  }
  return -1;
}
//-----------------------------------------------------------------
TVALIST_PRE void skTVAList<T>::grow()
     //-----------------------------------------------------------------
{
  if(m_GrowthIncrement != 0)
    m_ArraySize += m_GrowthIncrement;	// constant increase in size
  else{
    if(m_ArraySize==0)
      m_ArraySize = 1;
    else
      m_ArraySize *= 2;			// double size
  }

  T *  new_array=new T[m_ArraySize];
  if(m_Array){
    for (USize x=0;x<m_Entries;x++)		//??use memcopy for speed
      new_array[x]=m_Array[x];
    delete [] m_Array;
  }
  m_Array=new_array;
}
//-----------------------------------------------------------------
TVALIST_PRE void skTVAList<T>::growTo(USize new_size)
     //-----------------------------------------------------------------
{
  if (new_size>m_ArraySize){
    m_ArraySize=new_size;

    T *  new_array=new T[m_ArraySize];
    if(m_Array){
      for (USize x=0;x<m_Entries;x++)		//??use memcopy for speed
	new_array[x]=m_Array[x];
      delete [] m_Array;
    }
    m_Array=new_array;
  }
}

#endif