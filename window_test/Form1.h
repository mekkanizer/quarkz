#pragma once
#include"settings.h"

namespace window_test {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		TLVar^ array;
	private: System::Windows::Forms::Timer^  timer1;
	public:

		Settings^ settings;

		System::Void Form1::cell_Click(System::Object^  sender, System::EventArgs^  e);

		Form1(void)
		{
			settings = gcnew Settings;
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  sett;
	public: System::Windows::Forms::Panel^  panel1;
			System::Windows::Forms::Label^  label1;
			System::Windows::Forms::Label^  label2;
			System::Windows::Forms::Label^  label4;
			System::Windows::Forms::Label^  label7;

	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->sett = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// sett
			// 
			this->sett->BackColor = System::Drawing::SystemColors::Control;
			this->sett->Location = System::Drawing::Point(271, 12);
			this->sett->Name = L"sett";
			this->sett->Size = System::Drawing::Size(75, 23);
			this->sett->TabIndex = 0;
			this->sett->Text = L"Новая Игра";
			this->sett->UseVisualStyleBackColor = false;
			this->sett->Click += gcnew System::EventHandler(this, &Form1::sett_Click);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(50, 50);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(550, 550);
			this->panel1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(47, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			this->label1->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ForeColor = System::Drawing::Color::Blue;
			this->label2->BackColor = System::Drawing::Color::LightBlue;
			this->label2->Location = System::Drawing::Point(156, 17);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Ход Синих";
			this->label2->Visible = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(564, 12);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"label4";
			this->label4->Visible = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->ForeColor = System::Drawing::Color::Red;
			this->label7->BackColor = System::Drawing::Color::LightPink;
			this->label7->Location = System::Drawing::Point(418, 17);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(73, 13);
			this->label7->TabIndex = 3;
			this->label7->Text = L"Ход Красных";
			this->label7->Visible = false;
			// 
			// timer1
			// 
			this->timer1->Interval = 2000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(653, 626);
			this->BackColor = System::Drawing::Color::Gray;
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->sett);
			this->Name = L"Form1";
			this->Text = L"Монополия";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		System::Void sett_Click(System::Object^  sender, System::EventArgs^  e) ;

		System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) ;

		void gameover();
};
}

