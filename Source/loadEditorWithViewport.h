//
//  loadEditorWithViewport.hpp
//  Dexed
//
//  Created by George Rosar on 5/9/19.
//  Copyright © 2019 georgerosar.com. All rights reserved.
//

#include <stdio.h>
#include "PluginEditor.h"

class loadEditorWithViewport : public Component {
    public:
        //vars
        AudioProcessorEditor* myEditor;
        Viewport theViewport;
        Component itemHolder;
    
        //functions
        loadEditorWithViewport(AudioProcessorEditor* allEditor);
        ~loadEditorWithViewport();
        Viewport* getEditor(); //really actually not editor because
    
        void mouseDown(const MouseEvent &e) override;
        /* george */
        void mouseMagnify (const MouseEvent &e, float magnifyAmount) override;
        void mouseMove(const MouseEvent &event) override;
        void mouseEnter(const MouseEvent &event) override;
        void mouseExit(const MouseEvent &event) override;
        void mouseDrag(const MouseEvent &event) override;
        void mouseUp(const MouseEvent &event) override;
        void mouseDoubleClick(const MouseEvent &event) override;
        void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;
};
