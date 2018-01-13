/*
  Copyright 1996-2000
  Simon Whiteside, All Rights Reserved

  THIS CODE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
  PURPOSE.

  Demo_Controller.cpp

  This file implements the class which controls the behaviour of the
  view in the demo.

  $Id: Demo_Controller.cpp,v 1.1 2000/12/21 13:32:59 sdw Exp $
*/
#include "Demo_Controller.h"
#include "skRValueArray.h"
#include "dom/DOM_NodeList.hpp"

//-----------------------------------------------------------------
Controller::Controller(const skString& fileName)
  //-----------------------------------------------------------------
  //	this class loads the demo script file, whose methods
  //	are an extension of the class functionality
  : skXMLExecutable(fileName),m_View(0),m_FileName(fileName)
{
  init();
}
//-----------------------------------------------------------------
Controller::~Controller()
  //-----------------------------------------------------------------
{
  delete m_View;
}
//-----------------------------------------------------------------
skString Controller::getStringAttribute(DOM_Element elem,const skString& name)
//-----------------------------------------------------------------
{
  return toString(elem.getAttribute(fromString(name)));
}
//-----------------------------------------------------------------
int Controller::getIntegerAttribute(DOM_Element elem,const skString& name)
//-----------------------------------------------------------------
{
  return toString(elem.getAttribute(fromString(name))).to();
}
//-----------------------------------------------------------------
void Controller::init()
  //-----------------------------------------------------------------
{
  //	load the view description from the file
  //	and create the controls contained within the view definition
  DOM_Element code=getElement();
  DOM_Element viewNode=findChild(code,"View");
  if (viewNode.isNull()==false){
    skString title=getStringAttribute(viewNode,"Title");
    int x_pos=getIntegerAttribute(viewNode,"X");
    int y_pos=getIntegerAttribute(viewNode,"Y");
    int width=getIntegerAttribute(viewNode,"Width");
    int height=getIntegerAttribute(viewNode,"Height");
    m_View=new View(*this,title,x_pos,y_pos,width,height);
      //	look for some controls
    DOM_Element controls=findChild(viewNode,"Controls");
    if (controls.isNull()==false){
      DOM_NodeList controlsList=controls.getChildNodes();
      for (unsigned int i=0;i<controlsList.getLength();i++){
	DOM_Node node=controlsList.item(i);
	int nodeType=node.getNodeType();
	if (nodeType==DOM_Node::ELEMENT_NODE){
	  DOM_Element control=*(DOM_Element *)&node;
	  skString type=getStringAttribute(control,"Type");
	  int id=getIntegerAttribute(control,"Id");
	  skString text=getStringAttribute(control,"Text");
	  int x_pos=getIntegerAttribute(control,"X");
	  int y_pos=getIntegerAttribute(control,"Y");
	  int width=getIntegerAttribute(control,"Width");
	  int height=getIntegerAttribute(control,"Height");
	  m_View->addControl(type,id,text,x_pos,y_pos,width,height);
	}
      }
    }
  }
  skRValueArray args;
  skRValue ret;
  method("init",args,ret);
}
//-----------------------------------------------------------------
void Controller::buttonPressed(int id)
  //-----------------------------------------------------------------
  //	this method is a virtual from ViewCallback, it is called when the user
  //	presses a button
{
  DOM_Element code=getElement();
  //	look for the node for this control, matching on id
  DOM_Element viewNode=findChild(code,"View");
  if (viewNode.isNull()==false){
    DOM_Element controls=findChild(viewNode,"Controls");
    if (controls.isNull()==false){
      DOM_NodeList controlsList=controls.getChildNodes();
      for (unsigned int i=0;i<controlsList.getLength();i++){
	DOM_Node node=controlsList.item(i);
	int nodeType=node.getNodeType();
	if (nodeType==DOM_Node::ELEMENT_NODE){
	  DOM_Element control=*(DOM_Element *)&controlsList.item(i);
	  int this_id=getIntegerAttribute(control,"Id");
	  if (this_id==id){
	    skString methodName=getStringAttribute(control,"Method");
	    if (methodName.length()){
	      //	call a method on ourselves, if one is set up
	      skRValueArray args;
	      skRValue ret;
	      method(methodName,args,ret);
	    }
	    break;
	  }
	}
      }
    }
  }
}
//-----------------------------------------------------------------
bool Controller::method(const skString& s,skRValueArray& args,skRValue& ret)
  //-----------------------------------------------------------------
  //	this is the function called by the Simkin interpreter when a method 
  //	is invoked on this object
{
  bool bRet=false;
  if (IS_METHOD(s,"reload")){
    //	this code causes the script file to be re-read and
    //	the view recreated
    delete m_View;
    m_View=0;
    load(m_FileName);
    init();
    bRet=true;
  }else
    if (IS_METHOD(s,"setFocus") && m_View && args.entries()==1){
      //	sets focus to a control
      m_View->setFocus(args[0].intValue());
      bRet=true;
    }else
      if (IS_METHOD(s,"close") && m_View){
	//	closes the view and the application
	m_View->close();
	bRet=true;
      }else
	if (IS_METHOD(s,"run") && m_View && args.entries()==1){
	  //	run a command as a separate process
	  m_View->run(args[0].str());
	  bRet=true;
	}else
	  if (IS_METHOD(s,"getText") && m_View && args.entries()==1){
	    //	retrieves the text for a control
	    ret=m_View->getText(args[0].intValue());
	    bRet=true;
	  }else
	    if (IS_METHOD(s,"user") && m_View && args.entries()==1){
	      //	shows a message box to the user
	      m_View->user(args[0].str());
	      bRet=true;
	    }else
	      //	we pass any other method up to the base class, which in turn looks inside
	      //	the demo script file for a matching method
	      bRet=skXMLExecutable::method(s,args,ret);
  return bRet;
}
