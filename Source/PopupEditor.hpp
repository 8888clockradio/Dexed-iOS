//
//  PopupEditor.hpp
//  Dexed
//
//  Created by George Rosar on 5/13/19.
//  Copyright © 2019 georgerosar.com. All rights reserved.
//

#ifndef PopupEditor_hpp
#define PopupEditor_hpp

#include <stdio.h>

#endif /* PopupEditor_hpp */

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginData.h"
#include "ProgramListBox.h"
#include "PluginData.h"
#include "ParamDialog.h"
#include "CartManager.h"


class PopupEditor : public Component, public Button::Listener, public DragAndDropContainer {
    
    ScopedPointer<TextButton> saveButton;
    ScopedPointer<TextButton> closeButton;
    ScopedPointer<TextButton> externalButton;
    
    DexedAudioProcessorEditor *mainWindow;
    TextEditor *name = new TextEditor("Name");
    ComboBox *dest = new ComboBox("Dest");
    Cartridge destSysex;
    String currentName;
    bool activeCartridgeFound;
    
    CartManager* theCartManager;
    File *externalFile = NULL;
    
public:
    PopupEditor(const String& theName, DexedAudioProcessorEditor *editor);
    void openStorePanel(CartManager* cartManager);
    virtual ~PopupEditor();
    void paint(Graphics& g) override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void sendResponse(int theResponse);
private:
    //==============================================================================
    String text;
    TextLayout textLayout;
    ComponentBoundsConstrainer constrainer;
    ComponentDragger dragger;
    Rectangle<int> textArea;
    OwnedArray<TextButton> buttons;
    OwnedArray<TextEditor> textBoxes;
    OwnedArray<ComboBox> comboBoxes;
    
    
    ComboBox* SaveActionCombo = new ComboBox("SaveAction");
    
    OwnedArray<ProgressBar> progressBars;
    Array<Component*> customComps;
    OwnedArray<Component> textBlocks;
    Array<Component*> allComps;
    StringArray textboxNames, comboBoxNames;
};
