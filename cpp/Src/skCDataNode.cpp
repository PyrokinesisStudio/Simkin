/*
  Copyright 1996-2002
  Simon Whiteside

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

* $Id: skCDataNode.cpp,v 1.4 2002/12/13 17:21:54 sdw Exp $
*/
#include "skCDataNode.h"

//------------------------------------------
skCDataNode::skCDataNode(const skString& text)
//------------------------------------------
  : skTextNode(text)
{
}
//------------------------------------------
skNode::NodeType skCDataNode::getNodeType() const
//------------------------------------------
{
  return CDATA_SECTION_NODE;
}
//------------------------------------------
skNode * skCDataNode::clone()
//------------------------------------------
{
  return new skCDataNode(m_Text);
}
#ifdef STREAMS_ENABLED
//------------------------------------------
void skCDataNode::write(ostream& out) const
//------------------------------------------
{
  out << "![CDATA[" << m_Text << "!]]";
}
#endif