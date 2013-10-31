#pragma once

namespace window_test {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  sett;


	protected: 

	protected: 
	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->sett = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// sett
			// 
			this->sett->BackColor = System::Drawing::SystemColors::Control;
			this->sett->Location = System::Drawing::Point(271, 12);
			this->sett->Name = L"sett";
			this->sett->Size = System::Drawing::Size(75, 23);
			this->sett->TabIndex = 0;
			this->sett->Text = L"New Game";
			this->sett->UseVisualStyleBackColor = false;
			this->sett->Click += gcnew System::EventHandler(this, &Form1::sett_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(653, 626);
			this->Controls->Add(this->sett);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);

		}
#pragma endregion

		System::Void sett_Click(System::Object^  sender, System::EventArgs^  e) ;


	};
}

