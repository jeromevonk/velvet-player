#pragma once

namespace VelvetPlayer {

   using namespace System;
   using namespace System::ComponentModel;
   using namespace System::Collections;
   using namespace System::Windows::Forms;
   using namespace System::Data;
   using namespace System::Drawing;

   /// <summary>
   /// Summary for About
   /// </summary>
   public ref class About : public System::Windows::Forms::Form
   {
   public:
      About(void)
      {
         InitializeComponent();
      }

   protected:
      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      ~About()
      {
         if (components)
         {
            delete components;
         }
      }
   private: System::Windows::Forms::Label^  label1;
   private: System::Windows::Forms::Label^  label2;
   private: System::Windows::Forms::Label^  label3;
   private: System::Windows::Forms::Label^  label4;

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
         System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager( About::typeid ));
         this->label1 = (gcnew System::Windows::Forms::Label());
         this->label2 = (gcnew System::Windows::Forms::Label());
         this->label3 = (gcnew System::Windows::Forms::Label());
         this->label4 = (gcnew System::Windows::Forms::Label());
         this->SuspendLayout();
         // 
         // label1
         // 
         this->label1->AutoSize = true;
         this->label1->Font = (gcnew System::Drawing::Font( L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->label1->Location = System::Drawing::Point( 108, 12 );
         this->label1->Name = L"label1";
         this->label1->Size = System::Drawing::Size( 123, 19 );
         this->label1->TabIndex = 0;
         this->label1->Text = L"Velvet Player ";
         // 
         // label2
         // 
         this->label2->AutoSize = true;
         this->label2->Font = (gcnew System::Drawing::Font( L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->label2->Location = System::Drawing::Point( 133, 40 );
         this->label2->Name = L"label2";
         this->label2->Size = System::Drawing::Size( 73, 16 );
         this->label2->TabIndex = 1;
         this->label2->Text = L"Version 1.2";
         // 
         // label3
         // 
         this->label3->AutoSize = true;
         this->label3->Font = (gcnew System::Drawing::Font( L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->label3->Location = System::Drawing::Point( 75, 62 );
         this->label3->Name = L"label3";
         this->label3->Size = System::Drawing::Size( 189, 16 );
         this->label3->TabIndex = 2;
         this->label3->Text = L"A didatic example of MCI player";
         // 
         // label4
         // 
         this->label4->AutoSize = true;
         this->label4->Font = (gcnew System::Drawing::Font( L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0) ));
         this->label4->Location = System::Drawing::Point( 14, 86 );
         this->label4->Name = L"label4";
         this->label4->Size = System::Drawing::Size( 311, 16 );
         this->label4->TabIndex = 3;
         this->label4->Text = L"by Jerome Vergueiro Vonk | vonkjerome@gmail.com";
         // 
         // About
         // 
         this->AutoScaleDimensions = System::Drawing::SizeF( 6, 13 );
         this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
         this->ClientSize = System::Drawing::Size( 338, 121 );
         this->Controls->Add( this->label4 );
         this->Controls->Add( this->label3 );
         this->Controls->Add( this->label2 );
         this->Controls->Add( this->label1 );
         this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
         this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject( L"$this.Icon" )));
         this->MaximizeBox = false;
         this->MinimizeBox = false;
         this->Name = L"About";
         this->ShowIcon = false;
         this->ShowInTaskbar = false;
         this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
         this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
         this->Text = L"About";
         this->ResumeLayout( false );
         this->PerformLayout();

      }
#pragma endregion
   };
}
