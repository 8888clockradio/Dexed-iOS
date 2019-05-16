//
//  PopupEditor.cpp
//  Dexed
//
//  Created by George Rosar on 5/13/19.
//  Copyright © 2019 georgerosar.com. All rights reserved.
//

/**
 *
 * Copyright (c) 2015-2017 Pascal Gauthier.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#ifndef CartManager_h
#define CartManager_h

#include "CartManager.h"
#endif

#include "DXLookNFeel.h"
#include "PluginData.h"

#ifndef ParamDialog_h
#define ParamDialog_h
#include "ParamDialog.h"
#endif

#ifndef PopupEditor_hpp
#define PopupEditor_hpp

#include "PopupEditor.hpp"

#endif /* PopupEditor_hpp */



PopupEditor::PopupEditor(const String& theName, DexedAudioProcessorEditor *editor) : Component() {
    mainWindow = editor;
    setName(theName);
    
    addAndMakeVisible(closeButton = new TextButton("CLOSE"));
    closeButton->setBounds(4, 545, 50, 30);
    closeButton->addListener(this);
    
    if (theName == "PARAM")
    {
        printf("PARAM\r\n");
    }
    else if (theName == "STORE")
    {
        printf("STORE\r\n");
        addAndMakeVisible(externalButton = new TextButton("EXTERNAL"));
        externalButton->setBounds(52, 545, 50, 30);
        externalButton->addListener(this);
        
        addAndMakeVisible(saveButton = new TextButton("SAVE"));
        saveButton->setBounds(100, 545, 50, 30);
        saveButton->addListener(this);
    }
    else {
        return;
    }
}

PopupEditor::~PopupEditor() {

}

void PopupEditor::openStorePanel(CartManager* cartManager) {
    if (getName() == "STORE") {
        /*theCartManager = cartManager;
        
        Label* lblName = new Label();
        lblName->setText("Name", dontSendNotification);
        
        Label* lblDest = new Label();
        lblDest->setText("Program Destination", dontSendNotification);
        
        currentName = Cartridge::normalizePgmName((const char *) mainWindow->processor->data+145);
        destSysex = mainWindow->processor->currentCart;
        
        activeCartridgeFound = mainWindow->processor->activeFileCartridge.exists();
        name->setText(currentName);
        addAndMakeVisible(lblName);
        addAndMakeVisible(name);
        
        StringArray programs;
        destSysex.getProgramNames(programs);
        
        dest->addItemList(programs, 1);
        addAndMakeVisible(lblDest);
        addAndMakeVisible(dest);
        dest->setSelectedItemIndex (0);
        
        
        //comboBoxNames.add (onScreenLabel);
        */
    }
}

void PopupEditor::paint(Graphics &g) {
    g.fillAll(DXLookNFeel::lightBackground);
    g.setColour(DXLookNFeel::roundBackground);
    //g.fillRoundedRectangle(8, 8, 843, 535, 15);
    //g.setColour(Colours::whitesmoke);
}

void PopupEditor::buttonClicked(juce::Button *buttonThatWasClicked) {
    auto theName = getName();
    if (theName == "PARAM")
    {
        printf("PARAM\r\n");
    }
    else if (theName == "STORE")
    {
        printf("STORE\r\n");
    }
    if ( buttonThatWasClicked == closeButton ) {
        if (theName == "PARAM")
        {
            printf("PARAM\r\n");
            mainWindow->hitParams();
        }
        mainWindow->startTimer(100);
        setVisible(false);
        return;
    }
    
    if ( buttonThatWasClicked == saveButton ) {
        if (theName == "STORE")
        {
            printf("STORE\r\n");
            //when ComboBox Changes
            int response = 0;
            
            sendResponse(response);
                
        }
    }
}

void  PopupEditor::sendResponse(int theResponse) {
    /*if ( theResponse == 2 ) {
        FileChooser fc("Destination Sysex", mainWindow->processor->dexedCartDir, "*.syx;*.SYX;*.*", 1);
        
        if ( fc.browseForFileToOpen() ) {
            if ( externalFile != NULL )
                delete externalFile;
            
            externalFile = new File(fc.getResults().getReference(0));
            if ( destSysex.load(*externalFile) == 0 )
                NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Read error", "Unable to read file");
        }
    }
    if ( theResponse == 0 ) {
        
        int programNum = dest->getSelectedItemIndex();
        String programName(name->getText());
        if ( programName.length() > 10 ) {
            int toStrip = programName.length() - 10;
            programName = programName.dropLastCharacters(toStrip);
        }
        
        if ( externalFile == NULL ) {
            mainWindow->processor->currentCart.packProgram((uint8_t *) mainWindow->processor->data, programNum, programName, mainWindow->processor->controllers.opSwitch);
            rebuildProgramCombobox();
            mainWindow->processor->setCurrentProgram(programNum);
            mainWindow->processor->updateHostDisplay();
            
            int action = dialog.getComboBoxComponent("SaveAction")->getSelectedItemIndex();
            if ( action > 0 ) {
                File destination = processor->activeFileCartridge;
                if ( action == 1 ) {
                    FileChooser fc("Destination Sysex", processor->dexedCartDir, "*.syx;*.SYX", 1);
                    if ( ! fc.browseForFileToSave(true) )
                        break;
                    destination = fc.getResult();
                }
                
                processor->currentCart.saveVoice(destination);
                processor->activeFileCartridge = destination;
            }
        } else {
            destSysex.packProgram((uint8_t *) processor->data, programNum, programName, processor->controllers.opSwitch);
            if ( ! destSysex.saveVoice(*externalFile)) {
                AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Write error", "Unable to write file");
            }
        }
    }*/
}
