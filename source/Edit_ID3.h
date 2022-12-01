#pragma once

namespace VelvetPlayer {

   using namespace System;
   using namespace System::ComponentModel;
   using namespace System::Collections;
   using namespace System::Windows::Forms;
   using namespace System::Data;
   using namespace System::Drawing;
   using namespace System::Runtime::InteropServices; // for Marshal::

   /// <summary>
   /// A form for editing song informations
   /// </summary>
   public ref class Edit_ID3 : public System::Windows::Forms::Form
   {
   public:
      Edit_ID3(void)
      {
         InitializeComponent();
      }

      System::Void setFields(char* szArtist, char* szSong, char* szAlbum, bool bArt )
      {
         tbArtist->Text = gcnew String(szArtist);
         tbSong->Text   = gcnew String(szSong);
         tbAlbum->Text  = gcnew String(szAlbum);

         if ( bArt )
         {
            this->pictureBox->BackgroundImage = Image::FromFile(L"tmp_albumart.jpg");
            this->pictureBox->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            Application::DoEvents();
         }
      }

      System::Void getFields(char* szArtist, char* szSong, char* szAlbum )
      {
         char* szAuxArtist = (char*)(void*)Marshal::StringToHGlobalAnsi(tbArtist->Text );
         strcpy_s(szArtist, 128, szAuxArtist);

         char* szAuxSong   = (char*)(void*)Marshal::StringToHGlobalAnsi( tbSong->Text );
         strcpy_s(szSong, 128, szAuxSong);

         char* szAuxAlbum  = (char*)(void*)Marshal::StringToHGlobalAnsi( tbAlbum->Text );
         strcpy_s(szAlbum, 128, szAuxAlbum);
      }

   protected:
      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      ~Edit_ID3()
      {
         if (pictureBox->BackgroundImage != nullptr)
         {
            // Must free the resources! Otherwise, the file cant't be deleted from disk.
            delete pictureBox->BackgroundImage;
            pictureBox->BackgroundImage = nullptr;
         }

         if (components)
         {
            delete components;
         }
      }

   private: System::Windows::Forms::Button^  btOK;
   private: System::Windows::Forms::Button^  btCancel;
   private: System::Windows::Forms::Label^  label1;
   private: System::Windows::Forms::Label^  label2;
   private: System::Windows::Forms::Label^  label3;
   private: System::Windows::Forms::Label^  label4;
   private: System::Windows::Forms::TextBox^  tbArtist;
   private: System::Windows::Forms::TextBox^  tbSong;
   private: System::Windows::Forms::TextBox^  tbAlbum;
   private: System::Windows::Forms::PictureBox^  pictureBox;

   private:
      /// <summary>
      /// Required designer variable.
      /// </summary>
      System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
      /// <summary>
      /// Required method for Designer support - do not modify
      /// the contents of this method with the code editor.
      /// </summary>
      void InitializeComponent(void)
      {
         System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Edit_ID3::typeid));
         this->btOK = (gcnew System::Windows::Forms::Button());
         this->btCancel = (gcnew System::Windows::Forms::Button());
         this->label1 = (gcnew System::Windows::Forms::Label());
         this->label2 = (gcnew System::Windows::Forms::Label());
         this->label3 = (gcnew System::Windows::Forms::Label());
         this->label4 = (gcnew System::Windows::Forms::Label());
         this->tbArtist = (gcnew System::Windows::Forms::TextBox());
         this->tbSong = (gcnew System::Windows::Forms::TextBox());
         this->tbAlbum = (gcnew System::Windows::Forms::TextBox());
         this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
         (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
         this->SuspendLayout();
         //
         // btOK
         //
         this->btOK->DialogResult = System::Windows::Forms::DialogResult::OK;
         this->btOK->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
         this->btOK->Location = System::Drawing::Point(75, 331);
         this->btOK->Name = L"btOK";
         this->btOK->Size = System::Drawing::Size(52, 23);
         this->btOK->TabIndex = 0;
         this->btOK->Text = L"OK";
         this->btOK->UseVisualStyleBackColor = true;
         //
         // btCancel
         //
         this->btCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
         this->btCancel->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
         this->btCancel->Location = System::Drawing::Point(155, 331);
         this->btCancel->Name = L"btCancel";
         this->btCancel->Size = System::Drawing::Size(52, 23);
         this->btCancel->TabIndex = 1;
         this->btCancel->Text = L"Cancel";
         this->btCancel->UseVisualStyleBackColor = true;
         //
         // label1
         //
         this->label1->AutoSize = true;
         this->label1->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
         this->label1->Location = System::Drawing::Point(56, 9);
         this->label1->Name = L"label1";
         this->label1->Size = System::Drawing::Size(184, 19);
         this->label1->TabIndex = 2;
         this->label1->Text = L"Edit song information";
         //
         // label2
         //
         this->label2->AutoSize = true;
         this->label2->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
         this->label2->Location = System::Drawing::Point(29, 207);
         this->label2->Name = L"label2";
         this->label2->Size = System::Drawing::Size(40, 14);
         this->label2->TabIndex = 3;
         this->label2->Text = L"Artist:";
         //
         // label3
         //
         this->label3->AutoSize = true;
         this->label3->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
         this->label3->Location = System::Drawing::Point(29, 245);
         this->label3->Name = L"label3";
         this->label3->Size = System::Drawing::Size(39, 14);
         this->label3->TabIndex = 4;
         this->label3->Text = L"Song:";
         //
         // label4
         //
         this->label4->AutoSize = true;
         this->label4->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
         this->label4->Location = System::Drawing::Point(29, 281);
         this->label4->Name = L"label4";
         this->label4->Size = System::Drawing::Size(45, 14);
         this->label4->TabIndex = 5;
         this->label4->Text = L"Album:";
         //
         // tbArtist
         //
         this->tbArtist->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
         this->tbArtist->Location = System::Drawing::Point(75, 205);
         this->tbArtist->Name = L"tbArtist";
         this->tbArtist->Size = System::Drawing::Size(179, 21);
         this->tbArtist->TabIndex = 6;
         //
         // tbSong
         //
         this->tbSong->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
         this->tbSong->Location = System::Drawing::Point(77, 240);
         this->tbSong->Name = L"tbSong";
         this->tbSong->Size = System::Drawing::Size(176, 21);
         this->tbSong->TabIndex = 7;
         //
         // tbAlbum
         //
         this->tbAlbum->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
         this->tbAlbum->Location = System::Drawing::Point(77, 277);
         this->tbAlbum->Name = L"tbAlbum";
         this->tbAlbum->Size = System::Drawing::Size(176, 21);
         this->tbAlbum->TabIndex = 8;
         //
         // pictureBox
         //
         this->pictureBox->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox.BackgroundImage")));
         this->pictureBox->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
         this->pictureBox->Location = System::Drawing::Point(74, 41);
         this->pictureBox->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
         this->pictureBox->Name = L"pictureBox";
         this->pictureBox->Size = System::Drawing::Size(135, 146);
         this->pictureBox->TabIndex = 9;
         this->pictureBox->TabStop = false;
         //
         // Edit_ID3
         //
         this->AcceptButton = this->btOK;
         this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
         this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
         this->BackColor = System::Drawing::SystemColors::Control;
         this->CancelButton = this->btCancel;
         this->ClientSize = System::Drawing::Size(282, 373);
         this->Controls->Add(this->pictureBox);
         this->Controls->Add(this->tbAlbum);
         this->Controls->Add(this->tbSong);
         this->Controls->Add(this->tbArtist);
         this->Controls->Add(this->label4);
         this->Controls->Add(this->label3);
         this->Controls->Add(this->label2);
         this->Controls->Add(this->label1);
         this->Controls->Add(this->btCancel);
         this->Controls->Add(this->btOK);
         this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
         this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
         this->MaximizeBox = false;
         this->MinimizeBox = false;
         this->Name = L"Edit_ID3";
         this->ShowInTaskbar = false;
         this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
         this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
         this->Text = L"Edit ID3 tag";
         this->TopMost = true;
         (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
         this->ResumeLayout(false);
         this->PerformLayout();

      }
#pragma endregion
   };
}
