/**
 *
 * Copyright (c) 2013-2018 Pascal Gauthier.
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
#include "GlobalEditor.h"

#ifndef ParamDialog_h
#define ParamDialog_h
#include "ParamDialog.h"s
#endif
#include "SysexComm.h"
#include "Dexed.h"
#include "math.h"
#include <fstream>
#ifndef PopupEditor_hpp
#define PopupEditor_hpp

#include "PopupEditor.hpp"

#endif /* PopupEditor_hpp */

#include "msfa/fm_op_kernel.h"

//==============================================================================
DexedAudioProcessorEditor::DexedAudioProcessorEditor (DexedAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter),
    midiKeyboard (ownerFilter->keyboardState, MidiKeyboardComponent::horizontalKeyboard),
    cartManager(this), paramObj("PARAM", this), storeObj("STORE", this)
{
    setSize(866, ownerFilter->showKeyboard ? 674 : 581);
    
    processor = ownerFilter;
    
    lookAndFeel->setDefaultLookAndFeel(lookAndFeel);
    background = lookAndFeel->background;
    
    /* george */
    //hasProcessor_m = true;
    //processor->setEditorPresent(true, &exitLock);
    Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea;
    
    //auto contentWidth  = 866;
    //auto contentHeight = processor->showKeyboard ? 674 : 581;
    //auto scaleX = area.getWidth()  / static_cast<float> (contentWidth);
    //auto scaleY = area.getHeight() / static_cast<float> (contentHeight);
    //auto scale  = jmin (scaleX, scaleY);
    switch( PluginHostType::getPluginLoadedAs() )
    {
        case AudioProcessor::wrapperType_Undefined:  theViewport.setSize(area.getWidth(), area.getHeight());
            break;
        case AudioProcessor::wrapperType_AudioUnitv3:  theViewport.setSize(getWidth(), getHeight());
            break;
        case AudioProcessor::wrapperType_AudioUnit:  theViewport.setSize(getWidth(), getHeight());
            break;
        case AudioProcessor::wrapperType_Standalone:  theViewport.setSize(area.getWidth(), area.getHeight());
            break;
        default:  theViewport.setSize(area.getWidth(), area.getHeight());
            break;
    }
    removeAllChildren();
    //addAndMakeVisible(theViewport);
    itemHolder.setSize(866, processor->showKeyboard ? 674 : 581);
   
    
    //    theViewport.setViewedComponent(itemHolder, true);
     //start by commenting this out

    /* george */
    
    
    
    // OPERATORS
    itemHolder.addAndMakeVisible(&(operators[0]));
    operators[0].setBounds(2, 1, 287, 218);
    operators[0].bind(processor, 0);
    
    itemHolder.addAndMakeVisible(&(operators[1]));
    operators[1].setBounds(290, 1, 287, 218);
    operators[1].bind(processor, 1);
    
    itemHolder.addAndMakeVisible(&(operators[2]));
    operators[2].setBounds(578, 1, 287, 218);
    operators[2].bind(processor, 2);
    
    itemHolder.addAndMakeVisible(&(operators[3]));
    operators[3].setBounds(2, 219, 287, 218);
    operators[3].bind(processor, 3);
    
    itemHolder.addAndMakeVisible(&(operators[4]));
    operators[4].setBounds(290, 219, 287, 218);
    operators[4].bind(processor, 4);
    
    itemHolder.addAndMakeVisible(&(operators[5]));
    operators[5].setBounds(578, 219, 287, 218);
    operators[5].bind(processor, 5);

    // add the midi keyboard component..
    itemHolder.addAndMakeVisible (&midiKeyboard);
    //addAndMakeVisible (&midiKeyboard);  //george uncomment
    
    // The DX7 is a badass on the bass, keep it that way
    midiKeyboard.setLowestVisibleKey(24);

    midiKeyboard.setBounds(4, 581, getWidth() - 8, 90);

    itemHolder.addAndMakeVisible(&global);
    global.setBounds(2,436,864,144);
    global.bind(this);
    
    global.setMonoState(processor->isMonoMode());
    
    rebuildProgramCombobox();
    global.programs->addListener(this);
    
    itemHolder.addChildComponent(&cartManager);
    
    itemHolder.addChildComponent(&paramObj);
    
    itemHolder.addChildComponent(&storeObj);
    
    theViewport.setViewedComponent(&itemHolder);
    addAndMakeVisible(theViewport);
    
    
    //itemHolder.addChildComponent(attach);
    
    updateUI();
    startTimer(100);
    //exitLock.exit(); //george might need to remove this, but communication with processor
}

void DexedAudioProcessorEditor::resized() {
    Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea;
    
    if (processor != nullptr) {
        auto contentWidth  = 866;
        auto contentHeight = 674;
        auto scaleX = area.getWidth()  / static_cast<float> (contentWidth);
        auto scaleY = area.getHeight() / static_cast<float> (contentHeight);
        auto scale  = jmin (scaleX, scaleY);
        //setTransform (AffineTransform::scale (scale, scale));
        
        //printf("resized: PluginEditor.cpp\r\n");
        //printf("area.getWidth(): %i area.getHeight(): %i\r\n", area.getWidth(), area.getHeight());
        //printf("getWidth(): %i getHeight(): %i\r\n", getWidth(), getHeight());
        switch( PluginHostType::getPluginLoadedAs() )
        {
            case AudioProcessor::wrapperType_Undefined:
                midiKeyboard.setTransform(AffineTransform::scale (scale, scale));
                /*midiKeyboard.setTopLeftPosition(0, area.getHeight() - midiKeyboard.getHeight());
                theViewport.setSize(area.getWidth(), area.getHeight() - midiKeyboard.getHeight());*/
                break;
            case AudioProcessor::wrapperType_AudioUnitv3:  theViewport.setSize(getWidth(), getHeight());
                break;
            case AudioProcessor::wrapperType_AudioUnit:  theViewport.setSize(getWidth(), getHeight());
                break;
            case AudioProcessor::wrapperType_Standalone:  theViewport.setSize(area.getWidth(), area.getHeight());
                /*midiKeyboard.setTransform(AffineTransform::scale (scale, scale));
                midiKeyboard.setTopLeftPosition(0, area.getHeight() - midiKeyboard.getHeight());
                theViewport.setSize(area.getWidth(), area.getHeight() - midiKeyboard.getHeight());*/
                break;
            default:  theViewport.setSize(area.getWidth(), area.getHeight());
                break;
        }
        if (area.getWidth() > 866) {
            itemHolder.setTransform (AffineTransform::scale (scale, scale));
            //printf("itemHolder.getWidth(): %i itemHolder.getHeight(): %i\r\n", itemHolder.getWidth(), itemHolder.getHeight());
            //setCentrePosition(area.getWidth() * 0.5, area.getHeight() * 0.5);
            itemHolder.setCentrePosition (getWidth() / 2,
                               getHeight() / 2);
            
        }
    }
    repaint();
}

DexedAudioProcessorEditor::~DexedAudioProcessorEditor() {
    stopTimer();
    processor->unbindUI();
    setLookAndFeel(nullptr);
    /* george */
    //if (hasProcessor_m) processor->setEditorPresent(false, nullptr);
    /* george */
}


//==============================================================================
void DexedAudioProcessorEditor::paint (Graphics& g) {    
    g.setColour(background);
    g.fillRoundedRectangle(0.0f, 0.0f, (float) getWidth(), (float) getHeight(), 0);
}

void DexedAudioProcessorEditor::cartShow() {
    stopTimer();    
    cartManager.resetActiveSysex();
    cartManager.setBounds(4, 2, 859, 576);
    cartManager.setVisible(true);
    cartManager.initialFocus();
}


void DexedAudioProcessorEditor::loadCart(File file) {
    Cartridge cart;

    int rc = cart.load(file);
    
    if ( rc < 0 ) {
        NativeMessageBox::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "Error",
                                          "Unable to open: " + file.getFullPathName());
        return;
    }
    
    if ( rc != 0 ) {
        rc = NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, "Unable to find DX7 sysex cartridge in file",
                                          "This sysex file is not for the DX7 or it is corrupted. "
                                          "Do you still want to load this file as random data ?");
        if ( rc == 0 )
            return;
    }

    processor->loadCartridge(cart);
    rebuildProgramCombobox();
    processor->setCurrentProgram(0);
    global.programs->setSelectedId(processor->getCurrentProgram()+1, dontSendNotification);
    processor->updateHostDisplay();
    
    processor->activeFileCartridge = file;
    //exitLock.exit();  //george added because processor->
}

void DexedAudioProcessorEditor::saveCart() {
    File startFileName = processor->activeFileCartridge.exists() ? processor->activeFileCartridge : processor->dexedCartDir;

    FileChooser fc ("Export DX sysex...", processor->dexedCartDir, "*.syx;*.SYX", 1);
    if ( fc.browseForFileToSave(true) ) {
        if ( ! processor->currentCart.saveVoice(fc.getResults().getReference(0)) ) {
            NativeMessageBox::showMessageBoxAsync (AlertWindow::WarningIcon,
                                              "Error",
                                              "Unable to write: " + fc.getResults().getReference(0).getFullPathName());
        }
    }
    //exitLock.exit();  //george added because processor->
}

void DexedAudioProcessorEditor::hitParams() {
    bool ret = param.getDialogValues(processor->controllers, processor->sysexComm, &tp, &processor->showKeyboard);
    processor->setEngineType(tp);
    processor->savePreference();
    
    setSize(866, processor->showKeyboard ? 674 : 581);
    midiKeyboard.repaint();
    //attach.setVisible(false);
    
    if ( ret == false ) {
        NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Midi Interface", "Error opening midi ports");
    }
}

void DexedAudioProcessorEditor::parmShow() {
    tp = processor->getEngineType();
    
    /* george centering stuff */
    //might need to make attach a global var in this class
    Rectangle<int> area = theViewport.getViewArea();
    
    //attach.setTopLeftPosition(theViewport.getViewPositionX(), theViewport.getViewPositionY());
    //attach.setSize(area.getWidth(), area.getHeight());
    /* george */
    printf("theViewport.getViewPositionX(): %i theViewport.getViewPositionY(): %i\r\n", theViewport.getViewPositionX(), theViewport.getViewPositionY());
    printf("attach.getWidth(): %i attach.getHeight(): %i\r\n", attach.getWidth(), attach.getHeight());
     printf("attach.getX(): %i attach.getY(): %i\r\n", attach.getX(), attach.getY());
    
    //AlertWindow window("","", AlertWindow::NoIcon, &theViewport);
    //attach.setVisible(true);
    //AlertWindow window("","", AlertWindow::NoIcon, &(operators[3])); //george
    //PopupEditor window(this);
    stopTimer();
    paramObj.setBounds(4, 2, 859, 576);
    paramObj.setVisible(true);
    
    //ParamDialog param;
    param.setColour(AlertWindow::backgroundColourId, Colour(0x32FFFFFF));
    param.setDialogValues(processor->controllers, processor->sysexComm, tp, processor->showKeyboard);
    
    paramObj.addAndMakeVisible(&param);
    param.setTopLeftPosition(75, 120);
    
    printf("param.getX(): %i param.getY(): %i\r\n", param.getX(), param.getY());
    printf("param.getWidth(): %i param.getHeight(): %i\r\n", param.getWidth(), param.getHeight());
    //param.setAlwaysOnTop(true);
    //window.addButton("OK", 0);
    //window.addButton("Cancel" ,1);
    //if ( window.runModalLoop() != 0 )
     //   return;
    
    
    /* happens after save is hit */
    /*
    bool ret = param.getDialogValues(processor->controllers, processor->sysexComm, &tp, &processor->showKeyboard);
    processor->setEngineType(tp);
    processor->savePreference();
    
    setSize(866, processor->showKeyboard ? 674 : 581);
    midiKeyboard.repaint();
    //attach.setVisible(false);
    
    if ( ret == false ) {
        NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Midi Interface", "Error opening midi ports");
    }
    //exitLock.exit();  //george added because processor->
    //george might have to make for Auv3 and Standalone detection
    */
    
    //george
}

void DexedAudioProcessorEditor::initProgram() {
    processor->resetToInitVoice();
    //exitLock.exit();  //george added because processor-> these might need to go after?
}

void DexedAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged) {
    processor->setCurrentProgram(global.programs->getSelectedId()-1);
    processor->updateHostDisplay();
    //exitLock.exit();  //george added because processor-> these might need to go after?
}

void DexedAudioProcessorEditor::timerCallback() {
    /* george */
    /*exitLock.enter();
    if (!hasProcessor_m)
    {
        exitLock.exit();
        return;
    }*/
    /* george */
    //theViewport.updateVisibleArea();
    //itemHolder.repaint();
    if ( processor->forceRefreshUI ) {
        processor->forceRefreshUI = false;
        
    }
    for(int i=0;i<6;i++) {
        operators[i].repaint();
    }
    itemHolder.repaint();
    theViewport.repaint();
    theViewport.updateVisibleArea();
    
    if ( ! processor->peekVoiceStatus() )
        return;

    for(int i=0;i<6;i++) {
        operators[i].updateGain(sqrt(processor->voiceStatus.amp[5 - i]) / 8196);        // TODO: FUGLY !!!! change this sqrt nonsens
        operators[i].updateEnvPos(processor->voiceStatus.ampStep[5 - i]);
    }
    global.updatePitchPos(processor->voiceStatus.pitchStep);
    global.updateVu(processor->vuSignal);
    //exitLock.exit();  //george added because processor-> these might need to go after?
}   

void DexedAudioProcessorEditor::updateUI() {
    for(int i=0;i<processor->ctrl.size();i++) {
        processor->ctrl[i]->updateComponent();
    }
    for(int i=0;i<6;i++) {
        operators[i].updateDisplay();
    }
    rebuildProgramCombobox();
    global.updateDisplay();
    
    /* george */
    /* not working
    Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea;
    
    auto contentWidth  = 866;
    auto contentHeight = processor->showKeyboard ? 674 : 581;
    auto scaleX = area.getWidth()  / static_cast<float> (contentWidth);
    auto scaleY = area.getHeight() / static_cast<float> (contentHeight);
    auto scale  = jmin (scaleX, scaleY);
    auto scaleReverse = 1 / scale;
    setTransform (AffineTransform::scale (scale, scale));
    if ((int) area.getHeight() > (int) area.getWidth()) {
        setSize (area.getWidth() * scaleReverse,
                 area.getHeight() * scaleReverse);
        //printf("inside Tall\r\n");
    }
    else {
        setSize (area.getWidth() * scaleReverse,
                 area.getHeight() * scaleReverse);
        centreWithSize(contentWidth, contentHeight);
        //printf("inside Wide\r\n");
    }
    setTransform (AffineTransform::scale (scale, scale)); */
    /* george */
}
/* george */

void DexedAudioProcessorEditor::mouseMove(const MouseEvent &event) {
    /* george */
    //auto* theParent = getParentComponent();
    theViewport.mouseMove(event);
    //printf("mouseMove: send to parent\r\n");
    /* george */
}
void DexedAudioProcessorEditor::mouseEnter(const MouseEvent &event) {
    /* george */
    theViewport.mouseEnter(event);
   //printf("mouseEnter: send to parent\r\n");
    /* george */
}
void DexedAudioProcessorEditor::mouseExit(const MouseEvent &event) {
    /* george */
    theViewport.mouseExit(event);
    //printf("mouseExit: send to parent\r\n");
    /* george */
}
void DexedAudioProcessorEditor::mouseDrag(const MouseEvent &event) {
    /* george */
    //auto* theParent = getParentComponent();
    theViewport.mouseDrag(event);
    //printf("mouseDrag: send to parent\r\n");
    //autoScroll(event.getScreenX(), event.getScreenY(), 100, 5);
    
    /* george */
}
void DexedAudioProcessorEditor::mouseUp(const MouseEvent &event) {
    /* george */
    //auto* theParent = getParentComponent();
    theViewport.mouseUp(event);
    //printf("mouseUp: send to parent\r\n");
    /* george */
}
void DexedAudioProcessorEditor::mouseDoubleClick(const MouseEvent &event) {
    /* george */
    //auto* theParent = getParentComponent();
    theViewport.mouseDoubleClick(event);
    //printf("mouseDoubleClick: send to parent\r\n");
    /* george */
}
void DexedAudioProcessorEditor::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    /* george */
    //auto* theParent = getParentComponent();
    theViewport.mouseWheelMove(event, wheel);
    //printf("mouseWheelMove: send to parent\r\n");
    /* george */
}

void DexedAudioProcessorEditor::mouseDown (const MouseEvent &event) {
    //printf("mouseDown\r\n");
    //auto* theParent = getParentComponent();
    theViewport.mouseDown(event);
    //MouseListener::mouseDown(event);
}
void DexedAudioProcessorEditor::mouseMagnify (const MouseEvent &e, float magnifyAmount) 
{
    //MouseListener::mouseMagnify(e, magnifyAmount);
    //auto* theParent = getParentComponent();
    theViewport.mouseMagnify(e, magnifyAmount);
    //printf("mouseMagnify\r\n");
}

/* george */

void DexedAudioProcessorEditor::rebuildProgramCombobox() {
    global.programs->clear(dontSendNotification);
    
    processor->currentCart.getProgramNames(processor->programNames);
    
    for(int i=0;i<processor->getNumPrograms();i++) {
        String id;
        id << (i+1) << ". " << processor->getProgramName(i);
        global.programs->addItem(id, i+1);
    }
    
    global.programs->setSelectedId(processor->getCurrentProgram()+1, dontSendNotification);
    
    String name = Cartridge::normalizePgmName((const char *) processor->data+145);
    cartManager.setActiveProgram(processor->getCurrentProgram(), name);
    if ( name != processor->getProgramName(processor->getCurrentProgram()) )
        global.programs->setText("**. " + name, dontSendNotification);
    
    cartManager.resetActiveSysex();
    //exitLock.exit();  //george added because processor-> these might need to go after?
}

void DexedAudioProcessorEditor::storeProgram() {
    stopTimer();
    storeObj.setBounds(4, 2, 859, 576);
    storeObj.setVisible(true);
    
    storeObj.openStorePanel(&cartManager);
    
    //String currentName = Cartridge::normalizePgmName((const char *) processor->data+145);
    //Cartridge destSysex = processor->currentCart;
    //File *externalFile = NULL;

    //bool activeCartridgeFound = processor->activeFileCartridge.exists();
    
    /*while (true) {
        String msg;
        
        if ( externalFile == NULL ) {
            if ( activeCartridgeFound )
                msg = "Store program to current (" + processor->activeFileCartridge.getFileName() + ") / new cartridge";
            else
                msg = "Store program to current / new cartridge";
        } else {
            msg = "Store program to " + externalFile->getFileName();
        }*/
        
        //AlertWindow dialog("Store Program", msg, AlertWindow::NoIcon, &(operators[3])); //george
        //PopupEditor dialog(this); //george
        //AlertWindow dialog("Store Program", msg, AlertWindow::NoIcon, &theViewport); //george
        //dialog.addTextEditor("Name", currentName, String("Name"), false);
        // TODO: fix the name length to 10

        
        //StringArray programs;
        //destSysex.getProgramNames(programs);
        //dialog.addComboBox("Dest", programs, "Program Destination");

        
        /*
        if ( externalFile == NULL ) {
            StringArray saveAction;
            saveAction.add("Store program to DAW plugin song state");
            saveAction.add("Store program and create a new copy of the .syx cartridge");
            if ( activeCartridgeFound )
                saveAction.add("Store program and overwrite current .syx cartridge");
        
            //dialog.addComboBox("SaveAction", saveAction, "Store Action");
        }*/
                
        //dialog.addButton("OK", 0, KeyPress(KeyPress::returnKey));
        //dialog.addButton("CANCEL", 1, KeyPress(KeyPress::escapeKey));
        //dialog.addButton("EXTERNAL FILE", 2, KeyPress());
        
        //int response = dialog.runModalLoop(); //edit this in above function too
        //george might have to make for Auv3 and Standalone detection
        //auto viewPos = theViewport.getViewPosition();
        //dialog.setTopLeftPosition(viewPos.getX(), viewPos.getY());
        //george
        
        /*if ( response == 2 ) {
            FileChooser fc("Destination Sysex", processor->dexedCartDir, "*.syx;*.SYX;*.*", 1);

            if ( fc.browseForFileToOpen() ) {
                if ( externalFile != NULL ) 
                    delete externalFile;

                externalFile = new File(fc.getResults().getReference(0));
                if ( destSysex.load(*externalFile) == 0 )
                    continue;
                AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Read error", "Unable to read file");
            }
        }

        if ( response == 0 ) {
            TextEditor *name = dialog.getTextEditor("Name");
            ComboBox *dest = dialog.getComboBoxComponent("Dest");
            
            int programNum = dest->getSelectedItemIndex();
            String programName(name->getText());
            if ( programName.length() > 10 ) {
                int toStrip = programName.length() - 10;
                programName = programName.dropLastCharacters(toStrip);
            }

            if ( externalFile == NULL ) {
                processor->currentCart.packProgram((uint8_t *) processor->data, programNum, programName, processor->controllers.opSwitch);
                rebuildProgramCombobox();
                processor->setCurrentProgram(programNum);
                processor->updateHostDisplay();
                
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
        }
        break;
    }

    if ( externalFile != NULL )
        delete externalFile;
    cartManager.resetActiveSysex();
    //exitLock.exit();  //george added because processor-> these might need to go after?
         */
}

class MidiCCListener: public AlertWindow, Value::Listener {
    DexedAudioProcessorEditor *editor;
    Ctrl *target;
public :
    MidiCCListener(DexedAudioProcessorEditor *editor, Ctrl *target) : AlertWindow("","", AlertWindow::InfoIcon, editor) {
        this->editor = editor;
        this->target = target;
        setMessage("Mapping: " + String(target->label) + ", waiting for midi controller change (CC) message...");
        addButton("CANCEL", -1);
        editor->processor->lastCCUsed.setValue(-1);        
        editor->processor->lastCCUsed.addListener(this);
    }
    
    ~MidiCCListener() {
        editor->processor->lastCCUsed.removeListener(this);
    }
    
    void valueChanged(Value &value) {
        int cc = value.getValue();
        editor->processor->mappedMidiCC.remove(cc);
        editor->processor->mappedMidiCC.set(cc, target);
        editor->processor->savePreference();
        exitModalState(0);
    }
};

void DexedAudioProcessorEditor::discoverMidiCC(Ctrl *ctrl) {
    MidiCCListener ccListener(this, ctrl);
    ccListener.runModalLoop();
}

