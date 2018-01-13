/*
  Copyright 1996-2001
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

* $Id: skTracer.cpp,v 1.7 2002/02/06 23:21:54 sdw Exp $
*/
#include "skTracer.h"

//------------------------------------------
void skTracer::trace(const skString& s)
//------------------------------------------
{
#ifdef STREAMS_ENABLED
    cout << s;
	cout.flush();
#else
#ifdef UNICODE_STRINGS
	wprintf((const Char *)s);
#else
	printf((const Char *)s);
#endif
#endif
}
