/////////////////////////////////////////////////////////////////////////////
// Name:        mainform.cpp
// Purpose:     
// Author:      Sergey Talipov
// Modified by: 
// Created:     28/02/2025 18:16:12
// RCS-ID:      
// Copyright:   15681627-3C745D8E-630127F2
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Launcher.h"
////@begin includes
////@end includes

#include "mainform.h"
#include <wx/timer.h>      // Таймер
#include <wx/dir.h>        // Работа с директориями
#include <wx/stdpaths.h>   // Стандартные пути (например, путь к исполняемому файлу)
#include <wx/filename.h>   // Работа с именами файлов и путями
#include <wx/msgdlg.h>     // Диалоговые окна сообщений (например, ошибки, предупреждения)
#include <wx/config.h>     // Работа с конфигурационными файлами или реестром
#include <wx/fileconf.h>   // Заголовок для использования wxFileConfig
#include <wx/filefn.h>     // Функции для работы с файлами (копирование, удаление и т.д.)
#include <wx/textfile.h>   // Работа с текстовыми файлами

////@begin XPM images
#include "tsnsoft.xpm"
#include "home.xpm"
#include "dialogblocks.xpm"
////@end XPM images
#include "rpcpp.xpm"
#include "visualstudio.xpm"
#include "visualstudiocode.xpm"

// Константа для имени конфигурационного файла
const wxString CONFIG_FILE_NAME = L"wxProjectCreator.ini";


/*
 * MainForm type definition
 */

IMPLEMENT_CLASS(MainForm, wxFrame)


/*
 * MainForm event table definition
 */

	BEGIN_EVENT_TABLE(MainForm, wxFrame)

	////@begin MainForm event table entries
    EVT_BUTTON( BUTTON_CREATE, MainForm::OnCreateProject )
    EVT_CHOICE( CHOICE_TYPE, MainForm::OnTemplateChoice )
    EVT_BUTTON( ID_BITMAPBUTTON, MainForm::OnBitmapbuttonClick )
	////@end MainForm event table entries

	END_EVENT_TABLE()


	/*
	 * MainForm constructors
	 */

	MainForm::MainForm()
{
	Init();
}

MainForm::MainForm(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
	Init();
	Create(parent, id, caption, pos, size, style);

	// Инициализация бегущей строки
	m_originalText = L"✬   -=TSN Soft=-    ✬    г. Павлодар, 2025-2026 г.    ✬ https://github.com/tsnsoft    ";
	m_offset = 0;

	// Настройка таймера
	m_timer.SetOwner(this, 1); // Установка владельца таймера
	Bind(wxEVT_TIMER, &MainForm::OnTimer, this); // Привязка события таймера
	m_timer.Start(20); // Запуск таймера с интервалом 20мс

	wxPanel* panel = (wxPanel*)FindWindow(PANEL_SCROLL_TEXT);
	if (panel) {
		panel->SetDoubleBuffered(true); // Включение двойной буферизации
	}

	// Вызов OnTemplateChoice для инициализации состояния элементов
	wxCommandEvent dummyEvent;
	OnTemplateChoice(dummyEvent);
}


/*
 * MainForm creator
 */
void LoadSettings(); // прототип функции для работы при создании mainform

bool MainForm::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
	////@begin MainForm creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    this->SetBackgroundColour(wxColour(240, 240, 240));
    CreateControls();
    SetIcon(GetIconResource(wxT("tsnsoft.xpm")));
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
	////@end MainForm creation
		// Загружаем настройки из файла конфигурации
	LoadSettings();
	return true;
}


/*
 * MainForm destructor
 */

MainForm::~MainForm()
{
	////@begin MainForm destruction
	////@end MainForm destruction
}


/*
 * Member initialisation
 */

void MainForm::Init()
{
	////@begin MainForm member initialisation
	////@end MainForm member initialisation
}


/*
 * Control creation for MainForm
 */

void MainForm::CreateControls()
{
	////@begin MainForm content construction
    MainForm* itemFrame1 = this;

    wxGridBagSizer* itemGridBagSizer1 = new wxGridBagSizer(0, 0);
    itemGridBagSizer1->SetEmptyCellSize(wxSize(10, 19));
    itemFrame1->SetSizer(itemGridBagSizer1);

    wxButton* itemButton1 = new wxButton( itemFrame1, BUTTON_CREATE, wxT("Создать проект"), wxDefaultPosition, wxSize(150, -1), 0 );
    itemButton1->SetBackgroundColour(wxColour(239, 254, 237));
    itemButton1->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemButton1, wxGBPosition(5, 0), wxGBSpan(1, 3), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 6);

    wxTextCtrl* itemTextCtrl3 = new wxTextCtrl( itemFrame1, CTRL_MINGW_PATH, wxT("D:\\Development\\RedPanda-CPP\\mingw64"), wxDefaultPosition, wxSize(370, 28), 0 );
    itemTextCtrl3->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemTextCtrl3, wxGBPosition(4, 1), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 8);

    wxTextCtrl* itemTextCtrl2 = new wxTextCtrl( itemFrame1, CTRL_WIDGETS_PATH, wxT("D:\\Development\\RedPanda-CPP\\wxWidgets"), wxDefaultPosition, wxSize(370, 28), 0 );
    itemTextCtrl2->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemTextCtrl2, wxGBPosition(3, 1), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 8);

    wxTextCtrl* itemTextCtrl1 = new wxTextCtrl( itemFrame1, CTRL_PROJECT_NAME, wxT("wxProject1"), wxDefaultPosition, wxSize(370, 28), 0 );
    itemTextCtrl1->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemTextCtrl1, wxGBPosition(0, 1), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox2 = new wxCheckBox( itemFrame1, CHECKBOX_VISUAL, wxT("Визуальная программа"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox2->SetValue(false);
    itemCheckBox2->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemCheckBox2, wxGBPosition(2, 0), wxGBSpan(1, 2), wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 6);

    wxArrayString itemChoice3Strings;
    itemChoice3Strings.Add(wxT("DialogBlocks"));
    itemChoice3Strings.Add(wxT("RedPanda-CPP"));
    itemChoice3Strings.Add(wxT("Visual Studio"));
    itemChoice3Strings.Add(wxT("Visual Studio Code"));
    wxChoice* itemChoice3 = new wxChoice( itemFrame1, CHOICE_TYPE, wxDefaultPosition, wxSize(370, 28), itemChoice3Strings, 0 );
    itemChoice3->SetStringSelection(wxT("DialogBlocks"));
    itemChoice3->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemChoice3, wxGBPosition(1, 1), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemFrame1, TEXT_PROJECT_NAME, wxT("Имя для нового проекта:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText4->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemStaticText4, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 6);

    wxStaticText* itemStaticText1 = new wxStaticText( itemFrame1, TEXT_TYPE, wxT("Для какой IDE проект:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText1->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemStaticText1, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 6);

    wxBitmapButton* itemBitmapButton1 = new wxBitmapButton( itemFrame1, ID_BITMAPBUTTON, itemFrame1->GetBitmapResource(wxT("home.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    if (MainForm::ShowToolTips())
        itemBitmapButton1->SetToolTip(wxT("На сайт программы"));
    itemGridBagSizer1->Add(itemBitmapButton1, wxGBPosition(7, 2), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemFrame1, TEXT_MINGW_PATH, wxT("Путь к компилятору:\n(без пробелов)"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText5->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemStaticText5, wxGBPosition(4, 0), wxGBSpan(1, 1), wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 6);

    wxStaticText* itemStaticText2 = new wxStaticText( itemFrame1, TEXT_WIDGETS_PATH, wxT("Путь к сборке wxWidgets:\n(без пробелов)"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText2->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma")));
    itemGridBagSizer1->Add(itemStaticText2, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 6);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemGridBagSizer1->Add(itemBoxSizer3, wxGBPosition(6, 0), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxPanel* itemPanel4 = new wxPanel( itemFrame1, ID_PANEL, wxDefaultPosition, wxSize(-1, 95), wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel4->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    itemBoxSizer3->Add(itemPanel4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBitmap* itemStaticBitmap5 = new wxStaticBitmap( itemFrame1, IMAGE_TYPE, itemFrame1->GetBitmapResource(wxT("dialogblocks.xpm")), wxDefaultPosition, wxSize(118, 95), 0 );
    itemBoxSizer3->Add(itemStaticBitmap5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxPanel* itemPanel6 = new wxPanel( itemFrame1, ID_PANEL1, wxDefaultPosition, wxSize(-1, 95), wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel6->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    itemBoxSizer3->Add(itemPanel6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxPanel* itemPanel1 = new wxPanel( itemFrame1, PANEL_SCROLL_TEXT, wxDefaultPosition, wxSize(530, 35), wxNO_BORDER|wxTAB_TRAVERSAL );
    itemPanel1->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    itemGridBagSizer1->Add(itemPanel1, wxGBPosition(7, 0), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);

    // Connect events and objects
    itemPanel1->Connect(PANEL_SCROLL_TEXT, wxEVT_PAINT, wxPaintEventHandler(MainForm::OnPaint), NULL, this);
	////@end MainForm content construction
}

/*
 * Should we show tooltips?
 */

bool MainForm::ShowToolTips()
{
	return true;
}

/*
 * Get bitmap resources
 */

wxBitmap MainForm::GetBitmapResource(const wxString& name)
{
	// Bitmap retrieval
////@begin MainForm bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("home.xpm"))
    {
        wxBitmap bitmap(home_xpm);
        return bitmap;
    }
    else if (name == wxT("dialogblocks.xpm"))
    {
        wxBitmap bitmap(dialogblocks_xpm);
        return bitmap;
    }
    return wxNullBitmap;
	////@end MainForm bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MainForm::GetIconResource(const wxString& name)
{
	// Icon retrieval
////@begin MainForm icon retrieval
    wxUnusedVar(name);
    if (name == wxT("tsnsoft.xpm"))
    {
        wxIcon icon(tsnsoft_xpm);
        return icon;
    }
    return wxNullIcon;
	////@end MainForm icon retrieval
}


// Прототипы функций
void CopyDirectory(const wxString& source, const wxString& destination); // Копирование директории
void ReplaceInFile(const wxString& filePath, const wxString& projectName, wxString wxWidgetsPath, wxString mingwPath); // Замена в файле
void SaveSettings(); // Сохранение настроек


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

 // Создание проекта
void MainForm::OnCreateProject(wxCommandEvent& event)
{
	wxTextCtrl* projectNameCtrl = (wxTextCtrl*)FindWindow(CTRL_PROJECT_NAME); // Получаем указатель на поле ввода имени проекта
	wxChoice* templateChoice = (wxChoice*)FindWindow(CHOICE_TYPE); // Получаем указатель на выпадающий список
	wxCheckBox* visualCheckBox = (wxCheckBox*)FindWindow(CHECKBOX_VISUAL); // Получаем указатель на чекбокс
	wxTextCtrl* wxWidgetsPathCtrl = (wxTextCtrl*)FindWindow(CTRL_WIDGETS_PATH); // Получаем указатель на поле ввода пути к wxWidgets
	wxTextCtrl* mingwPathCtrl = (wxTextCtrl*)FindWindow(CTRL_MINGW_PATH); // Получаем указатель на поле ввода пути к MinGW

	wxString projectName = projectNameCtrl->GetValue(); // Получаем имя проекта
	if (projectName.IsEmpty()) { // Если имя проекта не введено, выводим сообщение об ошибке
		wxMessageBox(L"Введите имя проекта", L"Ошибка", wxOK | wxICON_ERROR);
		return;
	}

	wxString templateType = templateChoice->GetStringSelection(); // Получаем выбранный тип шаблона
	wxString basePath = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath(); // Получаем путь к исполняемому файлу
	wxString projectPath = basePath + L"/" + projectName; // Формируем путь к директории проекта

	// Создаем директорию проекта и проверяем, что она создалась
	if (!wxFileName::Mkdir(projectPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL)) {
		wxMessageBox(L"Не удалось создать директорию проекта", L"Ошибка", wxOK | wxICON_ERROR);
		return;
	}

	wxString templatePath; // Путь к шаблону проекта
	
	if (templateType == L"DialogBlocks") { // Выбран шаблон DialogBlocks
		if (visualCheckBox->GetValue())
			templatePath = basePath + L"/templates/dialogblocks_visual";
		else
			templatePath = basePath + L"/templates/dialogblocks_console";
	}
	else if (templateType == L"RedPanda-CPP") { // Выбран шаблон RedPanda-CPP
		if (visualCheckBox->GetValue())
			templatePath = basePath + L"/templates/redpanda_visual";
		else
			templatePath = basePath + L"/templates/redpanda_console";
	}
	else if (templateType == L"Visual Studio") { // Выбран шаблон Visual Studio
		if (visualCheckBox->GetValue())
			templatePath = basePath + L"/templates/vs_visual";
		else
			templatePath = basePath + L"/templates/vs_console";
	}
	else if (templateType == L"Visual Studio Code") { // Выбран шаблон Visual Studio Code
		if (visualCheckBox->GetValue())
			templatePath = basePath + L"/templates/vscode_visual";
		else
			templatePath = basePath + L"/templates/vscode_console";
	}

	wxString commonPath = basePath + L"/templates/common"; // Путь к общим файлам для всех шаблонов
	SaveSettings(); // Сохраняем настройки в файл
	CopyDirectory(templatePath, projectPath); // Копируем файлы шаблона в директорию проекта
	CopyDirectory(commonPath, projectPath); // Копируем общие файлы в директорию проекта

	wxString wxWidgetsPath = wxWidgetsPathCtrl->GetValue(); // Получаем путь к wxWidgets
	wxString mingwPath = mingwPathCtrl->GetValue(); // Получаем путь к MinGW

	// Переименовываем файлы проекта и заменяем в файлах проекта значения на введенные пользователем --------------------------------
	if (templateType == L"RedPanda-CPP") { // Если выбран шаблон RedPanda-CPP
		wxString devFilePath = projectPath + L"/redpanda-cpp.dev";
		wxString newDevFilePath = projectPath + L"/" + projectName + L".dev";
		if (wxFileExists(devFilePath)) {
			if (!wxRenameFile(devFilePath, newDevFilePath)) {
				wxMessageBox(L"Не удалось переименовать dev файл", L"Ошибка", wxOK | wxICON_ERROR);
				return;
			}
			ReplaceInFile(newDevFilePath, projectName, wxWidgetsPath, mingwPath);
		}
	}
	else if (templateType == L"DialogBlocks") { // Если выбран шаблон DialogBlocks
		wxString pjdFilePath = projectPath + L"/dialogblocks.pjd";
		wxString newPjdFilePath = projectPath + L"/" + projectName + L".pjd";
		if (wxFileExists(pjdFilePath)) {
			if (!wxRenameFile(pjdFilePath, newPjdFilePath)) {
				wxMessageBox(L"Не удалось переименовать pjd файл", L"Ошибка", wxOK | wxICON_ERROR);
				return;
			}
			ReplaceInFile(newPjdFilePath, projectName, wxWidgetsPath, mingwPath);
		}
	}
	else if (templateType == L"Visual Studio") { // Если выбран шаблон Visual Studio
		wxString slnFilePath = projectPath + L"/vs2022.sln";
		wxString newSlnFilePath = projectPath + L"/" + projectName + L".sln";
		if (wxFileExists(slnFilePath)) {
			if (!wxRenameFile(slnFilePath, newSlnFilePath)) {
				wxMessageBox(L"Не удалось переименовать sln файл", L"Ошибка", wxOK | wxICON_ERROR);
				return;
			}
			ReplaceInFile(newSlnFilePath, projectName, wxWidgetsPath, mingwPath);
		}
		wxString vcxFilePath = projectPath + L"/vs2022.vcxproj";
		wxString newVcxFilePath = projectPath + L"/" + projectName + L".vcxproj";
		if (wxFileExists(vcxFilePath)) {
			if (!wxRenameFile(vcxFilePath, newVcxFilePath)) {
				wxMessageBox(L"Не удалось переименовать vcxproj файл", L"Ошибка", wxOK | wxICON_ERROR);
				return;
			}
			ReplaceInFile(newVcxFilePath, projectName, wxWidgetsPath, mingwPath);
		}
	}
	else if (templateType == L"Visual Studio Code") { // Если выбран шаблон Visual Studio Code
		wxString tasksFilePath = projectPath + L"/.vscode/tasks.json";
		wxString launchFilePath = projectPath + L"/.vscode/launch.json";
		wxString propertiesFilePath = projectPath + L"/.vscode/c_cpp_properties.json";
		if (wxFileExists(tasksFilePath)) {
			ReplaceInFile(tasksFilePath, projectName, wxWidgetsPath, mingwPath);
		}
		if (wxFileExists(launchFilePath)) {
			ReplaceInFile(launchFilePath, projectName, wxWidgetsPath, mingwPath);
		}
		if (wxFileExists(propertiesFilePath)) {
			ReplaceInFile(propertiesFilePath, projectName, wxWidgetsPath, mingwPath);
		}
	}
	// ------------------------------------------------------------------------------------------------

	wxMessageBox(L"Проект создан", L"Готово", wxOK | wxICON_INFORMATION);
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

 // Изменение выбора шаблона
void MainForm::OnTemplateChoice(wxCommandEvent& event)
{
	wxChoice* templateChoice = (wxChoice*)FindWindow(CHOICE_TYPE);
	wxStaticText* wxWidgetsLabel = (wxStaticText*)FindWindow(TEXT_WIDGETS_PATH);
	wxTextCtrl* wxWidgetsPathCtrl = (wxTextCtrl*)FindWindow(CTRL_WIDGETS_PATH);
	wxStaticText* mingwLabel = (wxStaticText*)FindWindow(TEXT_MINGW_PATH);
	wxTextCtrl* mingwPathCtrl = (wxTextCtrl*)FindWindow(CTRL_MINGW_PATH);
	wxStaticBitmap* m_imageBitmap = (wxStaticBitmap*)FindWindow(IMAGE_TYPE);
	int sel = templateChoice->GetSelection(); // Получаем выбранный индекс
	if (sel == 1 || sel == 2 || sel == 3) { // Показываем поле для wxWidgets только для RedPanda-CPP, Visual Studio и Visual Studio Code
		wxWidgetsLabel->Show();
		wxWidgetsPathCtrl->Show();
	}
	else { // Скрываем поле для wxWidgets для DialogBlocks
		wxWidgetsLabel->Hide();
		wxWidgetsPathCtrl->Hide();
	}

	// Показываем поле для MinGW только для Visual Studio Code
	if (sel == 3) {
		mingwLabel->Show();
		mingwPathCtrl->Show();
	}
	else { // Скрываем поле для MinGW для остальных шаблонов
		mingwLabel->Hide();
		mingwPathCtrl->Hide();
	}

	// Меняем картинку в зависимости от выбора пользователя
	if (m_imageBitmap) {
		if (sel == 0) {
			m_imageBitmap->SetBitmap(wxBitmap(dialogblocks_xpm));
		}
		else if (sel == 1) {
			m_imageBitmap->SetBitmap(wxBitmap(rpcpp_xpm));
		}
		else if (sel == 2) {
			m_imageBitmap->SetBitmap(wxBitmap(visualstudio_xpm));
		}
		else if (sel == 3) {
			m_imageBitmap->SetBitmap(wxBitmap(visual_studio_code_xpm));
		}
	}
}

//Функции

// --- Функция загрузки настроек приложения из файла рядом с exe ---
void LoadSettings()
{
	// Получаем указатель на главное окно
	MainForm* frame = wxDynamicCast(wxGetApp().GetTopWindow(), MainForm);

	wxTextCtrl* projectNameCtrl = (wxTextCtrl*)frame->FindWindowById(CTRL_PROJECT_NAME);
	wxChoice* templateChoice = (wxChoice*)frame->FindWindowById(CHOICE_TYPE);
	wxTextCtrl* wxWidgetsPathCtrl = (wxTextCtrl*)frame->FindWindowById(CTRL_WIDGETS_PATH);
	wxTextCtrl* mingwPathCtrl = (wxTextCtrl*)frame->FindWindowById(CTRL_MINGW_PATH);
	wxCheckBox* visualCheckBox = (wxCheckBox*)frame->FindWindowById(CHECKBOX_VISUAL);

	// Получаем пути к файлам
	wxString exePath = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath();
	
	// Формируем путь к файлу конфигурации
	wxString configPath = exePath + wxFILE_SEP_PATH + CONFIG_FILE_NAME;

	// Создаем объект для работы с конфигурационным файлом
	wxFileConfig config("ProjectCreator", wxEmptyString, configPath, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
	wxString projectName, wxWidgetsPath, mingwPath; // Переменные для хранения значений из файла
	int templateIndex; // Индекс выбранного шаблона
	if (config.Read(L"ProjectName", &projectName)) { // Загружаем имя проекта
		projectNameCtrl->SetValue(projectName);
	}
	if (config.Read(L"TemplateType", &templateIndex)) { // Загружаем тип шаблона
		templateChoice->SetSelection(templateIndex);
	}
	if (config.Read(L"WxWidgetsPath", &wxWidgetsPath)) { // Загружаем путь к wxWidgets
		wxWidgetsPathCtrl->SetValue(wxWidgetsPath);
	}
	if (config.Read(L"MingwPath", &mingwPath)) { // Загружаем путь к MinGW
		mingwPathCtrl->SetValue(mingwPath);
	}
	long visualProgram = 0; // Переменная для хранения значения визуальной программы
	if (config.Read(L"VisualProgram", &visualProgram)) { // Загружаем значение визуальной программы
		visualCheckBox->SetValue(visualProgram == 1);
	}
}

// --- Функция сохранения настроек приложения в файл рядом с exe ---
void SaveSettings()
{
	MainForm* frame = wxDynamicCast(wxGetApp().GetTopWindow(), MainForm); // Получаем указатель на главное окно
	wxTextCtrl* projectNameCtrl = (wxTextCtrl*)frame->FindWindowById(CTRL_PROJECT_NAME);
	wxChoice* templateChoice = (wxChoice*)frame->FindWindowById(CHOICE_TYPE);
	wxTextCtrl* wxWidgetsPathCtrl = (wxTextCtrl*)frame->FindWindowById(CTRL_WIDGETS_PATH);
	wxTextCtrl* mingwPathCtrl = (wxTextCtrl*)frame->FindWindowById(CTRL_MINGW_PATH);
	wxCheckBox* visualCheckBox = (wxCheckBox*)frame->FindWindowById(CHECKBOX_VISUAL);
	wxString exePath = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath(); // Получаем путь к исполняемому файлу
	wxString configPath = exePath + wxFILE_SEP_PATH + CONFIG_FILE_NAME; // Формируем путь к файлу конфигурации
	wxFileConfig config("ProjectCreator", wxEmptyString, configPath, wxEmptyString, wxCONFIG_USE_LOCAL_FILE); // Создаем объект для работы с конфигурационным файлом
	config.Write(L"ProjectName", projectNameCtrl->GetValue()); // Сохраняем имя проекта
	config.Write(L"TemplateType", templateChoice->GetSelection()); // Сохраняем тип шаблона
	config.Write(L"WxWidgetsPath", wxWidgetsPathCtrl->GetValue()); // Сохраняем путь к wxWidgets
	config.Write(L"MingwPath", mingwPathCtrl->GetValue()); // Сохраняем путь к MinGW
	config.Write(L"VisualProgram", visualCheckBox->GetValue() ? 1 : 0); // Сохраняем значение визуальной программы
	config.Flush(); // Сохраняем изменения
}


// Функция для копирования директории (рекурсивно копирует файлы и поддиректории)
void MainForm::CopyDirectory(const wxString& source, const wxString& destination)
{
	wxDir dir(source); // Создаем объект для работы с директорией
	if (!dir.IsOpened()) { // Если не удалось открыть директорию, выводим сообщение об ошибке
		wxMessageBox(L"Не удалось открыть директорию", L"Ошибка", wxOK | wxICON_ERROR);
		return;
	}

	wxString filename; // Переменная для хранения имени файла
	bool cont = dir.GetFirst(&filename); // Получаем первый файл в директории
	while (cont) { // Пока есть файлы в директории
		wxString sourcePath = source + "/" + filename; // Формируем путь к исходному файлу
		wxString destPath = destination + "/" + filename; // Формируем путь к файлу назначения
		if (wxDirExists(sourcePath)) { // Если это директория, то рекурсивно копируем ее
			wxFileName::Mkdir(destPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL); // Создаем директорию
			CopyDirectory(sourcePath, destPath); // Рекурсивно копируем файлы и поддиректории
		}
		else if (wxFileExists(sourcePath)) { // Если это файл, то копируем его
			wxCopyFile(sourcePath, destPath); // Копируем файл
		}

		cont = dir.GetNext(&filename); // Получаем следующий файл в директории
	}
}

// Функция для замены содержимого файла
void MainForm::ReplaceInFile(const wxString& filePath, const wxString& projectName, wxString wxWidgetsPath, wxString mingwPath)
{
	// Нормализация путей: заменяем все обратные слэши (\) на прямые (/)
	if (!wxWidgetsPath.IsEmpty()) { // Если путь к wxWidgets не пустой
		wxWidgetsPath.Replace("\\", "/"); // Заменяем обратные слэши на прямые
		if (!wxWidgetsPath.EndsWith("/")) { // Если путь не заканчивается на прямой слэш
			wxWidgetsPath.Append("/"); // Добавляем прямой слэш в конец
		}
	}
	if (!mingwPath.IsEmpty()) { // Если путь к MinGW не пустой
		mingwPath.Replace("\\", "/"); // Заменяем обратные слэши на прямые
		if (!mingwPath.EndsWith("/")) { // Если путь не заканчивается на прямой слэш
			mingwPath.Append("/"); // Добавляем прямой слэш в конец
		}
	}

	wxTextFile file; // Создаем объект для работы с текстовым файлом
	if (!file.Open(filePath)) { // Если не удалось открыть файл для чтения, выводим сообщение об ошибке
		wxMessageBox(L"Не удалось открыть файл для чтения", L"Ошибка", wxOK | wxICON_ERROR);
		return;
	}

	wxString content; // Переменная для хранения содержимого файла
	
	// Читаем содержимое файла
	for (content = file.GetFirstLine(); !file.Eof(); content += file.GetNextLine() + "\n") {}

	// Закрываем файл
	file.Close();

	content.Replace("RPCPP_wx_App", projectName); // Заменяем в тексте файла значение RPCPP_wx_App на имя проекта
	content.Replace("DialogBlocks_wx_App", projectName); // Заменяем в тексте файла значение DialogBlocks_wx_App на имя проекта
	content.Replace("vs2022", projectName); // Заменяем в тексте файла значение vs2022 на имя проекта

	if (!wxWidgetsPath.IsEmpty()) { // Если путь к wxWidgets не пустой
		content.Replace("D:/Development/RedPanda-CPP/wxWidgets/", wxWidgetsPath); // Заменяем в тексте файла путь к wxWidgets
		content.Replace("D:\\Development\\RedPanda-CPP\\wxWidgets\\", wxWidgetsPath); // Заменяем в тексте файла путь к wxWidgets
		content.Replace("D:\\Development\\RedPanda-CPP\\wxWidgets/", wxWidgetsPath); // Заменяем в тексте файла путь к wxWidgets
	}

	if (!mingwPath.IsEmpty()) { // Если путь к MinGW не пустой
		content.Replace("D:/Development/RedPanda-CPP/mingw64/", mingwPath); // Заменяем в тексте файла путь к MinGW
		content.Replace("D:\\Development\\RedPanda-CPP\\mingw64\\", mingwPath); // Заменяем в тексте файла путь к MinGW
		content.Replace("D:\\Development\\RedPanda-CPP\\mingw64/", mingwPath); // Заменяем в тексте файла путь к MinGW
	}

	file.Clear(); // Очищаем содержимое файла
	file.AddLine(content); // Добавляем новое содержимое
	file.Write(); // Записываем содержимое в файл
	file.Close(); // Закрываем файл	
}


/*
 * wxEVT_PAINT event handler for ID_PANEL2
 */

 // Обработчик события рисования панели для бегущей строки
void MainForm::OnPaint(wxPaintEvent& event)
{
	wxPanel* panel = (wxPanel*)FindWindow(PANEL_SCROLL_TEXT); // Получаем указатель на панель
	if (!panel) return; // Если панель не найдена, выходим из функции

	wxPaintDC dc(panel); // Создаем объект для рисования
	dc.SetFont(panel->GetFont()); // Устанавливаем шрифт
	dc.Clear(); // Очищаем панель

	int width, height; // Переменные для хранения ширины и высоты панели
	panel->GetSize(&width, &height); // Получаем размеры панели

	// Рассчитываем ширину текста
	int textWidth = dc.GetTextExtent(m_originalText).GetWidth(); // Получаем ширину текста

	// Позиция первого экземпляра текста
	int x1 = width - m_offset; // Рассчитываем позицию первого экземпляра текста
	int y = (height - dc.GetCharHeight()) / 2; // Рассчитываем позицию текста по вертикали

	// Рисуем первый экземпляр текста
	dc.DrawText(m_originalText, x1, y); // Рисуем текст

	// Рисуем второй экземпляр текста для создания эффекта бесшовной прокрутки
	dc.DrawText(m_originalText, x1 - textWidth, y);
}

/*
 * wxEVT_TIMER event handler for 1
 */
 
 // Обработчик события таймера для бегущей строки
void MainForm::OnTimer(wxTimerEvent& event)
{
	wxPanel* panel = (wxPanel*)FindWindow(PANEL_SCROLL_TEXT); // Получаем указатель на панель
	if (!panel) return; // Если панель не найдена, выходим из функции

	int width; // Переменная для хранения ширины панели
	panel->GetSize(&width, nullptr); // Получаем ширину панели

	wxClientDC dc(panel); // Создаем объект для рисования
	dc.SetFont(panel->GetFont()); // Устанавливаем шрифт
	int textWidth = dc.GetTextExtent(m_originalText).GetWidth(); // Получаем ширину текста

	// Увеличиваем смещение
	m_offset += 2; // Шаг перемещения (можно настроить скорость)

	// Если текст полностью ушел за левый край, сбрасываем смещение
	if (m_offset >= textWidth) {
		m_offset = 0; // Сброс смещения для повторного появления текста
	}

	// Перерисовываем панель
	panel->Refresh();
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON
 */

void MainForm::OnBitmapbuttonClick( wxCommandEvent& event )
{
    wxLaunchDefaultBrowser("https://github.com/tsnsoft/wxProjectCreator/releases");
}

