/*;-------------------------------------------------------------------------
; SYMULATOR ZDERZEŃ
; KRZYSZTOF DEC GR.1
; INFORMATYKA SSI SEMESTR 5 2020/2021
; v.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.1.1 - stworzony interfejs graficzny do obsługi programu (14.10.2020)
; v.0.2 - dodanie bibliotek CppDLL oraz AsmDLL do projektu (27.10.2020)
; v.0.3 - implementacja interfejsu graficznego symulacji oraz dodanie podstaw ruchu kul (12.11.2020)
; v.0.3.1 - dodanie obsługi wykrywania zderzeń oraz tworzenia losowych symulacji (14.11.2020)
; v.0.4 - implementacja mechanizmu odbić kul od krawędzi okna symulacji oraz rozdzielania kul nachodzących na siebie (2.12.2020)
; v.0.5 - implementacja algorytmu zderzeń między kulami w C++ (9.01.2021)
; v.0.5.1 - dodanie sił tarcia do symulacji ruchu kul (10.01.2021)
; v.0.5.2 - dodanie obsługi wątków w symulacji zderzeń oraz ruchu kul (16.01.2021)
; v.0.6 - implementacja algorytmów zderzeń oraz ruchu kul w asemblerze (5.02.2021)
; v.0.6.1 - dodanie pomiarów czasu wykonania algorytmów (7.02.2021)
; v.0.7 - poprawiona implementacja algorytmów w asemblerze, usprawnienie działania w trybie Release w VS2019 (11.02.2021)
; v.1.0 - finalna wersja programu zgodna z założeniami projektu (12.02.2021)
;-------------------------------------------------------------------------*/

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



	private: System::Windows::Forms::Label^ timeLabel;
	private: System::Windows::Forms::Label^ speedLabel;
	private: System::Windows::Forms::Label^ speedLabel2;
	private: System::Windows::Forms::Label^ timeLabel2;

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
			this->timeLabel = (gcnew System::Windows::Forms::Label());
			this->speedLabel = (gcnew System::Windows::Forms::Label());
			this->speedLabel2 = (gcnew System::Windows::Forms::Label());
			this->timeLabel2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadBar))->BeginInit();
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
			this->label1->Text = L"Liczba wątków:";
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
			// timeLabel
			// 
			this->timeLabel->AutoSize = true;
			this->timeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->timeLabel->Location = System::Drawing::Point(155, 88);
			this->timeLabel->Name = L"timeLabel";
			this->timeLabel->Size = System::Drawing::Size(218, 20);
			this->timeLabel->TabIndex = 13;
			this->timeLabel->Text = L"Średni czas przemieszczenia:";
			this->timeLabel->Click += gcnew System::EventHandler(this, &Form1::label5_Click);
			// 
			// speedLabel
			// 
			this->speedLabel->AutoSize = true;
			this->speedLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->speedLabel->Location = System::Drawing::Point(379, 88);
			this->speedLabel->Name = L"speedLabel";
			this->speedLabel->Size = System::Drawing::Size(18, 20);
			this->speedLabel->TabIndex = 14;
			this->speedLabel->Text = L"0";
			this->speedLabel->Click += gcnew System::EventHandler(this, &Form1::speedLabel_Click);
			// 
			// speedLabel2
			// 
			this->speedLabel2->AutoSize = true;
			this->speedLabel2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->speedLabel2->Location = System::Drawing::Point(608, 88);
			this->speedLabel2->Name = L"speedLabel2";
			this->speedLabel2->Size = System::Drawing::Size(18, 20);
			this->speedLabel2->TabIndex = 16;
			this->speedLabel2->Text = L"0";
			// 
			// timeLabel2
			// 
			this->timeLabel2->AutoSize = true;
			this->timeLabel2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->timeLabel2->Location = System::Drawing::Point(446, 88);
			this->timeLabel2->Name = L"timeLabel2";
			this->timeLabel2->Size = System::Drawing::Size(157, 20);
			this->timeLabel2->TabIndex = 15;
			this->timeLabel2->Text = L"Średni czas zderzeń:";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(733, 126);
			this->Controls->Add(this->speedLabel2);
			this->Controls->Add(this->timeLabel2);
			this->Controls->Add(this->speedLabel);
			this->Controls->Add(this->timeLabel);
			this->Controls->Add(this->asmOptionButton);
			this->Controls->Add(this->cPlusOptionButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->threadBar);
			this->Controls->Add(this->startButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"BallsASM";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void startButton_Click(System::Object^ sender, System::EventArgs^ e) {
			if (cPlusOptionButton->Checked) {
				Simulation simulation(threadBar->Value, threadBar->Value, 1);
				long long* averageTimes = simulation.init();
				speedLabel->Text = averageTimes[0].ToString() + "us";
				speedLabel2->Text = averageTimes[1].ToString() + "us";
			}
			else if (asmOptionButton->Checked) {
				Simulation simulation(threadBar->Value, threadBar->Value, 2);
				long long* averageTimes = simulation.init();
				speedLabel->Text = averageTimes[0].ToString() + "us";
				speedLabel2->Text = averageTimes[1].ToString() + "us";
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
		System::Void cPlusOptionButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void asmOptionButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
		}
	private: System::Void speedLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
