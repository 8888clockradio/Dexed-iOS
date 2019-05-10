//
//  loadEditorWithViewport.cpp
//  Dexed
//
//  Created by George Rosar on 5/9/19.
//  Copyright © 2019 georgerosar.com. All rights reserved.
//
#include "loadEditorWithViewport.h"

loadEditorWithViewport::loadEditorWithViewport(AudioProcessorEditor* editor) : Component()
{
    MessageManager::getInstance()->callAsync ([=]
    {
        theEditor = editor;
        printf("test\r\n");
#if JUCE_IOS
        theEditor->setVisible (false);
#else
        theEditor->setVisible (true);
#endif
        
        //so the view is what it is being added to so have to intercept this and        maybe rewrite the addToDesktop function for a viewport
        //theViewport = Viewport("theViewport");
        theViewport.setSize(200, 300);
        //itemHolder = new Component();
        itemHolder.setSize(866, 571);
        itemHolder.addAndMakeVisible(theEditor);
        itemHolder.addChildComponent(theEditor);
        theViewport.setViewedComponent (&itemHolder, true);
     });
}

Viewport* loadEditorWithViewport::getEditor() {
    return &theViewport;
}

void loadEditorWithViewport::mouseDown(const MouseEvent &e) {
    /* george */
    //auto theParent = getParentComponent();
    theViewport.mouseDown(e);
    printf("loadEditor: mouseMove: send to parent\r\n");
    /* george */
}


void loadEditorWithViewport::mouseMove(const MouseEvent &event) {
    /* george */
    //auto theParent = getParentComponent();
    theViewport.mouseMove(event);
    printf("loadEditor: mouseMove: send to parent\r\n");
    /* george */
}
void loadEditorWithViewport::mouseEnter(const MouseEvent &event) {
    /* george */
    //auto theParent = getParentComponent();
    theViewport.mouseEnter(event);
    printf("loadEditor: mouseEnter: send to parent\r\n");
    /* george */
}
void loadEditorWithViewport::mouseExit(const MouseEvent &event) {
    /* george */
    //auto theParent = getParentComponent();
    theViewport.mouseExit(event);
    printf("loadEditor: mouseExit: send to parent\r\n");
    /* george */
}
void loadEditorWithViewport::mouseDrag(const MouseEvent &event) {
    /* george */
    //auto theParent = getParentComponent();
    printf("loadEditor: mouseDrag: send to parent\r\n");
    //autoScroll(event.getScreenX(), event.getScreenY(), 100, 5);
    theViewport.mouseDrag(event);
    /* george */
}
void loadEditorWithViewport::mouseUp(const MouseEvent &event) {
    /* george */
    //auto theParent = getParentComponent();
    theViewport.mouseUp(event);
    printf("loadEditor: mouseUp: send to parent\r\n");
    /* george */
}
void loadEditorWithViewport::mouseDoubleClick(const MouseEvent &event) {
    /* george */
    //auto theParent = getParentComponent();
    theViewport.mouseDoubleClick(event);
    printf("loadEditor: mouseDoubleClick: send to parent\r\n");
    /* george */
}
void loadEditorWithViewport::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    /* george */
    //auto theParent = getParentComponent();
    theViewport.mouseWheelMove(event, wheel);
    printf("loadEditor: mouseWheelMove: send to parent\r\n");
    /* george */
}

void loadEditorWithViewport::mouseMagnify (const MouseEvent &e, float magnifyAmount)
{
    /* george */
    //auto theParent = getParentComponent();
    theViewport.mouseMagnify(e, magnifyAmount);
    printf("loadEditor: mouseWheelMove: send to parent\r\n");
    /* george */
}

loadEditorWithViewport::~loadEditorWithViewport() {
    //destruct
}
