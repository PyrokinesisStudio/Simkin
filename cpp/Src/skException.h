/*
  Copyright 1996-2003
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

  $Id: skException.h,v 1.3 2003/01/20 18:48:18 simkin_cvs Exp $
*/
#ifndef SKEXCEPTION_H
#define SKEXCEPTION_H

#include "skGeneral.h"
#include "skString.h"

/**
* This class is a base class for exceptions thrown by Simkin
*/

class CLASSEXPORT skException
{
public:
  virtual skString toString() const=0;
};

#endif
