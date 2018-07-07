#include "Logic.h"
#pragma once

namespace Project1
{
	/// <summary>
	/// Summary for GameForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public: GameLogic ^game;
	public:
		MyForm(void)
		{
			InitializeComponent();
			game = gcnew GameLogic;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			delete game;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::PictureBox^  playing_field;
	private: System::Windows::Forms::Label^  label1;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->playing_field = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->playing_field))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12));
			this->button1->Location = System::Drawing::Point(459, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(94, 44);
			this->button1->TabIndex = 3;
			this->button1->Text = L"ÑÒÀÐÒ";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Honeydew;
			this->button2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9));
			this->button2->Location = System::Drawing::Point(459, 157);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 50);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Âêëþ÷èòü áîòà";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// playing_field
			// 
			this->playing_field->Cursor = System::Windows::Forms::Cursors::Hand;
			this->playing_field->Location = System::Drawing::Point(12, 12);
			this->playing_field->Name = L"playing_field";
			this->playing_field->Size = System::Drawing::Size(401, 370);
			this->playing_field->TabIndex = 6;
			this->playing_field->TabStop = false;
			this->playing_field->Click += gcnew System::EventHandler(this, &MyForm::playing_field_Click);
			this->playing_field->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::playing_field_Paint);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15));
			this->label1->Location = System::Drawing::Point(481, 102);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 29);
			this->label1->TabIndex = 7;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(769, 494);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->playing_field);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"GameForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->playing_field))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		playing_field->Invalidate();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		game->botOvkl(button2, label1, playing_field->CreateGraphics());
	}
	private: System::Void playing_field_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		game->StartGame(e, label1);
	}
	private: System::Void playing_field_Click(System::Object^  sender, System::EventArgs^  e)
	{
		game->Hod(playing_field->CreateGraphics(), label1, playing_field->PointToClient(System::Windows::Forms::Cursor::Position).Y, playing_field->PointToClient(System::Windows::Forms::Cursor::Position).X);
	}
};
}