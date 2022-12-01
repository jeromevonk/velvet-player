#pragma once

#include "StdAfx.h"

// The other forms
#include "Edit_ID3.h"
#include "About.h"

// Include MCI wrapper
#include "MCI_interface.h"

bool g_bShuffle  = false;
bool g_bAutosize = true;


namespace VelvetPlayer {

   using namespace System;
   using namespace System::ComponentModel;
   using namespace System::Collections;
   using namespace System::Windows::Forms;
   using namespace System::Data;
   using namespace System::Drawing;
   using namespace System::IO;
   using namespace System::Runtime::InteropServices; // for Marshal::

   #define MAX_FILE_LEN 220  // = 256 - sizeof("open \"\" type mpegvideo alias MCI_App")
   #define SESSION_FILE "velvetplayer.dat"

   typedef enum EState_tag
   {
      STOPPED = 0,
      PAUSED,
      PLAYING
   } EState;

   public ref class Main : public System::Windows::Forms::Form
   {
   public:
      Main(void)
      {
         InitializeComponent();
         MCI = new CMCI_interface("velvet");
         RestoreSession();
      }

   protected:
      ~Main()
      {
         if (components)
         {
            delete components;
         }
      }

   // Object to MCI wrapper
   private: CMCI_interface* MCI;

   // The state of the application
   private: static EState m_State = STOPPED;

   // Pick up random numbers
   private: static Random^ rnd = gcnew Random();

   // A list of the shuffled songs
   private: static System::Collections::Generic::List<int>^ L_Songs = gcnew System::Collections::Generic::List<int>();


   // ------------------------------------------------------------------
   // Windows forms items
   // ------------------------------------------------------------------
   private: System::Windows::Forms::MenuStrip^  menuStrip;
   private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
   private: System::Windows::Forms::Button^  btPlay;
   private: System::Windows::Forms::Button^  btStop;
   private: System::Windows::Forms::GroupBox^  groupBox2;
   private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem1;
   private: System::Windows::Forms::ToolStripMenuItem^  songToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  PlaylistToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  openFileStripMenuItem2;
   private: System::Windows::Forms::Button^  btNext;
   private: System::Windows::Forms::Label^  lbVolume;
   private: System::Windows::Forms::TextBox^  tbPosition;
   private: System::Windows::Forms::TrackBar^  trbVolume;
   private: System::Windows::Forms::TrackBar^  trbProgress;
   private: System::Windows::Forms::Button^  btPrevious;
   private: System::Windows::Forms::Timer^  timer;
   private: System::Windows::Forms::ListView^  playlist;
   private: System::Windows::Forms::ColumnHeader^  clmFileName;
   private: System::Windows::Forms::StatusStrip^  statusStrip1;
   private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel;
   private: System::Windows::Forms::ToolStripMenuItem^  shuffleToolStripMenuItem;
   private: System::ComponentModel::IContainer^  components;
   private: System::Windows::Forms::ColumnHeader^  clmPath;
   private: System::Windows::Forms::ColumnHeader^  clmSongName;
   private: System::Windows::Forms::ColumnHeader^  clmArtist;
   private: System::Windows::Forms::ColumnHeader^  clmAlbum;
   private: System::Windows::Forms::ColumnHeader^  clmLength;
   private: System::Windows::Forms::ToolStripMenuItem^  iD3TagToolStripMenuItem;
   private: System::Windows::Forms::Button^  btPause;
   private: System::Windows::Forms::ToolStripMenuItem^  removeAllToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
   private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
   private: System::Windows::Forms::ToolStripMenuItem^  fontColorToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  editFontToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  editColorToolStripMenuItem;
   private: System::Windows::Forms::ColorDialog^  colorDialog;
   private: System::Windows::Forms::FontDialog^  fontDialog;
   private: System::Windows::Forms::ToolStripMenuItem^  openFolderToolStripMenuItem;
   private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
   private: System::Windows::Forms::ToolStripMenuItem^  showColumnsToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  filenameToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  pathToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  resetToDefaultToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  autosizeColumnsToolStripMenuItem;
   private: System::Windows::Forms::ToolStripMenuItem^  removeToolStripMenuItem;


#pragma region Windows Form Designer generated code
      /// <summary>
      /// Required method for Designer support - do not modify
      /// the contents of this method with the code editor.
      /// </summary>
      void InitializeComponent(void)
      {
         this->components = (gcnew System::ComponentModel::Container());
         System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager( Main::typeid ));
         this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
         this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->openFileStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->openFolderToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
         this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->songToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->iD3TagToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->removeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->PlaylistToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->shuffleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->autosizeColumnsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->fontColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->editFontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->editColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->resetToDefaultToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->removeAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->showColumnsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->pathToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->filenameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->openToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
         this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
         this->btPlay = (gcnew System::Windows::Forms::Button());
         this->btStop = (gcnew System::Windows::Forms::Button());
         this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
         this->btPause = (gcnew System::Windows::Forms::Button());
         this->btPrevious = (gcnew System::Windows::Forms::Button());
         this->btNext = (gcnew System::Windows::Forms::Button());
         this->lbVolume = (gcnew System::Windows::Forms::Label());
         this->tbPosition = (gcnew System::Windows::Forms::TextBox());
         this->trbVolume = (gcnew System::Windows::Forms::TrackBar());
         this->trbProgress = (gcnew System::Windows::Forms::TrackBar());
         this->timer = (gcnew System::Windows::Forms::Timer( this->components ));
         this->playlist = (gcnew System::Windows::Forms::ListView());
         this->clmPath = (gcnew System::Windows::Forms::ColumnHeader());
         this->clmFileName = (gcnew System::Windows::Forms::ColumnHeader());
         this->clmArtist = (gcnew System::Windows::Forms::ColumnHeader());
         this->clmSongName = (gcnew System::Windows::Forms::ColumnHeader());
         this->clmAlbum = (gcnew System::Windows::Forms::ColumnHeader());
         this->clmLength = (gcnew System::Windows::Forms::ColumnHeader());
         this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
         this->toolStripStatusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
         this->colorDialog = (gcnew System::Windows::Forms::ColorDialog());
         this->fontDialog = (gcnew System::Windows::Forms::FontDialog());
         this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
         this->menuStrip->SuspendLayout();
         this->groupBox2->SuspendLayout();
         (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVolume))->BeginInit();
         (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbProgress))->BeginInit();
         this->statusStrip1->SuspendLayout();
         this->SuspendLayout();
         // 
         // menuStrip
         // 
         this->menuStrip->Items->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 5 ) {
            this->fileToolStripMenuItem,
               this->songToolStripMenuItem, this->PlaylistToolStripMenuItem, this->aboutToolStripMenuItem, this->showColumnsToolStripMenuItem
         } );
         this->menuStrip->Location = System::Drawing::Point( 0, 0 );
         this->menuStrip->Name = L"menuStrip";
         this->menuStrip->Size = System::Drawing::Size( 694, 24 );
         this->menuStrip->TabIndex = 0;
         this->menuStrip->Text = L"menuStrip1";
         // 
         // fileToolStripMenuItem
         // 
         this->fileToolStripMenuItem->DropDownItems->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 4 ) {
            this->openFileStripMenuItem2,
               this->openFolderToolStripMenuItem, this->toolStripSeparator1, this->exitToolStripMenuItem
         } );
         this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
         this->fileToolStripMenuItem->Size = System::Drawing::Size( 37, 20 );
         this->fileToolStripMenuItem->Text = L"&File";
         // 
         // openFileStripMenuItem2
         // 
         this->openFileStripMenuItem2->Name = L"openFileStripMenuItem2";
         this->openFileStripMenuItem2->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::O));
         this->openFileStripMenuItem2->Size = System::Drawing::Size( 175, 22 );
         this->openFileStripMenuItem2->Text = L"&Open File";
         this->openFileStripMenuItem2->Click += gcnew System::EventHandler( this, &Main::openToolStripMenuItem2_Click );
         // 
         // openFolderToolStripMenuItem
         // 
         this->openFolderToolStripMenuItem->Name = L"openFolderToolStripMenuItem";
         this->openFolderToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F));
         this->openFolderToolStripMenuItem->Size = System::Drawing::Size( 175, 22 );
         this->openFolderToolStripMenuItem->Text = L"Open &Folder";
         this->openFolderToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::openFolderToolStripMenuItem_Click );
         // 
         // toolStripSeparator1
         // 
         this->toolStripSeparator1->Name = L"toolStripSeparator1";
         this->toolStripSeparator1->Size = System::Drawing::Size( 172, 6 );
         // 
         // exitToolStripMenuItem
         // 
         this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
         this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F4));
         this->exitToolStripMenuItem->Size = System::Drawing::Size( 175, 22 );
         this->exitToolStripMenuItem->Text = L"E&xit";
         this->exitToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::exitToolStripMenuItem_Click );
         // 
         // songToolStripMenuItem
         // 
         this->songToolStripMenuItem->DropDownItems->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 2 ) {
            this->iD3TagToolStripMenuItem,
               this->removeToolStripMenuItem
         } );
         this->songToolStripMenuItem->Name = L"songToolStripMenuItem";
         this->songToolStripMenuItem->Size = System::Drawing::Size( 46, 20 );
         this->songToolStripMenuItem->Text = L"&Song";
         // 
         // iD3TagToolStripMenuItem
         // 
         this->iD3TagToolStripMenuItem->Name = L"iD3TagToolStripMenuItem";
         this->iD3TagToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::E));
         this->iD3TagToolStripMenuItem->Size = System::Drawing::Size( 223, 22 );
         this->iD3TagToolStripMenuItem->Text = L"Edit ID3 tag";
         this->iD3TagToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::iD3TagToolStripMenuItem_Click );
         // 
         // removeToolStripMenuItem
         // 
         this->removeToolStripMenuItem->Name = L"removeToolStripMenuItem";
         this->removeToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::R));
         this->removeToolStripMenuItem->Size = System::Drawing::Size( 223, 22 );
         this->removeToolStripMenuItem->Text = L"Remove from playlist";
         this->removeToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::removeToolStripMenuItem_Click );
         // 
         // PlaylistToolStripMenuItem
         // 
         this->PlaylistToolStripMenuItem->Checked = true;
         this->PlaylistToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
         this->PlaylistToolStripMenuItem->DropDownItems->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 4 ) {
            this->shuffleToolStripMenuItem,
               this->autosizeColumnsToolStripMenuItem, this->fontColorToolStripMenuItem, this->removeAllToolStripMenuItem
         } );
         this->PlaylistToolStripMenuItem->Name = L"PlaylistToolStripMenuItem";
         this->PlaylistToolStripMenuItem->Size = System::Drawing::Size( 56, 20 );
         this->PlaylistToolStripMenuItem->Text = L"&Playlist";
         // 
         // shuffleToolStripMenuItem
         // 
         this->shuffleToolStripMenuItem->Name = L"shuffleToolStripMenuItem";
         this->shuffleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::S));
         this->shuffleToolStripMenuItem->Size = System::Drawing::Size( 173, 22 );
         this->shuffleToolStripMenuItem->Text = L"Shuffle";
         this->shuffleToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::shuffleToolStripMenuItem_Click );
         // 
         // autosizeColumnsToolStripMenuItem
         // 
         this->autosizeColumnsToolStripMenuItem->Checked = true;
         this->autosizeColumnsToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
         this->autosizeColumnsToolStripMenuItem->Name = L"autosizeColumnsToolStripMenuItem";
         this->autosizeColumnsToolStripMenuItem->Size = System::Drawing::Size( 173, 22 );
         this->autosizeColumnsToolStripMenuItem->Text = L"Auto-size columns";
         this->autosizeColumnsToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::autosizeColumnsToolStripMenuItem_Click );
         // 
         // fontColorToolStripMenuItem
         // 
         this->fontColorToolStripMenuItem->DropDownItems->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 3 ) {
            this->editFontToolStripMenuItem,
               this->editColorToolStripMenuItem, this->resetToDefaultToolStripMenuItem
         } );
         this->fontColorToolStripMenuItem->Name = L"fontColorToolStripMenuItem";
         this->fontColorToolStripMenuItem->Size = System::Drawing::Size( 173, 22 );
         this->fontColorToolStripMenuItem->Text = L"Font and colors";
         // 
         // editFontToolStripMenuItem
         // 
         this->editFontToolStripMenuItem->Name = L"editFontToolStripMenuItem";
         this->editFontToolStripMenuItem->Size = System::Drawing::Size( 156, 22 );
         this->editFontToolStripMenuItem->Text = L"Edit font";
         this->editFontToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::editFontToolStripMenuItem_Click );
         // 
         // editColorToolStripMenuItem
         // 
         this->editColorToolStripMenuItem->Name = L"editColorToolStripMenuItem";
         this->editColorToolStripMenuItem->Size = System::Drawing::Size( 156, 22 );
         this->editColorToolStripMenuItem->Text = L"Edit text color";
         this->editColorToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::editColorToolStripMenuItem_Click );
         // 
         // resetToDefaultToolStripMenuItem
         // 
         this->resetToDefaultToolStripMenuItem->Name = L"resetToDefaultToolStripMenuItem";
         this->resetToDefaultToolStripMenuItem->Size = System::Drawing::Size( 156, 22 );
         this->resetToDefaultToolStripMenuItem->Text = L"Reset to default";
         this->resetToDefaultToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::resetToDefaultToolStripMenuItem_Click );
         // 
         // removeAllToolStripMenuItem
         // 
         this->removeAllToolStripMenuItem->Name = L"removeAllToolStripMenuItem";
         this->removeAllToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::A));
         this->removeAllToolStripMenuItem->Size = System::Drawing::Size( 173, 22 );
         this->removeAllToolStripMenuItem->Text = L"Remove All";
         this->removeAllToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::removeAllToolStripMenuItem_Click );
         // 
         // aboutToolStripMenuItem
         // 
         this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
         this->aboutToolStripMenuItem->Size = System::Drawing::Size( 52, 20 );
         this->aboutToolStripMenuItem->Text = L"About";
         this->aboutToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::aboutToolStripMenuItem_Click );
         // 
         // showColumnsToolStripMenuItem
         // 
         this->showColumnsToolStripMenuItem->DropDownItems->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 2 ) {
            this->pathToolStripMenuItem,
               this->filenameToolStripMenuItem
         } );
         this->showColumnsToolStripMenuItem->Name = L"showColumnsToolStripMenuItem";
         this->showColumnsToolStripMenuItem->Size = System::Drawing::Size( 99, 20 );
         this->showColumnsToolStripMenuItem->Text = L"Show Columns";
         this->showColumnsToolStripMenuItem->Visible = false;
         // 
         // pathToolStripMenuItem
         // 
         this->pathToolStripMenuItem->Name = L"pathToolStripMenuItem";
         this->pathToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::D1));
         this->pathToolStripMenuItem->Size = System::Drawing::Size( 158, 22 );
         this->pathToolStripMenuItem->Text = L"Path";
         this->pathToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::pathToolStripMenuItem_Click );
         // 
         // filenameToolStripMenuItem
         // 
         this->filenameToolStripMenuItem->Name = L"filenameToolStripMenuItem";
         this->filenameToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::D2));
         this->filenameToolStripMenuItem->Size = System::Drawing::Size( 158, 22 );
         this->filenameToolStripMenuItem->Text = L"Filename";
         this->filenameToolStripMenuItem->Click += gcnew System::EventHandler( this, &Main::filenameToolStripMenuItem_Click );
         // 
         // openToolStripMenuItem1
         // 
         this->openToolStripMenuItem1->Name = L"openToolStripMenuItem1";
         this->openToolStripMenuItem1->Size = System::Drawing::Size( 32, 19 );
         // 
         // openFileDialog
         // 
         this->openFileDialog->Filter = L"MP3 files | *.mp3";
         this->openFileDialog->InitialDirectory = L"C:\\\\Candidatos a serem deletados\\\\\\musicas";
         this->openFileDialog->Multiselect = true;
         // 
         // btPlay
         // 
         this->btPlay->BackColor = System::Drawing::Color::White;
         this->btPlay->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject( L"btPlay.BackgroundImage" )));
         this->btPlay->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
         this->btPlay->Font = (gcnew System::Drawing::Font( L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->btPlay->Location = System::Drawing::Point( 17, 18 );
         this->btPlay->Name = L"btPlay";
         this->btPlay->Size = System::Drawing::Size( 25, 25 );
         this->btPlay->TabIndex = 2;
         this->btPlay->UseVisualStyleBackColor = false;
         this->btPlay->Click += gcnew System::EventHandler( this, &Main::btPlay_Click );
         // 
         // btStop
         // 
         this->btStop->BackColor = System::Drawing::Color::White;
         this->btStop->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject( L"btStop.BackgroundImage" )));
         this->btStop->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
         this->btStop->Font = (gcnew System::Drawing::Font( L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->btStop->Location = System::Drawing::Point( 98, 18 );
         this->btStop->Name = L"btStop";
         this->btStop->Size = System::Drawing::Size( 25, 25 );
         this->btStop->TabIndex = 4;
         this->btStop->UseVisualStyleBackColor = false;
         this->btStop->Click += gcnew System::EventHandler( this, &Main::btStop_Click );
         // 
         // groupBox2
         // 
         this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
            | System::Windows::Forms::AnchorStyles::Right));
         this->groupBox2->BackColor = System::Drawing::Color::Transparent;
         this->groupBox2->Controls->Add( this->btPause );
         this->groupBox2->Controls->Add( this->btPrevious );
         this->groupBox2->Controls->Add( this->btNext );
         this->groupBox2->Controls->Add( this->lbVolume );
         this->groupBox2->Controls->Add( this->tbPosition );
         this->groupBox2->Controls->Add( this->trbVolume );
         this->groupBox2->Controls->Add( this->btPlay );
         this->groupBox2->Controls->Add( this->btStop );
         this->groupBox2->Controls->Add( this->trbProgress );
         this->groupBox2->Location = System::Drawing::Point( 12, 39 );
         this->groupBox2->Name = L"groupBox2";
         this->groupBox2->Size = System::Drawing::Size( 670, 108 );
         this->groupBox2->TabIndex = 6;
         this->groupBox2->TabStop = false;
         // 
         // btPause
         // 
         this->btPause->BackColor = System::Drawing::Color::White;
         this->btPause->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject( L"btPause.BackgroundImage" )));
         this->btPause->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
         this->btPause->Font = (gcnew System::Drawing::Font( L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->btPause->Location = System::Drawing::Point( 56, 18 );
         this->btPause->Name = L"btPause";
         this->btPause->Size = System::Drawing::Size( 25, 25 );
         this->btPause->TabIndex = 11;
         this->btPause->UseVisualStyleBackColor = false;
         this->btPause->Click += gcnew System::EventHandler( this, &Main::btPause_Click );
         // 
         // btPrevious
         // 
         this->btPrevious->BackColor = System::Drawing::Color::White;
         this->btPrevious->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject( L"btPrevious.BackgroundImage" )));
         this->btPrevious->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
         this->btPrevious->Font = (gcnew System::Drawing::Font( L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->btPrevious->Location = System::Drawing::Point( 139, 18 );
         this->btPrevious->Name = L"btPrevious";
         this->btPrevious->Size = System::Drawing::Size( 25, 25 );
         this->btPrevious->TabIndex = 10;
         this->btPrevious->UseVisualStyleBackColor = false;
         this->btPrevious->Click += gcnew System::EventHandler( this, &Main::btPrevious_Click );
         // 
         // btNext
         // 
         this->btNext->BackColor = System::Drawing::Color::White;
         this->btNext->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject( L"btNext.BackgroundImage" )));
         this->btNext->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
         this->btNext->Font = (gcnew System::Drawing::Font( L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->btNext->Location = System::Drawing::Point( 182, 18 );
         this->btNext->Name = L"btNext";
         this->btNext->Size = System::Drawing::Size( 25, 25 );
         this->btNext->TabIndex = 9;
         this->btNext->UseVisualStyleBackColor = false;
         this->btNext->Click += gcnew System::EventHandler( this, &Main::btNext_Click );
         // 
         // lbVolume
         // 
         this->lbVolume->AutoSize = true;
         this->lbVolume->BackColor = System::Drawing::Color::Transparent;
         this->lbVolume->Font = (gcnew System::Drawing::Font( L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->lbVolume->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
         this->lbVolume->Location = System::Drawing::Point( 355, 22 );
         this->lbVolume->Name = L"lbVolume";
         this->lbVolume->Size = System::Drawing::Size( 56, 16 );
         this->lbVolume->TabIndex = 8;
         this->lbVolume->Text = L"Volume:";
         // 
         // tbPosition
         // 
         this->tbPosition->BackColor = System::Drawing::SystemColors::MenuText;
         this->tbPosition->Font = (gcnew System::Drawing::Font( L"Microsoft YaHei UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->tbPosition->ForeColor = System::Drawing::SystemColors::Info;
         this->tbPosition->Location = System::Drawing::Point( 232, 19 );
         this->tbPosition->MaximumSize = System::Drawing::Size( 120, 90 );
         this->tbPosition->Multiline = true;
         this->tbPosition->Name = L"tbPosition";
         this->tbPosition->Size = System::Drawing::Size( 106, 25 );
         this->tbPosition->TabIndex = 7;
         this->tbPosition->Text = L"00:00 / 00:00";
         // 
         // trbVolume
         // 
         this->trbVolume->AutoSize = false;
         this->trbVolume->BackColor = System::Drawing::Color::FromArgb( static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
            static_cast<System::Int32>(static_cast<System::Byte>(16)) );
         this->trbVolume->LargeChange = 100;
         this->trbVolume->Location = System::Drawing::Point( 419, 19 );
         this->trbVolume->Maximum = 1000;
         this->trbVolume->Name = L"trbVolume";
         this->trbVolume->Size = System::Drawing::Size( 113, 25 );
         this->trbVolume->SmallChange = 10;
         this->trbVolume->TabIndex = 6;
         this->trbVolume->TickFrequency = 2;
         this->trbVolume->TickStyle = System::Windows::Forms::TickStyle::None;
         this->trbVolume->Value = 500;
         this->trbVolume->Scroll += gcnew System::EventHandler( this, &Main::trbVolume_Scroll );
         // 
         // trbProgress
         // 
         this->trbProgress->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
            | System::Windows::Forms::AnchorStyles::Right));
         this->trbProgress->AutoSize = false;
         this->trbProgress->BackColor = System::Drawing::Color::FromArgb( static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
            static_cast<System::Int32>(static_cast<System::Byte>(16)) );
         this->trbProgress->LargeChange = 15000;
         this->trbProgress->Location = System::Drawing::Point( 6, 59 );
         this->trbProgress->Name = L"trbProgress";
         this->trbProgress->Size = System::Drawing::Size( 658, 25 );
         this->trbProgress->TabIndex = 5;
         this->trbProgress->TickStyle = System::Windows::Forms::TickStyle::None;
         this->trbProgress->Scroll += gcnew System::EventHandler( this, &Main::trbSong_Scroll );
         // 
         // timer
         // 
         this->timer->Interval = 200;
         this->timer->Tick += gcnew System::EventHandler( this, &Main::timer_Tick );
         // 
         // playlist
         // 
         this->playlist->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
            | System::Windows::Forms::AnchorStyles::Left)
            | System::Windows::Forms::AnchorStyles::Right));
         this->playlist->BackColor = System::Drawing::Color::White;
         this->playlist->BackgroundImageTiled = true;
         this->playlist->Columns->AddRange( gcnew cli::array< System::Windows::Forms::ColumnHeader^  >( 6 ) {
            this->clmPath, this->clmFileName,
               this->clmArtist, this->clmSongName, this->clmAlbum, this->clmLength
         } );
         this->playlist->Font = (gcnew System::Drawing::Font( L"Constantia", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->playlist->ForeColor = System::Drawing::Color::FromArgb( static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
            static_cast<System::Int32>(static_cast<System::Byte>(16)) );
         this->playlist->FullRowSelect = true;
         this->playlist->HideSelection = false;
         this->playlist->Location = System::Drawing::Point( 12, 153 );
         this->playlist->MultiSelect = false;
         this->playlist->Name = L"playlist";
         this->playlist->ShowGroups = false;
         this->playlist->Size = System::Drawing::Size( 670, 280 );
         this->playlist->TabIndex = 7;
         this->playlist->UseCompatibleStateImageBehavior = false;
         this->playlist->View = System::Windows::Forms::View::Details;
         this->playlist->DoubleClick += gcnew System::EventHandler( this, &Main::playlist_MouseDoubleClick );
         // 
         // clmPath
         // 
         this->clmPath->Text = L"Path";
         this->clmPath->Width = 0;
         // 
         // clmFileName
         // 
         this->clmFileName->Text = L"Filename";
         this->clmFileName->Width = 0;
         // 
         // clmArtist
         // 
         this->clmArtist->Text = L"Artist";
         this->clmArtist->Width = 150;
         // 
         // clmSongName
         // 
         this->clmSongName->Text = L"Song";
         this->clmSongName->Width = 150;
         // 
         // clmAlbum
         // 
         this->clmAlbum->Text = L"Album";
         this->clmAlbum->Width = 150;
         // 
         // clmLength
         // 
         this->clmLength->Text = L"Length";
         // 
         // statusStrip1
         // 
         this->statusStrip1->AutoSize = false;
         this->statusStrip1->BackColor = System::Drawing::Color::WhiteSmoke;
         this->statusStrip1->Items->AddRange( gcnew cli::array< System::Windows::Forms::ToolStripItem^  >( 1 ) { this->toolStripStatusLabel } );
         this->statusStrip1->Location = System::Drawing::Point( 0, 447 );
         this->statusStrip1->Name = L"statusStrip1";
         this->statusStrip1->Size = System::Drawing::Size( 694, 22 );
         this->statusStrip1->TabIndex = 8;
         // 
         // toolStripStatusLabel
         // 
         this->toolStripStatusLabel->Name = L"toolStripStatusLabel";
         this->toolStripStatusLabel->Size = System::Drawing::Size( 0, 17 );
         // 
         // folderBrowserDialog
         // 
         this->folderBrowserDialog->Description = L"Select a folder to import songs from";
         // 
         // Main
         // 
         this->AllowDrop = true;
         this->AutoScaleDimensions = System::Drawing::SizeF( 6, 13 );
         this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
         this->BackColor = System::Drawing::Color::FromArgb( static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
            static_cast<System::Int32>(static_cast<System::Byte>(16)) );
         this->ClientSize = System::Drawing::Size( 694, 469 );
         this->Controls->Add( this->statusStrip1 );
         this->Controls->Add( this->playlist );
         this->Controls->Add( this->groupBox2 );
         this->Controls->Add( this->menuStrip );
         this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject( L"$this.Icon" )));
         this->MainMenuStrip = this->menuStrip;
         this->MinimumSize = System::Drawing::Size( 530, 368 );
         this->Name = L"Main";
         this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
         this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
         this->Text = L"Velvet Player";
         this->menuStrip->ResumeLayout( false );
         this->menuStrip->PerformLayout();
         this->groupBox2->ResumeLayout( false );
         this->groupBox2->PerformLayout();
         (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVolume))->EndInit();
         (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbProgress))->EndInit();
         this->statusStrip1->ResumeLayout( false );
         this->statusStrip1->PerformLayout();
         this->ResumeLayout( false );
         this->PerformLayout();

      }
#pragma endregion

//-----------------------------------------
// Button click handlers
//-----------------------------------------

private: System::Void btPlay_Click(System::Object^  sender, System::EventArgs^  e)
{
   String^ File;

   if ( m_State == PAUSED )
   {
      // Resume the song that is already playing
      resume();
   }
   else
   {
      try
      {
         File = this->playlist->SelectedItems[0]->SubItems[0]->Text + "\\" + this->playlist->SelectedItems[0]->SubItems[1]->Text;

         if ( m_State == PLAYING )
         {
            // Stop whatever is playing, then play selected song from the beggining
            stop();
         }
         play(File);
      }
      catch(...)
      {
         SetStatusLabel("No song selected on playlist.");
      }
   }
}
private: System::Void btPause_Click(System::Object^  sender, System::EventArgs^  e)
{
   if ( m_State == PLAYING )
   {
      // Let's pause the playback
      pause();
   }
   else if (m_State == PAUSED )
   {
      // Resume the song that is already playing
      resume();
   }
}
private: System::Void btStop_Click(System::Object^  sender, System::EventArgs^  e)
{
   // No harm to always call stop
   stop(); // hammer time
}
private: System::Void btPrevious_Click(System::Object^  sender, System::EventArgs^  e)
{
   // First, stop if playing
   if ( m_State == PLAYING || m_State == PAUSED )
   {
      stop(); // hammer time
   }

   previous();
}
private: System::Void btNext_Click(System::Object^  sender, System::EventArgs^  e)
{
   // First, stop if playing
   if ( m_State == PLAYING || m_State == PAUSED )
   {
      stop(); // hammer time
   }

   next();
}

//-----------------------------------------
// Menu handlers
//-----------------------------------------
// File_menu
private: System::Void openToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e)
{
   if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
   {
      // How many items were in the list before the user clicked open?
      int iBefore = this->playlist->Items->Count;

      // Add songs to the playlist
      for each (String^ file in openFileDialog->FileNames)
      {
         AddSongToPlaylist(file);
      }

      // How many are in the playlist now?
      int iAfter = this->playlist->Items->Count;

      // Focus on the first item added at this time (or the first item at all if nothings was there before)
      // Since the items index begins at position 0 and the count starts on 1, we don't need to add 1
      // Eg.: if there were 3 items(indexes 0,1,2), the next item will be at index 3
      this->playlist->Items[iBefore]->Selected = true;
      this->playlist->Items[iBefore]->Focused  = true;

      // Inform user
      SetStatusLabel( (iAfter - iBefore).ToString() + " songs added");

      // Create a new shuffle list
      ShuffleSongs();

      // Now that we added some files, resize the colums
      ResizePlaylistColumns();

      // Save session
      SaveSession();
   }
   else
   {
      SetStatusLabel("");
   }
}
private: System::Void openFolderToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
   {
      // How many items were in the list before the user browsed a folder?
      int iBefore = this->playlist->Items->Count;

      // Prompt the user if shoud look inside sub-directories
      if ( System::Windows::Forms::DialogResult::Yes == MessageBox::Show( "Include sub-folders? This may take a few minutes", "Recursive?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) )
      {
         // Add all MP3 files on the selected folder and its sub-directories
         AddFolderToPlaylist(folderBrowserDialog->SelectedPath, true);
      }
      else
      {
         // Add all MP3 files on the selected folder
         AddFolderToPlaylist(folderBrowserDialog->SelectedPath, false);
      }

      // How many are in the playlist now?
      int iAfter = this->playlist->Items->Count;

      // If there was a change, focus on the first new item
      if ( iAfter > iBefore )
      {
         this->playlist->Items[iBefore]->Selected = true;
         this->playlist->Items[iBefore]->Focused  = true;

         // Inform user
         SetStatusLabel( (iAfter - iBefore).ToString() + " songs added");

         // Create a new shuffle list
         ShuffleSongs();

         // Now that we added some files, resize the colums
         ResizePlaylistColumns();

         // Save session
         SaveSession();
      }
      else
      {
         SetStatusLabel("");
      }
   }
}
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   // Farewell!
   Application::Exit();
}

// Song_menu
private: System::Void iD3TagToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   // String to edit in tag
   char szArtist[128];
   char szSong[128];
   char szAlbum[128];

   // Read the id3 tag
   String^ strMP3;
   try
   {
      strMP3 = this->playlist->SelectedItems[0]->SubItems[0]->Text + "\\" + this->playlist->SelectedItems[0]->SubItems[1]->Text;
   }
   catch(...)
   {
      SetStatusLabel("No song selected on playlist.");
      return;
   }

   IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(strMP3);
   char* szMP3 = static_cast<char*>(ptrToNativeString.ToPointer() );

   ID3_Tag myTag(szMP3);
   if ( myTag.GetMp3HeaderInfo() == NULL )
   {
      SetStatusLabel("There was a problem getting MP3 header info for selected song");
      Marshal::FreeHGlobal(ptrToNativeString);
      return;
   }

   // Clean up
   Marshal::FreeHGlobal(ptrToNativeString);

   // Artist
   ID3_Frame* frameArtist = myTag.Find(ID3FID_LEADARTIST);
   if (NULL != frameArtist)
   {
      frameArtist->GetField(ID3FN_TEXT)->SetEncoding(ID3TE_ISO8859_1);
      frameArtist->GetField(ID3FN_TEXT)->Get(szArtist, sizeof(szArtist));
   }
   else
   {
      sprintf_s(szArtist, sizeof(szArtist), "Unknown");
   }

   // Song
   ID3_Frame* frameTitle = myTag.Find(ID3FID_TITLE);
   if (NULL != frameTitle)
   {
      frameTitle->GetField(ID3FN_TEXT)->SetEncoding(ID3TE_ISO8859_1);
      frameTitle->GetField(ID3FN_TEXT)->Get(szSong, sizeof(szSong));
   }
   else
   {
      sprintf_s(szSong, sizeof(szSong), "Unknown");
   }

   // Album
   ID3_Frame* frameAlbum = myTag.Find(ID3FID_ALBUM);
   if (NULL != frameAlbum)
   {
      frameAlbum->GetField(ID3FN_TEXT)->SetEncoding(ID3TE_ISO8859_1);
      frameAlbum->GetField(ID3FN_TEXT)->Get(szAlbum, sizeof(szAlbum));
   }
   else
   {
      sprintf_s(szAlbum, sizeof(szAlbum), "Unknown");
   }

   // Album art
   ID3_Frame* frameAlbumArt = myTag.Find(ID3FID_PICTURE);
   bool bArt = false;
   if ( NULL != frameAlbumArt && frameAlbumArt->Contains(ID3FN_DATA))
   {
      frameAlbumArt->Field(ID3FN_DATA).ToFile("tmp_albumart.jpg");
      bArt = true;
   }


   // Construct the Edit_ID3 Form inside this context, so that
   // its destructor will be called immediately after we finish updating
   {
      // Set the fields with the information that is already in the tag
      Edit_ID3 editID3_Form;
      editID3_Form.setFields(szArtist, szSong, szAlbum, bArt);

      // Show the form: if the user presses OK, we update the tag
      if ( editID3_Form.ShowDialog() == System::Windows::Forms::DialogResult::OK)
      {
         editID3_Form.getFields(szArtist, szSong, szAlbum);

         if (NULL != frameArtist)
         {
            // The frame already exists, just update it
            frameArtist->GetField(ID3FN_TEXT)->Set(szArtist);
         }
         else
         {
            // The ID3FID_LEADARTIST frame doesn't exist, let's create a new one
            ID3_Frame frame;
            frame.SetID(ID3FID_LEADARTIST);
            frame.GetField(ID3FN_TEXT)->Set(szArtist);
            myTag.AddFrame(frame);
         }

         if (NULL != frameTitle )
         {
            // The frame already exists, just update it
            frameTitle->GetField(ID3FN_TEXT)->Set(szSong);
         }
         else
         {
            // The ID3FID_TITLE frame doesn't exist, let's create a new one
            ID3_Frame frame;
            frame.SetID(ID3FID_TITLE);
            frame.GetField(ID3FN_TEXT)->Set(szSong);
            myTag.AddFrame(frame);
         }

         if (NULL != frameAlbum )
         {
            // The frame already exists, just update it
            frameAlbum->GetField(ID3FN_TEXT)->Set(szAlbum);
         }
         else
         {
            // The ID3FID_ALBUM frame doesn't exist, let's create a new one
            ID3_Frame frame;
            frame.SetID(ID3FID_ALBUM);
            frame.GetField(ID3FN_TEXT)->Set(szAlbum);
            myTag.AddFrame(frame);
         }

         // We are finished, update the tag
         myTag.Update();

         // Edit in the playlist as well.
         this->playlist->SelectedItems[0]->SubItems[2]->Text = gcnew String(szArtist);
         this->playlist->SelectedItems[0]->SubItems[3]->Text = gcnew String(szSong);
         this->playlist->SelectedItems[0]->SubItems[4]->Text = gcnew String(szAlbum);

         SetStatusLabel("Updated");
      }
   }

   // Since the form has been destroyed, we can delete the .jpg
   if ( File::Exists(gcnew String("tmp_albumart.jpg") ) )
   {
      try
      {
         File::Delete(gcnew String("tmp_albumart.jpg"));
      }
      catch(Exception^ e)
      {
         e;
         //SetStatusLabel("Unable to delete album art");
      }
   }
}
private: System::Void removeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   try
   {
      int iIndex  = this->playlist->FocusedItem->Index;
      this->playlist->Items->RemoveAt(iIndex);
      ResizePlaylistColumns();

      // Create a new shuffle list
      ShuffleSongs();

      // Save session
      SaveSession();
   }
   catch(...)
   {
      SetStatusLabel("No song selected on playlist.");
   }
}

// Playlist_menu
private: System::Void shuffleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   if ( g_bShuffle == false)
   {
      g_bShuffle = true;
      shuffleToolStripMenuItem->Checked = true;
      ShuffleSongs();
   }
   else
   {
      g_bShuffle = false;
      shuffleToolStripMenuItem->Checked = false;
   }

   // Save session
   SaveSession();
}
private: System::Void autosizeColumnsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   if ( g_bAutosize == false)
   {
      g_bAutosize = true;
      autosizeColumnsToolStripMenuItem->Checked = true;
      ResizePlaylistColumns();
   }
   else
   {
      g_bAutosize = false;
      autosizeColumnsToolStripMenuItem->Checked = false;
   }

   // Save session
   SaveSession();
}
private: System::Void removeAllToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   this->playlist->Items->Clear();
   ResizePlaylistColumns();

   // Create a new shuffle list
   ShuffleSongs();

   // Save session
   SaveSession();
}
private: System::Void editFontToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   if (fontDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
   {
      this->playlist->Font = fontDialog->Font;
      ResizePlaylistColumns();

      // Save session
      SaveSession();
   }
}
private: System::Void editColorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   if (colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
   {
      this->playlist->ForeColor = colorDialog->Color;

      // Save session
      SaveSession();
   }
}
private: System::Void resetToDefaultToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   this->playlist->Font = (gcnew System::Drawing::Font( L"Constantia", 9.75F, System::Drawing::FontStyle::Bold,
                                                        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
   this->playlist->ForeColor = System::Drawing::SystemColors::ControlText;

   ResizePlaylistColumns();

   // Save session
   SaveSession();
}

// About
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   About^ AboutForm = gcnew About;
   AboutForm->ShowDialog();
}

// Hidden_ShowColumns_menu
private: System::Void pathToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   if ( this->playlist->Columns[0]->Width == 0 )
   {
      this->playlist->Columns[0]->Width = 200;
      pathToolStripMenuItem->Checked = false;
   }
   else
   {
      this->playlist->Columns[0]->Width = 0;
      pathToolStripMenuItem->Checked = false;
   }
}
private: System::Void filenameToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
   if ( this->playlist->Columns[1]->Width == 0 )
   {
      this->playlist->Columns[1]->Width = 90;
      filenameToolStripMenuItem->Checked = false;
   }
   else
   {
      this->playlist->Columns[1]->Width = 0;
      filenameToolStripMenuItem->Checked = false;
   }
}

//-----------------------------------------
// Trackbars handlers and timer
//-----------------------------------------
private: System::Void trbVolume_Scroll(System::Object^  sender, System::EventArgs^  e)
{
   if ( m_State == PLAYING )
   {
      // Set volume
      DWORD dwRet = MCI->SetVolume(trbVolume->Value);
      if ( 0 != dwRet)
      {
         SetStatusLabel("Error MCI->SetVolume (" + dwRet.ToString() + ")");
         return;
      }
   }
   else
   {
      // Not playing, does not need to set the volume now
   }
}
private: System::Void trbSong_Scroll(System::Object^  sender, System::EventArgs^  e)
{
   if ( m_State == PLAYING )
   {
      // Set position
      DWORD dwRet = MCI->Seek(trbProgress->Value);
      if ( NO_SEEKING_ALLOWED == dwRet )
      {
         SetStatusLabel("Seeking not allowed for this song");
         return;
      }
      else if ( 0 != dwRet)
      {
         SetStatusLabel("Error MCI->Seek (" + dwRet.ToString() + ")");
         return;
      }
   }
   else
   {
      // Not playing.
   }
}
private: System::Void timer_Tick(System::Object^  sender, System::EventArgs^  e)
{
   int iMinutes = 0;
   int iSeconds = 0;
   int iCurrentMiliSecond = 0;

   if ( m_State == PLAYING )
   {
      // Still playing the song?
      if ( MCI->isPlaying() )
      {
         // Still playing, so update trackbar and textbox
         DWORD dwRet = MCI->GetCurrentPosition(&iMinutes, &iSeconds);
         if ( 0 != dwRet )
         {
            return;
         }
         else
         {
            this->tbPosition->Text = String::Format("{0:00}", iMinutes) + ":" + String::Format("{0:00}", iSeconds) + " / " + String::Format("{0:00}", MCI->m_iCurrentSongMinLen) + ":" + String::Format("{0:00}", MCI->m_iCurrentSongSecLen) ;
         }

         dwRet = MCI->GetCurrentPosition(&iCurrentMiliSecond);
         if ( 0 != dwRet )
         {
            return;
         }
         else
         {
            if ( 0 != trbProgress->Maximum )
            {
               if ( iCurrentMiliSecond > trbProgress->Maximum )
               {
                  trbProgress->Value = trbProgress->Maximum;
               }

               trbProgress->Value = iCurrentMiliSecond;
            }
            
         }
      }
      else
      {
         // This song has finished, go to the next
         stop();
         next();

         // Sleep a bit, so that MCI can start playing before we check again
         System::Threading::Thread::Sleep(5);
      }
   }
}

//-----------------------------------------
// Playlist selection
//-----------------------------------------
private: System::Void playlist_MouseDoubleClick(System::Object^  sender, System::EventArgs^  e)
{
   // First, stop if playing
   if ( m_State == PLAYING || m_State == PAUSED )
   {
      stop(); // hammer time
   }

   // Play selected song
   String^ File;
   File = this->playlist->SelectedItems[0]->SubItems[0]->Text + "\\" + this->playlist->SelectedItems[0]->SubItems[1]->Text;

   play(File);
}

//-----------------------------------------
// Generic functions for playback
//-----------------------------------------
private: System::Void play(String^ File)
{
   // First, convert szFile to char*
   IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(File);
   char* szFile = static_cast<char*>(ptrToNativeString.ToPointer() );

   bool bCanSeek = true;
   ID3_Tag myTag(szFile);
   const Mp3_Headerinfo* mp3info;
   if ( ( mp3info = myTag.GetMp3HeaderInfo() ) == NULL )
   {
      SetStatusLabel("There was a problem getting MP3 header info for selected song");
      Marshal::FreeHGlobal(ptrToNativeString);
      return;
   }

   // If the song was encoded using variable bit rate (VBR), we cannot seek through the song because MCI will get confused
   long lVBR = mp3info->vbr_bitrate;
   if ( 0 != lVBR )
   {
      bCanSeek = false;
   }

   // First, we open
   DWORD dwRet = MCI->Open(szFile, bCanSeek);
   if ( 0 != dwRet )
   {
      char buffer[1024] = {0};
      mciGetErrorString(dwRet, (LPSTR)buffer, sizeof(buffer));
      SetStatusLabel("Error MCI->Open (" + dwRet.ToString() + "): " + gcnew String(buffer));
      Marshal::FreeHGlobal(ptrToNativeString);
      return;
   }


   // Clean up
   Marshal::FreeHGlobal(ptrToNativeString);

   // Then, we play
   dwRet = MCI->Play();
   if ( 0 != dwRet )
   {
      char buffer[1024] = {0};
      mciGetErrorString(dwRet, (LPSTR)buffer, sizeof(buffer));
      SetStatusLabel("Error MCI->Play (" + dwRet.ToString() + "): " + gcnew String(buffer));
      return;
   }
   else
   {
      m_State = PLAYING;
      timer->Enabled = true;
   }

   // Set volume
   dwRet = MCI->SetVolume(trbVolume->Value);
   if ( 0 != dwRet )
   {
      SetStatusLabel("Error MCI->SetVolume (" + dwRet.ToString() + ")");
      return;
   }

   // Set trackbar
   int iSeconds = 0;
   dwRet = MCI->GetSongLength(&iSeconds);
   if ( 0 != dwRet )
   {
      SetStatusLabel("Error MCI->GetSongLength (" + dwRet.ToString() + ")");
      return;
   }
   else
   {
      // Since GetCurrentPosition returns in milliseconds, we must do the same here
      trbProgress->Maximum = iSeconds*1000;
   }

   // Set song length
   this->tbPosition->Text = "00:00 / " + String::Format("{0:00}", MCI->m_iCurrentSongMinLen) + ":" + String::Format("{0:00}", MCI->m_iCurrentSongSecLen);


   // Update status label
   SetStatusLabel("Playing: " + Path::GetFileName(File) );

}
private: System::Void pause()
{
   DWORD dwRet = MCI->Pause();
   if ( 0 != dwRet )
   {
      SetStatusLabel("Error MCI->Pause (" + dwRet.ToString() + ")");
      return;
   }
   else
   {
      // Change the tag
      m_State = PAUSED;
   }

   SetStatusLabel("Paused");
}
private: System::Void resume()
{
   // Resume
   DWORD dwRet = MCI->Resume();
   if ( 0 != dwRet )
   {
      char buffer[1024] = {0};
      mciGetErrorString(dwRet, (LPSTR)buffer, sizeof(buffer));
      SetStatusLabel("Error MCI->Open (" + dwRet.ToString() + "): " + gcnew String(buffer));
      return;
   }
   else
   {
      m_State = PLAYING;
   }

   // Update status label
   SetStatusLabel("Resuming: " + Path::GetFileName( gcnew String( MCI->GetCurrentSong() ) ) );
}
private: System::Void stop()
{
   // First, we stop
   DWORD dwRet = MCI->Stop();
   if ( 0 != dwRet)
   {
      // There might be no song playing, so we don't set the status label here
      return;
   }

   // Then, we close
   dwRet = MCI->Close();
   if ( 0 != dwRet )
   {
      // There might be no song opened, so we don't set the status label here
      return;
   }

   // Set trackbar to zero
   trbProgress->Value = 0;

   // Set track length to zero
   this->tbPosition->Text = L"00:00 / 00:00";

   m_State = STOPPED;

   SetStatusLabel("");
}
private: System::Void next()
{
   try
   {
      int iCurrentSongIndex  = this->playlist->FocusedItem->Index;
      int iCount             = this->playlist->Items->Count;

      if ( false == g_bShuffle )
      {
         // Select next song on the playlist
         if (iCurrentSongIndex + 1 < iCount )
         {
            this->playlist->Items[iCurrentSongIndex+1]->Selected = true;
            this->playlist->Items[iCurrentSongIndex+1]->Focused = true;
         }
         else
         {
            this->playlist->Items[0]->Selected = true;
            this->playlist->Items[0]->Focused = true;
         }
      }
      else
      {
         // Get the index of the current song on the shuffle list
         int iToPlay = L_Songs->IndexOf(iCurrentSongIndex);
         if ( iToPlay < 0)
         {
            // Some error happened.
            SetStatusLabel("Error shuffling");
            this->playlist->Items[0]->Selected = true;
            this->playlist->Items[0]->Focused = true;
         }
         else
         {
            // Selected next song on the shuffle list
            iToPlay++;
            if ( iToPlay >= L_Songs->Count )
            {
               // It was the last song of the shuffle list, so start again
               iToPlay = 0;
            }
            this->playlist->Items[ L_Songs[iToPlay] ]->Selected = true;
            this->playlist->Items[ L_Songs[iToPlay] ]->Focused = true;
         }
      }

      // Play selected song
      String^ File;
      File = this->playlist->SelectedItems[0]->SubItems[0]->Text + "\\" + this->playlist->SelectedItems[0]->SubItems[1]->Text;

      play(File);
   }
   catch(...)
   {
      SetStatusLabel("No song selected on playlist.");
   }
}
private: System::Void previous()
{
   try
   {
      int iCurrentSongIndex = this->playlist->FocusedItem->Index;
      int iCount            = this->playlist->Items->Count;

      if ( false == g_bShuffle )
      {
         // No shuffling here, select previous song on the playlist
         if (iCurrentSongIndex > 0)
         {
            this->playlist->Items[iCurrentSongIndex-1]->Selected = true;
            this->playlist->Items[iCurrentSongIndex-1]->Focused = true;
         }
         else
         {
            this->playlist->Items[iCount-1]->Selected = true;
            this->playlist->Items[iCount-1]->Focused = true;
         }
      }
      else
      {
         // Get the index of the current song on the shuffle list
         int iToPlay = L_Songs->IndexOf(iCurrentSongIndex);
         if ( iToPlay < 0)
         {
            // Some error happened.
            SetStatusLabel("Error shuffling");
            this->playlist->Items[0]->Selected = true;
            this->playlist->Items[0]->Focused = true;
         }
         else
         {
            // Selected next song on the shuffle list
            iToPlay--;
            if ( iToPlay < 0)
            {
               // It was the last song of the shuffle list, so start again
               iToPlay = L_Songs->Count - 1;
            }
            this->playlist->Items[ L_Songs[iToPlay] ]->Selected = true;
            this->playlist->Items[ L_Songs[iToPlay] ]->Focused = true;
         }
      }

      // Play selected song
      String^ File;
      File = this->playlist->SelectedItems[0]->SubItems[0]->Text + "\\" + this->playlist->SelectedItems[0]->SubItems[1]->Text;
      
      play(File);
   }
   catch(...)
   {
      SetStatusLabel("No song selected on playlist.");
   }
}

//-----------------------------------------
// Auxiliar functions
//-----------------------------------------
private: System::Void SetStatusLabel( String^ strStatus)
{
   // The actual width of the form Window fits about 110 characters
   if (strStatus->Length < 110)
   {
      toolStripStatusLabel->Text = strStatus;
   }
   else
   {
      toolStripStatusLabel->Text = gcnew String( strStatus->Substring(0, 110) ) + "...";
   }
}
private: System::Void AddSongToPlaylist(String^ szSongToAdd)
{
   ListViewItem^ item = gcnew ListViewItem(szSongToAdd, 0 );
   item->Text         = Path::GetDirectoryName(szSongToAdd);
   item->SubItems->Add( Path::GetFileName(szSongToAdd) );

   // Read the id3 tag
   char* szMP3 = (char*)(void*)Marshal::StringToHGlobalAnsi( szSongToAdd );
   ID3_Tag myTag(szMP3);

   // Artist
   ID3_Frame* frameArtist = myTag.Find(ID3FID_LEADARTIST);
   if (NULL != frameArtist)
   {
      char szArtist[128] = {0};
      frameArtist->GetField(ID3FN_TEXT)->SetEncoding(ID3TE_ISO8859_1);
      frameArtist->GetField(ID3FN_TEXT)->Get(szArtist, sizeof(szArtist));
      item->SubItems->Add( gcnew String(szArtist) );
   }
   else
   {
      item->SubItems->Add( "Unknown" );
   }

   // Song
   ID3_Frame* frameTitle = myTag.Find(ID3FID_TITLE);
   if (NULL != frameTitle)
   {
      char szSong[128] = {0};
      frameTitle->GetField(ID3FN_TEXT)->SetEncoding(ID3TE_ISO8859_1);
      frameTitle->GetField(ID3FN_TEXT)->Get(szSong, sizeof(szSong));
      item->SubItems->Add( gcnew String(szSong) );
   }
   else
   {
      item->SubItems->Add( "Unknown" );
   }

   // Album
   ID3_Frame* frameAlbum = myTag.Find(ID3FID_ALBUM);
   if (NULL != frameAlbum)
   {
      char szAlbum[128] = {0};
      frameAlbum->GetField(ID3FN_TEXT)->SetEncoding(ID3TE_ISO8859_1);
      frameAlbum->GetField(ID3FN_TEXT)->Get(szAlbum, sizeof(szAlbum));
      item->SubItems->Add( gcnew String(szAlbum) );
   }
   else
   {
      item->SubItems->Add( "Unknown" );
   }

   //Length
   const Mp3_Headerinfo* mp3info;
   if ((mp3info = myTag.GetMp3HeaderInfo()) != NULL)
   {
      item->SubItems->Add( String::Format("{0:00}", mp3info->time / 60)
                           + ":"
                           + String::Format("{0:00}", mp3info->time % 60) );
   }
   else
   {
      item->SubItems->Add( "Unknown" );
   }

   this->playlist->Items->Add(item);

   // We do not need to call ResizePlaylistColumns() here, the caller is responsible for that
}
private: System::Void ResizePlaylistColumns()
{
   // Only if 'Auto-size Columns' is checked
   if ( g_bAutosize )
   {
      // Artist
      this->playlist->AutoResizeColumn(2, ColumnHeaderAutoResizeStyle::ColumnContent);
      if ( playlist->Columns[2]->Width < 150)
      {
         playlist->Columns[2]->Width = 150;
      }

      // Song
      this->playlist->AutoResizeColumn(3, ColumnHeaderAutoResizeStyle::ColumnContent);
      if ( playlist->Columns[3]->Width < 150)
      {
         playlist->Columns[3]->Width = 150;
      }

      // Album
      this->playlist->AutoResizeColumn(4, ColumnHeaderAutoResizeStyle::ColumnContent);
      if ( playlist->Columns[4]->Width < 150)
      {
         playlist->Columns[4]->Width = 150;
      }

      // Length
      // The ColumnHeaderAutoResizeStyle::HeaderSize for the last column would also
      // expand the column to the right-edge of the control
      // This is not what we want, so just resize it to a predetermined size
      playlist->Columns[5]->Width = 60;
   }
}
private: System::Void AddFolderToPlaylist(String^ szFolder, bool bRecursive)
{
   try
   {
      // Process the list of files found in the directory.
      array<String^>^fileEntries = Directory::GetFiles( szFolder );
      IEnumerator^ files = fileEntries->GetEnumerator();
      while ( files->MoveNext() )
      {
         String^ fileName = safe_cast<String^>(files->Current);

         // Only add if it is an MP3-encoded song
         if (Path::GetExtension(fileName) == ".mp3")
         {
            AddSongToPlaylist(fileName);
         }
      }

      if ( bRecursive )
      {
         // Recurse into subdirectories of this directory.
         array<String^>^subdirectoryEntries = Directory::GetDirectories( szFolder );
         IEnumerator^ dirs = subdirectoryEntries->GetEnumerator();
         while ( dirs->MoveNext() )
         {
            String^ subdirectory = safe_cast<String^>(dirs->Current);
            AddFolderToPlaylist( subdirectory, bRecursive );
         }
      }
   }
   catch(...)
   {
      // Bad permission?
   }
}
private: System::Void SaveSession()
{
   // Use .NET StreamWriter class to write to the file
   try
   {
      StreamWriter^ sw = gcnew StreamWriter(SESSION_FILE);
      int iCount = this->playlist->Items->Count;

      for( int i = 0; i < iCount; i++)
      {
         String^ str;
         try
         {
            str = gcnew String(this->playlist->Items[i]->SubItems[0]->Text ) + "\\"
               +  gcnew String(this->playlist->Items[i]->SubItems[1]->Text );

            // Add this song to the file
            sw->WriteLine(str);
         }
         catch(...)
         {
            SetStatusLabel("Something went wrong with item: " + iCount.ToString());
            return;
         }
      }

      // The separator
      sw->WriteLine("##########");

      // Shuffle On of Off
      g_bShuffle? sw->WriteLine("true"): sw->WriteLine("false");

      // Auto-size columns On or Off
      g_bAutosize? sw->WriteLine("true"): sw->WriteLine("false");

      // The color
      sw->WriteLine(this->playlist->ForeColor.ToArgb());

      // Font family and size
      String^ toFile = TypeDescriptor::GetConverter( System::Drawing::Font::typeid )->ConvertToString( this->playlist->Font );
      sw->WriteLine(toFile);

      // Close the streamwriter
      sw->Close();
   }
   catch(Exception^ e)
   {
      SetStatusLabel("Problem saving session file: " + e->ToString());
   }
}
private: System::Void RestoreSession()
{
   try
   {
      StreamReader^ sr = File::OpenText(SESSION_FILE);

      // Add the songs
      String^ strSong;
      while ((strSong = sr->ReadLine()) != nullptr)
      {
         if ( File::Exists(strSong) && Path::GetExtension(strSong) == ".mp3")
         {
            AddSongToPlaylist(strSong);
         }
         else if ( strSong->Contains("###") )
         {
            // End of songs
            break;
         }
      }

      // Shuffle On of Off
      String^ strTemp;
      if ( (strTemp = sr->ReadLine()) != nullptr)
      {
         g_bShuffle = Convert::ToBoolean(strTemp);
      }

      if ( (strTemp = sr->ReadLine()) != nullptr)
      {
         g_bAutosize = Convert::ToBoolean(strTemp);
      }

      // Set the foreground color of the playlist;
      String^ strForeColor;
      if ( (strForeColor = sr->ReadLine()) != nullptr)
      {
         Color color = Color::FromArgb( Convert::ToInt32(strForeColor) );
         this->playlist->ForeColor = color;
      }

      // Set the font of the playlist
      String^ strFont;
      if ( (strFont = sr->ReadLine()) != nullptr)
      {
         System::ComponentModel::TypeConverter^ converter = TypeDescriptor::GetConverter( Drawing::Font::typeid );
         Drawing::Font^ font = dynamic_cast<Drawing::Font^>(converter->ConvertFromString(strFont));
         this->playlist->Font = font;
      }

      sr->Close();

      // Set shuffling according to saved session
      if ( g_bShuffle )
      {
         shuffleToolStripMenuItem->Checked = true;
         ShuffleSongs();
      }
      else
      {
         shuffleToolStripMenuItem->Checked = false;
      }

      // Set auto-sizing according to saved session
      if ( g_bAutosize )
      {
         autosizeColumnsToolStripMenuItem->Checked = true;
         ResizePlaylistColumns();
      }
      else
      {
         autosizeColumnsToolStripMenuItem->Checked = false;
      }
   }
   catch(FileNotFoundException^ e)
   {
      e; // prevent the warning
   }
   catch(Exception^ e)
   {
      SetStatusLabel( e->ToString() );
   }
}
private: System::Void ShuffleSongs()
{
   if ( g_bShuffle )
   {
      delete L_Songs;
      L_Songs = gcnew System::Collections::Generic::List<int>();

      for( int i = 0; i < playlist->Items->Count; i++ )
      {
         L_Songs->Add(i);
      }

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      // Shuffle the List usign the modern Fisher–Yates shuffle algorithm
      // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      for( int i = 0; i < playlist->Items->Count - 2; i++ )
      {
         int j = rnd->Next(i, playlist->Items->Count);
         int aux = L_Songs[i];

         L_Songs[i] = L_Songs[j];
         L_Songs[j] = aux;
      }
   }
}

}; //end of class
}  // end of namespace
