/////////////////////////////////////////////////////////////////////////////
// Name:        mainform.h
// Purpose:     
// Author:      Sergey Talipov
// Modified by: 
// Created:     28/02/2025 18:16:12
// RCS-ID:      
// Copyright:   15681627-3C745D8E-630127F2
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAINFORM_H_
#define _MAINFORM_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
#include "wx/gbsizer.h"
////@end includes
/*!
 * Forward declarations
 */
#include <wx/timer.h>
////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MAINFORM 10000
#define BUTTON_CREATE 10001
#define CTRL_MINGW_PATH 10014
#define CTRL_WIDGETS_PATH 10005
#define CTRL_PROJECT_NAME 10002
#define CHECKBOX_VISUAL 10003
#define CHOICE_TYPE 10004
#define TEXT_PROJECT_NAME 10010
#define TEXT_TYPE 10009
#define ID_BITMAPBUTTON 10015
#define TEXT_MINGW_PATH 10013
#define TEXT_WIDGETS_PATH 10008
#define ID_PANEL 10006
#define IMAGE_TYPE 10011
#define ID_PANEL1 10007
#define PANEL_SCROLL_TEXT 10012
#define SYMBOL_MAINFORM_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_MAINFORM_TITLE wxT("wxProjectCreator для wxWidgets 3.4 (ver.11)")
#define SYMBOL_MAINFORM_IDNAME ID_MAINFORM
#define SYMBOL_MAINFORM_SIZE wxSize(540, 380)
#define SYMBOL_MAINFORM_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * MainForm class declaration
 */

class MainForm: public wxFrame
{    
    DECLARE_CLASS( MainForm )
    DECLARE_EVENT_TABLE()
private:
    wxString m_originalText;
    int m_offset;
    wxTimer m_timer;
    void OnTimer(wxTimerEvent& event);
public:
    /// Constructors
    MainForm();
    MainForm( wxWindow* parent, wxWindowID id = SYMBOL_MAINFORM_IDNAME, const wxString& caption = SYMBOL_MAINFORM_TITLE, const wxPoint& pos = SYMBOL_MAINFORM_POSITION, const wxSize& size = SYMBOL_MAINFORM_SIZE, long style = SYMBOL_MAINFORM_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MAINFORM_IDNAME, const wxString& caption = SYMBOL_MAINFORM_TITLE, const wxPoint& pos = SYMBOL_MAINFORM_POSITION, const wxSize& size = SYMBOL_MAINFORM_SIZE, long style = SYMBOL_MAINFORM_STYLE );

    void CopyDirectory(const wxString& source, const wxString& destination);
    void ReplaceInFile(const wxString& filePath, const wxString& projectName, wxString wxWidgetsPath, wxString mingwPath);
    /// Destructor
    ~MainForm();

    /// Initialises member variables
    
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin MainForm event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for BUTTON_CREATE
    void OnCreateProject( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for CHOICE_TYPE
    void OnTemplateChoice( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON
    void OnBitmapbuttonClick( wxCommandEvent& event );

    /// wxEVT_PAINT event handler for PANEL_SCROLL_TEXT
    void OnPaint( wxPaintEvent& event );

////@end MainForm event handler declarations
////@begin MainForm member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MainForm member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin MainForm member variables
////@end MainForm member variables
};

#endif
    // _MAINFORM_H_
