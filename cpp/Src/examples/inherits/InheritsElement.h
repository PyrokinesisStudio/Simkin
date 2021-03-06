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

  $Id: InheritsElement.h,v 1.6 2002/12/13 17:21:54 sdw Exp $
*/
#ifndef INHERITSELEMENT_H
#define INHERITSELEMENT_H

#include "skXMLElementObject.h"
#include <xercesc/dom/deprecated/DOM_Element.hpp>

/** 
 * this class extends the skXMLElementObject class with understanding of the <inherits> tag. It overrides the createXMLElementObject method to make sure that any sub-elements are also checked.
 */
class InheritsElement : public skXMLElementObject {
 public:
    /**
     * Default constructor - does nothing
     */
  InheritsElement();
  /**
   * passes parameters up to parent, and then calls replaceInherits to look for inherits tags
   * @param location location of the script
   * @param elem the element associated with this object
   */
  InheritsElement(const skString& location,DOM_Element elem);
 protected:
  /**
   * This method overrides the parent method and ensures that replaceInherits is called on the element associated with this object
   */
  virtual void setElement(DOM_Element elem);
  /**
   * This method overrides the parent method, it makes sure that if an object is created to associated with a sub-element, an InheritsElement type is used
   */
  virtual skXMLElementObject * createXMLElementObject(const skString& location,DOM_Element element);
  /**
   * This method walks through the given element, replacing any instances of <inherits> with the contents of the XML file given as the value of the inherits tag
   */
  static void replaceInherits(DOM_Element elem);
};

#endif
