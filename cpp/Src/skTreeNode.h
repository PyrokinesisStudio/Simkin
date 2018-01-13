/*
  Copyright 1996-2001
  Simon Whiteside

 * $Id: skTreeNode.h,v 1.7 2001/03/05 16:46:28 sdw Exp $
*/


#ifndef TREENODE_H
#define TREENODE_H

#include "skString.h"

class  skTreeNode;
class  skTreeNodeList;

/**
 * This class provides an iterator over the children of a treenode
 */
class  skTreeNodeListIterator 
{
 public:
  /**
   * Constructor - creates an iterator for the given treenode
   */
  skTreeNodeListIterator(const skTreeNode&);
  /**
   * Default constructor
   */
  ~skTreeNodeListIterator();
  /**
   * returns the next child of the treenode
   */
  skTreeNode * operator ()();
  /**
   * resets the iteration to the start of the list of children in the treenode
   */
  void reset();
 private:
  const skTreeNode& m_Node;
  USize	m_Index;
};

/**
 * This class encapsulates a node in a tree.
 * The node has a label, a piece of data and a list of subitems
*/
class  skTreeNode 
{
 public:
  /**
   * Default Constructor - blank label, data and an empty children list
   */
  skTreeNode();
  /**
   * Destructor
   */
  virtual ~skTreeNode();
  /**
   * Copy Constructor - does a deep copy
   */
  skTreeNode(const skTreeNode& );
  /**
   * Constructor - creates a treenode with the given label
   */
  skTreeNode(const skString& label); 
  /**
   * Constructor - creates a treenode with the given label and data
   */
  skTreeNode(const skString& label,const skString& data);
  /**
   * Constructor - creates a treenode with the given label and data (converted to a string form)
   */
  skTreeNode(const skString& label,bool data);
  /**
   * Constructor - creates a treenode with the given label and data (converted to a string form)
   */
  skTreeNode(const skString& label,int  data);
  /**
   * Constructor - creates a treenode with the given label and data (converted to a string form)
   */
  skTreeNode(const skString& label,long data);
  /**
   * Constructor - creates a treenode with the given label and data (converted to a string form)
   */
  skTreeNode(const skString& label,float data);
  /**
   * Assignment operator - does a deep copy
   */
  skTreeNode& operator=(const skTreeNode& );
  /**
   * Returns this node's label
   */
  skString label() const;
  /**
   * Changes this node's label
   */
  void  label(const skString& s);
  /**
   * Returns this node's data
   */
  skString data() const;
  /**
   * Changes this node's data
   */
  void  data(const skString& s);
  /**
   * Returns this node's data as a boolean value
   */
  bool	boolData() const;
  /**
   * Changes this node's data - converting the value to a string
   */
  void	boolData(bool);
  /**
   * Returns this node's data as an integer value
   */
  int 	intData() const;
  /**
   * Changes this node's data - converting the value to a string
   */
  void	intData(int);
  /**
   * Returns this node's data as a long integer value
   */
  long  longData() const;
  /**
   * Changes this node's data - converting the value to a string
   */
  void	longData(long);
  /**
   * Returns this node's data as a float value
   */
  float floatData() const;
  /**
   * Changes this node's data - converting the value to a string
   */
  void	floatData(float);
  /**
   * adds the given node to the start of the child list for this node
   */
  void  prependChild(skTreeNode*);
  /**
   * adds the given node to the end of the child list for this node
   */
  void  addChild(skTreeNode*);
  /**
   * Assigns the given node to the first node with the matching label in the child list of this node. If no match is found, the node is added to the end of the list
   */
  void  setChild(skTreeNode*);	
  /**
   * deletes the given node from the list of children at this node
   */
  void  deleteChild(skTreeNode*);
  /**
   * Returns true if the child list of this node contains the given node
   */
  bool	containsChild(skTreeNode*);
  /**
   * This method searches for a node whose label matches the one given
   * @return the first match, or 0 if none found
   */
  skTreeNode* findChild(const skString& label) const;
  /**
   * This method searches for a node whose label and data matches the ones given
   * @return the first match, or 0 if none found
   */
  skTreeNode* findChild(const skString& label,const skString& data) const;
  /**
   * Finds the data associated with the first child whose label matches that given
   * @param label - the label to look for
   * @param defaultVal - the value to return if a match is not found
   * @return the value of a matched child's data, or the default value
   */
  skString findChildData(const skString& label,const skString& defaultVal) const;
  /**
   * Finds the data associated with the first child whose label matches that given as a boolean
   * @param label - the label to look for
   * @param defaultVal - the value to return if a match is not found
   * @return the value of a matched child's data, or the default value
   */
  bool	findChildboolData(const skString& label, bool defaultVal=false) const;
  /**
   * Finds the data associated with the first child whose label matches that given as an integer
   * @param label - the label to look for
   * @param defaultVal - the value to return if a match is not found
   * @return the value of a matched child's data, or the default value
   */
  int	findChildIntData(const skString& label, int defaultVal=0) const;
  /**
   * Finds the data associated with the first child whose label matches that given as a long integer
   * @param label - the label to look for
   * @param defaultVal - the value to return if a match is not found
   * @return the value of a matched child's data, or the default value
   */
  long	findChildLongData(const skString& label, long defaultVal=0) const;
  /**
   * Finds the data associated with the first child whose label matches that given as a float
   * @param label - the label to look for
   * @param defaultVal - the value to return if a match is not found
   * @return the value of a matched child's data, or the default value
   */
  float	findChildFloatData(const skString& label, float defaultVal=0.0f) const;
  /**
   * Returns the data for nth child in the list of children at this node
   */
  skString nthChildData(USize index) const;
  /**
   * Returns the data for nth child in the list of children at this node as an integer
   */
  int	nthChildIntData(USize index) const;
  /**
   * Writes this node to an output stream with the given indentation
   */
  void  write(ostream& out,USize tabstops) const;
  /**
   * Writes this node out to a file
   * @return true if the file could be written, or false if there was a problem
   */
  bool	write(const skString& file) const;
  /**
   * Returns a child from the list at this node
   * @param i - the index of the item
   * @return the child
   * @exception skBoundsException if the index is outside the range of the list
   */
  skTreeNode *  nthChild(USize  i) const;
  /**
   * Returns the number of children at this node
   */
  USize numChildren() const;
  /**
   * makes a deep copy of the items from the other node, but does not change the label or data of this node
   */
  void	copyItems(skTreeNode& node);
  /**
   * Moves the items from the child list of the given node into this node
   */
  void	moveItemsFrom(skTreeNode& node);
  /**
   * deletes all children from the list
   */
  void	clear();
  /**
   * Reads a treenode from the given file
   * @exception skTreeNodeReaderException if there was an error in the file
   */
  static skTreeNode * read(const skString& file);
 
  friend class skTreeNodeList;
  friend class skTreeNodeListIterator;

 private:
  /**
   * the label for this node
   */
  skString m_Label;
  /**
   * the data for this node
   */
  skString m_Data;
  /**
   * this children of this node
   */
  skTreeNodeList * m_Items;
};
/**
 * this class is used to read a TreeNode from a text stream.
 */
class  skTreeNodeReader 
{
 public:
  /**
   * Constructor - takes the input stream to read the TreeNode from
   */
  skTreeNodeReader(istream& in);
  /**
   * Constructor - takes the input stream to read the TreeNode from, and specifies a filename
   */
  skTreeNodeReader(istream& in,const char *  fileName);
  /**
   * Destructor
   */
  ~skTreeNodeReader();
  /**
   * Starts the parse of the input stream
   * @exception skTreeNodeReaderException if there was an error in the file
   * @return a TreeNode, if the read was successful
   */
  skTreeNode* read();
 private:
  class P_TreeNodeReader* pimp;
};
/**
 * this class encapsulates an error encountered while parsing a treenode text stream
 */
class skTreeNodeReaderException {
 public:
  /**
   * Constructor - takes information about the exception
   */
  skTreeNodeReaderException(const skString& fileName,const skString& msg)
    : m_FileName(fileName),m_Msg(msg){
  }
  /**
   * Returns a string describing the exception
   */
  skString toString(){
    return m_FileName+":"+m_Msg;
  }
 private:
  skString m_FileName;
  skString m_Msg;
};

#endif
			







