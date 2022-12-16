#include "SDLInputService.h"
#include <iostream>
#include <SDL.h>

class Event_Wrapper{
public:
    explicit Event_Wrapper(SDL_Event e) : event{e}{}
    SDL_Event event;
};

SDLInputService::SDLInputService(): _hasReceivedQuitSignal{false}
{
    _actionMap = ActionMap::getActionMap(); // actionMap the service will use as reference
    bindKeys(); // bind all the SDL keynames with our InputKey enum values
}

// handle input via SDL
void SDLInputService::handleInputs()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) //check for pollevents
    {
        if (event.type == SDL_KEYDOWN) // if key is pressed
        {
            auto key = _inputBinds.find(SDL_GetKeyName(event.key.keysym.sym))->second; // get key
            _actionMap->setInputKeyPressed(key, true); // handle action for this key
        }

        if (event.type == SDL_KEYUP) // if key is released
        {
            auto key = _inputBinds.find(SDL_GetKeyName(event.key.keysym.sym))->second; // get key
            _actionMap->setInputKeyPressed(key, false); // handle action for this key
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) // if mouse button is pressed
        {
            SDLInputService::handleMouseEvent(Event_Wrapper{event}, true); // handle mouse event
        }
        if (event.type == SDL_MOUSEBUTTONUP) // if mouse button is released
        {
            SDLInputService::handleMouseEvent(Event_Wrapper{event}, false); // handle mouse event
        }
        if (event.type == SDL_MOUSEMOTION) // if mouse button is released
        {
            //Don't do anything during mouse motion
        }
        if (event.type==SDL_QUIT) // if close button is pressed of window
        {
            _hasReceivedQuitSignal = true; // let gameloop now to stop handling inputs
        }
    }

    //Update mouse position
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    _actionMap->setMousePosition(mouseX, mouseY); //set current mouse pos
}

void SDLInputService::handleMouseEvent(Event_Wrapper event, bool pressed) {
    switch(event.event.button.button){
        case 1: // left mouse button
            _actionMap->setInputKeyPressed(Mouse_Left, pressed); // handle action for this button
            break;
        case 2: // middle mouse button
            _actionMap->setInputKeyPressed(Mouse_Middle, pressed); // handle action for this button
            break;
        case 3: // right mouse button
            _actionMap->setInputKeyPressed(Mouse_Right, pressed); // handle action for this button
            break;
        default: // when no button is pressed but mouse moved
            break;
    }

}

// bind all the SDL keynames with our InputKey enum values
void SDLInputService::bindKeys() {

    _inputBinds.insert(std::pair<std::string, InputKey>("0", Key_0));
    _inputBinds.insert(std::pair<std::string, InputKey>("1", Key_1));
    _inputBinds.insert(std::pair<std::string, InputKey>("2", Key_2));
    _inputBinds.insert(std::pair<std::string, InputKey>("3", Key_3));
    _inputBinds.insert(std::pair<std::string, InputKey>("4", Key_4));
    _inputBinds.insert(std::pair<std::string, InputKey>("5", Key_5));
    _inputBinds.insert(std::pair<std::string, InputKey>("6", Key_6));
    _inputBinds.insert(std::pair<std::string, InputKey>("7", Key_7));
    _inputBinds.insert(std::pair<std::string, InputKey>("8", Key_8));
    _inputBinds.insert(std::pair<std::string, InputKey>("9", Key_9));
    _inputBinds.insert(std::pair<std::string, InputKey>("A", Key_A));
    _inputBinds.insert(std::pair<std::string, InputKey>("AC Back", Key_AC_Back));
    _inputBinds.insert(std::pair<std::string, InputKey>("AC Bookmarks", Key_AC_Bookmarks));
    _inputBinds.insert(std::pair<std::string, InputKey>("AC Forward", Key_AC_Forward));
    _inputBinds.insert(std::pair<std::string, InputKey>("AC Home", Key_AC_Home));
    _inputBinds.insert(std::pair<std::string, InputKey>("AC Refresh", Key_AC_Refresh));
    _inputBinds.insert(std::pair<std::string, InputKey>("AC Search", Key_AC_Search));
    _inputBinds.insert(std::pair<std::string, InputKey>("AC Stop", Key_AC_Stop));
    _inputBinds.insert(std::pair<std::string, InputKey>("Again", Key_AC_Again));
    _inputBinds.insert(std::pair<std::string, InputKey>("AltErase", Key_AltErase));
    _inputBinds.insert(std::pair<std::string, InputKey>("'", Key_Quote));
    _inputBinds.insert(std::pair<std::string, InputKey>("Application", Key_Application));
    _inputBinds.insert(std::pair<std::string, InputKey>("AudioMute", Key_AudioMute));
    _inputBinds.insert(std::pair<std::string, InputKey>("AudioNext", Key_AudioNext));
    _inputBinds.insert(std::pair<std::string, InputKey>("AudioPlay", Key_AudioPlay));
    _inputBinds.insert(std::pair<std::string, InputKey>("AudioPrev", Key_AudioPrev));
    _inputBinds.insert(std::pair<std::string, InputKey>("AudioStop", Key_AudioStop));
    _inputBinds.insert(std::pair<std::string, InputKey>("B", Key_B));
    _inputBinds.insert(std::pair<std::string, InputKey>("\\", Key_Backslash));
    _inputBinds.insert(std::pair<std::string, InputKey>("Backspace", Key_Backspace));
    _inputBinds.insert(std::pair<std::string, InputKey>("BrightnessDown", Key_BrightnessDown));
    _inputBinds.insert(std::pair<std::string, InputKey>("BrightnessUp", Key_BrightnessUp));
    _inputBinds.insert(std::pair<std::string, InputKey>("C", Key_C));
    _inputBinds.insert(std::pair<std::string, InputKey>("Calculator", Key_Calculator));
    _inputBinds.insert(std::pair<std::string, InputKey>("Cancel", Key_Cancel));
    _inputBinds.insert(std::pair<std::string, InputKey>("CapsLock", Key_CapsLock));
    _inputBinds.insert(std::pair<std::string, InputKey>("Clear", Key_Clear));
    _inputBinds.insert(std::pair<std::string, InputKey>("Clear / Again", Key_ClearAgain));
    _inputBinds.insert(std::pair<std::string, InputKey>(",", Key_Comma));
    _inputBinds.insert(std::pair<std::string, InputKey>("Computer", Key_Computer));
    _inputBinds.insert(std::pair<std::string, InputKey>("Copy", Key_Copy));
    _inputBinds.insert(std::pair<std::string, InputKey>("CrSel", Key_CrSel));
    _inputBinds.insert(std::pair<std::string, InputKey>("CurrencySubUnit", Key_CurrencySubUnit));
    _inputBinds.insert(std::pair<std::string, InputKey>("CurrencyUnit", Key_CurrencyUnit));
    _inputBinds.insert(std::pair<std::string, InputKey>("Cut", Key_Cut));
    _inputBinds.insert(std::pair<std::string, InputKey>("D", Key_D));
    _inputBinds.insert(std::pair<std::string, InputKey>("DecimalSeparator", Key_DecimalSeparator));
    _inputBinds.insert(std::pair<std::string, InputKey>("Delete", Key_Delete));
    _inputBinds.insert(std::pair<std::string, InputKey>("DisplaySwitch", Key_DisplaySwitch));
    _inputBinds.insert(std::pair<std::string, InputKey>("Down", Key_Down));
    _inputBinds.insert(std::pair<std::string, InputKey>("E", Key_E));
    _inputBinds.insert(std::pair<std::string, InputKey>("Eject", Key_Eject));
    _inputBinds.insert(std::pair<std::string, InputKey>("End", Key_End));
    _inputBinds.insert(std::pair<std::string, InputKey>("=", Key_Equals));
    _inputBinds.insert(std::pair<std::string, InputKey>("Escape", Key_Escape));
    _inputBinds.insert(std::pair<std::string, InputKey>("Execute", Key_Execute));
    _inputBinds.insert(std::pair<std::string, InputKey>("ExSel", Key_ExSel));
    _inputBinds.insert(std::pair<std::string, InputKey>("F", Key_F));
    _inputBinds.insert(std::pair<std::string, InputKey>("F1", Key_F1));
    _inputBinds.insert(std::pair<std::string, InputKey>("F10", Key_F10));
    _inputBinds.insert(std::pair<std::string, InputKey>("F11", Key_F11));
    _inputBinds.insert(std::pair<std::string, InputKey>("F12", Key_F12));
    _inputBinds.insert(std::pair<std::string, InputKey>("F13", Key_F13));
    _inputBinds.insert(std::pair<std::string, InputKey>("F14", Key_F14));
    _inputBinds.insert(std::pair<std::string, InputKey>("F15", Key_F15));
    _inputBinds.insert(std::pair<std::string, InputKey>("F16", Key_F16));
    _inputBinds.insert(std::pair<std::string, InputKey>("F17", Key_F17));
    _inputBinds.insert(std::pair<std::string, InputKey>("F18", Key_F18));
    _inputBinds.insert(std::pair<std::string, InputKey>("F19", Key_F19));
    _inputBinds.insert(std::pair<std::string, InputKey>("F2", Key_F2));
    _inputBinds.insert(std::pair<std::string, InputKey>("F20", Key_F20));
    _inputBinds.insert(std::pair<std::string, InputKey>("F21", Key_F21));
    _inputBinds.insert(std::pair<std::string, InputKey>("F22", Key_F22));
    _inputBinds.insert(std::pair<std::string, InputKey>("F23", Key_F23));
    _inputBinds.insert(std::pair<std::string, InputKey>("F24", Key_F24));
    _inputBinds.insert(std::pair<std::string, InputKey>("F3", Key_F3));
    _inputBinds.insert(std::pair<std::string, InputKey>("F4", Key_F4));
    _inputBinds.insert(std::pair<std::string, InputKey>("F5", Key_F5));
    _inputBinds.insert(std::pair<std::string, InputKey>("F6", Key_F6));
    _inputBinds.insert(std::pair<std::string, InputKey>("F7", Key_F7));
    _inputBinds.insert(std::pair<std::string, InputKey>("F8", Key_F8));
    _inputBinds.insert(std::pair<std::string, InputKey>("F9", Key_F9));
    _inputBinds.insert(std::pair<std::string, InputKey>("Find", Key_Find));
    _inputBinds.insert(std::pair<std::string, InputKey>("G", Key_G));
    _inputBinds.insert(std::pair<std::string, InputKey>("`", Key_BackQuote));
    _inputBinds.insert(std::pair<std::string, InputKey>("H", Key_H));
    _inputBinds.insert(std::pair<std::string, InputKey>("Help", Key_Help));
    _inputBinds.insert(std::pair<std::string, InputKey>("Home", Key_Home));
    _inputBinds.insert(std::pair<std::string, InputKey>("I", Key_I));
    _inputBinds.insert(std::pair<std::string, InputKey>("Insert", Key_Insert));
    _inputBinds.insert(std::pair<std::string, InputKey>("J", Key_J));
    _inputBinds.insert(std::pair<std::string, InputKey>("K", Key_K));
    _inputBinds.insert(std::pair<std::string, InputKey>("KBDIllumDown", Key_KBDillumDown));
    _inputBinds.insert(std::pair<std::string, InputKey>("KBDIllumToggle", Key_KBDillumToggle));
    _inputBinds.insert(std::pair<std::string, InputKey>("KBDIllumUp", Key_KBDillumUp));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 0", Key_Keypad_0));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 00", Key_Keypad_00));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 000", Key_Keypad_000));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 1", Key_Keypad_1));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 2", Key_Keypad_2));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 3", Key_Keypad_3));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 4", Key_Keypad_4));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 5", Key_Keypad_5));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 6", Key_Keypad_6));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 7", Key_Keypad_7));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 8", Key_Keypad_8));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad 9", Key_Keypad_9));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad A", Key_Keypad_A));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad &", Key_Keypad_Ampsersand));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad @", Key_Keypad_AT));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad B", Key_Keypad_B));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad Backspace", Key_Keypad_Backspace));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad Binary", Key_Keypad_Binary));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad C", Key_Keypad_C));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad Clear", Key_Keypad_Clear));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad ClearEntry", Key_Keypad_ClearEntry));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad :", Key_Keypad_Colon));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad ,", Key_Keypad_Comma));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad D", Key_Keypad_D));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad &&", Key_Keypad_DBLAmpersand));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad ||", Key_Keypad_DBVerticalBar));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad Decimal", Key_Keypad_Decimal));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad /", Key_Keypad_Divide));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad E", Key_Keypad_E));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad Enter", Key_Keypad_Enter));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad =", Key_Keypad_Equals));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad = (AS400)", Key_Keypad_EqualsAs400));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad !", Key_Keypad_Exclam));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad F", Key_Keypad_F));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad >", Key_Keypad_Greater));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad #", Key_Keypad_Hash));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad Hexadecimal", Key_Keypad_Hexadecimal));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad {", Key_Keypad_LeftBrace));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad (", Key_Keypad_LeftParen));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad <", Key_Keypad_Less));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad MemAdd", Key_Keypad_MemAdd));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad MemClear", Key_Keypad_MemClear));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad MemDivide", Key_Keypad_MemDivide));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad MemMultiply", Key_Keypad_MemMultiply));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad MemRecall", Key_Keypad_MemRecall));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad MemStore", Key_Keypad_MemStore));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad MemSubtract", Key_Keypad_MemSubtract));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad -", Key_Keypad_Minus));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad *", Key_Keypad_Multiply));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad Octal", Key_Keypad_Octal));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad %", Key_Keypad_Percent));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad .", Key_Keypad_Period));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad +", Key_Keypad_Plus));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad +/-", Key_Keypad_PlusMinus));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad ^", Key_Keypad_Power));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad }", Key_Keypad_RightBrace));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad )", Key_Keypad_RightParen));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad Space", Key_Keypad_Space));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad Tab", Key_Keypad_Tab));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad |", Key_Keypad_VerticalBar));
    _inputBinds.insert(std::pair<std::string, InputKey>("Keypad XOR", Key_Keypad_Xor));
    _inputBinds.insert(std::pair<std::string, InputKey>("L", Key_L));
    _inputBinds.insert(std::pair<std::string, InputKey>("Left Alt", Key_LAlt));
    _inputBinds.insert(std::pair<std::string, InputKey>("Left Ctrl", Key_LCtrl));
    _inputBinds.insert(std::pair<std::string, InputKey>("Left", Key_Left));
    _inputBinds.insert(std::pair<std::string, InputKey>("[", Key_LeftBracket));
    _inputBinds.insert(std::pair<std::string, InputKey>("Left GUI", Key_LGui));
    _inputBinds.insert(std::pair<std::string, InputKey>("Left Shift", Key_LShift));
    _inputBinds.insert(std::pair<std::string, InputKey>("M", Key_M));
    _inputBinds.insert(std::pair<std::string, InputKey>("Mail", Key_Mail));
    _inputBinds.insert(std::pair<std::string, InputKey>("MediaSelect", Key_MediaSelect));
    _inputBinds.insert(std::pair<std::string, InputKey>("Menu", Key_Menu));
    _inputBinds.insert(std::pair<std::string, InputKey>("-", Key_Minus));
    _inputBinds.insert(std::pair<std::string, InputKey>("ModeSwitch", Key_Mode));
    _inputBinds.insert(std::pair<std::string, InputKey>("Mute", Key_Mute));
    _inputBinds.insert(std::pair<std::string, InputKey>("N", Key_n));
    _inputBinds.insert(std::pair<std::string, InputKey>("Numlock", Key_NumLockClear));
    _inputBinds.insert(std::pair<std::string, InputKey>("O", Key_O));
    _inputBinds.insert(std::pair<std::string, InputKey>("Oper", Key_Oper));
    _inputBinds.insert(std::pair<std::string, InputKey>("Out", Key_Out));
    _inputBinds.insert(std::pair<std::string, InputKey>("P", Key_P));
    _inputBinds.insert(std::pair<std::string, InputKey>("PageDown", Key_PageDown));
    _inputBinds.insert(std::pair<std::string, InputKey>("PageUp", Key_PageUp));
    _inputBinds.insert(std::pair<std::string, InputKey>("Paste", Key_Paste));
    _inputBinds.insert(std::pair<std::string, InputKey>("Pause", Key_Pause));
    _inputBinds.insert(std::pair<std::string, InputKey>(".", Key_Period));
    _inputBinds.insert(std::pair<std::string, InputKey>("Power", Key_Power));
    _inputBinds.insert(std::pair<std::string, InputKey>("PrintScreen", Key_PrintScreen));
    _inputBinds.insert(std::pair<std::string, InputKey>("Prior", Key_Prior));
    _inputBinds.insert(std::pair<std::string, InputKey>("Q", Key_Q));
    _inputBinds.insert(std::pair<std::string, InputKey>("R", Key_R));
    _inputBinds.insert(std::pair<std::string, InputKey>("Right Alt", Key_Ralt));
    _inputBinds.insert(std::pair<std::string, InputKey>("Right Ctrl", Key_RCtrl));
    _inputBinds.insert(std::pair<std::string, InputKey>("Return", Key_Return));
    _inputBinds.insert(std::pair<std::string, InputKey>("Right GUI", Key_RGui));
    _inputBinds.insert(std::pair<std::string, InputKey>("Right", Key_Right));
    _inputBinds.insert(std::pair<std::string, InputKey>("]", Key_RightBracket));
    _inputBinds.insert(std::pair<std::string, InputKey>("Right Shift", Key_RShift));
    _inputBinds.insert(std::pair<std::string, InputKey>("S", Key_S));
    _inputBinds.insert(std::pair<std::string, InputKey>("ScrollLock", Key_ScrollLock));
    _inputBinds.insert(std::pair<std::string, InputKey>("Select", Key_Select));
    _inputBinds.insert(std::pair<std::string, InputKey>(";", Key_SemiColon));
    _inputBinds.insert(std::pair<std::string, InputKey>("Separator", Key_Separator));
    _inputBinds.insert(std::pair<std::string, InputKey>("/", Key_Slash));
    _inputBinds.insert(std::pair<std::string, InputKey>("Sleep", Key_Sleep));
    _inputBinds.insert(std::pair<std::string, InputKey>("Space", Key_Space));
    _inputBinds.insert(std::pair<std::string, InputKey>("Stop", Key_Stop));
    _inputBinds.insert(std::pair<std::string, InputKey>("SysReq", Key_SysReq));
    _inputBinds.insert(std::pair<std::string, InputKey>("T", Key_T));
    _inputBinds.insert(std::pair<std::string, InputKey>("Tab", Key_Tab));
    _inputBinds.insert(std::pair<std::string, InputKey>("ThousandsSeparator", Key_ThousandSeperator));
    _inputBinds.insert(std::pair<std::string, InputKey>("U", Key_U));
    _inputBinds.insert(std::pair<std::string, InputKey>("Undo", Key_Undo));
    _inputBinds.insert(std::pair<std::string, InputKey>("", Key_Unknown));
    _inputBinds.insert(std::pair<std::string, InputKey>("Up", Key_Up));
    _inputBinds.insert(std::pair<std::string, InputKey>("V", Key_V));
    _inputBinds.insert(std::pair<std::string, InputKey>("VolumeDown", Key_VolumeDown));
    _inputBinds.insert(std::pair<std::string, InputKey>("VolumeUp", Key_VolumeUp));
    _inputBinds.insert(std::pair<std::string, InputKey>("W", Key_W));
    _inputBinds.insert(std::pair<std::string, InputKey>("WWW", Key_WWW));
    _inputBinds.insert(std::pair<std::string, InputKey>("X", Key_X));
    _inputBinds.insert(std::pair<std::string, InputKey>("Y", Key_Y));
    _inputBinds.insert(std::pair<std::string, InputKey>("Z", Key_Z));
    _inputBinds.insert(std::pair<std::string, InputKey>("&", Key_Ampersand));
    _inputBinds.insert(std::pair<std::string, InputKey>("*", Key_Asterisk));
    _inputBinds.insert(std::pair<std::string, InputKey>("@", Key_At));
    _inputBinds.insert(std::pair<std::string, InputKey>("^", Key_Caret));
    _inputBinds.insert(std::pair<std::string, InputKey>(":", Key_Colon));
    _inputBinds.insert(std::pair<std::string, InputKey>("$", Key_Dollar));
    _inputBinds.insert(std::pair<std::string, InputKey>("!", Key_Exclaim));
    _inputBinds.insert(std::pair<std::string, InputKey>(">", Key_Greater));
    _inputBinds.insert(std::pair<std::string, InputKey>("#", Key_Hash));
    _inputBinds.insert(std::pair<std::string, InputKey>("(", Key_LeftParen));
    _inputBinds.insert(std::pair<std::string, InputKey>("<", Key_Less));
    _inputBinds.insert(std::pair<std::string, InputKey>("%", Key_Percent));
    _inputBinds.insert(std::pair<std::string, InputKey>("+", Key_Plus));
    _inputBinds.insert(std::pair<std::string, InputKey>("?", Key_Question));
    _inputBinds.insert(std::pair<std::string, InputKey>("\"", Key_QuoteDbl));
    _inputBinds.insert(std::pair<std::string, InputKey>(")", Key_RightParen));
    _inputBinds.insert(std::pair<std::string, InputKey>("_", Key_Underscore));
}

bool SDLInputService::hasReceivedQuitSignal() const{
    return _hasReceivedQuitSignal;
}
