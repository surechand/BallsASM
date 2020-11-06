#pragma once
#include "simulation.h"

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
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

	private: System::Windows::Forms::Button^ startButton;

	private: System::Windows::Forms::TrackBar^ threadBar;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RadioButton^ cPlusOptionButton;
	private: System::Windows::Forms::RadioButton^ asmOptionButton;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TrackBar^ ballBar;
	private: System::Windows::Forms::Label^ timeLabel;
	private: System::Windows::Forms::Label^ speedLabel;

	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->threadBar = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->cPlusOptionButton = (gcnew System::Windows::Forms::RadioButton());
			this->asmOptionButton = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->ballBar = (gcnew System::Windows::Forms::TrackBar());
			this->timeLabel = (gcnew System::Windows::Forms::Label());
			this->speedLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ballBar))->BeginInit();
			this->SuspendLayout();
			// 
			// startButton
			// 
			this->startButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->startButton->Location = System::Drawing::Point(25, 17);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(93, 78);
			this->startButton->TabIndex = 0;
			this->startButton->Text = L"Start";
			this->startButton->UseVisualStyleBackColor = true;
			this->startButton->Click += gcnew System::EventHandler(this, &Form1::startButton_Click);
			// 
			// threadBar
			// 
			this->threadBar->Location = System::Drawing::Point(140, 15);
			this->threadBar->Maximum = 64;
			this->threadBar->Minimum = 1;
			this->threadBar->Name = L"threadBar";
			this->threadBar->Size = System::Drawing::Size(362, 45);
			this->threadBar->TabIndex = 2;
			this->threadBar->Value = 12;
			this->threadBar->Scroll += gcnew System::EventHandler(this, &Form1::threadBar_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(232, 47);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(116, 20);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Liczba w¹tków:";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(354, 47);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(27, 20);
			this->label2->TabIndex = 4;
			this->label2->Text = L"12";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// cPlusOptionButton
			// 
			this->cPlusOptionButton->AutoSize = true;
			this->cPlusOptionButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->cPlusOptionButton->Location = System::Drawing::Point(509, 17);
			this->cPlusOptionButton->Name = L"cPlusOptionButton";
			this->cPlusOptionButton->Size = System::Drawing::Size(56, 24);
			this->cPlusOptionButton->TabIndex = 8;
			this->cPlusOptionButton->TabStop = true;
			this->cPlusOptionButton->Text = L"C++";
			this->cPlusOptionButton->UseVisualStyleBackColor = true;
			this->cPlusOptionButton->CheckedChanged += gcnew System::EventHandler(this, &Form1::cPlusOptionButton_CheckedChanged);
			// 
			// asmOptionButton
			// 
			this->asmOptionButton->AutoSize = true;
			this->asmOptionButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->asmOptionButton->Location = System::Drawing::Point(509, 36);
			this->asmOptionButton->Name = L"asmOptionButton";
			this->asmOptionButton->Size = System::Drawing::Size(94, 24);
			this->asmOptionButton->TabIndex = 9;
			this->asmOptionButton->TabStop = true;
			this->asmOptionButton->Text = L"Asembler";
			this->asmOptionButton->UseVisualStyleBackColor = true;
			this->asmOptionButton->CheckedChanged += gcnew System::EventHandler(this, &Form1::asmOptionButton2_CheckedChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label3->Location = System::Drawing::Point(354, 101);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(18, 20);
			this->label3->TabIndex = 12;
			this->label3->Text = L"1";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label4->Location = System::Drawing::Point(232, 101);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(100, 20);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Liczba pi³ek: ";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// ballBar
			// 
			this->ballBar->Location = System::Drawing::Point(140, 69);
			this->ballBar->Maximum = 64;
			this->ballBar->Minimum = 1;
			this->ballBar->Name = L"ballBar";
			this->ballBar->Size = System::Drawing::Size(362, 45);
			this->ballBar->TabIndex = 10;
			this->ballBar->Value = 1;
			this->ballBar->Scroll += gcnew System::EventHandler(this, &Form1::ballBar_Scroll);
			// 
			// timeLabel
			// 
			this->timeLabel->AutoSize = true;
			this->timeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->timeLabel->Location = System::Drawing::Point(508, 75);
			this->timeLabel->Name = L"timeLabel";
			this->timeLabel->Size = System::Drawing::Size(127, 20);
			this->timeLabel->TabIndex = 13;
			this->timeLabel->Text = L"Czas wykonania:";
			this->timeLabel->Click += gcnew System::EventHandler(this, &Form1::label5_Click);
			// 
			// speedLabel
			// 
			this->speedLabel->AutoSize = true;
			this->speedLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->speedLabel->Location = System::Drawing::Point(641, 75);
			this->speedLabel->Name = L"speedLabel";
			this->speedLabel->Size = System::Drawing::Size(18, 20);
			this->speedLabel->TabIndex = 14;
			this->speedLabel->Text = L"0";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(733, 126);
			this->Controls->Add(this->speedLabel);
			this->Controls->Add(this->timeLabel);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->ballBar);
			this->Controls->Add(this->asmOptionButton);
			this->Controls->Add(this->cPlusOptionButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->threadBar);
			this->Controls->Add(this->startButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ballBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void startButton_Click(System::Object^ sender, System::EventArgs^ e) {
			Simulation simulation(threadBar->Value, ballBar->Value);
			if (cPlusOptionButton->Checked) {
				simulation.setDllMethod(1);
				simulation.init();
			}
			else if (asmOptionButton->Checked) {
				simulation.setDllMethod(2);
				simulation.init();
			}
		}
		System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void threadBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			label2->Text = threadBar->Value.ToString();
		}
		System::Void ballBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			label3->Text = ballBar->Value.ToString();
		}
		System::Void cPlusOptionButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void asmOptionButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
		}
	};
}
